// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

//creating a linked lists
typedef struct node
{
    char word[46];
    struct node *next;
}
node;

//hash table
node hashtable[71545]; //71545
//number of words in the dictionary
long nword = 0;
//check if dictionary is loaded
bool check1;

//hash function
//name of this function is djb2
//http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++) != 0)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % 71545;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char loword[strlen(word) + 1];
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        loword[i] = tolower(word[i]);
    }
    loword[i] = '\0';
    int x = hash(loword);
    for (node *ptr = hashtable[x].next; ptr != NULL; ptr = ptr -> next)
    {
        if (strcmp(ptr -> word, loword) == 0)
        {
            return true;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    char wordd[46];

    FILE *fl = fopen(dictionary, "r");
    if (!fl)
    {
        printf("couldn't open the dictionary file\n");
        return false;
    }

    while (fscanf(fl, "%s", wordd) != EOF)
    {
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            unload();
            printf("couldn't create a node\n");
            return false;

        }
        strcpy(newnode -> word, wordd);

        int x = hash(wordd);

        if (hashtable[x].next != NULL)
        {
            newnode -> next = hashtable[x].next;
            hashtable[x].next = newnode;
        }
        else
        {
            hashtable[x].next = newnode;
            newnode -> next = NULL;
        }
        nword++;
    }

    //check if it sucessfully read all the words and reahced end of the file
    if (feof(fl))
    {
        check1 = true;
        fclose(fl);
        return true;
    }
    else
    {
        fclose(fl);
        return false;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (check1 == true)
    {
        return nword;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *ptr;
    node *nextnode;
    for (int i = 0; i < 71545; i++)
    {
        ptr = hashtable[i].next;
        while (ptr != NULL)
        {
            nextnode = ptr -> next;
            free(ptr);
            ptr = nextnode;
        }
    }

    if (ptr == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
