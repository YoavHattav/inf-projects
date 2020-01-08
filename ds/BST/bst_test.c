#include <stdio.h>






int CompareFunc(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	return (data1 > data2);
}

bst_t *TESTBSTCreate()
{

}

void TESTBSTDestroy()
{

}
int TESTBSTInsert()
{

}
void TESTBSTRemove()
{

}
bst_itr_t TESTBSTFind()
{

}
int TESTBSTForeach()
{

}
size_t TESTBSTSize()
{

}
int TESTBSTIsEmpty()
{

}
void *TESTBSTGetData()
{

}
bst_itr_t TESTBSTBegin()
{

}
bst_itr_t TESTBSTEnd()
{

}
bst_itr_t TESTBSTNext()
{

}
bst_itr_t TESTBSTPrev()
{

}
int TESTBSTIsSameItr()
{

}

int main()
{
	
	TESTBSTCreate();
	TESTBSTDestroy();
	TESTBSTInsert();
	TESTBSTRemove();
	TESTBSTFind();
	TESTBSTForeach();
	TESTBSTSize();
	TESTBSTIsEmpty();
	TESTBSTGetData();
	TESTBSTBegin();
	TESTBSTEnd();
	TESTBSTNext();
	TESTBSTPrev();
	TESTBSTIsSameItr();
	

}