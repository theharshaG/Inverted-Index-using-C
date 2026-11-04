#ifndef INVERTED_H
#define INVERTED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 1
#define FAILURE 0

#define HASH_SIZE 27 // 0-25 for 'a'-'z', index 26 for numbers/other chars

typedef struct file //single linked list
{
    char f_name[20]; // stores the filenames
    struct file *link; //points to the next file node
}F_node;

// Level 2: Which file has this word, and how many times?
typedef struct SubNode {
    char filename[64];         // Name of the file (e.g. "file1.txt")
    int word_count;            // How many times the word appears in this file
    struct SubNode *sub_link;  // Pointer to the next file
} SubNode;

// Level 1: The unique word itself
typedef struct MainNode {
    char word[50];              // The word string (e.g. "apple")
    int file_count;             // In how many different files does it exist?
    SubNode *sub_link;          // Pointer to head of the file list (SubNodes)
    struct MainNode *main_link; // Pointer to next word in this hash bucket
} MainNode;

// The Hash Table: An array of pointers to MainNodes
typedef struct {
    MainNode *table[HASH_SIZE]; // table[0] is 'a', table[1] is 'b', etc.
} HashTable;

//input file validation
void validate_files(int argc, char *argv[], F_node **head);
int check_extension(char *filename);
int check_duplicates(F_node *head, char *filename);
int insert_last(F_node **head, char *filename);
int isExist(char *filename);

//creat data base
int create_database(HashTable *HT_arr, F_node *head);
void initializeHashTable(HashTable *HT_arr);
int get_index(char *word);

void display_database(HashTable *HT_arr);

#endif