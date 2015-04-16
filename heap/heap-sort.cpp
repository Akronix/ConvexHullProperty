/*
 * heap-sort.cpp
 *
 * Descp: Sorting algorithm using a heap.
 * 
 * Complexity: O(nlogn)
 *
 ******************************************************************************
 *
 ******************************************************************************
 * Pre: sequence of ints to sort
 * 	formally: array of n ints
 * 
 * Post: ints already sorted, from less to most.
 * 	formally: for (i:= 1; i<n-1)
 * 				[i-1] <= [i] <= [i+1] 
 *
 ******************************************************************************
 *  Created on: 09-03-2014
 *      Author: Abel Serrano
 */

#include "heap.h"

using namespace std;

template<typename T>
void heapSort(T toSort[], int n)
{
	heap<T> h;
	for (int i = 0; i<n && i<heap<T>::MAX_HEAP; i++)
		h.insert(toSort[i]);
	for (int i = 0; i<n && i<heap<T>::MAX_HEAP; i++)
		toSort[i] = h.deleteMin();
	return;
}
