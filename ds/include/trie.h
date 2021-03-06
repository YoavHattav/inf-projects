#ifndef __TRIE_H__
#define __TRIE_H__

#include <stddef.h> /* size_t */

typedef enum Status
{
    SUCC,
    FAIL
} status_t;

typedef enum Bool
{
    FALSE,
    TRUE
} bool_t;

typedef enum availability {TAKEN, AVAILABLE} availability_t;

typedef struct Trie trie_t;

/*
* TrieCreate() - 
* Returns pointer to the Trie, will return NULL if failed. 
* complexity of malloc();       
*/
trie_t *TrieCreate(size_t height);

/*
* TrieDetroy() -
* Destroys and frees Trie from memory.
* undefined behaviour for @trie NULL pointer
* complexity: free();                  
*/
void TrieDestroy(trie_t *trie);

/*
* TrieInsert() -
* Inserts a new trie element.
* undefined behaviour for @trie NULL pointer
* complexity: malloc();                  
*/
status_t TrieInsert(trie_t *trie, const unsigned char *ip);

/*
* TrieCountLeafs() -
* Counts the number of occupied leafs in the trie.
* undefined behaviour for @trie NULL pointer
* complexity: O(n);                  
*/
size_t TrieCountOccupiedLeafs(const trie_t *trie);

void TrieFreeLeaf(trie_t *trie, unsigned char *ip);

void TrieNextAvailable(trie_t *trie, unsigned char *ip_allocated);

availability_t TrieIsAvailable(const trie_t *trie, unsigned char *ip);

#endif 

