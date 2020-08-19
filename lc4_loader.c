/************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <string.h>
#include "lc4_memory.h"
#include "lc4_disassembler.h"
#include <stdlib.h>

/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name){
    FILE *file ;
    file = fopen(file_name, "r");
    if(file == NULL) {
        printf("File not found\n");
        return NULL;
    }
    printf("File opening completed...\n");
	return file;
}

int parse_file(FILE* my_obj_file, row_of_memory** memory){
    unsigned  char  level[2];
    unsigned char address[2];
    unsigned char num[2];
    unsigned char value[2];
    row_of_memory* p = *memory;
    int count,number,str;

    while(1){
        if(feof(my_obj_file)){
            break;
        }

        fread (level, sizeof(unsigned char), 2, my_obj_file);
        fread (address, sizeof(unsigned char), 2, my_obj_file);
        fread (num, sizeof(unsigned char), 2, my_obj_file);
        count=(address[0]<<8)+address[1];
        number=(num[0]<<8)+num[1];

        if ((level[0] == 0xCA && level[1] == 0xDE) || (level[0] == 0xDA && level[1] == 0xDA)) {
            for(int i=0; i<number;++i){
                fread (value, sizeof(unsigned char), 2, my_obj_file);
                str=(value[0]<<8)+value[1];
                printf("%d",str);
                add_to_list(&p, count, str);
                count++;
            }
        }

        else if (level[0] == 0xC3 && level[1] == 0xB7){
            char* temp = malloc(number + 1);
            fread(temp, 1, number, my_obj_file);
            row_of_memory* target = search_address(p, count);

            if (target == NULL){
                add_to_list(&p, count, 0);
                target = search_address(p, count);
            }
            if(strlen(temp)!=0) {
                target->label = temp;
            }
            else{
                free(temp);
            }
        }
    }

    *memory = p;
    fclose(my_obj_file);
    return 0;
}
