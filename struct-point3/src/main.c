/*
 ============================================================================
 Name        : main.c
 Author      : P. Bovey
 Version     : 2019
 Copyright   : HEIA-FR Génie Electrique - Info Tech II
 Description : Main to launch test of structures in C (ANSI-style)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"


// main needs the number of structures to generate as argument (positive integer format)

int main(int argc, const char* argv[]) {
	int size_tableau = 0;
	struct struct_table *ptr_tableau = NULL;

	printf("Started\n");

	if (argc == 2){						// check if argument present !
		size_tableau = atoi(argv[1]);

		if (size_tableau > 0){			// something to test ?

			// generate structures
			ptr_tableau = initStructs(size_tableau);
			// print structures as initially generated
			showStructs(ptr_tableau, size_tableau);

			// test structures sorting forward by Types
			sortStructsType(ptr_tableau, size_tableau, SORT_FORWARD);
			// print structures after forward sorting
			showStructs(ptr_tableau, size_tableau);

			// test structures sorting reverse by Content - make sense only after a Type sorting !
			sortStructsContent(ptr_tableau, size_tableau, SORT_REVERSE);
			// print structures after reverse sorting
			showStructs(ptr_tableau, size_tableau);

			// test structures sorting reverse by Types
			sortStructsType(ptr_tableau, size_tableau, SORT_REVERSE);
			// print structures after reverse sorting
			showStructs(ptr_tableau, size_tableau);

			// test structures sorting forward by Content - make sense only after a Type sorting !
			sortStructsContent(ptr_tableau, size_tableau, SORT_FORWARD);
			// print structures after forward sortingd
			showStructs(ptr_tableau, size_tableau);

			// release and free allocated memory
			freeStructs(ptr_tableau, size_tableau);

		} else {
			printf("1st argument must be an integer > 0 !\n"); // bad argument
		}

		printf("Ended\n");

	} else {
		printf("Usage: \"./Structs X <return>\" - with X the number of structure to generate randomly!\n");
	}

	exit (EXIT_SUCCESS);

}
