/*
 * main.cpp
 *
 * Descp: 
 *  Solving: "The robot path planning problem"
 *  
 *  In this assignment, we are required to implement a program which look for
 * the shortest path between two points, avoiding an obstacle located in the middle
 * of those points.
 * 
 * The problem definition is read from a text file called test_cases.in, following
 * the syntax described in readFile.
 *
 ******************************************************************************
 *
 ******************************************************************************
 * Pre: <Departure (A)
 * 		<Destination (B)
 * 		<array of points which are the vertices of the the obstacle
 *
 * Post:
 * 		>Convex hull of A U B U Obstacle
 * 		>Shortest path joining A and B, dodging the obstacle 
 *
 ******************************************************************************
 *  Created on: 02-04-2014
 *      Author: Abel Serrano
 */

#include "CH_Algorithms.cpp"	//source file for the convex hull algorithms
#include <vector>		// std::vector for sets of points
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream
#include <fstream>		// To read file
#include <cassert>		// assert function

using namespace std;

const char* file = "test_cases.in";
const unsigned int MAX_POINTS_OBS = 15;

struct testCase
{
	Point2f init, dest;
	int nPointsObstacle;
	Point2f obstacle[MAX_POINTS_OBS];
};

/**
 * Syntax of the input file is the following:
 * NUMCASES N -> N: integer which represent number of cases
 * case i begin -> i: declarates that case i is starting to be defined
 * initx inity -> two floats: initx and inity, which defines the initial point
 * destx desty -> two floats: destx and desty, which defines the destination point
 * n -> n: integer which defines the number of points for defining the obstacle
 * subsequently, there are n pairs of x and y coordinates for each point defining the obstacle.
 * end -> defines the end for case i 
 */
bool readFile(const char* filePath, testCase*& cases, unsigned int &ncases)
{
	ifstream file;
	file.open(filePath,ios::in);
	string line;
	ncases = 0;
	
	if ( file.is_open() )
	{
		if ( getline (file,line) && (line.substr(0,8)=="NUMCASES") )
		{
			ncases = stoi(line.substr(8));
			
			cases = new testCase[ncases];
			cout << "Number of cases defined: " << ncases << endl;
			
			for (unsigned int counter = 0; counter < ncases; ++counter)
			{
				while (getline (file,line) && !(line.substr(0,4)=="case"))
				; //Between cases definition; it avoids comments, empty lines or whatever is not case a definition.
				
				cout << "Reading case " << counter << endl;
				
				testCase *newCase = &(cases[counter]);
				string::size_type sz;
				
				getline (file,line);
				float xf = (stof(line,&sz));
				newCase->init.x(xf);
				newCase->init.y(stof(line.substr(sz)));
				
				getline (file,line);
				newCase->dest.x(stof(line,&sz));
				newCase->dest.y(stof(line.substr(sz)));
				
				getline (file,line);
				int n = stoi(line);
				newCase->nPointsObstacle = n;
				
				for (int i = 0; i<newCase->nPointsObstacle; i++)
				{
					getline (file,line);
					newCase->obstacle[i].x(stof(line,&sz));
					newCase->obstacle[i].y(stof(line.substr(sz)));
				}						

				getline (file,line); //reading end
			}	      		
		file.close();
		return true;
		}
		else
		{
			cerr << "Number of cases is not defined" << endl;
			return false;
		}
	}
	else
	{
		cerr << "Input file couldn't be read" << endl;
		return false;
	}
}

/**
 * Print the points stored in vector<Point2f>
 */
void printVector(vector<Point2f> s)
{
	ostringstream string_point;
	
	for (unsigned int i = 0; i < s.size(); ++i)
	{
		string_point.str("");	//Initialize stream
		string_point << "p" << i;
		string_point << '(' << s[i].x() << ',' << s[i].y() << ')'; //Construct the string in the form: (x,y) for each point
		std::cout << string_point.str() << ", ";					//Print the stream into the default output
	}
		
	std::cout << std::endl;
}

/**
 * Calculates the length of the path summing the distances between every segment of the path.
 */
float distance(const std::vector<Point2f> &path)
{
	float acum = 0;
	for (unsigned int i = 0; i < (path.size()-1); ++i)
		acum += path[i].distanceBetweenTwoPoints(path[i+1]);
	return acum;
}


/**
 * Note: initialPoint != destinationPoint, so at least, size(convexHullSet) > 1
 * /return: the shortest (less length) between the the upper and the lower mid hulls.
 * 		In case their length are equal it returns any of them.
 */
std::vector<Point2f> calculateShortestMidHull(const std::vector<Point2f> &convexHullSet, const Point2f &initialPoint,
		const Point2f &destinationPoint)
{
	//Declarations
	std::vector<Point2f> upperMidHull, lowerMidHull;
	
	//Just checking if the convexHullSet has initialPoint correctly defined as the first point of the vector
	assert(convexHullSet[0] == initialPoint);
	
	//Now, we calculate both convex hull mids (lower and upper) from the initial point to the destination point
	//Upper
	int j = 0;
	while(!(convexHullSet[j] == destinationPoint))
	{
			upperMidHull.push_back(convexHullSet[j]);
			j = (j+1) % convexHullSet.size();
	}
	upperMidHull.push_back(convexHullSet[j]); //add destination point too
	cout << "Upper mid convex hull is: ";
	printVector(upperMidHull);
	
	//Lower
	int k = 0;
	while(!(convexHullSet[k] == destinationPoint))
	{
			lowerMidHull.push_back(convexHullSet[k]);
			k = (k+convexHullSet.size()-1) % convexHullSet.size();
	}
	lowerMidHull.push_back(convexHullSet[k]); //add destination point too
	cout << "Lower mid convex hull is: ";
	printVector(lowerMidHull);
	
	//Finally, we return the shortest (i.e. less size) beetwen the two mids
	float distanceUpperMidHull = distance(upperMidHull);
	float distanceLowerMidHull = distance(lowerMidHull);
	
	if (distanceUpperMidHull <= distanceLowerMidHull)
	{
		cout << "The upper mid hull is the shortest path, with length: " << distanceUpperMidHull << endl;
		return upperMidHull;
	}
	else
	{
		cout << "The lower mid hull is the shortest path, with length: " << distanceLowerMidHull << endl;
		return lowerMidHull;
	}
}

/**
 * main function.
 * Declares variables, call to readFile and to the CH algorithms.
 * Get the output, compares it and show to the user.
 */
int main(int argc, char **argv)
{
	//Declarations
	Point2f initialPoint, destinationPoint;
	testCase* cases;
	unsigned int ncases,n;
	Point2f pointsToGetHull[MAX_POINTS_OBS+2];
	vector<Point2f> d_c_path, iterative_path;
		//Functions used:
		bool readFile(const char* filePath, testCase*& cases, unsigned int &ncases);
		std::vector<Point2f> DivideAndConquestConvexHull (Point2f P[], int numberPoints);
		std::vector<Point2f> IterativeConvexHull (Point2f P[], int numberPoints);
		std::vector<Point2f> calculateShortestMidHull(const std::vector<Point2f> &convexHullSet, const Point2f &initialPoint,
		const Point2f &destinationPoint);
		void printVector(vector<Point2f> s);
	
	//read input
	cout << "Reading input from file: " << file << endl;
	if (readFile(file,cases,ncases))
	{
		cout << "==================================================" << endl << endl;
		
		//Executing read cases from the file
		for (unsigned int icases = 0; icases<ncases; icases++)
		{
			cout << "----->Running case " << icases << "<-----" << endl;
			
			initialPoint = cases[icases].init;
			destinationPoint = cases[icases].dest;
			n = cases[icases].nPointsObstacle;
			
			//Construct set union(obstacle, initialPoint, destinationPoint)
			pointsToGetHull[0] = initialPoint;
			for (unsigned int i = 0, j = 1; i<n; ++i, ++j)
				pointsToGetHull[j] = cases[icases].obstacle[i];
			pointsToGetHull[n+1] = destinationPoint;
			
			cout << "Points to be explored:";
			for (unsigned int i = 0; i<n+2; i++)
				cout << " ("<< pointsToGetHull[i].x() << "," << pointsToGetHull[i].y() << ")";
			cout <<endl;
			
			//Calculating path using iterative
			cout << "Calculating convex hull set by iterative algorithm..." << endl;
			
			iterative_path = IterativeConvexHull (pointsToGetHull, n+2);
			
			iterative_path = calculateShortestMidHull(iterative_path,initialPoint,destinationPoint);
				
			cout << "This is the final shortest path avoiding the obstacle found by iterative: ";
			printVector(iterative_path);
			
			cout << endl;
			
			cout << "---------------------------------------------------" << endl << endl;

			//Calculating path using divide and conquest
			cout << "Calculating convex hull set by divide and conquest algorithm..." << endl;
			
			d_c_path = DivideAndConquestConvexHull (pointsToGetHull, n+2);
			
			d_c_path = calculateShortestMidHull(d_c_path,initialPoint,destinationPoint);
				
			cout << "This is the final shortest path avoiding the obstacle found by divide & conquest algorithm: ";
			printVector(d_c_path);
			
			cout << "==================================================" << endl << endl;
			
			//Checking outputs
			assert(d_c_path == iterative_path);
			
			cout << "----->Done case: " << icases << "<-----" << endl;
			cout << "==================================================" << endl << endl;
		}
	}
	else //happened an error
	{
		return 1;
	}
	
	delete cases;
	return 0;
}

