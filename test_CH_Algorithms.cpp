/*
 * test_CH_Algorithms.cpp
 *
 * Descp: 
 *  Executable for testing the HullProperty-finders algorithms
 *
 ******************************************************************************
 *
 ******************************************************************************
 * Pre: 
 * 		<some tests
 *
 * Post:
 * 		>If the tests were ok or not
 *
 ******************************************************************************
 *  Created on: 02-04-2014
 *      Author: Abel Serrano
 */

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream
#include "CH_Algorithms.cpp"
#include <vector>
#include <deque>

//Variables to select which algorithm is goint to be debugged
#define TEST_ITERATIVE
#define TEST_DIVIDE_CONQUEST

typedef bool (*ArrayOfTests[]) ();

using namespace std;

void printDeque2(deque<Point2f> s)
{
	cout << "Points of this path: ";
	ostringstream string_point;
	
	for (auto it = begin(s); it != end(s); ++it)
	{
		string_point.str("");	//Initialize stream
		string_point << '(' << it->x() << ',' << it->y() << ')'; //Construct the string in the form: (x,y) for each point
		cout << string_point.str() << ", ";						//Print the stream into the default output
	}
		
	cout << endl;
}


void printVector2(vector<Point2f> s)
{
	cout << "Points of this path: ";
	ostringstream string_point;
	
	for (auto it = begin(s); it != end(s); ++it)
	{
		string_point.str("");	//Initialize stream
		string_point << '(' << it->x() << ',' << it->y() << ')'; //Construct the string in the form: (x,y) for each point
		cout << string_point.str() << ", ";						//Print the stream into the default output
	}
		
	cout << endl;
}

#ifdef	TEST_ITERATIVE
static bool test_print_deque()
{
	deque<Point2f> test;
	Point2f p1(1,1);
	Point2f p2(2,2);
	Point2f p3(3,3);
	test.push_front(p3);
	test.push_front(p2);
	test.push_front(p1);
	
	printDeque2(test);
	
	return true;
}

static bool test_iterative_lower()
{
	Point2f p1(0,0);
	Point2f p2(1,-1);
	Point2f p3(1.25,2);
	Point2f p4(1.75,0);
	Point2f p5(2.25,1);
	Point2f p6(2.75,-0.75);
	Point2f p7(3,0.75);
	Point2f obstacle[] = {p1,p2,p3,p4,p5,p6,p7};
	deque<Point2f> deque_output;
	deque_output = LowerHull (obstacle, 7);
	cout << "The algorithm output was -> ";
	printDeque2(deque_output);
	
	
	deque<Point2f> expected_output;
	expected_output.push_back(p7);
	expected_output.push_back(p6);
	expected_output.push_back(p2);
	expected_output.push_back(p1);
	cout << "The expect output was -> ";
	printDeque2(expected_output);
	
	return (expected_output == deque_output);
}

static bool test_iterative_upper()
{
	Point2f p1(0,0);
	Point2f p2(1,-1);
	Point2f p3(1.25,2);
	Point2f p4(1.75,0);
	Point2f p5(2.25,1);
	Point2f p6(2.75,-0.75);
	Point2f p7(3,0.75);
	Point2f obstacle[] = {p1,p2,p3,p4,p5,p6,p7};
	deque<Point2f> deque_output;
	deque_output = UpperHull (obstacle, 7);
	cout << "The algorithm output was -> ";
	printDeque2(deque_output);
	
	
	deque<Point2f> expected_output;
	expected_output.push_back(p1);
	expected_output.push_back(p3);
	expected_output.push_back(p7);
	cout << "The expect output was -> ";
	printDeque2(expected_output);
	
	return (expected_output == deque_output);
}

/**
 * In this test, we expect to get the path with lowest length between the lower hull and the upper hull, by the iterative algorithms.
 * The input points are sorted.
 */
bool test_iterative_hull_sorted()
{
	Point2f p1(0,0);
	Point2f p2(1,-1);
	Point2f p3(1.25,2);
	Point2f p4(1.75,0);
	Point2f p5(2.25,1);
	Point2f p6(2.75,-0.75);
	Point2f p7(3,0.75);
	Point2f obstacle[] = {p1,p2,p3,p4,p5,p6,p7};
	vector<Point2f> vector_output;
	vector_output = IterativeConvexHull (obstacle, 7);
	cout << "The algorithm output was -> ";
	printVector2(vector_output);
	
	vector<Point2f> expected_output;
	expected_output.push_back(p1);
	expected_output.push_back(p3);
	expected_output.push_back(p7);
	expected_output.push_back(p6);
	expected_output.push_back(p2);
	cout << "The expect output was -> ";
	printVector2(expected_output);
	
	return (expected_output == vector_output);
}

/**
 * In this test, we expect to get the path with lowest length between the lower hull and the upper hull, by the iterative algorithms.
 * The input points are sorted.
 */
bool test_iterative_hull_sorted2()
{
	Point2f p1(-4,-3);
	Point2f p2(-1.4,0.9);
	Point2f p3(-1.4,-0.2);
	Point2f p4(-1,2);
	Point2f p5(-0.5,0.7);
	Point2f p6(-0.4,-1.2);
	Point2f p7(-0.23,1.45);
	Point2f p8(0.33333,0.487);
	Point2f p9(0.95,-1);
	Point2f p10(1,2);
	Point2f p11(1.43,0.3);
	Point2f p12(1.8,1.45);
	Point2f p13(1.85,-2);
	Point2f p14(2,2);
	Point2f p15(4,3);
	
	Point2f obstacle[] = {p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15};
	vector<Point2f> vector_output;
	vector_output = IterativeConvexHull (obstacle, 15);
	cout << "The algorithm output was -> ";
	printVector2(vector_output);
	
	vector<Point2f> expected_output;
	expected_output.push_back(p1);
	expected_output.push_back(p4);
	expected_output.push_back(p15);
	expected_output.push_back(p13);
	cout << "The expect output was -> ";
	printVector2(expected_output);
	
	return (expected_output == vector_output);
}

/**
 * In this test, we expect to get the path with lowest length between the lower hull and the upper hull, by the iterative algorithms.
 * The input points are unsorted.
 */
bool test_iterative_hull_unsorted()
{
	Point2f p1(0,0);
	Point2f p2(1,-1);
	Point2f p3(1.25,2);
	Point2f p4(1.75,0);
	Point2f p5(2.25,1);
	Point2f p6(2.75,-0.75);
	Point2f p7(3,0.75);
	Point2f obstacle[] = {p5,p4,p2,p6,p3,p1,p7};
	vector<Point2f> vector_output;
	vector_output = IterativeConvexHull (obstacle, 7);
	cout << "The algorithm output was -> ";
	printVector2(vector_output);
	
	
	vector<Point2f> expected_output;
	expected_output.push_back(p1);
	expected_output.push_back(p3);
	expected_output.push_back(p7);
	expected_output.push_back(p6);
	expected_output.push_back(p2);
	cout << "The expect output was -> ";
	printVector2(expected_output);
	
	return (expected_output == vector_output);
}
#endif

#ifdef TEST_DIVIDE_CONQUEST
/*********************** NOW, TESTS FOR ********************
 ***********************************************************
 ************** DIVIDE AND CONQUER ALGORITHM ***************
 ***********************************************************
 */
bool test_dc_1 ()
{
	Point2f p1(0.15,0.15);
	Point2f p2(1,-1);
	Point2f p3(1.25,2);
	Point2f p4(1.75,0);
	Point2f p6(2.75,-0.75);
	Point2f p7(3,0.75);
	Point2f obstacle[] = {p1,p2,p3,p4,p6,p7};
	vector<Point2f> vector_output;
	vector_output = DivideAndConquestConvexHull (obstacle, 6);
	cout << "The algorithm output was -> ";
	printVector2(vector_output);
	
	
	vector<Point2f> expected_output;
	expected_output.push_back(p1);
	expected_output.push_back(p3);
	expected_output.push_back(p7);
	expected_output.push_back(p6);
	expected_output.push_back(p2);
	cout << "The expect output was -> ";
	printVector2(expected_output);
	
	return (expected_output == vector_output);

}

bool test_dc_2 () //trivial one, just to try if this works with small sets
{
	Point2f p1(1,2);
	Point2f p2(1.75,3);
	Point2f p3(3,1);
	Point2f p4(4,4);
	Point2f obstacle[] = {p1,p2,p3,p4};
	vector<Point2f> vector_output;
	vector_output = DivideAndConquestConvexHull (obstacle, 4);
	cout << "The algorithm output was -> ";
	printVector2(vector_output);
	
	vector<Point2f> expected_output;
	expected_output.push_back(p1);
	expected_output.push_back(p2);
	expected_output.push_back(p4);
	expected_output.push_back(p3);
	cout << "The expect output was -> ";
	printVector2(expected_output);
	return (expected_output == vector_output);
}

/**
 * Equivalent to test_iterative_hull_unsorted
 */
bool test_dc_3 () //7 points
{
	Point2f p1(0,0);
	Point2f p2(1,-1);
	Point2f p3(1.25,2);
	Point2f p4(1.75,0);
	Point2f p5(2.25,1);
	Point2f p6(2.75,-0.75);
	Point2f p7(3,0.75);
	Point2f obstacle[] = {p1,p5,p4,p2,p6,p3,p7};
	vector<Point2f> vector_output;
	vector_output = DivideAndConquestConvexHull (obstacle, 7);
	cout << "The algorithm output was -> ";
	printVector2(vector_output);
	
	vector<Point2f> expected_output;
	expected_output.push_back(p1);
	expected_output.push_back(p3);
	expected_output.push_back(p7);
	expected_output.push_back(p6);
	expected_output.push_back(p2);
	cout << "The expect output was -> ";
	printVector2(expected_output);
	
	return (expected_output == vector_output);
}

/**
 * Equivalent to test_iterative_hull_sorted2
 */
bool test_dc_4 () //hard one. 15 points. unsorted.
{
	Point2f p1(-4,-3);
	Point2f p2(-1.4,0.9);
	Point2f p3(-1.4,-0.2);
	Point2f p4(-1,2);
	Point2f p5(-0.5,0.7);
	Point2f p6(-0.4,-1.2);
	Point2f p7(-0.23,1.45);
	Point2f p8(0.33333,0.487);
	Point2f p9(0.95,-1);
	Point2f p10(1,2);
	Point2f p11(1.43,0.3);
	Point2f p12(1.8,1.45);
	Point2f p13(1.85,-2);
	Point2f p14(2,2);
	Point2f p15(4,3);
	
	Point2f obstacle[] = {p12,p5,p15,p4,p8,p6,p7,p2,p9,p1,p11,p10,p13,p14,p3};
	vector<Point2f> vector_output;
	vector_output = DivideAndConquestConvexHull (obstacle, 15);
	cout << "The algorithm output was -> ";
	printVector2(vector_output);
	
	vector<Point2f> expected_output;
	expected_output.push_back(p1);
	expected_output.push_back(p4);
	expected_output.push_back(p15);
	expected_output.push_back(p13);
	cout << "The expect output was -> ";
	printVector2(expected_output);
	return (expected_output == vector_output);
}

#endif

int main(int argc, char **argv)
{

#ifdef TEST_ITERATIVE
	cout << "Testing iterative Convex hull algorithms..." << endl << endl;
	
	ArrayOfTests tests = {test_print_deque,test_iterative_upper,test_iterative_lower,
		test_iterative_hull_sorted,test_iterative_hull_sorted2,test_iterative_hull_unsorted}; 
	/* No need to put &test1 since the standard says 
	that a function name in this context is converted to the address of the function */

	const int NUM_TEST_IT = 6;
	
	for (int i = 0; i<NUM_TEST_IT; i++)
	{
		cout << "Starting test number " << i+1 << endl;
		if (tests[i]())
			cout << "The test " << i+1 << " was successfully passed!" << endl;
		else
			cout << "The test " << i+1 << " throw an incoherence" << endl;
		cout << "==================================================" << endl << endl;
	}
#endif

#ifdef TEST_DIVIDE_CONQUEST
	cout << "Testing D&C Convex hull algorithms..." << endl << endl;
	
	ArrayOfTests test_dc = {test_dc_1,test_dc_2,test_dc_3,test_dc_4};

	const int NUM_TEST_RE = 4;
	
	for (int i = 0; i<NUM_TEST_RE; i++)
	{
		cout << "Starting test number " << i+1 << endl;
		if (test_dc[i]())
			cout << "The test " << i+1 << " was successfully passed!" << endl;
		else
			cout << "The test " << i+1 << " throw an incoherence" << endl;
		cout << "==================================================" << endl << endl;
	}
#endif
	
	return 0;
}


 

