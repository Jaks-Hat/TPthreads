#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


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

int search(int* vect, int n, int x)
{
	int i=0;
	while ((i < n) && vect[i] != x)
	{
		i++;
	}

	return vect[i]==x?1:0;
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

	vector = initVector(argv[1], &vector_size);

	printf("Search for number : ");
	scanf("%d", &val);

	//printf("taille : %lu", sizeof(vector));
	(search(vector, vector_size, val) == 1)?printf("Valeur présente"):printf("Valeur absente");

	return 0;

}

