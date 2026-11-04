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

//actual data base function
int create_database(HashTable *HT_arr, F_node *head)
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
            // Convert word into lowercase
            for(int i = 0; word[i] != '\0'; i++)
            {
                word[i] = tolower((unsigned char)word[i]);
            }

            // Calculate hash index
            int index = get_index(word);

            // Case 1: Hash index is empty
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
                new->main_link = NULL;

                // Create first SubNode
                SubNode *snew = malloc(sizeof(SubNode));

                if(snew == NULL)
                {
                    free(new);
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(snew->filename, head->f_name);
                snew->word_count = 1;
                snew->sub_link = NULL;

                new->sub_link = snew;

                HT_arr->table[index] = new;
            }
            else
            {
                // Case 2: Hash index already contains MainNodes
                MainNode *temp = HT_arr->table[index];

                // Search for the word
                while(temp != NULL)
                {
                    if(strcmp(temp->word, word) == 0)
                        break;

                    temp = temp->main_link;
                }

                // Case 2A: Word already exists
                if(temp != NULL)
                {
                    SubNode *stemp = temp->sub_link;
                    SubNode *prev = NULL;

                    // Search for the filename
                    while(stemp != NULL)
                    {
                        if(strcmp(stemp->filename, head->f_name) == 0)
                        {
                            stemp->word_count++;
                            break;
                        }

                        prev = stemp;
                        stemp = stemp->sub_link;
                    }

                    // Case 2B: Filename doesn't exist
                    if(stemp == NULL)
                    {
                        SubNode *snew = malloc(sizeof(SubNode));

                        if(snew == NULL)
                        {
                            fclose(fp);
                            return FAILURE;
                        }

                        strcpy(snew->filename, head->f_name);
                        snew->word_count = 1;
                        snew->sub_link = NULL;

                        if(prev == NULL)
                        {
                            temp->sub_link = snew;
                        }
                        else
                        {
                            prev->sub_link = snew;
                        }

                        temp->file_count++;
                    }
                }
                else
                {
                    // Case 3: Word doesn't exist
                    // Create a new MainNode

                    MainNode *new = malloc(sizeof(MainNode));

                    if(new == NULL)
                    {
                        fclose(fp);
                        return FAILURE;
                    }

                    strcpy(new->word, word);
                    new->file_count = 1;
                    new->main_link = NULL;

                    // Create first SubNode
                    SubNode *snew = malloc(sizeof(SubNode));

                    if(snew == NULL)
                    {
                        free(new);
                        fclose(fp);
                        return FAILURE;
                    }

                    strcpy(snew->filename, head->f_name);
                    snew->word_count = 1;
                    snew->sub_link = NULL;

                    new->sub_link = snew;

                    // Traverse to the last MainNode
                    temp = HT_arr->table[index];

                    while(temp->main_link != NULL)
                    {
                        temp = temp->main_link;
                    }

                    temp->main_link = new;
                }
            }
        }

        fclose(fp);

        // Move to next filename
        head = head->link;
    }

    return SUCCESS;
}