/*
 ============================================================================
 Name        : structs.c
 Author      : P. Bovey
 Version     : 2019
 Copyright   : HEIA-FR Génie Electrique - Info Tech II
 Description : Structures in C (ANSI-Style)
 	 	 	   (tables, pointers, structures, allocations, tri)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structs.h"

// declaration of an hidden function...
// exchange data in the table of pointer to the structures
void exchange(struct struct_table *ptr_first, struct struct_table *ptr_second);


// display structures
void showStructs(struct struct_table *ptr_table, int size_table){
	int nbr_n_type = 0, nbr_p_type = 0, nbr_t_type = 0;
	struct struct_p_type *ptr_p_type = NULL;
	struct struct_t_type *ptr_t_type = NULL;

	for (int i = 0; i < size_table; i++) {
		printf("Display structure %i of type %i - ", i+1, ptr_table[i].type);

		switch (ptr_table[i].type) {

			case eN_Type:
				nbr_n_type++;
				printf("No type defined here!\n");
				break;

			case eP_Type:
				nbr_p_type++;
				ptr_p_type = (struct struct_p_type *) ptr_table[i].ptr;
				printf("P_Type of age %i\n", ptr_p_type->age);
				break;

			case eT_Type:
				nbr_t_type++;
				ptr_t_type = (struct struct_t_type *) ptr_table[i].ptr;
				printf("T_Type of qte %i\n", ptr_t_type->qte);
				break;
		}
	}
	printf("Total of %i structures retrieved with %i N_TYPE, %i P_TYPE and %i T_TYPE\n" ,nbr_n_type + nbr_p_type + nbr_t_type, nbr_n_type, nbr_p_type, nbr_t_type);
}


// generate structures
struct struct_table* initStructs(int size_table){
	int new_type = 0;
	int nbr_n_type = 0, nbr_p_type = 0, nbr_t_type = 0;

	struct struct_table *ptr_table = NULL;
	struct struct_p_type *ptr_p_type = NULL;
	struct struct_t_type *ptr_t_type = NULL;
	void * ptr_struct_type = NULL;


	printf("Generation and initialization of %i structures\n", size_table);

	ptr_table = calloc(size_table,sizeof(struct struct_table));		// allocate memory for table[size]

	if (ptr_table == NULL) {
		exit(EXIT_FAILURE); 	// memory allocation error, quit with an error
	}

	// Random selection of structure type
	srand(time(NULL));  // pseudo random using time seed

	for (int i = 0; i < size_table; i++) {
		new_type = rand() % eNbr_Types;			// random type modulo nbr of types

		switch (new_type) {

			case eN_Type:
				nbr_n_type++;				// no structure
				ptr_struct_type = NULL;		// no pointer
				break;

			case eP_Type:
				ptr_p_type = calloc(1,sizeof(struct struct_p_type));	//  1 structure P memory allocation
				if (ptr_p_type == NULL) {
					exit(EXIT_FAILURE); 	// memory allocation error, quit with an error
				}
				ptr_p_type->age = rand() % MAX_AGE;
				// .. etc. name not allocated here
				ptr_struct_type = (void *) ptr_p_type; 	// table request void* pointer
				nbr_p_type++;
				break;

			case eT_Type:
				ptr_t_type = calloc(1,sizeof(struct struct_t_type));	//  1 structure T memory allocation
				if (ptr_t_type == NULL) {
					exit(EXIT_FAILURE); 	// memory allocation error, quit with an error
				}
				ptr_t_type->qte = rand() % MAX_QTE;
				// ... etc. thing and id not allocated here
				ptr_struct_type = (void *) ptr_t_type; 	// table request void* pointer
				nbr_t_type++;
				break;
		}

		// set values in table[i]
		ptr_table[i].type = new_type;
		ptr_table[i].ptr = ptr_struct_type;
	}
	printf("Total of %i structures allocated with %i N_TYPE, %i P_TYPE and %i T_TYPE\n" ,nbr_n_type + nbr_p_type + nbr_t_type, nbr_n_type, nbr_p_type, nbr_t_type);
	return ptr_table;
}


// sort structures by type
// We use a bubble sort algorithm (see bubble sort doc in Wikipedia if unknown!)
// only move indexes in the table, don't touch the structures itself !
void sortStructsType(struct struct_table *ptr_table, int size_table, int sorting_direction){
	if (sorting_direction == SORT_FORWARD){
		printf("Sorting type forward\n");
		for (int i = 1; i <= size_table; i++){ // repeat the bubble sort for the size of the table
			for (int index = 0; index < size_table -1; index++){ // browse the table forward up to the before last structure index
				if (ptr_table[index].type > ptr_table[index+1].type){	// exchange pointers only if in the wrong order (BIGGER !!)
					exchange(&ptr_table[index], &ptr_table[index+1]);
				}
			}
		}
	} else {
		printf("Sorting type reverse\n");
		for (int i = 1; i <= size_table; i++){ // repeat the bubble sort for the size of the table
			for (int index = 0; index < size_table -1; index++){ // browse the table forward up to the before last structure index
				if (ptr_table[index].type < ptr_table[index+1].type){	// exchange pointers only if in the wrong order (SMALLER !!)
					exchange(&ptr_table[index], &ptr_table[index+1]);
				}
			}
		}
	}
}


// sort structures by content
// We use a bubble sort algorithm (see bubble sort doc in Wikipedia if unknown!)
// only move indexes in the table, don't touch the structures itself !
void sortStructsContent(struct struct_table *ptr_table, int size_table, int sorting_direction){
	if (sorting_direction == SORT_FORWARD){
		printf("Sorting content forward\n");
		for (int i = 1; i <= size_table; i++){ // repeat the bubble sort for the size of the table
			for (int index = 0; index < size_table -1; index++){ // browse the table forward up to the before last structure index
				switch (ptr_table[index].type){
					case eP_Type:
						// use type casting to address the field of the P_TYPE structure
						if ((ptr_table[index+1].type == eP_Type) &&
							((struct struct_p_type*) ptr_table[index].ptr)->age > ((struct struct_p_type*) ptr_table[index+1].ptr)->age)
								// exchange pointers only if in the wrong order (BIGGER !!)
								exchange(&ptr_table[index], &ptr_table[index+1]);
					break;

					case eT_Type:
						// use type casting to address the field of the T_TYPE structure
						if ((ptr_table[index+1].type == eT_Type) &&
							((struct struct_t_type*) ptr_table[index].ptr)->qte > ((struct struct_t_type*) ptr_table[index+1].ptr)->qte)
								// exchange pointers only if in the wrong order (BIGGER !!)
								exchange(&ptr_table[index], &ptr_table[index+1]);
					break;
				}
			}
		}
	} else {
		printf("Sorting content reverse\n");
		for (int i = 1; i <= size_table; i++){ // repeat the bubble sort for the size of the table
			for (int index = 0; index < size_table -1; index++){ // browse the table forward up to the before last structure index
				switch (ptr_table[index].type){
					case eP_Type:
						// use type casting to address the field of the P_TYPE structure
						if ((ptr_table[index+1].type == eP_Type) &&
							((struct struct_p_type*) ptr_table[index].ptr)->age < ((struct struct_p_type*) ptr_table[index+1].ptr)->age)
								// exchange pointers only if in the wrong order (SMALLER !!)
								exchange(&ptr_table[index], &ptr_table[index+1]);
					break;

					case eT_Type:
						// use type casting to address the field of the T_TYPE structure
						if ((ptr_table[index+1].type == eT_Type) &&
							((struct struct_t_type*) ptr_table[index].ptr)->qte < ((struct struct_t_type*) ptr_table[index+1].ptr)->qte)
								// exchange pointers only if in the wrong order (SMALLER !!)
								exchange(&ptr_table[index], &ptr_table[index+1]);
					break;
				}
			}
		}
	}
}


// exchange data in the table of pointer to the structures
void exchange(struct struct_table *ptr_first, struct struct_table *ptr_second){
	// temporary storages for data exchange
	int tmp_type;
	void* tmp_ptr;

	// preserve first data
	tmp_type = ptr_first->type;
	tmp_ptr = ptr_first->ptr;
	// copy second data in first data
	ptr_first->type = ptr_second->type;
	ptr_first->ptr = ptr_second->ptr;
	// copy first data in second data using the preserved ones
	ptr_second->type = tmp_type;
	ptr_second->ptr = tmp_ptr;
}


// free allocated memory
void freeStructs(struct struct_table *ptr_table, int size_table){
	int nbr_n_type = 0, nbr_p_type = 0, nbr_t_type = 0;
	struct struct_p_type *ptr_p_type = NULL;
	struct struct_t_type *ptr_t_type = NULL;

	// free structures memory
	for (int i = 0; i < size_table; i++) {
		switch(ptr_table[i].type){

			case eN_Type:			// nothing to free
				nbr_n_type++;
				break;

			case eP_Type:			// free a P_Type structure memory
				ptr_p_type = (struct struct_p_type *) ptr_table[i].ptr;		// retrieve the right type to free the right memory size
				free (ptr_p_type);
				nbr_p_type++;
				break;

			case eT_Type:			// free a T_Type structure memory
				ptr_t_type = (struct struct_t_type *) ptr_table[i].ptr;		// retrieve the right type to free the right memory size
				free (ptr_t_type);
				nbr_t_type++;
				break;
		}
	}

	free(ptr_table);	// free table memory
	printf("Free %i structures with %i N_TYPE, %i P_TYPE and %i T_TYPE\n" ,nbr_n_type + nbr_p_type + nbr_t_type, nbr_n_type, nbr_p_type, nbr_t_type);

}
