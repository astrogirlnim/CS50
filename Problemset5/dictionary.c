// Implements a dictionary's functionality

//Dictionary notes: "mispelling" means a word is not in the dictionary provided
//Each word contains letters and possibly apostrophes (but not at the first position)

#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 33;

// Hash table
node *table[N]; //set hash table to null initially

int recursive_check(node *current_node, const char *word);
int recursive_delete(node *current_node);

//FUNCTIONS:


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Get word hash
    int hash_index = hash(word);

    node *current_node = table[hash_index]; //Keeps track of the current node

    //Compare words in linked list at that index (recursive)
    if (recursive_check(current_node, word) == 1)
    {
        return true;
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    //Hash function: djb2, courtesy of http://www.cse.yorku.ca/~oz/hash.html.
    unsigned int hash1 = 5381;
    int c;

    while ((c = *word++))
    {
        hash1 = ((hash1 << 5) + hash1) + tolower(c);
    }
    return hash1 % N; //Get the modulo of the hash
}



// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r"); //open the file
    char word_buffer[LENGTH + 1]; //buffer to store each word during read

    //Check memory
    if (dic == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    //Scan through the file line by line
    while (fscanf(dic, "%s\n", word_buffer) != EOF)
    {
        //While we haven't reached the end of the file:

        //Allocate memory for a new node
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            //check memory
            free(new_word);
            return new_word;
        }

        //Put word buffer in node
        strcpy(new_word -> word, word_buffer);

        //Get the hash (index which corresponds to bucket number)
        int bucket_index = hash(new_word -> word);

        //Put the node in the hash table
        if (table[bucket_index] != NULL)
        {
            //nth hash array element is not empty

            //Append node to beginning of the linked list
            new_word -> next = table[bucket_index];
            table[bucket_index] = new_word;
        }
        else
        {
            //Empty nth hash array element

            //No appending to linked list
            new_word -> next = NULL;

            //Make array index equal to the node
            table[bucket_index] = new_word;
        }

    }


    fclose(dic);
    return true;
}



// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //Count the number of lines (words) in the hash table

    unsigned int line_count = 0; //line counter

    for (int i = 0; i < N; i++)
    {
        //iterate through each bucket
        node *current_buckets = table[i]; //a bucket is set to a temporary variable

        while (current_buckets != NULL)
        {
            line_count++;
            current_buckets = current_buckets -> next;
        }
    }


    if (line_count != 0)
    {
        //If there are words in the dictionary, return the number of words.
        return line_count;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int del; //initialize delete boolean

    //Iterate and free
    for (int i = 0; i < N; i++)
    {
        //Node to keep track of current node
        node *current_node = table[i];
        del = recursive_delete(current_node);
        free(current_node);
    }

    if (del == 1)
    {
        return true;
    }
    return false;
}


//HELPER FUNCTIONS

//Recursively checks if words matches that in a node
int recursive_check(node *current_node, const char *new_word)
{
    while (current_node !=  NULL)
    {
        if (strcasecmp(current_node -> word, new_word) == 0)
        {
            //If the string matches a dictionary word, return
            return 1;
        }
        else
        {
            recursive_check(current_node -> next, new_word);
        }
    }
    //compares base case (if current_node == NULL)
    return 0;
}


int recursive_delete(node *current_node)
{
    //Handle base case
    if (current_node == NULL)
    {
        free(current_node);
        return 1;
    }

    //Free all elements of the linked list
    node *temp = current_node; //temp node to keep track of current
    recursive_delete(temp -> next);

    //Free the current node
    free(temp);
    return 0;
}