#include "inverted.h"

int update_db(HashTable *HT_arr)
{
    if (HT_arr == NULL)
    {
        return FAILURE;
    }

    // 1. Check whether database is already created / not empty
    if (is_database_empty(HT_arr) == SUCCESS)
    {
        printf(RED"ERROR: Database is already created, cannot update database\n"RESET);
        return FAILURE;
    }

    char backup[20];
    printf(BLUE"Enter Backup file name: "RESET);
    scanf(" %19s", backup);

    // 2. Validations
    if (check_extension(backup) == FAILURE)
    {
        printf(RED"ERROR: Check Extension Of File..\n"RESET);
        return FAILURE;
    }
    if (isExist(backup) == FAILURE)
    {
        printf(RED"ERROR: File Not Exist..\n"RESET);
        return FAILURE;
    }
    if (isEmpty(backup) == FAILURE)
    {
        printf(RED"ERROR: File is Empty..\n"RESET);
        return FAILURE;
    }

    FILE *fp = fopen(backup, "r");
    if (fp == NULL)
    {
        printf(RED"ERROR: Failed to open the file..\n"RESET);
        return FAILURE;
    }

    // Check if the file starts with '#'
    int first_char = fgetc(fp);
    if (first_char != '#')
    {
        printf(RED"ERROR: %s is not a valid database backup file\n"RESET, backup);
        fclose(fp);
        return FAILURE;
    }
    rewind(fp);

    char line[100];
    char word[50];
    char filename[64];

    int index = -1;
    int word_count;

    MainNode *new_main = NULL;
    MainNode *temp_main = NULL;

    SubNode *new_sub = NULL;
    SubNode *sub_tail = NULL;

    // 3. Read line by line
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Line 1: "#1" -> get the bucket index
        if (line[0] == '#' && isdigit((unsigned char)line[1]))
        {
            sscanf(line, "#%d", &index);
        }
        // Line 2: "WORD: bye" -> create the MainNode
        else if (strncmp(line, "WORD:", 5) == 0)
        {
            sscanf(line, "WORD: %49s", word);

            new_main = malloc(sizeof(MainNode));
            if (new_main == NULL)
            {
                fclose(fp);
                return FAILURE;
            }
            strcpy(new_main->word, word);
            new_main->file_count = 0;
            new_main->sub_link = NULL;
            new_main->main_link = NULL;
            sub_tail = NULL;
        }
        // Line 3: "FILECOUNT: 1" -> assign file count
        else if (strncmp(line, "FILECOUNT:", 10) == 0)
        {
            int fc = 0;
            sscanf(line, "FILECOUNT: %d", &fc);
            if (new_main != NULL)
            {
                new_main->file_count = fc;
            }
        }
        // Line 4: "FILE: text2.txt  WORDCOUNT: 1" -> create SubNode
        else if (strncmp(line, "FILE:", 5) == 0)
        {
            if (sscanf(line, "FILE: %63s WORDCOUNT: %d", filename, &word_count) == 2)
            {
                new_sub = malloc(sizeof(SubNode));
                if (new_sub == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }
                strcpy(new_sub->filename, filename);
                new_sub->word_count = word_count;
                new_sub->sub_link = NULL;

                if (new_main != NULL)
                {
                    if (new_main->sub_link == NULL)
                        new_main->sub_link = new_sub;
                    else
                        sub_tail->sub_link = new_sub;

                    sub_tail = new_sub;
                }
            }
        }
        // Line 5: "#" -> End of this word's block: insert into table[index]
        else if (line[0] == '#' && !isdigit((unsigned char)line[1]))
        {
            if (new_main != NULL && index >= 0 && index < HASH_SIZE)
            {
                if (HT_arr->table[index] == NULL)
                {
                    HT_arr->table[index] = new_main;
                }
                else
                {
                    temp_main = HT_arr->table[index];
                    while (temp_main->main_link != NULL)
                    {
                        temp_main = temp_main->main_link;
                    }
                    temp_main->main_link = new_main;
                }
                new_main = NULL;
                sub_tail = NULL;
            }
        }
    }

    // Flush last node if file ended without trailing '#'
    if (new_main != NULL && index >= 0 && index < HASH_SIZE)
    {
        if (HT_arr->table[index] == NULL)
        {
            HT_arr->table[index] = new_main;
        }
        else
        {
            temp_main = HT_arr->table[index];
            while (temp_main->main_link != NULL)
            {
                temp_main = temp_main->main_link;
            }
            temp_main->main_link = new_main;
        }
        new_main = NULL;
    }

    fclose(fp);
    printf(GREEN"INFO: Database updated successfully from %s\n"RESET, backup);
    return SUCCESS;
}