#include <stdio.h>

#include "../include/trie.h"

#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
#define UNUSED(x) (void)(x)
#define RUN_TEST(test)\
{\
  if(test)\
  {\
    printf(GREEN);\
    printf("SUCCESS\n");\
    printf(RESET);\
  }\
  else\
  {\
    printf(RED);\
    printf("FAIL \n");\
    printf(RESET);\
  }\
}

static void TestCreate()
{
	size_t height = 5;
	trie_t *tree = TrieCreate(height);
	printf("Create/Destroy\n");

	RUN_TEST(0 == TrieCountOccupiedLeafs(tree));

	TrieDestroy(tree);
}

static void TestInsert()
{
	size_t height = 6;
	trie_t *tree = TrieCreate(height);

	unsigned char ip1[4] = {255, 188, 240, 10};
	unsigned char ip2[4] = {255, 188, 240, 75};
	unsigned char ip3[4] = {255, 188, 240, 32};
	unsigned char ip4[4] = {255, 188, 240, 43};
	unsigned char ip5[4] = {255, 188, 240, 65};
	unsigned char ip6[4] = {255, 188, 240, 7};

	printf("Insert\n");

	RUN_TEST(SUCC == TrieInsert(tree, ip1));
	RUN_TEST(SUCC == TrieInsert(tree, ip2));
	RUN_TEST(SUCC == TrieInsert(tree, ip3));
	RUN_TEST(SUCC == TrieInsert(tree, ip4));
	RUN_TEST(SUCC == TrieInsert(tree, ip5));

	RUN_TEST(TAKEN == TrieIsAvailable(tree, ip1));
	RUN_TEST(TAKEN == TrieIsAvailable(tree, ip2));
	RUN_TEST(AVAILABLE == TrieIsAvailable(tree, ip6));

	RUN_TEST(5 == TrieCountOccupiedLeafs(tree));
	TrieFreeLeaf(tree, ip1);

	RUN_TEST(4 == TrieCountOccupiedLeafs(tree));
	RUN_TEST(AVAILABLE == TrieIsAvailable(tree, ip1));

	TrieDestroy(tree);
}

static void TestAvailability()
{
	size_t height = 3;
	trie_t *tree = TrieCreate(height);

	unsigned char ip0[4] = {255, 188, 240, 0};
	unsigned char ip1[4] = {255, 188, 240, 1};
	unsigned char ip2[4] = {255, 188, 240, 2};
	unsigned char ip3[4] = {255, 188, 240, 3};
	unsigned char ip4[4] = {255, 188, 240, 4};
	unsigned char ip5[4] = {255, 188, 240, 5};
	
	printf("AVAILABLEITY\n");

	RUN_TEST(SUCC == TrieInsert(tree, ip0));
	RUN_TEST(SUCC == TrieInsert(tree, ip1));
	RUN_TEST(SUCC == TrieInsert(tree, ip2));
	RUN_TEST(SUCC == TrieInsert(tree, ip3));
	RUN_TEST(SUCC == TrieInsert(tree, ip4));
	RUN_TEST(SUCC == TrieInsert(tree, ip5));
	
	printf("tree->root->direction[0]->state should be TAKEN\ntree->root->direction[1]->state should be AVAILABLE\n");

	TrieDestroy(tree);
}

int main()
{
	TestCreate();
	TestInsert();
	TestAvailability();

	return 0;
}
