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
 * Version 1.2 :
 * Some possible improvements from the Classes & Data structures in c++ book:
 * 		->No swaps needed since we can compare the elements before to find the right place in the heap.
 * 		->Constructor of a heap with n elements from an array (no heap) in O(n)
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
heap<T>::heap(const heap& otherHeap)
{
	last = otherHeap.last;
	for (int i = 1; i<=last; ++i)
		this->cont[i] = otherHeap.cont[i];
}

/**
 * It applies the heapify function: check children and parent, and swap with the min. if any child is lower.
 * Pre: A subtree is a heap, except for the node in the argument, which is looking its place up to down
 * Post: A subtree which is a heap
 */
template <class T>
void heap<T>::heapify(const int subtreeRoot, T temp)
{
	int i = subtreeRoot;
	bool heap_property = false;
	
	while (i<=last/2 && !heap_property)	//heapifying if we are not in the leaves and heap property is not accomplished
	{
		int min; //index of the min between left and right children
		if (!(cont[2*i]>cont[2*i+1]) || (2*i == last))	//if left is lower or equal than right or there is no right child
			min =  2*i;									//min is the left child
		else
			min = 2*i+1;								//else, min is the right child.
			
		heap_property = !(temp > cont[min]);	//heap property := temp is lower or equal than min of its children
		if (!heap_property)
		{
			cont[i] = cont[min];			//min. child go up one level
			i = min;						//to move on the index to the min. child.
		}
	}
	
	cont[i] = temp;	//Either we i is a leave or we got the heap property with cont[i] and we place here the previous last.
	
}

/* Constructor of a heap with n elements from an array in O(n) */
template <class T>
heap<T>::heap(const T array[], const int n)
{
	/* Copying array content into the heap array container */
	last=n;
	for (int i = 0, j = 1; i<n; i++, j++ )
		cont[j] = array[i];
	
	/* Variables definition */
	int parentIndex;
	
	//(We start assuming leafs (cont[last/2 +1]...cont[last]) are subheaps with just one node.
	//From there we keep making subheaps upwards, merging like this all the suheaps until we reach the top.
	//Finally we obtain a heap we all the elements of the array. This is O(n/2)
	for ( parentIndex = last / 2; parentIndex >= 1; --parentIndex)
	{
		heapify(parentIndex,cont[parentIndex]);
	}
}

/*
 * Not needed anymore since we got the function argument in insert and a temp local variable in deleteMin
 * where we can compare the element we want to place until we find the right place for it. Avoiding to 
 * do swaps in the process, and therefore, improving in efficiency.
 * It's one assignment instruction the difference, but, be aware that now we are storing any data type,
 * since simple integers until long data structures, as long as they have implemented the > operator.*/
/*template <class T>
static void swap_heap(T& x, T& y)
{
	T temp = x;
	x = y;
	y = temp;
}*/


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
	T lastElement = cont[last];	//temporal storing of the previous last element
	last--;
	heapify(1,lastElement);
	
	return root;
}

template <class T>
bool heap<T>::isEmpty() const
{
	return !last;
}

template <class T>
bool heap<T>::operator==(const heap<T>& h2) const
{
	if (this->last == h2.last)
	{
		heap<T> h1_copy (*this), h2_copy(h2);
		bool equal = true;
		while (!h1_copy.isEmpty() && equal)
			equal = h1_copy.deleteMin() == h2_copy.deleteMin();
		return equal;
	}
	else
		return false;
}

