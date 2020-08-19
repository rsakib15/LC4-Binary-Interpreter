/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>
#include "lc4_loader.h"
#include "lc4_disassembler.h"

/*
 * adds a new node to a linked list pointed to by head
 */

int add_to_list(row_of_memory** head,short unsigned int address,short unsigned int contents){
    /* check to see if there is already an entry for this address and update the contents, if so */
    /* allocate memory for a single node */
	/* populate fields in newly allocated node w/ address&contents */
	/* if head==NULL, node created is the new head of the list! */
	/* otherwise, insert node into the list in address ascending order */
	/* return 0 for success, -1 if malloc fails */

	row_of_memory* memory= malloc(sizeof(row_of_memory));
    if (memory == NULL){
		return -1;
	}

	memory->address=address;
    memory->contents=contents;
    memory->label=NULL;
    memory->assembly=NULL;
    memory->next=NULL;

	if(*head==NULL){
        *head=memory;
    }
    else{
        row_of_memory* node = *head;
        while(node->next != NULL){
            node = node->next;
        }
        node->next = memory;
    }
	return 0 ;
}

/*
 * search linked list by address field, returns node if found
 */

row_of_memory* search_address (row_of_memory* head, short unsigned int address ){
	/* traverse linked list, searching each node for "address"  */
	/* return pointer to node in the list if item is found */
	/* return NULL if list is empty or if "address" isn't found */
	/* return pointer to node in list that matches */
	/* return NULL if list is empty or if "address" isn't found */

	row_of_memory *memory = head;
    while (memory != NULL){
        if (memory->address == address){
			return memory;
		}
		memory = memory->next;
	}
	return NULL ;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head, short unsigned int opcode  ){
    /* opcode parameter is in the least significant 4 bits of the short int and ranges from 0-15 */
    /* traverse linked list until node is found with matching opcode AND "assembly" field of node is empty */
	/* return pointer to node in the list if item is found */
	/* return NULL if list is empty or if no matching nodes */

	row_of_memory* memory = head;
	while(1){
        if (memory == NULL) {
            break;
        }
        if (((0b1111000000000000 & memory->contents) == (opcode<<12)))  {
            if(memory->assembly == NULL)
			break;
		}
		memory = memory->next;
	}
	if (memory==NULL){
        return NULL;
	}
	else{
        return memory;
	}
}


void print_list (row_of_memory* head ){
	/* make sure head isn't NULL */
    /* print out a header */
	/* traverse linked list, print contents of each node */
    if(head == NULL){
        printf("nothing here\n");
    }
    else{
        printf("Label\t\taddress\t\tcontents\t\tassembly\n");
        row_of_memory* node = head;
        while(node != NULL){
            printf("%s\t\t%04x\t\t%04x\t\t%s\n", node->label, node->address, node->contents, node->assembly);
            node = node->next;
        }
    }
}

/*
 * delete entire linked list
 */

int delete_list(row_of_memory** head ){
	/* delete entire list node by node */
	/* if no errors, set head = NULL upon deletion */
	/* return 0 if no error, -1 for any errors that may arise */

    row_of_memory* memory=*head;
    row_of_memory* nextptr;

    while( memory!= NULL){
        free(memory->assembly);
        free(memory->label);
        nextptr = memory -> next;
        free(memory);
        memory = nextptr;
        *head = NULL;
    }
    return -1;
}
