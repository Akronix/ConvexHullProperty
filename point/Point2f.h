#ifndef POINT2F_H
#define POINT2F_H

class Point2f
{
    public:
        Point2f();
        Point2f(float x, float y);
        Point2f(const Point2f& otherPoint);
        Point2f& operator=(const Point2f& other);

        /** Comparison operator
         *  \param other point to compare with
         *  \return true if the point is the same or describe the same coordinates
         *  		false otherwise.
         */
        bool operator==(const Point2f& other) const;

		/**
		 * 'Greater than' operator
		 * \param other point to compare with.
         *  \return I define one point greater than another, If the former has got a greater x-value.
         * If both x-values are the same, it compares the y-values.
         * If both have equal x- and y-values, then this can return either false or true.
		 */
		 bool operator>(const Point2f& other) const;
		
		// the following getters/setters will be inlined (little more efficient)
		/* Getters */
        inline float x() const;
        inline float y() const;
        
        /* Setters */
        inline Point2f& x(float newX);
		inline Point2f& y(float newY);
		
		/* Others */
		float distanceBetweenTwoPoints (const Point2f& other) const;
		
    private:
        float m_coord [2];
};
#endif // Point2f_H

