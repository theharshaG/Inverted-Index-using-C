#include "inverted.h"
void save_database(HashTable *HT_arr)
{
    char file[20];
    char ch;
    do{
        printf(BLUE"Enter FILE name to save: "RESET);
        scanf("%s",file);
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
            printf("\n");
        }
    }while(tolower(ch)!='y');
    FILE *fp=fopen(file,"w");
    for(int i=0;i<HASH_SIZE;i++)
    {
        MainNode *temp=HT_arr->table[i];
        while(temp!=NULL)
        {
            fprintf(fp,"#%-5d%-10s%-10d", i,temp->word,temp->file_count);
            SubNode *stemp=temp->sub_link;
            while(stemp!=NULL)
            {
                fprintf(fp,"%-12s %-5d",stemp->filename,stemp->word_count);
                stemp=stemp->sub_link;
            }
            fprintf(fp,"#\n");
            temp=temp->main_link;
        }
    }
    fclose(fp);
    printf(GREEN"INFO: Database saved successfully!!\n"RESET);

}
