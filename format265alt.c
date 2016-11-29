/*
 * UVic SENG 265, Fall 2016, A#4
 *
 * This will contain a solution to format265alt.c. In order to complete the
 * task of formatting a file, it must open the file and pass the result
 * to a routine in formatter.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include "formatter.h"

int main(int argc, char *argv[]) {
#ifdef DEBUG
	/*char** uf_lines;*/ /** An array of unformatted lines **/
	char** f_lines; /** An array of formatted lines **/
	FILE *file = fopen(argv[1], "r");
	int num_lines = 0;

	if(file == NULL){
		fprintf(stderr, "unable  to open %s\n", argv[1]);
		exit(1);	
	}

	f_lines = format_file(file);
	/*uf_lines = (char**) realloc(uf_lines, sizeof(char*) * 1);*/

	/*num_lines = strlen(*uf_lines);*/
	/*printf("NUM_LINES: %d\n",num_lines);*/
	/*printf("THIS SHOULD BE A NIL: %p\n",f_lines[7]);*/
	char** line;
	int count = 0;
	for(line = f_lines; *line != NULL; line++) {
		printf("%s\n", *line);
		count++;
		
	}
	free(f_lines);

	fclose(file);

#endif
	exit(0);
}
