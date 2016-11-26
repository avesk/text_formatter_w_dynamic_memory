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
 	char* temp = NULL; /* for getting the max line length and the number of lines */
 	size_t temp_len = 0;
 	size_t temp_read;
 	int idx;
 	char** lines;
 	char** temp_lines;
 	int size = 1;
 	size_t max_line = 0;
 	int i;

 	/*while((temp_read = getline(&temp, &temp_len, infile)) != -1){
 		num_lines ++;
 		if(temp_read > max_line) max_line = temp_read;
 	}

 	rewind(infile);*/

 	/** creates an array of char**'s for each char* (otherwise known as a string or a line) **/
 	/** an array of addresses holding addresses which store chars **/
 	lines = (char**) malloc(sizeof(char*) * size);
	if(!lines){
		printf("Error allocating memory for malloc on %d", 39); 
		abort();
	}

	while((read = getline(&line, &len, infile)) != -1){
 		/*printf("Retrieved line of length %zu :\n", read);*/
		size*=2;
 		lines = (char**) realloc(lines, sizeof(char*) * size);
 		if(!lines){
			printf("Error allocating memory for malloc on %d", 39); 
			abort();
		}

		lines[idx] = (char*) malloc(sizeof(char) * len);
		
 		if(!lines){ 
 			printf("Error allocating memory for malloc on line 32");
			abort();
		}

		strncpy(lines[idx], line, max_line);
		
 		idx ++;				
 	}

 	/*printf("%s",lines[2]);*/
 	/*
 	char ** l;
 	for(l = lines; *l != NULL; l++) {
		printf("%s", *l);
	} */
	
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
