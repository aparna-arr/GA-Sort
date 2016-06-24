#include"stdio.h"
#include"stdlib.h"
#include"string.h"

#define MAX_STRING 80

void usage(void);
int parse_input(int argc, char * argv[], int * num_elem, int ** elem, int * pop_size);

int main(int argc, char * argv[])
{
	int num_elements;
	int * elements;
	int pop_size;

	int success = parse_input(argc, argv, &num_elements, &elements, &pop_size);	

	if (success == -1)
	{
		usage();	
		return 1;
	}

	/* DEBUG */

	printf("num_elements is [%d]\n", num_elements);

	return 0;
}

void usage(void) 
{
	char * usage_str = "usage: gasort <population size> <file with list>\0";
	printf("%s\n", usage_str);
}

int parse_input(int argc, char * argv[], int * num_elem, int ** elem, int * pop_size)
{
	printf("start of parse_input()\n");
	if (argc != 3)
		return -1;


	char filename[MAX_STRING];

	printf("before first sscanf\n");

	if (sscanf(argv[1], "%d", pop_size) != 1 || sscanf(argv[2], "%s", filename) != 1)
		return -1;

	printf("after first sscanf\n");
	FILE * fp = fopen(filename, "r");

	if (fp == NULL)
	{
		printf("Cannot open file :[%s]\n",filename);
		return -1;
	}

	char * line;
	size_t len = 0;

	printf("before getline\n");
	int read = getline(&line, &len, fp);
	printf("after getline\n");
	
	if (read == -1)
	{
		printf("Could not read line from file\n");
		fclose(fp);
		return -1;
	}	
	
	printf("before first strtok\n")	;
	char * copy = (char *) malloc(sizeof(line));

     	strcpy(copy,line);

	char * token = strtok(copy," ");
	printf("after first strtok token is [%s]\n", token)	;
	*num_elem = 0;

	while(token != NULL)
	{
		token = strtok(NULL," ");
		printf("token is [%s]\n",token);
		(*num_elem)++;
	}

	if (*num_elem == 0)
	{
		printf("Your file has 0 elements!\n");
		return -1;
	}

	printf("num_elem is [%d]\n",*num_elem);

	printf("before first malloc\n");
	*elem = (int*) malloc(sizeof(int) * (*num_elem));
	printf("after first malloc\n");
//	printf("sizeof int [%d], sizeof *elem [%d]\n",(int)sizeof(int), (int)sizeof(*elem));

	printf("before sscanf\n");
	
	if(sscanf(strtok(line," "), "%d", &(*elem)[0]) != 1)
	{
		free(*elem);
		fclose(fp);
		printf("You have non-ints in your file!\n");
		return -1;
	}
	

//	printf("line is [%s]\n", line);
//	printf("first tok is [%s]\n", strtok(line," "));
	printf("after sscanf\n");

	printf("before loop\n");
	int i = 0;

	printf("num_elem is [%d]\n", *num_elem);
	int num = *num_elem;
	printf("num is [%d]\n",num);
	for (i = 1; i < num; i++)
	{
//		printf("on i [%d]\n",i);

//		char * tok = strtok(NULL, " ");
//		printf("tok is [%s]\n", tok);

		if(sscanf(strtok(NULL," "),"%d",&(*elem)[i]) != 1)
		{
			fclose(fp);
			printf("You have non-ints in your file!\n");
			return -1;
		}

	}

	fclose(fp);

	return 1;
}
