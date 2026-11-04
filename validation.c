#include "inverted.h"

int check_extension(char *str)
{
    int len=strlen(str);
    if(len<4)
    {
        return FAILURE;
    }
    if(strcmp(str+len-4,".txt")==0)
    {
        return SUCCESS;
    }
    return FAILURE;
}
int check_duplicates(F_node *head, char *filename)
{
    while(head!=NULL)
    {
        if(strcmp(head->f_name,filename)==0)
        {
            return FAILURE;
        }
        head=head->link;
    }
    return SUCCESS;
}
int isExist(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        return FAILURE;
    }

    fclose(fp);
    return SUCCESS;
}
int isEmpty(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        return FAILURE;
    }

    int ch = fgetc(fp);
    fclose(fp);

    if(ch==EOF)
    {
        return FAILURE;
    }
    return SUCCESS;

}
int insert_last(F_node **head, char *filename)
{
    F_node *new=malloc(sizeof(F_node));
    if(new==NULL)
    {
        return FAILURE;
    }
    strcpy(new->f_name,filename);
    new->link=NULL;
    if(*head==NULL)
    {
        *head=new;
    }
    else
    {
        F_node *temp=*head;
        while(temp->link!=NULL)
        {
            temp=temp->link;
        }
        temp->link=new;
    }
    return SUCCESS;
}
void validate_files(int argc, char *argv[], F_node **head)
{
    for (int i = 1; i < argc; i++)
    {
        if (check_extension(argv[i]) == FAILURE)
        {
            printf("%s: Invalid extension\n", argv[i]);
            continue;
        }

        if (check_duplicates(*head, argv[i]) == FAILURE)
        {
            printf("%s: Duplicate file\n", argv[i]);
            continue;
        }

        if (isExist(argv[i]) == FAILURE)
        {
            printf("%s: File does not exist or cannot be opened\n", argv[i]);
            continue;
        }

        if (isEmpty(argv[i]) == FAILURE)
        {
            printf("%s: File is empty\n", argv[i]);
            continue;
        }

        if (insert_last(head, argv[i]) == FAILURE)
        {
            printf("Memory allocation failed\n");
            continue;
        }

        printf("%s: File accepted\n", argv[i]);
    }
}