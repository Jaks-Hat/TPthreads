#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define NB_SONG 3

typedef struct{
  int nb_song;
  char * chant;
}infos_supporter;

void *supporter (void *arg){
  infos_supporter * supporter = (infos_supporter *) arg;
  int       i ;
  int       pid ;
  pthread_t tid ;
  pid = getpid () ;
  tid = pthread_self () ;
  srand ((int) tid) ;

  for (i = 0; i < supporter->nb_song; i++){
    printf ("Processus %d Thread %x : %s \n", pid, (unsigned int) tid, supporter->chant) ;
    usleep (rand() / RAND_MAX * 1000000.) ;
  }
  return (void *) tid ;
}

int main (int argc, char **argv){

  int team1 ;
  int team2 ;
  int i ;
  int nb_threads = 0 ;
  pthread_t *tids ;
  infos_supporter * french;
  infos_supporter * english;

  if (argc != 5){
    fprintf(stderr, "usage : %s team1 team2 nb_chant1 nb_chant2\n", argv[0]) ;
    exit (-1) ;
  }

  team1 = atoi (argv[1]) ;
  team2  = atoi (argv[2]) ;
  nb_threads = team1 + team2;
  tids = malloc (nb_threads*sizeof(pthread_t)) ;

  /* Initialisation infos_supporter struct for french*/
  french = malloc(sizeof(infos_supporter));
  french->nb_song = atoi(argv[3]);
  french->chant = "Allons enfants de la patrie";

  /* Initialisation infos_supporter struct for english*/
  english = malloc(sizeof(infos_supporter));
  english->nb_song = atoi(argv[4]);
  english->chant = "Swing low, sweet chariot";

  /* Create the threads for team1 */
  for (i = 0 ; i < team1; i++){
    pthread_create (&tids[i], NULL, supporter,french) ;
  }
  /* Create the other threads (ie. team2) */
  for ( ; i < nb_threads; i++){
    pthread_create (&tids[i], NULL, supporter,english) ;
  }

  /* Wait until every thread ened */
  for (i = 0; i < nb_threads; i++){
    pthread_join (tids[i], NULL) ;
  }

  free (tids) ;
  return EXIT_SUCCESS;
}
