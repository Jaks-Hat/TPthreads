#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>


typedef struct args_struct
{
	int* v;
	int vsize;
	int value;
} args_struct;

int *initVector(char* sourcefile, int* size)
{
	FILE* fd;
	int i = 0;

	if ((fd = fopen(sourcefile, "r")))
	{
		if (fscanf(fd, "%d", size) == EOF)
		{
			printf("Error : source file empty...\n");
			exit(1);
		}
		int* vector = malloc((*size)*sizeof(int));
		while((i < (*size)) && (fscanf(fd, "%d", &vector[i]) != EOF))
		{
			i++;
		}
		fclose(fd);
		if (vector[i] == EOF)
		{
			printf("Error : wrong values number !\n");
			exit(1);
		}

		//display
		int j;
		for (j = 0; j < (*size)	; j++)
		{
			printf("%d ", vector[j]);
		}

		return vector;
		
	}
	printf("Error at opening file !\n");
	exit(1);

}

void search(int* vect, int n, int x)
{
	int i=0;
	while ((i < n) && vect[i] != x)
	{
		i++;
	}

	if (pthread_self() == t1)
		while (pthread_kill(t2, SIGKILL) != 0);
	else
		while (pthread_kill(t1, SIGKILL) != 0);

	vect[i]==x?printf("Value exists !"):printf("Value does not exist!");
}


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Error : wrong argument number !\n");
		exit(1);
	}

	int* vector;
	int vector_size;
	int val; 
	pthread_t t1, t2;

	vector = initVector(argv[1], &vector_size);

	printf("Search for number : ");
	scanf("%d", &val);


	//singlethreaded version
	//(search(vector, vector_size, val) == 1)?printf("Valeur présente"):printf("Valeur absente");


	//multithreaded version

	int* vector1 = malloc((vector_size/2)*sizeof(int));
	int* vector2 = malloc((vector_size-(vector_size/2))*sizeof(int));
	int i;
	for (i = 0; i < vector_size; i++)
	{
		if (i <= vector_size/2)
			vector1[i] = vector[i];
		else
			vector2[i-vector_size/2] = vector[i];
	}

	// first half of vector
	args_struct args_t1;
	args->v = vector1;
	args->vsize = vector_size/2;
	args->value = val;

	// second half of vector
	args_struct args_t2;
	args->v = vector2;
	args->vsize = vector_size-(vector_size/2);
	args->value = val;

	pthread_create(&t1, NULL, search, args_t1);
	pthread_create(&t2, NULL, search, args_t2);


	return 0;

}

