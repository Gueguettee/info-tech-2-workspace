/*
 ============================================================================
 Name        : structs.h
 Author      : P. Bovey
 Version     : 2019
 Copyright   : HEIA-FR Génie Electrique - Info Tech II
 Description : Structures in C (ANSI-Style)
 	 	 	   (tables, pointers, structures, allocations, tri)
 ============================================================================
*/

#define MAX_AGE 100
#define MAX_QTE 1000

#define SORT_REVERSE 0
#define SORT_FORWARD 1

// definition types of available structures
// eN_Type is for no structure allocated
// eP_Type for person structure
// eT_Type for thing structure
typedef enum {eN_Type, eP_Type, eT_Type, eNbr_Types} structs_t;


// index to the various structures (mixed type)
struct struct_table {
	int type;				// store the type of pointed structures
	void* ptr;				// generic void pointer to the structure
};

// type person
struct struct_p_type {
	char* name;
	int	  age;
};

// type thing
struct struct_t_type {
	char* thing;
	int	  id;
	int   qte;
};


// functions prototypes

// display structures
void showStructs(struct struct_table *ptr_table, int size_table);

// generate structures
struct struct_table* initStructs(int size_table);

// sort structures by types
void sortStructsType(struct struct_table *ptr_table, int size_table, int sorting_direction);

// sort structures by content
void sortStructsContent(struct struct_table *ptr_table, int size_table, int sorting_direction);

// free allocated memory
void freeStructs(struct struct_table *ptr_table, int size_table);
