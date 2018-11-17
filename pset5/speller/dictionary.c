// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

#define ALPHALEN 26

typedef struct node
{
    char entry[LENGTH + 1];
    struct node *next;
} node;

// declaring hash table
node *hashTable[ALPHALEN] = {NULL};

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    for(int i; i < strlen(word); i++)
    {
        word[i] = tolower(word[i]);
    }
    // get hash from passed word
    int first;
    first = word[0];
    // set cursor to first position of linked list in corresponding hash location
    node *cursor = hashTable[first];
    // loop each node in linked list
    while (cursor != NULL)
    {
        // compare word to dictionary entry
        if (strcasecmp(word, newNode->next) == 0)
        {
            // if match, move cursor to next node in linked list
            cursor = cursor->next;
        }
    }
    // if the cursor reaches the end of the linked list without finding a match
    if (cursor == NULL)
    {

    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // declaring word variable
    char *word = NULL;
    // open file
    FILE *inFile = fopen(dictionary, "r");
    // success check
    if (inFile == NULL)
    {
        printf("Could not open file");
        return 1;
    }
    // loop dictionary file
    while (fgets(word, LENGTH, inFile) != NULL)
    {
        // make memory for new word node
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            unload();
            return false;
        }
        // nullify string
        int len = strlen(word);
        word[len + 1] = '\0';
        // assign node.entry the new found word
        strcpy(newNode->entry, word);
        // get first letter of word
        int first;
        first = newNode->entry[0];
        // insert new node into linked list at corresponding hash location
        newNode->next = hashTable[first];
        hashTable[first] = newNode;

    }


    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
