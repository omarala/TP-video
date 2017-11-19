#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <pthread.h>

#include "stream_common.h"
#include "oggstream.h"

void * ALL_IS_OK = (void * ) 123456789L ;


int main(int argc, char *argv[]) {
    int res;
    void * status;
    /*void * status_video;
      void * status_audio;*/

    pthread_t audio_pid;
    pthread_t video_pid;
    
    if (argc != 2) {
	fprintf(stderr, "Usage: %s FILE", argv[0]);
	exit(EXIT_FAILURE);
    }
    assert(argc == 2);


    // Initialisation de la SDL
    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    atexit(SDL_Quit);
    assert(res == 0);
    
    // start the two stream readers
    pthread_create(&audio_pid, NULL, (void *) &vorbisStreamReader, argv[1]);
    
    pthread_create(&video_pid, NULL, (void *) &theoraStreamReader, argv[1]);
    
    
    // wait audio thread

    // 1 seconde de garde pour le son,
    sleep(1);

    // tuer les deux threads videos si ils sont bloqués

    // attendre les 2 threads videos
    pthread_join(video_pid, &status);
    /*pthread_join(
    if(status == ALL_IS_OK)
    printf("Thread %lx completed ok \n", status);*/
    //pthread_join(audio_pid, &audio);
    
    exit(EXIT_SUCCESS);    
}
