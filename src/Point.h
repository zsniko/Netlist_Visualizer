// -*- explicit-buffer-name: "Point.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_POINT_H
#define NETLIST_POINT_H

#include <iostream>
#include "Indentation.h"

namespace Netlist {


  class Point {
    public:
      inline         Point     ();
      inline         Point     ( int x, int y);
      inline  int    getX      () const;
      inline  int    getY      () const;
      inline  Point& setX      ( int );
      inline  Point& setY      ( int );
      inline  Point& translate ( int dx, int dy );
      inline  Point& translate ( const Point& );
    private:
      int  x_;
      int  y_;
  };

  inline         Point::Point     () : x_(0), y_(0) { }
  inline         Point::Point     ( int x, int y) : x_(x), y_(y) { }
  inline  int    Point::getX      () const { return x_; }
  inline  int    Point::getY      () const { return y_; }
  inline  Point& Point::setX      ( int x )  { x_ = x; return *this; } 
  inline  Point& Point::setY      ( int y )  { y_ = y; return *this; }
  inline  Point& Point::translate ( int dx, int dy ) { x_+=dx; y_+=dy; return *this; }
  inline  Point& Point::translate ( const Point& p ) { return translate( p.getX(), p.getY() ); }

  inline  std::ostream& operator<< ( std::ostream& stream, const Point& p )
  { stream << "<Point " << p.getX() << " " << p.getY() << ">"; return stream; }


}  // Netlist namespace.

#endif  // NETLIST_POINT_H