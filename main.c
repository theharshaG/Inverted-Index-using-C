#include "inverted.h"
int main(int argc,char *argv[])
{
    if (argc < 2)
    {
        printf(RED"Error: Insufficient arguments.\n"RESET);
        printf(RED "Usage: " GREEN "%s" RED " <file1.txt> <file2.txt> ...\n" RESET, argv[0]);        
        return FAILURE;
    }
    F_node *head = NULL;
    HashTable HT_arr;
    initializeHashTable(&HT_arr);

    validate_files(argc, argv, &head);
    F_node *temp=head;
    printf(BLUE"\nInserted File: \n"RESET);
    while(temp!=NULL)
    {
        printf(BLUE"%s -> "RESET,temp->f_name);
        temp=temp->link;
    }
   
    int ch;
    do
    {
        printf("\n========================================\n");
        printf(GRAY"         INVERTED SEARCH MENU           \n"RESET);
        printf("========================================\n");
        printf(GRAY"1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n"RESET);
        printf(BLUE"\nEnter your choice: "RESET);

        if(scanf("%d",&ch)!=1)
        {
            printf(RED"Invalid input. Please enter a valid number.\n"RESET);
            while(getchar()!='\n');
            continue;
        }
        printf("\n");
        switch(ch)
        {
            case 1:
                // Create Database
                if(create_database(&HT_arr,head)==SUCCESS)
                {
                    printf(GREEN"DataBase Created!!"RESET);
                }
                else
                {
                    printf(RED"Failed to create data base\n"RESET);
                }
                break;

            case 2:
                // Display Database
                display_database(&HT_arr);
                break;

            case 3:
                // Search Database
                search(&HT_arr);
                break;

            case 4:
                // Save Database
                break;

            case 5:
                // Update Database
                break;

            case 6:
                printf(RED"Exiting Inverted Search...\n"RESET);
                break;

            default:
                printf(RED"Invalid choice.\n"RESET);
        }
    } while (ch!=6);
    
}