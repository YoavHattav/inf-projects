/*********************************/
/*    Data Structures            */
/*    sorts API                  */
/*    Author : Yoav Hattav       */
/*    Reviewed By:               */
/*    Date:      05/01/2020      */
/*                               */
/*********************************/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */
void ArrayPrinter(int *arr);

void BubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

int CountingSort(const int *arr, size_t size, int min, int max, int *res);

#endif
