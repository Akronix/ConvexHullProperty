/*
 * heap.h
 *
 *  This is a Minheap implementation which stores integer numbers.
 *  A minheap is a complete binary tree in which its internal nodes and
 * satisfying that every internal node in the graph stores a key
 * greater than or equal to its parent’s key.
 * 
 * This is the header file with the definitions for the operations for this ADT.
 *
 * Version 1.1 : 
 * 	->Made class template to contain any data type.
 * Version 1.2 :
 * 		->No swaps needed since we can compare the elements before to find the right place in the heap.
 * 		->Constructor of a heap with n elements from an array (no heap) in O(n)
 * 
 * Note that, in order to use compound data types (struct or class) for this template
 * class, you must overload the following operators:
 * 		=			Used to assign values into the heap and to swap or move values inside the heap.
 * 		>			Used to compare which element has got a key greater than the other.
 * 		==			Used to compare two heaps or for looking for an element		
 * 		
 ******************************************************************************
 *  Created on: 13-03-2014
 *      Author: Abel Serrano
 */

#ifndef heap_h
#define heap_h

template <class T>
class heap
{
	public:
	
	//maximum elements in the heap
	const static int MAX_HEAP = 30;
	
	//default constructor:
	heap();
	//copy constructor:
	heap(const heap& otherHeap);
	//Constructor of a heap with n elements from a random array in O(n)
	heap(const T array[], const int n);
	
	//overloading == operator
	bool operator==(const heap<T>& h2) const;
	
	void insert(const T& x);
	T deleteMin();
	bool isEmpty() const;
	
	private:
	union {			//last stored in cont[0] for saving memory
		int last;
		T cont[MAX_HEAP+1]; 
	};
	
	//Pre: for all i <> j in h, isheap(i); i.e. j doesn't accomplish heap property 
	void heapify(const int subtreeRoot, T temp);
	//Post: isheap(root)
};

#include "heap_v2.cpp"

#endif //heap_h
