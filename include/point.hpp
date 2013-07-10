// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2011 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  point.hpp                                                                       */
/*  project    :  lectures in programming && software engineering                                 */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(BUW_MATH3D_POINT_HPP)
#define BUW_MATH3D_POINT_HPP

#include <iosfwd>
#include <vector.hpp>

namespace math3d {

class point 
{
public:

  point();
  point(double, double, double, double = 1.0); // x, y, z, w
  
  double const& operator[](unsigned) const;
  double&       operator[](unsigned);

  point& operator+=(vector const&);
  point& operator-=(vector const&);

  static point const& origin();     // p[0,0,0,1]

private:
  
  double data_[4];
};

point operator-(point const&);
point operator+(point const&, vector const&);
point operator-(point const&, vector const&);
bool operator==(point const&, point const&);
double distance(point const&, point const&);

std::ostream& operator<<(std::ostream&, point const&);
} // namespace math3d {

#endif // #if !defined(BUW_MATH3D_POINT_HPP)
