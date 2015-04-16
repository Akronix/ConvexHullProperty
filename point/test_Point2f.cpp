/*
 * test_Point2f.cpp
 *
 * Descp:
 *  File for testing the ADT: Point2f
 *
 ******************************************************************************
 *
 ******************************************************************************
 * Pre: Some tests for all functions of Point2f
 *
 * Post: Results of the tests
 *
 ******************************************************************************
 *  Created on: 02-04-2014
 *      Author: Abel Serrano
 */

#include "Point2f.cpp"
#include <iostream>
#include <assert.h>

typedef bool (*ArrayOfTests[]) (); 
using namespace std;

bool testConstructors()
{
	cout << "Testing constructors..." << endl;
	
	Point2f p1;
	assert(p1.x()==0);
	assert(p1.y()==0);
	cout << "Default values for a point: " << p1.x() << ", " << p1.y() << endl;
	
	Point2f	p2(12.6f,13.0f);
	assert(p2.x()==12.6f);
	assert(p2.y()==13.0f);
	cout << "Values for point 2: " << p2.x() << ", " << p2.y() << endl;
	
	Point2f p3(p2);
	assert(p3.x()==p2.x());
	assert(p3.y()==p2.y());
	cout << "Values for point 3: " << p3.x() << ", " << p3.y() << endl;
	
	return true;
	
}

bool testAssignment()
{
	cout << "Testing assignments..." << endl;
	
	Point2f	p1(12.6f,13.0f);
	
	Point2f p2;
	p2 = p1;
	assert(p1.x()==p2.x());
	assert(p1.y()==p2.y());
	cout << "Values for point source: " << p1.x() << ", " << p1.y() << endl;
	cout << "Values for point destination: " << p2.x() << ", " << p2.y() << endl;
	
	Point2f p3(5.0f,5.0f);
	p3 = p1;
	assert(p3.x()==p1.x());
	assert(p3.y()==p1.y());
	cout << "Values for point source: " << p1.x() << ", " << p1.y() << endl;
	cout << "Values for point destination: " << p3.x() << ", " << p3.y() << endl;
	
	cout << "Testing setters..." << endl;
	cout << "Value x before setting : " << p3.x() << endl;
	p3.x(158.7f);
	cout << "Value x after setting : " << p3.x() << endl <<endl;
	assert(p3.x()==158.7f);
	
	cout << "Value y before setting : " << p3.y() << endl;
	p3.y(0.001f);
	cout << "Value y after setting : " << p3.y() << endl <<endl;	
	assert(p3.y()==0.001f);
	
	cout << "Values for point destination: " << p3.x() << ", " << p3.y() << endl;
	
	return true;
	
}

bool testComparison()
{
	cout << "Testing comparisons..." << endl;
	
	Point2f p1, p2;
	assert(p1==p2);
	cout << "Equals for default constructor" << endl;
	
	Point2f p11 (0.556f,0.2254f), p12(4486.0f,4532.0f);
	p11 = p12;
	assert(p11==p12);
	cout << "Equals after assignment" << endl;
	
	Point2f p13 (0.55f,0.224f), p14(p13);
	assert(p13==p14);
	cout << "Equals after copy constructor" << endl;
	
	Point2f p3(0.05f+0.05f,0.0f), p4(0.1f,0.0f);
	cout << "p3-x value is: " << p3.x() << endl;
	cout << "p4-x value is: " << p4.x()	<< endl;
	assert(p3==p4);
	cout << "Equals for equivalent coord (1)" << endl;
	
	Point2f p7(0.0f,0.05f), p8(0.0f,0.025f*2);
	assert(p7==p8);
	cout << "Equals for equivalent coord (2)" << endl;
	
	float p9_x= ((((((0.7f - 0.5f) -0.1f) -0.05f) -0.02f)-0.01f)-0.01f);
	Point2f p9(p9_x,0.0f), p10(0.01f,0.0f);
	cout << "p9-x value is: " << p3.x() << endl;
	cout << "p10-x value is: " << p4.x()	<< endl;
	assert(p9==p10);
	cout << "Equals for equivalent coord (3)" << endl;
	
	Point2f p5(0.01f, 80000.0f), p6(0.0099f,80001.0f);
	if (!(p5==p6))
		cout << "Not equals two numbers very close each other" << endl;
	else
		return false;
	
	return true;	
}

bool testDistancesBetweenPoints()
{
	Point2f p1(0,0), p2(3,4);
	float d;
	
	d = p1.distanceBetweenTwoPoints(p2);
	assert(d==5.0f);
	
	Point2f p3(3.5,1.25), p4(-1,-1);
	d = p3.distanceBetweenTwoPoints(p4);
	assert(d==5.0311529f);
	
	Point2f p5(5,8), p6(11,2);
	d = p5.distanceBetweenTwoPoints(p6);
	assert(d==8.485281374f);
	
	return true;
}


int main(int argc, char **argv)
{
	cout << "Testing functions of Point3f ADT..." << endl << endl;
	
	ArrayOfTests tests = {testConstructors,testAssignment,testComparison,testDistancesBetweenPoints};
	
	for (int i = 0; i<4; i++)
	{
		cout << "Starting test number " << i+1 << endl;
		if (tests[i]())
			cout << "The test " << i+1 << " was successfully passed!" << endl;
		else
			cout << "The test " << i+1 << " throw an incoherence" << endl;
		cout << "==================================================" << endl << endl;
	}
	
	return 0;
	
}

