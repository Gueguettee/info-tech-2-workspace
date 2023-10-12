#include <stdio.h>
#include <stdint.h>


#define N_DOUBLE_STRUCT 4


typedef enum
{
    eP_Type,
    eT_Type,
    eNbr_Types
}
structs_t;

struct struct_table
{
    int type;
    void* ptr;
};

struct struct_p_type
{
    char* name;
    int age;
};

struct struct_t_type
{
    char* thing;
    int id;
    int qte;
};


struct struct_table* InitStructs(uint16_t nbreStructs)
{
    struct struct_table *mainStructs;
    mainStructs = (struct struct_table *)malloc(sizeof(struct struct_table) * nbreStructs);

    for(uint16_t i = 0; i < nbreStructs; i++)
    {
        struct struct_p_type *str;
        str = (struct struct_p_type *)malloc(sizeof(struct struct_p_type));
        str->name = "John";
        str->age = (i+1)*5;

        struct struct_t_type *str2;
        str2 = (struct struct_t_type*)malloc(sizeof(struct struct_t_type));
        str2->thing = "Plane";
        str2->id = (i+1)*5+1;
        str2->qte = i+1;

        mainStructs[2*i].type = eP_Type;
        mainStructs[2*i].ptr = str;
        mainStructs[2*i+1].type = eT_Type;
        mainStructs[2*i+1].ptr = str2;
    }
    return mainStructs;
}


int main(int argc, const char *argv[])
{
    puts("!!!Hello World!!!");

    struct struct_table* mainStructs = InitStructs(N_DOUBLE_STRUCT);

    for(uint16_t i=0; i<N_DOUBLE_STRUCT*2; i++)
    {
        if((mainStructs[i].type == eT_Type)&&(mainStructs[i+1].type))
        {
            struct struct_table
        }
    }

    return 0;
}
