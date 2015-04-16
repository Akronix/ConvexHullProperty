/*
 * test_heap-sort.cpp
 *
 * Descp: To test sorting by heaps (heap-sort.cpp source file)
 *
 ******************************************************************************
 *
 ******************************************************************************
 * Pre: some simple tests of sorting integers & floats.
 * 
 * Post: If the tests were ok or not, and the prints out of the numbers.
 *
 ******************************************************************************
 *  Created on: 09-03-2014
 *      Author: Abel Serrano
 */

#include <iostream>
#include "heap-sort.cpp"

using namespace std;

template<typename T>
bool areEqualArrays(T a1[], T a2[], int n)
{
	bool equal = true;
	for (int i = 0; equal && i<n; i++)
	{
		equal = a1[i] == a2[i];
	}
	
	return equal;
}


bool test(int numbers[], int arraySolution[], int n)
{
	cout << "The input array is:" << endl;
	for (int i = 0; i<n; i++)
		cout << numbers[i] << ", ";
	cout << endl;
	heapSort<int>(numbers,n);
	cout << "Sorted!:" << endl;
	for (int i = 0; i<n && i<heap<int>::MAX_HEAP; i++)
		cout << numbers[i] << ", ";
	cout << endl;
	return areEqualArrays(numbers,arraySolution,n);
}

bool test_floats(float numbers[], float arraySolution[], int n)
{
	cout << "The input array is:" << endl;
	for (int i = 0; i<n; i++)
		cout << numbers[i] << ", ";
	cout << endl;
	heapSort<float>(numbers,n);
	cout << "Sorted!:" << endl;
	for (int i = 0; i<n && i<heap<float>::MAX_HEAP; i++)
		cout << numbers[i] << ", ";
	cout << endl;
	return areEqualArrays(numbers,arraySolution,n);
}

bool test_floats_explicit_array(float numbers[],  float arraySolution[], int n)
{
	cout << "The input array is:" << endl;
	for (int i = 0; i<n; i++)
		cout << numbers[i] << ", ";
	cout << endl;
	
	heapSort<float>(numbers,n);
	cout << "Sorted!:" << endl;
	for (int i = 0; i<n && i<heap<float>::MAX_HEAP; i++)
		cout << numbers[i] << ", ";
	cout << endl;
	
	return areEqualArrays(numbers,arraySolution,n);
	
}

int main(int argc, char **argv)
{
	int array1[] = {8,14,2,3,23,-2};
	int array1Solution[] = {-2,2,3,8,14,23}; 
	if (test(array1,array1Solution,6))
		cout << "Test 1 was ok" << endl;
	else
		cout << "test 1 not passed" << endl;
	
	int array2[] = {1,1,1,1,2,0,3,3,3,0};
	int array2Solution[] = {0,0,1,1,1,1,2,3,3,3}; 
	if (test(array2,array2Solution,10))
		cout << "Test 2 was ok" << endl;
	else
		cout << "test 2 not passed" << endl;
	
	cout << "Now, go ahead with sorting floats: " << endl;
	float array3[] = {12.45f,0.004f,5.87f,5.86f,5.865f,-0.34f};
	float array3Solution[] = {-0.34f,0.004f,5.86f,5.865f,5.87f,12.45f}; 
	if (test_floats(array3,array3Solution,6))
		cout << "Test 3 was ok" << endl;
	else
		cout << "test 3 not passed" << endl;
	
	float array4[8];
	array4[0] = 0.0f;
	for (int i = 0,j = 1; i<8; i++, j++)
		array4[j] = array3[i];
	array4[7] = 54.5f;
	float array4Solution[] = {-0.34f,0.0f,0.004f,5.86f,5.865f,5.87f,12.45f,54.5f};
	if (test_floats_explicit_array(array4,array4Solution,8))
		cout << "Test 4 was ok" << endl;
	else
		cout << "test 4 not passed" << endl;
	
	return 0;
}

