#include "inverted.h"
int main(int argc,char *argv[])
{
    if (argc < 2)
    {
        printf("Error: Insufficient arguments.\n");
        printf("Usage: %s <file1.txt> <file2.txt> ...\n", argv[0]);
        return FAILURE;
    }
    F_node *head = NULL;

    validate_files(argc, argv, &head);
   
    int ch;
    do
    {
        printf("\n========================================\n");
        printf("         INVERTED SEARCH MENU           \n");
        printf("========================================\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if(scanf("%d",&ch)!=1)
        {
            printf("Invalid input. Please enter a valid number.\n");
            while(getchar()!='\n');
            continue;
        }
        switch(ch)
        {
            case 1:
                // Create Database
                break;

            case 2:
                // Display Database
                break;

            case 3:
                // Search Database
                break;

            case 4:
                // Save Database
                break;

            case 5:
                // Update Database
                break;

            case 6:
                printf("Exiting Inverted Search...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (ch!=6);
    
}