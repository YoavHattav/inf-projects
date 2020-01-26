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

typedef int (*cmp_func_t)(const void *data1, const void *data2, void *param);

void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size, cmp_func_t cmp, void *param);

void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size, cmp_func_t cmp, void *param);

#endif
