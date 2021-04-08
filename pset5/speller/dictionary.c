// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; //string
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Declare number of words loaded into dictionary to count for Size function
unsigned int no_of_words = 0;

// Hash function - Hashes word to a number
// Credit: https://gist.github.com/choaimeloo/ffb96f7e43d67e81f0d44c08837f5944
unsigned int hash(const char *word)
{
    unsigned int h = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        h = (h << 2) ^ word[i];
    }
    return h % N;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Creates copy of word on which hash function can be performed
    int word_length = strlen(word);
    char word_copy[word_length + 1];
    for (int i = 0; i < word_length; i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    // Adds null terminator to end string
    word_copy[word_length] = '\0';

    // Initializes index for hashed word
    int hash_value = hash(word_copy);

    // Access linked list at that index in hash table
    // Sets cursor to point to same address as hash table bucket
    node *cursor = table[hash_value];

    // Traverse linked list, looking for the word (strcasecmp)
    while (cursor != NULL)
    {
        if (strcasecmp (word_copy, cursor->word) == 0)
        return true;

        else
        cursor = cursor->next;
    }
    // Return false if cursor reaches end of list and word has not been found
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dictf = fopen(dictionary, "r");

    //Check if file is available
    if (dictf == NULL)
    {
        printf("Couldn't find dictionary file\n");
        return false;
    }

    // Read string from file one at a time
    // and continue til the end of file
    while (true)
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node));

        // Error message if create new node unsuccessfully
        if (n == NULL)
        {
            printf("Could not allocate memory\n");
            return false;
        }

        // Scan words from dictionary, and input each word to new node
        int end_of_file = fscanf(dictf, "%s", n->word);
        n->next = NULL;


        // Stop while loop when reach end of file
        if (end_of_file == EOF)
        {
            free(n);
            break;
        }

         // Count words loaded successfully
        no_of_words++;

        // Hash word to obtain hash value
        int hash_value = hash(n->word);

        // Declare "head" pointer pointing to bucket
        node *head = table[hash_value];

        //If bucket is empty, insert first node
        if (head == NULL)
        {
            table[hash_value] = n;
        }

        // If bucket is not empty, insert new node
        // into the front of linked-list
        else
        {
          //  printf("word %s hash %d\n",n->word,hash_value);
            n->next = head; // n now points at the first element (element that head points to)
            table[hash_value] = n; // set n as the new first element of the bucket
        }
    }
    // Close file dictionary after loading
    fclose (dictf);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return no_of_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loop through all the buckets of hash table
    for (int i = 0; i < N; i++)
    {
        // Create cursor and tmp to traverse through linked list
        node *cursor = table[i]; // Cursor pointer pointing to table[i] bucket
        node *tmp = cursor; // Temp pointer pointing to the same place as cursor pointer

        // Free node pointed by tmp after moving cursor 1 node ahead
        // to keep track of the list
        // one->two
        while (cursor != NULL)
        {
            tmp = cursor; // Temp pointer points to the same place as cursor
            cursor = cursor->next; // Cursor pointer points to the next element
            free(tmp); // Free temp pointer
        }
    }
    return true;
}
