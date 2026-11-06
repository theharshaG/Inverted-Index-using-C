#include"inverted.h"
void free_database(HashTable *HT_arr)
{
    if (HT_arr == NULL)
        return;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        MainNode *m_temp = HT_arr->table[i];

        while (m_temp != NULL)
        {
            MainNode *next_main = m_temp->main_link; // Save next word node

            // 1. Free all SubNodes for this word first
            SubNode *s_temp = m_temp->sub_link;
            while (s_temp != NULL)
            {
                SubNode *next_sub = s_temp->sub_link; // Save next sub node
                free(s_temp);
                s_temp = next_sub;
            }

            // 2. Free the MainNode itself
            free(m_temp);

            m_temp = next_main;
        }

        // Set bucket pointer to NULL
        HT_arr->table[i] = NULL;
    }
}
void free_file_list(F_node **head)
{
    if (head == NULL || *head == NULL)
        return;

    F_node *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->link; // Advance head
        free(temp);            // Free current node
    }
}