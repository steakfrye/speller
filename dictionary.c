<<<<<<< HEAD
// Implements a dictionary's functionality
=======
// Implements a dictionary's functionality using a trie data structure
>>>>>>> 2930f00bb48c21d2c65597b28ef9d128d2449940

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

//create node
typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

//made with some help from https://www.geeksforgeeks.org/trie-insert-and-search/
//creates new node and sets to NULL
struct node *newNode(void)
{
    node *pNode = (node *)calloc(1, sizeof(node));

    if (pNode)
    {
        pNode->is_word = false;

        for(int i = 0; i < 27; i++)
            pNode->children[i] = NULL;
    }
    return pNode;
}
//recursive function to free node memory
void destroy(node *seek)
{
    //safeguard
    if(!seek) return;

    //iterate through each node
    for (int b = 0; b < 27; b++)
        destroy(seek->children[b]);
    //base case
    free(seek);
}

//define global variables
int wordCount = 0;
struct node *root;
int charIndex(char c) //converts char into an integer
{
    if (c == '\'') //including apostrophes
        return 26;
    else if (isalpha(c))
    {
        if (isupper(c))
            c += 32;
        c -= 97; //convert letter a to z into numbers 0 to 25
    }
    return c;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //create traveling node
    node *wordCheck = root;
    //iterate through each letter of the word
    for (int level = 0; level < strlen(word); level++)
    {
        int index = charIndex(word[level]);
        //read through children until end of word or returns NULL
        if (!wordCheck->children[index])
            return false; //letter not found
        wordCheck = wordCheck->children[index];
    }
    //word was found
    return(wordCheck != NULL && wordCheck->is_word);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //clear root node
    root = newNode();

    //open dictionary
    FILE * dict = fopen(dictionary, "r");
    if (!dict)
    {
        fclose(dict);
        return false;
    }

    //prepare to read through dictionary
    char* dword = malloc(LENGTH + 1); //set buffer for each word
    bool endOfDict = false;
    node *trav = root; //set traversal node to root

    //iterate through each character of dictionary
    while (fgets(dword, LENGTH + 1 , dict))
    {
        for (int r = 0; r < strlen(dword); r++)
        {
            if (isalpha(dword[r]) || dword[r] == '\'')
            {
               int dindex = charIndex(dword[r]);
                //is there already a node for that letter?
                if (!trav->children[dindex])
                   trav->children[dindex] = newNode();
                trav = trav->children[dindex];
            }
                //jump to next line, word is complete
            else if (dword[r] == '\n')
            {
                //prepare for next word
                trav->is_word = true;
                trav = root;
                wordCount++;
            }
        }
    }
    //close
    free(dword); //free malloc
    fclose(dict); //close dictionary
    if (wordCount > 0) //has the dictionary been read through?
        endOfDict = true;
    return(endOfDict);
}
//Returns number of words in dictionary else 0 if not yet loaded
unsigned int size(void)
{
    return(wordCount);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //use destroy function to unload root
    destroy(root);
    return true;
}
