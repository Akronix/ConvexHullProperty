/*
 * test_heap.cpp
 *
 * Descp: File for testing the heap ADT
 *
 ******************************************************************************
 *
 ******************************************************************************
 * Pre: some tests
 *
 * Post: If the tests were ok or not, and the print of the heaps.
 *
 ******************************************************************************
 *  Created on: 14-03-2014
 *      Author: Abel Serrano
 */

#include "heap.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* timer and random number */
#include <assert.h>       /* asserts */
#include <iostream>
#include <unistd.h>		/* For sleep()*/

typedef bool (*ArrayOfTests[]) (); 
using namespace std;

void printHeap(heap<int> h)
{
	int lvlcount = 1, nextlvl = 1;  //For printing one line per level.
	int counter = 0;
	
	while (!h.isEmpty())
	{
		cout << h.deleteMin() << "   ";
		lvlcount--;
		if (lvlcount == 0)
		{
			cout << endl;
			lvlcount = nextlvl *= 2;
		}
		++counter;
		
	}
	cout << endl << "The number of elements in the heap is: " << counter << endl;
	cout << endl;
}

/** Testing constructors **/
bool test0()
{
	heap<int> h1;
	h1.insert(3);
	h1.insert(7);
	h1.insert(5);
	h1.insert(2);
	h1.insert(1);
	h1.insert(8);
	h1.insert(4);
	printHeap(h1);
	
	int array[] = {3,7,5,2,1,8,4};
	heap<int> h1Array(array,7);
	printHeap(h1Array);
	
	return (h1==h1Array);
	
	heap<int> h2;
	h2.insert(12);
	h2.insert(11);
	h2.insert(11);
	h2.insert(7);
	h2.insert(18);
	h2.insert(15);
	h2.insert(6);
	h2.insert(5);
	h2.insert(14);
	h2.insert(11);
	printHeap(h2);
	
	int array2[] = {12,11,11,7,18,15,6,5,14,11};
	heap<int> h2Array(array2,10);
	printHeap(h2Array);
	
	assert(h2==h2Array);

	return true;
}

bool test1()
{
	heap<int> h;
	h.insert(8);
	h.insert(3);
	h.insert(2);
	h.insert(1);
	cout << "For testing heap:" << endl;
	printHeap(h);
	int solution[] = {1,2,3,8};
	heap<int> h2(solution,4);
	cout << "For solution heap:" << endl;
	printHeap(h2);
	assert (h==h2);
	return true;
}

bool test2()
{
	heap<int> h;
	h.insert(6);
	h.insert(15);
	h.insert(9);
	h.insert(10);
	h.insert(8);
	h.insert(3);
	cout << "For testing heap:" << endl;
	printHeap(h);
	int solution[] = {3,8,6,15,10,9};
	heap<int> h2(solution,6);
	cout << "For solution heap:" << endl;
	printHeap(h2);
	return h==h2;
}

bool test3()
{
	int init[] = {10,13,25,55,23,33,30,66,74,51,49,36,34,44};
	heap<int> h(init,14);
	h.deleteMin();
	h.deleteMin();
	cout << "For testing heap:" << endl;
	printHeap(h);
	
	int solution[] = {23,34,25,55,44,33,30,66,74,51,49,36};
	heap<int> h2(solution,12);
	cout << "For solution heap:" << endl;
	printHeap(h2);
	return h==h2;
}

bool test4()
{
	int init[] = {3,8,6,15,10,9};
	heap<int> h(init,6);
	h.deleteMin();
	h.deleteMin();
	cout << "For testing heap:" << endl;
	printHeap(h);
	
	int solution[] = {8,10,9,15};
	heap<int> h2(solution,4);
	cout << "For solution heap:" << endl;
	printHeap(h2);
	return h==h2;
}

/**
 * Test with random numbers and max of heap
 */
bool test5()
{
	// Random numbers test (hard tests start here)
	cout << "-->Now we go with random numbers<--" << endl;
	heap<int> h1;
	
	int randomArray[heap<int>::MAX_HEAP];
	for (int i = 0; i<heap<int>::MAX_HEAP; i++)
	{
		int randn = rand() % 100 + 1; // randn in the range from 1 to 100
		randomArray[i] = randn;
		h1.insert(randn);
	}
	
	printHeap(h1);
	
	heap<int> h1Array(randomArray, heap<int>::MAX_HEAP);
	printHeap(h1Array);
	
	assert (h1 == h1Array);
	return true;
}

int main(int argc, char **argv)
{
	time_t timer, beginning_time = time(NULL);
	
	/* initialize random seed: */
	srand (beginning_time);
  
	cout << "Testing minHeaps..." << endl << endl;
	
	//function<bool()>tests[] = {test1,test2,test3,test4}; //using #include <functional>
	// bool *(test[]) () => array of function returning bool pointer => ILLEGAL
	//bool *test() []; => function returning and array of bool pointers => ILLEGAL
	// bool *test[]() => array of functions returning a bool pointer => ILLEGAL
	
	ArrayOfTests tests = {test0,test1,test2,test3,test4,test5}; /* No need to put &test1 since the standard says that a function name in this context is converted to the address of the function */
	const int NUM_TESTS = 6;
	
	for (int i = 0; i<NUM_TESTS; i++)
	{
		cout << "Starting test number " << i+1 << endl;
		if (tests[i]())
			cout << "The test " << i+1 << " was successfully passed!" << endl;
		else
			cout << "The test " << i+1 << " throw an incoherence" << endl;
		cout << "==================================================" << endl << endl;
	}
	
	cout << "--------------->¡¡¡TEST PASSED!!!<---------------" << endl << endl;
	
	timer = difftime(time(NULL),beginning_time);
	cout << "Seconds elapsed for this test: " << timer << endl;
	
	return 0;
	
}
