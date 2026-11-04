#include "inverted.h"

void display_database(HashTable *HT_arr)
{
    printf(GREEN"%40s\n","[---DATABASE---]");
    printf("--------------------------------------------------------------------\n");

    printf("%-8s %-15s %-15s %-15s %-8s\n",
           "Index", "Word", "Filecount", "Files Name", "Wordcount");

    printf("--------------------------------------------------------------------\n");
    for(int i = 0; i < HASH_SIZE; i++)
    {
        MainNode *temp = HT_arr->table[i];

        while(temp != NULL)
        {
            printf("%-8d %-15s %-15d", i, temp->word, temp->file_count);

            SubNode *sub_temp = temp->sub_link;

            while(sub_temp != NULL)
            {
                printf("%-15s %-10d",sub_temp->filename,sub_temp->word_count);

                sub_temp = sub_temp->sub_link;
            }

            printf("\n");

            temp = temp->main_link;
        }
    }
    printf(RESET);
}