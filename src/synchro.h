#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <stdbool.h>
#include "ensitheora.h"

extern bool fini;


/* Les extern des variables pour la synchro ici */
extern pthread_mutex_t m;
extern pthread_cond_t clect;
extern pthread_cond_t cecr;
extern pthread_cond_t cdessin;
extern int nbTextureBase;
extern int nbTextureAttente;

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
