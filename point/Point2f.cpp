#include "Point2f.h"
#include <cmath>

Point2f::Point2f(float x, float y)
{
	this->m_coord[0] = x;
	this->m_coord[1] = y;
}

Point2f::Point2f() : Point2f(0,0)
{
}

Point2f::Point2f(const Point2f& otherPoint) :           // Copy constructor
Point2f((otherPoint.m_coord[0]),(otherPoint.m_coord[1])) // Calling to the main constructor
{
}


Point2f& Point2f::operator=(const Point2f& rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    else
    {
    	this->m_coord[0] = rhs.m_coord[0];
    	this->m_coord[1] = rhs.m_coord[1];
    	return *this;
    }
}

bool Point2f::operator==(const Point2f &other) const
{
    if (this == &other)
    	return false;
    else
    	if (this == nullptr)
    		return false;

    else 
    {
		//return ((this->m_coord[0] == other.m_coord[0]) 
    			//&& (this->m_coord[1] == other.m_coord[1]));
    			
		//Since some float numbers can't be represented accurately in the machine, we have to compare the diference with an epsilon
		float e = 0.000001f;
		return (std::abs(this->m_coord[0] - other.m_coord[0]) < e
    			&& std::abs(this->m_coord[1] - other.m_coord[1] < e));
    }
}

bool Point2f::operator>(const Point2f& other) const
{
	if (this == nullptr || &other == nullptr)
		return false;
	else
	{
		float e = 0.000001f;
		if (std::abs(this->m_coord[0] - other.m_coord[0]) < e)
		{
			if (this->m_coord[1] > other.m_coord[1])
				return true;
			else
				return false;
		}
		
		else if (this->m_coord[0]>other.m_coord[0])
			return true;
		else
			return false;			
	}
	
}

 inline float Point2f::x() const {
    return m_coord[0];
  }

  inline float Point2f::y() const {
    return m_coord[1];
  }
 
 inline Point2f& Point2f::x(float newX) { 
	 m_coord[0] = newX; return *this; 
 }

 inline Point2f& Point2f::y(float newY) { 
	 m_coord[1] = newY; return *this; 
 }

/**
 * Calculates the distance between two points using the Pitagoras' Theorem (or vector modulo, which is the same)
 */
float Point2f::distanceBetweenTwoPoints (const Point2f& other) const{
	float leg_x = other.m_coord[0] - this->m_coord[0];
	float leg_y = other.m_coord[1] - this->m_coord[1];
	return std::hypot(leg_x,leg_y); //since c+11, hypot() is provided by cmath; otherwise I could use: sqrt(pow(leg_x,2) + pow(leg_y,2));
	
}
 
