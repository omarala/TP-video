#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <pthread.h>

#include "stream_common.h"
#include "oggstream.h"
#include "synchro.h"
//extern pthread_t theora2sdlthread;

void * ALL_IS_OK = (void * ) 123456789L ;

int main(int argc, char *argv[]) {
    pthread_t audio_pid;
    pthread_t video_pid;

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cconsom, NULL);
    pthread_cond_init(&cdepot, NULL);
    pthread_cond_init(&cdessin, NULL);

    pthread_mutex_init(&mutex_video, NULL);

    pthread_mutex_init(&mutex_taille_fenetre, NULL);
    pthread_cond_init(&ctaille, NULL);

    //pthread_mutex_init(&mutex_texture, NULL);
    pthread_cond_init(&ctexture, NULL);

    if (argc != 2) {
	fprintf(stderr, "Usage: %s FILE", argv[0]);
	exit(EXIT_FAILURE);
    }
    assert(argc == 2);

    int res;
    void * status;
    void *file = (void *)argv[1];

    // Initialisation de la SDL
    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    atexit(SDL_Quit);
    assert(res == 0);

    // start the two stream readers
    pthread_create(&audio_pid, NULL, vorbisStreamReader, file);
    pthread_create(&video_pid, NULL, theoraStreamReader, file);


    // wait audio thread
    pthread_join(audio_pid, &status);
    if(status == ALL_IS_OK){
      printf("Audio thread %lx completed ok. \n", audio_pid);
    }


    // 1 seconde de garde pour le son,
    sleep(1);

    // tuer les deux threads videos si ils sont bloqués
    pthread_cancel(video_pid);
    pthread_cancel(theora2sdlthread); //défini dans stream_common.h

    // attendre les 2 threads videos
    pthread_join(video_pid, &status);
    if(status == ALL_IS_OK)
      printf("Video thread %lx completed ok \n", (long unsigned int)status);
    pthread_join(theora2sdlthread, &status);
    if(status == ALL_IS_OK)
      printf("SDL thread %lx completed ok \n", (long unsigned int)status);


    //pthread_join(audio_pid, &audio);

    exit(EXIT_SUCCESS);
}
