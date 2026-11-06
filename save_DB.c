#include "inverted.h"

void save_database(HashTable *HT_arr)
{
    if(HT_arr == NULL || is_database_empty(HT_arr) == FAILURE)
    {
        printf(RED"INFO: Data Base Empty []\n"RESET);
        return;
    }
    char file[20];
    char ch;

    while(1){
        printf(BLUE"Enter FILE name to save: "RESET);
        scanf(" %s",file);
        if(check_extension(file)==FAILURE)
        {
            printf(RED"ERROR: Invalid FILE Extension!!\n"RESET);
            continue;
        }
        if((isExist(file))==SUCCESS)
        {
            printf(RED"INFO: File already Exist!!\n"RESET);
            printf(BLUE"1] Enter Y for overwrite\n");
            printf("2] Enter N for change the file name [Y/N]: "RESET);
            scanf(" %c",&ch);

            if(tolower((unsigned char)ch) == 'n')
                continue;

            if(tolower((unsigned char)ch) != 'y')
                continue;

            printf("\n");
        }
        break;
    }
    FILE *fp=fopen(file,"w");
    for(int i=0;i<HASH_SIZE;i++)
    {
        MainNode *temp=HT_arr->table[i];
        while(temp!=NULL)
        {
            fprintf(fp, "#%d\n", i);
            //fprintf(fp,"#%-5d%-10s%-10d", i,temp->word,temp->file_count);
            fprintf(fp, "WORD: %s\n", temp->word);
            fprintf(fp, "FILECOUNT: %d\n", temp->file_count);

            SubNode *stemp=temp->sub_link;
            while(stemp!=NULL)
            {
                //fprintf(fp,"%-12s %-5d",stemp->filename,stemp->word_count);
                fprintf(fp, "FILE: %s  WORDCOUNT: %d\n",
                        stemp->filename,
                        stemp->word_count);

                stemp=stemp->sub_link;
            }
            fprintf(fp,"#\n");
            temp=temp->main_link;
        }
    }
    fclose(fp);
    printf(GREEN"INFO: Database information is saved into %s file successfully\n"RESET,file);

}
