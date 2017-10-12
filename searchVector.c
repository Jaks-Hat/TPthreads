#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 1024
int find = 0;

typedef struct{
  int element;
  int * vector;
  int sizeVector,start;
}infos_search;

int initialise_vector(int * vector){

  char buffer[50];
  char * token;
  int sizeVector =0;

  if(fgets(buffer, sizeof(buffer), stdin)==NULL){printf("Erreur de lecture");exit(0);};
  /* get the first token */
  token = strtok(buffer," ");
  /* walk through other tokens */
  while( token != NULL ) {
      vector[sizeVector] = atoi(token);
      sizeVector++;
      token = strtok(NULL, " ");
  }
  return sizeVector;
}

void searched_element(int element,int * vector,int sizeVector){
  int i = 0;
  while(i < sizeVector && vector[i] != element){
    i++;
  }
  printf("Element find at postion %i in vector\n",i);
}

/* function who search a eleme t, arg is a struct of type infos_search */
void * searched_element_threads(void * arg){

  /* Use of a mutex beacause we write in variable find*/
  pthread_mutex_t mutex_stock;
  infos_search * infos = (infos_search *) arg;
  int i = infos->start;
  while(i < infos->sizeVector && find!=1 &&(infos->vector)[i] != infos->element){
    i++;
  }
  if((infos->vector)[i] == infos->element){
    pthread_mutex_lock (&mutex_stock);
    find = 1;
    printf("Element find at postion %i in vector\n",i);
    pthread_mutex_unlock (&mutex_stock);

  }
  free(infos);
  return NULL;
}

int main (int argc, char **argv){

  int * vector = malloc(sizeof(int)*MAX_SIZE);
  int sizeVector,nb_threads,i;
  pthread_t *tids ;

  if (argc != 3){
    fprintf(stderr, "usage : %s nbThreads searched_Element \n", argv[0]) ;
    exit (-1) ;
  }

  /*SEQUENTIAL METHOD*/
   /*
  sizeVector = initialise_vector(vector);
  searched_element(atoi(argv[2]),vector,sizeVector);
  */

  /* MULTITHREAD METHOD*/
  nb_threads = atoi(argv[1]);
  tids = malloc (nb_threads*sizeof(pthread_t));

  /* Initialisation du vecteur */
  sizeVector = initialise_vector(vector);
  /* Create the threads for  */
  for (i = 0 ; i < nb_threads; i++){
      /* Create and initialise struct for the threads */
      infos_search * infos = malloc(sizeof(infos_search));
      infos->vector = vector;
      infos->element = atoi(argv[2]);
    if(i == 0){
      infos->start = 0;
      infos->sizeVector = floor(sizeVector/nb_threads);
    }else{
      infos->start = floor(sizeVector/nb_threads)*i+1;
      infos->sizeVector = infos->start + floor(sizeVector/nb_threads);
    }
    pthread_create (&tids[i],NULL,searched_element_threads,infos) ;
  }

  /* Wait until every thread ened */
  for (i = 0; i < nb_threads; i++){
    pthread_join (tids[i], NULL) ;
  }
  if(find ==0){
      printf("L'élément n'a pas été trouvé\n");
  }
  free (tids) ;
  free(vector);
  return EXIT_SUCCESS;
}
