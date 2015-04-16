/*
 * heap.cpp
 * 
 * This is the implementation file with the c++ code for the operations for this ADT.
 * The heap is implemented with an array, following this:
 * 	For a node i, an array P:
 *	• left child is P[2i]
 *	• right child at P[2i + 1]
 *	• parent is P[i/2]
 * AND
 *  heap-propery is committed:
 * 		for every node i:
 * 			P[i] <= P[2i]
 * 			P[i] <= P[2i+1]
 * 
 * Version 1.1 : 
 * 		->Made class template to contain any data type.
 * 
 * Some possible improvements (not implemented yet) from the Classes & Data structures in c++ book:
 * 		->One-assignment swap
 * 		->Constructor of a heap with n elements in one array in O(n)
 ******************************************************************************
 *  Created on: 13-03-2014
 *      Author: Abel Serrano
 */

using namespace std;

template <class T>
heap<T>::heap()
{
	last=0;
}

template <class T>
heap<T>::heap(T array[])
{
	last=array[0];
	for (int i = 1; i<=last; i++)
	{
		cont[i] = array[i];
	}
}

template <class T>
static void swap_heap(T& x, T& y)
{
	T temp = x;
	x = y;
	y = temp;
}

template <class T>
void heap<T>::insert(const T& x)
{
	++last;
	
	int i = last;
	while (i>1 && cont[i/2]>x)	//looking for the right place for x
		{
			cont[i] = cont[i/2]; //swap parent with its children
			i = i/2;			//up to the next parent
		}
	cont[i] = x;				//Found where x is less than its parent, place here.
}

template <class T>
T heap<T>::deleteMin()
{
	T root = cont[1];
	cont[1] = cont[last];
	last--;
	int i = 1;
	bool heap_property = false;
	
	while (i<=last/2 && !heap_property)	//heapifying 
	{
		int min;
		if (!(cont[2*i]>cont[2*i+1]) || (2*i == last))
			min =  2*i;
		else
			min = 2*i+1;
		heap_property = !(cont[i] > cont[min]); 
		if (!heap_property)
		{
			swap_heap(cont[min],cont[i]);
			i = min;
		}
	}
	
	return root;
}

template <class T>
bool heap<T>::isEmpty()
{
	return !last;
}

template <class T>
bool heap<T>::operator==(const heap<T>& h2) const
{
	if (this->last == h2.last)
	{
		bool equal = true;
		for (int i = 1; i<=this->last && equal; i++)
			equal = this->cont[i] == h2.cont[i];
		return equal;
	}
	else
		return false;
}

