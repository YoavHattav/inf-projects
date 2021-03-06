/*********************************/
/*    Heapify                    */
/*    Heap API                   */
/*    Author : Yoav Hattav       */
/*    Reviewed By:               */
/*    Date:      23/01/2020      */
/*                               */
/*********************************/

#ifndef __HEAPIFY_H__
#define __HEAPIFY_H__

#include <stddef.h> /* size_t */
#include "../include/priorityq.h"


void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size, compare_func_ptr cmp, void *param);

void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size, compare_func_ptr cmp, void *param);

#endif
