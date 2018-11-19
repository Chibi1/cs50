// Implements a dictionary's functionality

#include <ctype.h>
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
node *hashTable[ALPHALEN + 1] = {NULL};

// declare dictionary size to zero
int dictSize = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // conversion to lower case for dictionary comparison
    int len = strlen(word);
    char *_word = calloc(1, sizeof(int) * len);
    strcpy(_word, word);
    int i = 0;
	while (_word[i] != '\0')
	{
    	if (_word[i] >= 'A' && _word[i] <= 'Z')
    	{
        	_word[i] = _word[i] + 32;
    	}
      	i++;
	}

    // get ascii from passed word
    int first;
    first = _word[0];

    // get hash from passed word
    int hash = first - 97;

    // set cursor to first position of linked list in corresponding hash location
    node *cursor = hashTable[hash];

    // loop each node in linked list
    bool match;
    while (cursor != NULL)
    {
        // compare word to dictionary entry
        char *nextEntry = cursor->entry;
        if (strcasecmp(_word, nextEntry) == 0)
        {
            match = true;
            free(_word);
            return true;
        }
        else
        {
            match = false;

            // if not match, move cursor to next node in linked list
            cursor = cursor->next;
        }
    }

    // if the cursor reaches the end of the linked list without finding a match
    if (cursor == NULL && match == false)
    {
        free(_word);
        // printf("[...]\n");
        return false;
    }

    return NULL;
}

bool loaded;
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // declaring word variable
    char word[LENGTH + 1] = {};
    // int n = LENGTH;

    // open file
    FILE *inFile = fopen(dictionary, "r");

    // success check
    if (inFile == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    // loop dictionary file
    while (fscanf(inFile, "%s", word) != EOF)
    {
        // printf("%s\n", word);

        // increment dictionary size
        dictSize++;

        // // make memory for new word node
        node *newNode = calloc(1, sizeof(node));
        if (newNode == NULL)
        {
            unload();
            return false;
        }

        // nullify string
        int len = strlen(word);
        word[len] = '\0';

        // assign node.entry the new found word
        strcpy(newNode->entry, word);

        // get first letter of word
        int first;
        first = newNode->entry[0];

        // get hash
        int hash = first - 97;

        // insert new node into linked list at corresponding hash location
        if (hashTable[hash] == NULL) // if nothing yet at index location
        {
            newNode->next = NULL;
            hashTable[hash] = newNode;
        }
        else
        {
            newNode->next = hashTable[hash];
            hashTable[hash] = newNode;
        }
    }
    fclose(inFile);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        // printf("\n%i\n", dictSize);
        return dictSize;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor;
    node *temp;
    // char *test;
    // test = hashTable[0]->next->entry;
    // printf("\n%s\n", test);
    // loop through hash table indexes
    for (int i = 0; i < LENGTH + 1; i++)
    {
        // set cursor to start of linked list
        cursor = hashTable[i];

        // check for entry at first node of every hash index
        while (cursor == NULL)
        {
            free(cursor);
            i++;
            // set cursor to start of linked list
            cursor = hashTable[i];
        }

        // loop through every node
        while(cursor != NULL)
        {
            // attach temp cursor to cursor
            temp = cursor;

            // move cursor to next node
            cursor = cursor->next;

            // free node the temp cursor is still pointing to
            free(temp);
        }
        // free(hashTable);
        return true;
    }
    return false;
}
