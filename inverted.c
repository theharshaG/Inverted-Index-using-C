#include "inverted.h"

void initializeHashTable(HashTable *HT_arr)
{
    for(int i=0;i<HASH_SIZE;i++)
    {
        HT_arr->table[i]=NULL;
    }
}

// Detects hash table index for the given word
int get_index(char *word)
{
    char ch = tolower(word[0]);

    if(ch >= 'a' && ch <= 'z')
        return ch - 'a';
    else
        return 26;
}
int Creat_database(HashTable *HT_arr, F_node *head)
{
    FILE *fp;
    char word[50];

    while(head != NULL)
    {
        fp = fopen(head->f_name, "r");

        if(fp == NULL)
            return FAILURE;

        while(fscanf(fp, "%49s", word) == 1)
        {
            int index = get_index(word);

            if(HT_arr->table[index] == NULL)
            {
                MainNode *new = malloc(sizeof(MainNode));

                if(new == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(new->word, word);
                new->file_count = 1;
                new->sub_link = NULL;
                new->main_link = NULL;

                HT_arr->table[index] = new;
            }
        }

        fclose(fp);

        head = head->link;
    }

    return SUCCESS;
}