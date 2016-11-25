/*
 * UVic SENG 265, Fall 2016,  A#4
 *
 * This will contain the bulk of the work for the fourth assignment. It
 * provide similar functionality to the class written in Python for
 * assignment #3.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"



char **format_file(FILE *infile) {
	char * line = NULL;
 	size_t len = 0;
 	size_t read;
 	int idx = 0;
 	char** lines;

 	/** creates an array of char**'s for each char* (otherwise known as a string or a line) **/
 	lines = (char**) malloc(sizeof(char*) * 50);
	if(!lines){
		printf("Error allocating memory for malloc on line 21"); 
		abort();
	}


/***************************** CODE THAT WORKS ******************/
	while((read = getline(&line, &len, infile)) != -1){
 		/*printf("Retrieved line of length %zu :\n", read);
 		printf("%s", line); **/
/***************************** END CODE THAT WORKS ******************/	

		lines[idx] = (char*) malloc(sizeof(char) * read);
		idx++;
 		if(!lines){ 
 			printf("Error allocating memory for malloc on line 32");
			abort();
		}

		lines[idx] = line;
		
		/*if (line) {
 			free(line);
 		}*/
 	}

 	/*printf("%s\n",lines[0]);*/
 	
 	char ** l;

 	for (l = lines; *l != NULL; l++) {
		printf ("%s\n", *l);
	}

	return lines;
}


char **format_lines(char **lines, int num_lines) {
	char **result = lines;

#ifdef DEBUG
	result = (char **)malloc(sizeof(char *) * 2);
	if (result == NULL) {
		return NULL;
	}

	result[0] = (char *)malloc(sizeof(char) * 80);
	if (result[0] == NULL) {
		return NULL;
	}
	strncpy(result[0], "(machine-like voice) EXTERMINATE THEM!", 79);

	result[1] = (char *)malloc(sizeof(char) * 2);
	if (result[1] == NULL) {
		return NULL;
	}
	result[1][0] = '\0';
#endif

	return result;
}
