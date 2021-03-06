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
trie_t *TrieCreate();

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
status_t TrieInsert(trie_t *trie, char *str);

/*
* TrieIsEmpty() -
* Checks if the trie is empty.
* undefined behaviour for @trie NULL pointer
* return value:
    -TRUE
    -FALSE
* complexity: O(1);                  
*/
bool_t TrieIsEmpty(const trie_t *trie);

/*
* TrieSize() -
* Counts the number of elements in the trie.
* undefined behaviour for @trie NULL pointer
* complexity: O(n);                  
*/
size_t TrieSize(const trie_t *trie);

/*
* TrieCountLeafs() -
* Counts the number of leafs in the trie.
* undefined behaviour for @trie NULL pointer
* complexity: O(n);                  
*/
size_t TrieCountLeafs(const trie_t *trie);

void TrieFreeLeaf(trie_t *trie, char *str);

void TrieFirstAvailable(trie_t *trie, char *buffer);

availability_t TrieIsAvailable(trie_t *trie, char *str);

#endif 

