#include "inverted.h"

void update_db(HashTable *HT_arr)
{
    char backup[20];
    printf("Enter Backup file name: ");
    scanf(" %s",backup);

    if(check_extension(backup)==FAILURE)
    {
        printf("ERROR: Check Extension Of File..\n");
    }
    if(isExist(backup)==FAILURE)
    {
        printf("ERROR: File Not Exist..\n");
    }
    if(isEmpty(backup)==FAILURE)
    {
        printf("ERROR: Fail is Empty..\n");   
    }

    // Check whether hash table is empty
    for(int i = 0; i < HASH_SIZE; i++)
    {
        if(HT_arr->table[i] != NULL)
        {
            printf("ERROR: Hash table is not empty\n");
            return;
        }
    }
    
    FILE *fp=fopen(backup,"r");
    if(fp==NULL)
    {
        printf("ERROR: Failed to open the file..\n");
    
    }
    while(1)
    {
        
    }
   

}