#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int *initVector(char* sourcefile)
{
	FILE* fd;
	int nbvalues;
	int i = 0;

	if ((fd = fopen(sourcefile, "r")))
	{
		if (fscanf(fd, "%d", &nbvalues) == EOF)
		{
			printf("Error : source file empty...\n");
			exit(1);
		}
		int* vector = malloc(nbvalues*sizeof(int));
		while((i < nbvalues) && (fscanf(fd, "%d", &vector[i]) != EOF))
		{
			i++;
		}
		fclose(fd);
		if (vector[i] == EOF)
		{
			printf("Error : wrong values number !\n");
			exit(1);
		}

		int j;
		for (j = 0; j < nbvalues; j++)
		{
			printf("%d ", vector[j]);
		}

		return vector;
		
	}
	printf("Error at opening file !\n");
	exit(1);

}


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Error : wrong argument number !\n");
		exit(1);
	}

	int* vector = initVector(argv[1]);
	printf("\nval : %d", vector[0]);

	return 0;

}

