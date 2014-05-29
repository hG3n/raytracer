#ifndef BUW_RGB_HPP
#define BUW_RGB_HPP

// header, system
#include <iosfwd>


class Color {
public : // enums, typedefs

  typedef float value_t;

  Color();
  Color(value_t r, value_t g, value_t b); 
  Color(Color const&);
  ~Color();

  //methods
  void print (std::ostream& os) const;

  value_t&        operator[](unsigned component);
  const value_t&  operator[](unsigned component) const;

  void   operator+=(const Color&);
  void   operator=(const Color&);
  bool   operator==(const Color&);
  Color& operator*=(const Color&);

private:
  value_t data_[3]; // rgb
};

Color operator+(const Color& a, const Color& b);
Color operator*(const Color&, const Color);
std::ostream& operator<<(std::ostream& os, Color const&);

#endif // BUW_RGB_HPP
