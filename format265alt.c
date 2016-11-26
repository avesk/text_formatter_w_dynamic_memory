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
	/**printf("%s does nothing right now.\n", argv[0]);**/
	FILE *file = fopen(argv[1], "r");
	char** uf_lines;

	if(file == NULL){
		fprintf(stderr, "unable  to open %s\n", argv[1]);
		exit(1);	
	}

	uf_lines = format_file(file);
	char** line;
	for(line = uf_lines; *line != NULL; line++) {
		printf ("%s", *line);
	}

#endif
	exit(0);
}
