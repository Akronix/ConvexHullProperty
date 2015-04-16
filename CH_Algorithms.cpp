/*
 * CH_Algorithms.cpp
 *
 * Descp: This module provides the implementation of some algorithms which solves the ConvexHull problem.
 * Either in an iterative way, either in a recursive way (divide and conquer)
 * 
 *
 ******************************************************************************
 *
 ******************************************************************************
 * Pre:
 * 	>A set of points, in an array form.
 * 	>The number of points in the set above.
 *
 * Post: 
 *  <std::vector of the points which represents the convex hull set.
 * 		conditions of output:
 * 			* The points in the vector are sorted in clockwise order from the first point until the last point
 * 			* The first point in the vector is the leftmost point
 *
 ******************************************************************************
 *  Created on: 02-04-2014
 *      Author: Abel Serrano
 * 
 * Possible improves:
 * -To use vector inside of iterative instead of deque
 * -To use pointers to the points of whole polygon inside D&C algorithm instead of local lists (more efficient)
 * 
 */
 
#include "point/Point2f.cpp"
#include "heap/heap-sort.cpp"
#include <deque>
#include <vector>
#include <stack>
#include <cmath> //for abs
#include <iostream>

#undef DEBUG //To activate or not the verbose mode

/************** DEBUG UTILITIES ***************/

#ifdef DEBUG
#include <string>
#include <sstream> 
#define writedbg( x ) std::cout << x
#define writelndbg( x ) std::cout << x << std::endl
#else
#define writedbg( x ) 
#define writelndbg( x ) 
#define printVectorDbg( x ) 
#endif

#ifdef DEBUG
void printVectorDbg(vector<Point2f> s)
{
	ostringstream string_point;
	
	for (auto it = begin(s); it != end(s); ++it)
	{
		string_point.str("");	//Initialize stream
		string_point << '(' << it->x() << ',' << it->y() << ')'; //Construct the string in the form: (x,y) for each point
		std::cout << string_point.str() << ", ";						//Print the stream into the default output
	}
		
	std::cout << std::endl;
}
#endif

/*****************************/


/************** ITERATIVE ALGORITHM ***************/

/**
 * Returns 1 if ABC forms a left turn
 * Returns -1 if ABC forms a right turn
 * Returns 0 if ABC forms a straight line
 */
static int turn(const Point2f& A,const Point2f& B,const Point2f& C)
{
	double result,t1,t2;
	
	//Calculates cross product for the three points
	t1 = (double) (B.x() - A.x()) * (C.y() - A.y());
	t2 = (double) (B.y() - A.y()) * (C.x() - A.x());
	result = t1 - t2;
	
	if (result > 0.0000001)
		return 1;
		
	else if (result < -0.0000001)
		return -1;
		
	else
		return 0;
}

std::deque<Point2f> UpperHull(Point2f L[], int n)
{
	Point2f last1 (L[0]), last2(L[1]), last3 ;// Last 3 points in the list 
	
	std::deque< Point2f > Lupper; //At least, it's going to store 3 points
	Lupper.push_back(last1);
	Lupper.push_back(last2);
	
	for (int i=2; i<n;i++)
	{
		Lupper.push_back(L[i]);
		last3 = L[i];
		while (Lupper.size() > 2 && turn(last1, last2, last3)>=0) //right turn is when the cross-product is <0
			{
				Lupper.pop_back(); //Remove last3 from deque
				Lupper.pop_back(); //Remove last2 from deque
				
				last2 = last1;		// last2 now is --last2 (i.e., last1)
				
				if (Lupper.size() > 1)
				{
					Lupper.pop_back();
					last1 = Lupper.back(); //this two lines is equivalent to say --last1 (last 1 is previous last1)
					Lupper.push_back(last2); //Restore previous last1
				}
				
				Lupper.push_back(last3); //Restore last3
			}
			
		//Advancing last points of the deque
		last1 = last2;
		last2 = last3;
	}
	return Lupper;
}

std::deque<Point2f> LowerHull(Point2f L[], int n)
{
	Point2f last1(L[n-1]), last2(L[n-2]), last3;
	
	std::deque< Point2f > LLower; //At least, it's going to store 3 points
	LLower.push_back(last1);
	LLower.push_back(last2);
	
	for (int i = n-3; i>=0; --i)
	{
		LLower.push_back(last3 = L[i]);
		while ( LLower.size() > 2 && turn(last1,last2,last3) >= 0)
		{
			LLower.pop_back(); //Remove last3 from deque
				LLower.pop_back(); //Remove last2 from deque
				
				last2 = last1;		// last2 now is --last2 (i.e., last1)
				
				if (LLower.size() > 1)
				{
					LLower.pop_back();
					last1 = LLower.back(); //this two lines is equivalent to say --last1 (last 1 is previous last1)
					LLower.push_back(last2); //Restore previous last1
				}
				
				LLower.push_back(last3); //Restore last3
		}
			
		//Advancing last points of the deque
		last1 = last2;
		last2 = last3;
		
	}
	
	return LLower;	
}

/**
 * Complexity: big theta(n)
 */
std::vector<Point2f> IterativeConvexHull (Point2f P[], int numberPoints)
{
	heapSort<Point2f>(P,numberPoints);
	
	std::deque<Point2f> Lupper = UpperHull(P,numberPoints);
	std::deque<Point2f> LLower = LowerHull(P,numberPoints);
	
	/* We want (upperHull U LowerHull) as output (sorted in clockwise order) */
	// We start copying Lupper to the output
	std::vector<Point2f> iterativeConvexHull(Lupper.begin(),Lupper.end());
	
	//And we add LLower except the first and the last point
	for (unsigned int i = 1; i < LLower.size()-1; i++)
		{	
			Point2f p = LLower[i];
			writelndbg("adding next point from lower to iterative hull: " <<  p.x() << ", "<< p.y());
			iterativeConvexHull.push_back(p);
		}
		
	return iterativeConvexHull;
}


/*****************************/


/************** DIVIDE AND CONQUER ALGORITHM ***************/

/**
 * Calculates the convex hull set for a given set of points, using a divide and conquer algorithm
 * Returns a vector which represents that set, sorted in clockwise order and starting with the 
 * leftmost point as first point of the vector
 */
std::vector<Point2f> DivideAndConquestConvexHull (Point2f P[], int numberPoints)
{
	//declarations
	std::vector<Point2f> DAndCRecursive (std::vector<Point2f> set);
		
	//Sorting input in ascending order of x-values (important because we want to split the sets with points from left to right)
	heapSort<Point2f>(P,numberPoints);
	Point2f leftmostPoint = P[0];
	
	// using iterator constructor to copy arrays:
	std::vector<Point2f> initialSet(P, P + numberPoints);
	writedbg("Set to get convex hull by D&C: ");
	printVectorDbg(initialSet);

	//Calculate actual convex hull set for this input set of points
	std::vector<Point2f> convexHullSet(DAndCRecursive(initialSet));
	
	//For convergence and more standard output, we want the leftmost point
	// to be the first point of the ouput vector, and the rest is sorted clockwise from it.
	std::vector<Point2f> outputConvexHullSet;
	outputConvexHullSet.reserve(convexHullSet.size());
	
	//First, we move to initial point:
	unsigned int indexLeftMost = 0;
	while (!(convexHullSet[indexLeftMost] == leftmostPoint))
		indexLeftMost = (indexLeftMost+1) % convexHullSet.size();
		
	//Second, we rebuild the output vector from that point
	for (unsigned int i = 0; i<convexHullSet.size(); i++)
		{
			outputConvexHullSet.push_back(convexHullSet[indexLeftMost]);
			indexLeftMost = (indexLeftMost+1) % convexHullSet.size();
		}
	
	writedbg("Convex Hull polygon, by divide and conquest algorithm, for this set of points is: ");
	printVectorDbg(outputConvexHullSet);
	
	
	return outputConvexHullSet;
}

/**
 * Base case: 3 points or less, this set of points always accomplish the convex hull property
 * Split step: Divide the initial set in subsets until we get sets in the base case.
 * Merge step: Produces an union of the subsets obtained above, keeping the convex hull property
 */
std::vector<Point2f> DAndCRecursive (std::vector<Point2f> set)
{
	void split(std::vector<Point2f>,std::vector<Point2f>&,std::vector<Point2f>&);
	std::vector<Point2f> merge(std::vector<Point2f>,std::vector<Point2f>);
	
	if (set.size() <= 3 )
		return set;
	else
	{
		std::vector<Point2f> L1, L2;
		split(set, L1, L2); 	//divide P into two distinct lists L1, L2
		return merge(DAndCRecursive(L1), DAndCRecursive(L2));
	}
}

/**
 * Divide a set of points in two halfs of subset of points
 */
void split(const std::vector<Point2f> initialSet,std::vector<Point2f> &subSetA,std::vector<Point2f> &subSetB)
{
	int half = initialSet.size() / 2;
	
	std::vector<Point2f>::const_iterator it = initialSet.begin();
	
	subSetA.assign(it,it+half);					//range version of assign, assigning half to subsetA
	subSetB.assign(it+half,initialSet.end());	//an the other half left to subsetB
	
	writedbg("Points of subsetA (just created after split): ");
	printVectorDbg(subSetA);
	writedbg("Points of subsetB (just created after split): ");
	printVectorDbg(subSetB);
}

/**
 * The merge step is the tricky one here
 * This function call, one by one to every step the algorithm needs to follow to merge two convex polygons.
 * They are:
 * 1) Sort de vertices, for both polygons, in clockwise
 * 2) Calculate the lower and upper tangents (bridges) to both polygons
 * 3) Create a new set which is the union of both subsets minus the points which are between the tangent points.
 */
std::vector<Point2f> merge(std::vector<Point2f> subSetA, std::vector<Point2f> subSetB)
{
	/*Declarations:*/
	std::vector<Point2f> mergeSet;
	mergeSet.reserve(subSetA.size()+subSetB.size()); // merge set needs, at most, the sum of the size of both subsets
	
	/*Declarations of functions */
	std::vector<Point2f> sortClockWise(std::vector<Point2f> set, int &indexLeftMost, int &indexRightMost);
	
	void upperTangentPoints(const std::vector<Point2f> subSetA, const std::vector<Point2f> subSetB,
	int indexRightMostA, int indexLeftMostB,
	int &tanPinA, int &tanPinB);
	//returns the tangent vertices for the upper tangent line in two last ints
	 
	void lowerTangentPoints(const std::vector<Point2f> &subSetA, const std::vector<Point2f> &subSetB,
	int indexRightMostA, int indexLeftMostB,
	int &tanPinA, int &tanPinB);
	//returns the tangent vertices for the lower tangent line in two last ints
	
	/* Declarations for indices */
	int upperTanPinA, upperTanPinB, lowerTanPinA, lowerTanPinB;
	int indexRightMostA, indexLeftMostA;
	int indexLeftMostB, indexRightMostB;
	
	//sort both subsets in clockwise and return indexes for leftmost and rightmost
	subSetA = sortClockWise(subSetA,indexLeftMostA,indexRightMostA);
	subSetB = sortClockWise(subSetB,indexLeftMostB,indexRightMostB);
	
	writedbg("Points of subsetA sorted in clockwise: ");
	printVectorDbg(subSetA);
	writedbg("Points of subsetB sorted in clockwise: ");
	printVectorDbg(subSetB);
	
	//calculate lower and upper tangents
	lowerTangentPoints(subSetA,subSetB,indexRightMostA,indexLeftMostB,lowerTanPinA,lowerTanPinB);
	upperTangentPoints(subSetA,subSetB,indexRightMostA,indexLeftMostB,upperTanPinA,upperTanPinB);
	
	writelndbg("Tangent points of lower tangent line to both subsets are: (" << subSetA[lowerTanPinA].x()
	<< ", " << subSetA[lowerTanPinA].y() << ") & (" 
	<< subSetB[lowerTanPinB].x() << ", " << subSetB[lowerTanPinB].y() << ")");
	
	writelndbg("Tangent points of upper tangent line to both subsets are: (" << subSetA[upperTanPinA].x()
	<< ", " << subSetA[upperTanPinA].y() << ") & (" 
	<< subSetB[upperTanPinB].x() << ", " << subSetB[upperTanPinB].y() << ")");
	
	//->merge two subsets given the upper and lower tangents into mergeSet
	int j,k;

	//int nPointsBetweenTangentPoints = 1 + std::abs(upperTanPinA-lowerTanPinA);
	for (j = lowerTanPinA; j != upperTanPinA; j = ((j+1)%subSetA.size()))
		mergeSet.push_back(subSetA[j]);
	
	//we add the upper tangent point for A as well (it was the exit condition for the loop)
	mergeSet.push_back(subSetA[j]);
	
	//nPointsBetweenTangentPoints = 1 + std::abs(upperTanPinB-lowerTanPinB);
	for (k = upperTanPinB; k != lowerTanPinB; k = (k+1)%subSetB.size())
		mergeSet.push_back(subSetB[k]);
		
	//we add the upper tangent point for B as well (it was the exit condition for the loop)
	mergeSet.push_back(subSetB[k]);
	
	mergeSet.shrink_to_fit(); /* we shrink the capacity of mergeset to its actual size, I consider this important since
								   we are using a recursive algorithm (expensive in memory) and the actual size and the
								   capacity may differ substantially*/
								
	
	writedbg("Points of merged set: ");
	printVectorDbg(mergeSet);
		
	return mergeSet;
}


/**
 * Sort the points of set in clockwise order, using cross product, and returns indices for leftmost and rightmost points.
 * Complexity: big theta(n)
 */
std::vector<Point2f> sortClockWise(std::vector<Point2f> set, int &indexLeftMost, int &indexRightMost)
{
	if (set.size() > 1)
	{
		//Declarations
		int indexNoClock, indexClock, prev_index;
		const int initial = 0;
		int setSize = set.size();
		std::vector<Point2f> setClockWise(setSize);
		std::stack<Point2f> lowerHalfClock;
		
		//Subsets have to be sorted in x-value ascending to able to sort clock wise.
		heapSort(set.data(),setSize);
		
		//Setting up certain variables
		indexClock = 0;
		indexLeftMost = initial;
		setClockWise[indexClock] = set[initial];
		prev_index = initial;
		indexNoClock = (prev_index+1)%setSize;
		
		// Going over every point of the input set and building the upper-half clockwise-sorted set
			//Looking for next point which makes a right turn from setClockWise[indexClock]
			//At the end of this loop:
			//prev_index will be the index in set which corresponds to the last point inserted in setClockWise
			//indexNoClock will be the index for the next point to look at in set
			//indexClock will be incremented by one
			//setClockWise[indexClock] will be updated to the next clockwise direction point
			bool doRightTurn = false;
			while (indexNoClock!=(setSize-1))
			{
				doRightTurn = turn(set[prev_index], set[indexNoClock], set[indexNoClock+1]) < 0;
				
				if (doRightTurn)
				{
					setClockWise[++indexClock] = set[indexNoClock];
					prev_index = indexNoClock;
				}
				else
					lowerHalfClock.push(set[indexNoClock]);
					
				++indexNoClock;
			}
			
			//Inserting rightmost point i.e. if (indexNoClock == (setSize-1))
			setClockWise[++indexClock] = set[indexNoClock];
			indexRightMost = indexClock;
		
		//The rest of the clockwise-sorted set is the lower half taken in reverse, so this can be easily added,
		//using the lowerHalfClock stack, previously used:
		while (!lowerHalfClock.empty())
		{
			setClockWise[++indexClock] = lowerHalfClock.top();
			lowerHalfClock.pop();		
		}
		
		return setClockWise;
	}
	else
	{
		indexLeftMost = 0;
		indexRightMost = 0;
		return set;
	}
}

/**
 * Calculates the tangent points for the lower tanget line between subSetA and subSetB.
 */
void lowerTangentPoints(const std::vector<Point2f> &subSetA, const std::vector<Point2f> &subSetB,
 int indexRightMostA, int indexLeftMostB,
 int &tanPinA, int &tanPinB)
{
	writelndbg("Calculating the lower tanget points...");
	
	//Function definitions
	bool isLowerTangent(const Point2f &p1, const Point2f &p2, const std::vector<Point2f> &s);
	bool noLowerTangentToA;
	bool noLowerTangentToB;
	
	int a = indexRightMostA; 
	int b = indexLeftMostB;
	
	writelndbg("index right most a:" << a << "- values :" << subSetA[a].x() << ", "<< subSetA[a].y());
	writelndbg("index left most b:" << b << "- values :" << subSetB[b].x() << ", "<< subSetB[b].y());
	
	do
	{
		noLowerTangentToA = !isLowerTangent(subSetA[a],subSetB[b],subSetA);
		while (noLowerTangentToA)
		{
			writelndbg("  incr a ");
			a = (a+1)%subSetA.size();
			noLowerTangentToA = !isLowerTangent(subSetA[a],subSetB[b],subSetA);
		}
		
		noLowerTangentToB = !isLowerTangent(subSetA[a],subSetB[b],subSetB);
		while (noLowerTangentToB)
		{
			writelndbg("  decr b");
			b = (b+subSetB.size()-1)%subSetB.size();
			noLowerTangentToB = !isLowerTangent(subSetA[a],subSetB[b],subSetB);
		}
		
		noLowerTangentToA = !isLowerTangent(subSetA[a],subSetB[b],subSetA);//b changed, so previously islowertangent isn't valid
		
	} while ( noLowerTangentToA || noLowerTangentToB);
	
	tanPinA = a;
	tanPinB = b;
	
	writelndbg("");
	writelndbg("These are the lower tangent points: subsetA[" << a << "], subsetB[" << b << "]");
	
	return;
}

/**
 * Check if the line defined by p1 and p2 has an y-value lower than every point in s.
 * Complexity: O(n), with n number of points in s.
 */
bool isLowerTangent(const Point2f &p1, const Point2f &p2, const std::vector<Point2f> &s)
{
	//Constructing uv line explicit equation f(x):y=mx+n
	writelndbg("is lower tangent?");
	
	//Calculating m (slope)
	float dx = p2.x() - p1.x(), dy = p2.y() - p1.y();
	if (dx == 0)  //dx = 0. we got a vertical line. not handled so far;
		{
			std::cerr << "Two points with same x value is not supported by divide and conquer algorithm" << endl;
			exit(1);
		}
	float m = dy / dx;
	writelndbg("This is m:" << m);
	
	//Calculating n
	float n = p1.y() - m * p1.x() ;
	writelndbg("This is n:" << n);

	//Now, we have to check if:
	// For all p in s: f(p.x) <= p.y
	//if true, we got a lower tangent
	bool isLineLowerThanPoint = true;
	for (std::vector<Point2f>::const_iterator it = s.begin(); it != s.end() && isLineLowerThanPoint; ++it)
	{
		writedbg("loop: ");
		float fpx = (it->x()) * m + n - 0.0001; //extra epsilon to avoid equals
		writelndbg("analyzing point: " << it->x() << ", " << it->y());
		isLineLowerThanPoint = (fpx < (it->y()));
	}
	writelndbg("islower return: " <<  isLineLowerThanPoint);

	return isLineLowerThanPoint;
}

/**
 * Calculates the tangent points for the upper tanget line between subSetA and subSetB.
 */
void upperTangentPoints(const std::vector<Point2f> subSetA, const std::vector<Point2f> subSetB,
 int indexRightMostA, int indexLeftMostB,
 int &tanPinA, int &tanPinB)
{
	writelndbg("Calculating the upper tanget points...");
	
	//Function definitions:
	bool isUpperTangent(Point2f p1, Point2f p2, std::vector<Point2f> s);
	bool noUpperTangentToA;
	bool noUpperTangentToB;
	int a = indexRightMostA;
	int b = indexLeftMostB;
	
	writelndbg("index right most a:" << a << "- values :" << subSetA[a].x() << ", "<< subSetA[a].y());
	writelndbg("index left most b:" << b << "- values :" << subSetB[b].x() << ", "<< subSetB[b].y());
	
	do
	{
		noUpperTangentToA = !isUpperTangent(subSetA[a],subSetB[b],subSetA);
		while (noUpperTangentToA)
		{
			writelndbg("  decr a ");
			a = (a+subSetA.size()-1)%subSetA.size();
			noUpperTangentToA = !isUpperTangent(subSetA[a],subSetB[b],subSetA);
		}
		
		noUpperTangentToB = !isUpperTangent(subSetA[a],subSetB[b],subSetB);
		while (noUpperTangentToB)
		{
			writelndbg("  incr b ");
			b = (b+1)%subSetB.size();
			noUpperTangentToB = !isUpperTangent(subSetA[a],subSetB[b],subSetB);
		}
		
		noUpperTangentToA = !isUpperTangent(subSetA[a],subSetB[b],subSetA);
	
	} while ( noUpperTangentToA || noUpperTangentToB);
	
	tanPinA = a;
	tanPinB = b;
	writelndbg("");
	writelndbg("These are the lower tangent points: subsetA[" << a << "], subsetB[" << b << "]");
	return;
}

/**
 * Check if the line defined by p1 and p2 has an y-value upper than every point in s.
 * Complexity: O(n), with n number of points in s.
 */
bool isUpperTangent(Point2f p1, Point2f p2, std::vector<Point2f> s)
{
	//Constructing uv line explicit equation f(x):y=mx+n
	writelndbg("is upper tangent?");

	//Calculating m (slope)
	float dx = p2.x() - p1.x(), dy = p2.y() - p1.y();
	if (dx == 0)  //dx = 0. we got a vertical line. not handled so far;
		{
			std::cerr << "Two points with same x value is not supported by divide and conquer algorithm" << endl;
			exit(1);
		}
	float m = dy / dx;
	writelndbg("This is m:" << m);
	
	//Calculating n
	float n = p1.y() - m * p1.x();
	writelndbg("This is n:" << n);
	
	//Now, we have to check if:
	// For all p in s: f(p.x) >= p.y
	//if true, we got a Upper tangent
	bool isLineUpperThanPoint = true;
	for (std::vector<Point2f>::iterator it = s.begin(); it != s.end() && isLineUpperThanPoint; ++it)
	{
		writedbg("loop: ");
		float fpx = (it->x()) * m + n + 0.0001; //extra epsilon to avoid equals
		writelndbg("analyzing point: " << it->x() << ", " << it->y());
		isLineUpperThanPoint = (fpx > (it->y()));
	}
	
	writelndbg("isUpper return: " <<  isLineUpperThanPoint);
	return isLineUpperThanPoint;
}
