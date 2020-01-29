/*********************************/
/*    Data Structures            */
/*    sorts API                  */
/*    Author : Yoav Hattav       */
/*    Reviewed By:               */
/*    Date:      05/01/2020      */
/*                               */
/*********************************/

#ifndef __SORTS_H__
#define __SORTS_H__

#include <stddef.h> /* size_t */

typedef int (*compare_func_ptr)(const void *data1, const void *data2);

void BubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

int CountingSort(const int *arr, size_t size, int min, int max, int *res);

int RadixSort(unsigned int *arr, size_t size, unsigned int num_of_bits);

void MergeSort(int *src_arr, int *temp_arr, size_t size);

void QuickSort(void *base, size_t num_of_memb, size_t elem_size, compare_func_ptr user_cmp);

void *BinarySearch(void *arr, size_t elem_size, size_t num_of_elem,
 int (*cmp)(const void *data1, const void *data2, const void *param), const void *data, const void *param);

void *JumpSearch(void *arr, size_t elem_size, size_t num_of_elem,
 int (*cmp)(const void *data1, const void *data2, const void *param), const void *data, const void *param);

#endif
