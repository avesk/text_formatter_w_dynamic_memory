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

#define BUFLEN 500
struct Line_data{
	char** formatted_str;
	char current_line[1000];
	int line_size;
} ld;

int lw = 0, lm = 0, ls = 0, ft = 0;
int lf = 0; /** lines formatted **/
int char_count = 0;
int total_lines;
int max_line;

void add_linelen_mem(){ /** allocates memory for the length of a new line **/
	printf("HERE IS THE VALUE OF LW: %d\n", lw);
	ld.formatted_str[lf] = (char*) malloc(sizeof(char) *(51));
 	if(!ld.formatted_str[lf]){ 
 		printf("Error allocating memory for malloc in add_linelen_mem ");
		abort();
	}
}

void add_line_mem(){ /** allocates memory for a new line **/
	printf("%d\n", lf);
	total_lines*=2;
printf("DEBUG A %x\n", ld.formatted_str);
	char** new_p = (char**) realloc(ld.formatted_str, sizeof(char *) * total_lines);
 	if(!new_p){ 
 		printf("Error allocating memory for malloc in add_line_mem ");
		abort();
	}
	ld.formatted_str = new_p;
printf("DEBUG B %x\n", ld.formatted_str);
}

int in_para_formatter(char* l, int first_word){
	char *token;
	token = strtok(l, " \n");/** Deliminate words at spaces and newlines **/

	while(token){
		char_count += strlen(token);/** Keeps track of how many characters are on each line **/

		if(char_count +1 > lw){
			/*strncat(ld.current_line, "\n", 1);*/
			strncpy(ld.formatted_str[lf], ld.current_line, strlen(ld.current_line)+1);/** Append the current line to the list of lines **/
			/*printf("%s\n",ld.formatted_str[lf]);*/
			strncpy(ld.current_line, "", 2); /** Clear the current line **/
			strncat(ld.current_line, token, strlen(token)+1);
			char_count = strlen(token); /** add the word to the current line **/
			lf +=1; /** Increment lines formatted **/
			add_linelen_mem();
			first_word = 0;
		}

		else if(char_count +1 == lw){
			strncat(ld.current_line, " ",2 ); /** add a space to the current line **/
			strncat(ld.current_line, token, strlen(token)+1); /** add the word to the current line **/
			printf("THIS IS LF: %d\n", lf);
			strncpy(ld.formatted_str[lf], ld.current_line, strlen(ld.current_line)+1);/** Append the current line to the list of lines **/
			strncpy(ld.current_line, "", 2); /** Clear the current line **/
			char_count = 0;
			lf +=1; /** Increment lines formatted **/
			add_linelen_mem();
			first_word = 1;
		}

		else{
			if(first_word){ /* If we are processing the first word of the line, just concatenate the word with no spaces, or else we will get extra spaces */
				strncat(ld.current_line, token, strlen(token)+1); /** add the word to the current line **/
				first_word = 0;
				/*printf("IM IN HERE\n");*/
			}
			else{
				strncat(ld.current_line, " ", 2); /** add a space to the current line **/
				strncat(ld.current_line, token, strlen(token)+1); /** add the word to the current line **/
				char_count ++; /** add the space to the charcount **/
			}
		}

		token = strtok(NULL, " \n"); /** loops back around **/
	}

	return first_word;
}

int check_cmd(char* l){ /** Returns 1 if valid cmd was found, 0 if none was found **/
	if(strncmp(l, ".LW", 3) == 0) {
		/*printf("FOUND LW\n");*/
		set_args(l, ".LW ", 'w');

	}
	else if(strncmp(l, ".LS", 3) == 0) {
		/*printf("FOUND LS\n");*/
		set_args(l, ".LS ", 's');

	}
	else if(strncmp(l, ".LM", 3) == 0) {
		/*printf("FOUND LM\n");*/
		set_args(l, ".LM ", 'm');

	}
	else if(strncmp(l, ".FT", 3) == 0) {
		/*printf("FOUND FT\n");*/
		set_args(l, ".FT ", 't');

	}
	else return 0;

	return 1;
  
}

void set_args(char* l, char* cmd, char id){
	/*printf("%s%s%c\n", l, cmd, id );*/
	int plus_flg=0;
	int sub_flg=0;
	char* arith_arg;
	char *format_tok;
	format_tok = strtok(l, cmd);
	char *endp;/** Needs to be initialized for the next non numerical value in strtol **/

	if(strstr(format_tok, "+") != NULL) {
		arith_arg = strtok(format_tok, "+");
		plus_flg = 1; /** Notify program that the arguments are additive **/
	}

	else if(strstr(format_tok, "-") != NULL) {
		arith_arg = strtok(format_tok, "-");
		sub_flg = 1; /** Notify program that the arguments are additive **/
	}
	
	switch(id) {
      case 'w' :
        lw = strtol(format_tok, &endp, 10);
        add_linelen_mem();/** add the appropriate amount of memory for the line based on the value of lw **/
        ft = 1;
         break;
      case 'm' :
      	if(plus_flg){ /** add arguments rather than reallocate them **/
      		printf("ISHOULD BE ADDING %s to THE ARGS\n", arith_arg);
      		lm += strtol(arith_arg, &endp, 10);
        	break;	
      	}
      	if(sub_flg){ /** add arguments rather than reallocate them **/
      		printf("ISHOULD BE SUBTRACTING %s to THE ARGS\n", arith_arg);
      		lm -= strtol(arith_arg, &endp, 10);
       		break;	
      	}
      	lm = strtol(format_tok, &endp, 10);
      case 's' :
        ls = strtol(format_tok, &endp, 10);
         break;
      case 't' :
        if(strstr(l, "off") != NULL) ft = 0;
        else ft = 1;
         break;
      default :
        break;
   }
   return;
}

char **format_file(FILE *infile) {
	char * line = NULL;
 	size_t len = 0;
 	size_t read;
 	int idx=0;
 	char** lines = NULL;
 	int size = 15;
 	max_line = 0;


 	
 	lines = (char**) malloc(sizeof(char*) * size);
	if(!lines){
		printf("Error allocating memory for malloc on %d", 39); 
		abort();
	}

	while((read = getline(&line, &len, infile)) != -1){
 		if(len>max_line) max_line = len;
 		if(size < idx+1){
			size*=2;
printf("DEBUG E %x\n", lines);
			char** new_p = (char**) realloc(lines, sizeof(char*) * size);
 			if(!new_p){
				printf("Error allocating memory for malloc in format_file"); 
				abort();
			}
			else lines = new_p;
printf("DEBUG F %x\n", lines);
		}

printf("DEBUG C %x\n", lines[idx]);
		lines[idx] = (char*) malloc(sizeof(char) * (len+1));
printf("DEBUG D %x\n", lines[idx]);
 		if(lines[idx] == NULL){ 
 			printf("Error allocating memory for malloc in format_file");
			abort();
		}
		strncpy(lines[idx], line, len+1); /** copy the current line being processed into the current index of the array */
 		idx ++; /** Keep count of the current index **/	
 	}
 	if(line){
 		free(line);
 	} 

 	char** f_lines;

 	format(lines);

	return ld.formatted_str;
}

void format(char** lines){
	int first_word = 0;
	int new_para = 1;
	total_lines = 10;
	char** l;

	ld.formatted_str = (char**) malloc(sizeof(char*) * total_lines);
	if(!ld.formatted_str){
		printf("Error allocating memory for malloc"); 
		abort();
	}

	int count = 0;
	for(l = lines; *l != NULL; l++) {
		count ++;
		if(total_lines <= lf) add_line_mem();
		if(check_cmd(*l)){/** checks and sets args if there were arguments **/

			new_para = 1;
			continue;
		}	
		/*printf("LW:%d, LM:%d, LS:%d, FT:%d\n",lw,lm,ls,ft);*/
		/*if(new_para && ft == 1){*/ /** Special formatting case for new paragraphs **/
		/*}*/
		if(ft == 1 && new_para){
			first_word = 1;
		}

		if(ft == 1){
			first_word = in_para_formatter(*l, first_word);
			new_para = 0;
			/*printf("total_lines AFTER THE IN PARA : %d\n",total_lines );*/
		}

		else{
			
			printf("IM WORKING\n");
			lw = max_line;
			add_line_mem();
			printf("IM STILL WORKING lf is: %d, lw is %d the line is: %s size of line is: %d\n",lf, lw, *l, strlen(*l));
			strncpy(ld.formatted_str[lf], *l, strlen(*l)+1);
			lf++;
			add_linelen_mem();
		}

		/*else{
			char *token;
			token = strtok(l, "\n");/** if formatting is off, concat the raw lines to the lines list **/
		/*	while(token){
				strncpy(ld.current_line, "", 2);
				strncat(ld.current_line, token, strlen(token)+1);
				token = strtok(NULL, "\n"); /** loops back around **/
		/*	}
			strncpy(ld.formatted_str[lf], ld.current_line, strlen(ld.current_line));
			lf++;
		}*/
		
	}

	if(ft == 1 && ld.current_line){ /*as long as formatting is on, the last line processed should be added to the lines list, if it already was, an empty string will be appended*/
		/*printf("BEFORE THE LAST LINE IS ADDED%s\n", ld.formatted_str[lf]);*/
    	strncpy(ld.formatted_str[lf], ld.current_line, strlen(ld.current_line)+1);
    	ld.formatted_str[lf+1] = (char*) malloc(sizeof(char) *2);
	 	if(!ld.formatted_str){ 
	 		printf("Error allocating memory for malloc in add_linelen_mem ");
			abort();
		}
		/*strncpy(ld.formatted_str[lf], "BLAHBLAH", 10);*/
    	ld.formatted_str[lf+1] = NULL;
    	/*printf("%d\n", lf);*/
    	/*printf("THIS SHOULD BE A NULL:%p\n",ld.formatted_str[lf+1]);*/
    }       

}


char **format_lines(char **lines, int num_lines) {
	char **result;
	
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
