#include "synchro.h"
#include "ensitheora.h"
#include <pthread.h>

bool fini;
bool texturestate = false;
/* les variables pour la synchro, ici */
pthread_mutex_t m, mutex_taille_fenetre;
pthread_cond_t cconsom, cdepot, cdessin, ctaille, ctexture;
// ctexture;
int nbTextureAttente = 0;


bool taille = false;


/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    pthread_mutex_lock(&mutex_taille_fenetre);
    windowsx = buffer[0].width;
    windowsy = buffer[0].height;
    taille = true;
    pthread_cond_signal(&ctaille);
    pthread_mutex_unlock(&mutex_taille_fenetre);
}

void attendreTailleFenetre() {
  pthread_mutex_lock(&mutex_taille_fenetre);
  while(!taille){
    pthread_cond_wait(&ctaille, &mutex_taille_fenetre);
  }
  taille = false;
  pthread_mutex_unlock(&mutex_taille_fenetre);
}

void signalerFenetreEtTexturePrete() {
  pthread_mutex_lock(&mutex_taille_fenetre);
  /*i++;
  printf("signaler texture : %i\n", i);
  printf("la fenetre est prete \n");*/
  texturestate = true;
  //fini = true;
  pthread_cond_signal(&ctexture);
  pthread_mutex_unlock(&mutex_taille_fenetre);
}

void attendreFenetreTexture() {
  pthread_mutex_lock(&mutex_taille_fenetre);
  i++;
  //printf("attendre texture : %i\n", i);
  while(!texturestate)
    pthread_cond_wait(&ctexture, &mutex_taille_fenetre);
  texturestate = false;
  //pthread_cond_signal(&ctexture);
  pthread_mutex_unlock(&mutex_taille_fenetre);

}

void debutConsommerTexture() {
    pthread_mutex_lock(&m);
    if(nbTextureAttente <= 0)
      pthread_cond_wait(& cconsom, &m);
    nbTextureAttente --;
    pthread_mutex_unlock(&m);
}

void finConsommerTexture() {
    pthread_mutex_lock(&m);

    pthread_cond_signal(&cdepot);
    pthread_mutex_unlock(&m);
}

void debutDeposerTexture() {
    pthread_mutex_lock(&m);
    nbTextureAttente ++;
    if(nbTextureAttente>=NBTEX)
      pthread_cond_wait(&cdepot, &m);
    //fini = false;
    pthread_mutex_unlock(&m);
}

void finDeposerTexture() {
    pthread_mutex_lock(&m);

    pthread_cond_signal(&cconsom);
    pthread_mutex_unlock(&m);
}
