#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <stdbool.h>
#include "ensitheora.h"

extern bool fini;


/* Les extern des variables pour la synchro ici */
extern pthread_mutex_t m;
extern pthread_mutex_t mutex_taille_fenetre;
extern pthread_cond_t cconsom;
extern pthread_cond_t cdepot;
extern pthread_cond_t cdessin;
extern pthread_cond_t ctaille;
extern pthread_cond_t ctexture;
extern int nbTextureAttente;
extern bool texturestate;
/* Fonctions de synchro à implanter */

void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre();

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture();
void finDeposerTexture();

#endif
