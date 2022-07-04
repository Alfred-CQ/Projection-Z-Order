/*
 * Punto N Dimensional
 * Chillitupa Quispihuanca, Alfred Addison
 * Estructuras de Datos Avanzadas
 * CCOMP6-1
 * C++
 * Point.hpp
*/

#ifndef _POINT_HPP_
    #define _POINT_HPP_

    #include <iostream>

    #include <math.h>
    
    template <std::size_t N, typename ElemType>
    class Point{
        
        public:
            
            std::size_t m_size   = N;
            std::size_t beg      = 0;
            std::size_t end      = m_size - 1;
            
            unsigned long z_value = -1;

            ElemType* m_coordinates = new ElemType[N];
        
            /* Constructors and Destructor */
            Point  ();
            Point  (ElemType*);
            
            ~Point ();
            
            /* Setters */

            /* Getters */
            std::size_t get_size()    const;
            ElemType*   get_content() const;

            /* Overloads */
            bool      operator ==  (const Point<N,ElemType>&);
            bool      operator !=  (const Point<N,ElemType>&);
            bool      operator >=  (const Point<N,ElemType>&);
            bool      operator <=  (const Point<N,ElemType>&);

            Point<N,ElemType>& operator =   (const Point<N,ElemType>&);
            ElemType  operator []  (std::size_t) const;
            ElemType& operator []  (std::size_t);

            /* Utilities */
            void printContent ();
    };

    /* Implementation - Constructors and Destructor */
    template <std::size_t N, typename ElemType>
    Point<N, ElemType>::Point::Point()
    { 
        std::size_t i;
        for ( i = 0; i < m_size; ++i)
            m_coordinates[i] = 0;
    }

    template <std::size_t N, typename ElemType>
    Point<N, ElemType>::Point::Point(ElemType coordinates[])
    { 
        std::size_t i;
        for ( i = 0; i < m_size; ++i)
            m_coordinates[i] = coordinates[i];
    }

    template <std::size_t N, typename ElemType>
    Point<N, ElemType>::Point::~Point()
    { 
       
    }
    
    /* Implementation - Setters */

    /* Implementation - Getters */
    template <std::size_t N, typename ElemType>
    std::size_t Point<N, ElemType>::Point::get_size() const
    {
        return m_size;
    }
           

    /* Implementation - Overloads */
    template <std::size_t N, typename ElemType>
    bool Point<N, ElemType>::Point::operator == (const Point& point) 
    {
        std::size_t i;

        for ( i = 0; i < m_size; ++i)
            if (m_coordinates[i] != point[i])
                return 0;
        
        return 1;
    }

    template <std::size_t N, typename ElemType>
    bool Point<N, ElemType>::Point::operator != (const Point& point) 
    {
        return !(*this == point);
    }

    template <std::size_t N, typename ElemType>
    bool Point<N, ElemType>::Point::operator >= (const Point& point) 
    {
        return (m_coordinates[0] >= point[0]) && (m_coordinates[1] >= point[1]);
    }
    
    template <std::size_t N, typename ElemType>
    bool Point<N, ElemType>::Point::operator <= (const Point& point) 
    {
        return (m_coordinates[0] <= point[0]) && (m_coordinates[1] <= point[1]);;
    }

    template <std::size_t N, typename ElemType>
    Point<N, ElemType>& Point<N, ElemType>::Point::operator = (const Point<N, ElemType>& point)
    {
        if (*this == point)
            return *this;
        
        std::size_t i;
        for ( i = 0; i < m_size; ++i)
            m_coordinates[i] = point[i];

        return *this;
    }

    template <std::size_t N, typename ElemType>
    ElemType Point<N, ElemType>::Point::operator[] (size_t index) const{
        return m_coordinates[index];
    }

    template <std::size_t N, typename ElemType>
    ElemType& Point<N, ElemType>::Point::operator[] (size_t index){
        return m_coordinates[index];
    }

    /* Implementation - Utilities */

    template <std::size_t N, typename ElemType>
    void Point<N, ElemType>::Point::printContent()
    { 
        std::size_t i;
        
        std::cout << "{ ";
        for ( i = 0; i < m_size; ++i)
            std::cout << m_coordinates[i] << " ";
        std::cout << "}\n";
    }
    
    template <size_t N, typename ElemType>
    double euclideanDistance(Point<N,ElemType>& x, Point<N,ElemType>& y)
    {
        double distance = 0.f;
        std::size_t i;

        for (i = 0; i < N; ++i)
            distance +=  ((x[i] - y[i])*(x[i] - y[i])); 
            
        return sqrt( distance );
    }
      

#endif
