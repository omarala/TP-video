#include "synchro.h"
#include "ensitheora.h"
#include <pthread.h>

bool fini;

/* les variables pour la synchro, ici */
pthread_mutex_t m;
pthread_cond_t clect;
pthread_cond_t cecr;
pthread_cond_t cdessin;
pthread_mutex_init(& m, NULL);
pthread_cond_init(& clect, NULL);
pthread_cond_init(& cecr, NULL);
pthread_cond_init(& cdessin, NULL);

int nbTextureAttente = 0;
int nbTextureBase = 0;

/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    windowsx = buffer[0].width;
    windowsy = buffer[0].height;
}

void attendreTailleFenetre() {
  /* whuuuuuuuuuuuuut */
}

void signalerFenetreEtTexturePrete() {
  /* biiiiiiiiiiiiite */
}

void attendreFenetreTexture() {
  /* charger toute les textures d'une fenetre */
}

void debutConsommerTexture() {
    pthread_mutex_unlock(& m);
    nbTextureAttente ++;
    while(fini && nbTextureAttente<NBTEX)
      pthread_cond_wait(& clect, & m);
    nbTextureBase ++;
    pthread_cond_signal(&cdessin);
    nbTextureAttente --;
    pthread_mutex_unlock(&m);
}

void finConsommerTexture() {
    pthread_mutex_lock(& m);
    nbTextureBase --;
    if(nbTextureBase == 0)
      pthread_cond_signal(&cecr);
    pthread_mutex_unlock(& m);
}

void debutDeposerTexture() {
    pthread_mutex_lock(&m);
    while((fini || nbTextureAttente>0))
      pthread_cond_wait(&clect, &m);
    fini = true;
    pthread_mutex_unlock(&m);
}

void finDeposerTexture() {
    pthread_mutex_lock(& m);
    if(nbTextureAttente > 0)
      pthread_cond_signal(&clect);
    else
      pthread_cond_signal(& cecr);
    pthread_mutex_lock(&m);
}
