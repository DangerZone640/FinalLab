#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26

struct TrieNode{
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};
// Trie structure
struct Trie{
    struct TrieNode *root;
};
struct TrieNode *createTrieNode(){
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node){
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++){
            node->children[i] = NULL;
        }
    }
    return node;
}

// Initializes a trie structure
struct Trie *createTrie(){
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    if (trie){
        trie->root = createTrieNode();
    }
    return trie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word){
    struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++){
        int index = word[i] - 'a';
        if (!current->children[index])
            current->children[index] = createTrieNode();
        current = current->children[index];
    }
    current->count++;
}

void deallocateTrieNode(struct TrieNode *node)
{
    if (node)
        for (int i = 0; i < ALPHABET_SIZE; i++)
            deallocateTrieNode(node->children[i]);
        free(node);
    
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie){
    if (pTrie){
        deallocateTrieNode(pTrie->root);
        free(pTrie);
    }
    return NULL;
}

int countOccurrences(struct TrieNode *node, char *word){
    if (!node)
        return 0;
    if (*word == '\0')
        return node->count;
    int index = *word - 'a';
    return countOccurrences(node->children[index], word + 1);
}
// computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word){
    if (!pTrie || !word)
        return 0;
    struct TrieNode *current = pTrie->root;
    return countOccurrences(current, word);
}

// Reads the dictionary file and returns the number of words
// Also, stores the words in pInWords array
int readDictionary(char *filename, char **pInWords){
    int numWords = 0;
    FILE *file = fopen(filename, "r");
    if (file){
        char word[100];
        while (fscanf(file, "%s", word) != EOF){
            pInWords[numWords] = strdup(word);
            numWords++;
        }
        fclose(file);
    }
    return numWords;
}


int main(void)
{
    char *inWords[256];

    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
