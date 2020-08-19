/************************************************************************/
/* File Name : lc4.c 													*/
/* Purpose   : This file contains the main() for this project			*/
/*             main() will call the loader and disassembler functions	*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_loader.h"
#include "lc4_memory.h"
#include "lc4_disassembler.h"


/* program to mimic pennsim loader and disassemble object files */

int main (int argc, char** argv) {
	/**
	 * main() holds the linked list &
	 * only calls functions in other files
	 */
    char* filename=NULL;

    /* step 1: create head pointer to linked list: memory 	*/
    row_of_memory* memory = NULL ;


    if (argc >= 2){
        /* step 2: determine filename, then open it		*/
        /*   TODO: extract filename from argv, pass it to open_file() */
        FILE *file=open_file(argv[1]);

        if(file==NULL){
            printf("Error to open the file\n");
        }

        /* step 3: call function: parse_file() in lc4_loader.c 	*/
        /*   TODO: call function & check for errors		*/
        parse_file(file, &memory);

        /* step 4: call function: reverse_assemble() in lc4_disassembler.c */
        /*   TODO: call function & check for errors		*/
        reverse_assemble(memory);

        /* step 5: call function: print_list() in lc4_memory.c 	*/
        /*   TODO: call function */
        print_list(memory);

        /* step 6: call function: delete_list() in lc4_memory.c */
        /*   TODO: call function & check for errors		*/
        int d=delete_list(&memory);
        if(d==-1){
            printf("Memory Cleared");
        }


    }
    else{
        printf("No Files added\n");
    }

	/* only return 0 if everything works properly */
	return 0 ;
}
