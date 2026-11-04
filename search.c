#include "inverted.h"

void search(HashTable *HT_arr)
{
    char word[20];

    printf("Enter word to search: ");
    scanf("%19s", word);

    int index = get_index(word);

    MainNode *temp = HT_arr->table[index];

    while(temp != NULL)
    {
        if(strcmp(temp->word, word) == 0)
        {
            printf(BLUE"\nWord found!\n"RESET);
            printf(GREEN"-----------------------------------------------------------------------\n");
            printf("%-8s %-15s %-15s %-15s %-8s\n","Index","Word", "Filecount", "Files Name", "Wordcount");
            printf("------------------------------------------------------------------------\n");

            //printf("%s    %d  ", temp->word, temp->file_count);

            SubNode *sub_temp = temp->sub_link;

            while(sub_temp != NULL)
            {
                //printf("    %s    %d  ",sub_temp->filename,sub_temp->word_count);
                 printf("%-8d %-15s %-15d %-20s %-10d\n",
                       index,
                       temp->word,
                       temp->file_count,
                       sub_temp->filename,
                       sub_temp->word_count);

                sub_temp = sub_temp->sub_link;
            }

            printf(RESET);
            return;
        }

        temp = temp->main_link;
    }

    printf(RED"Word not found!!\n"RESET);
}