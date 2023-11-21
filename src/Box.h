// -*- explicit-buffer-name: "Box.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_BOX_H
#define NETLIST_BOX_H

#include <iostream>
#include <algorithm>
#include "Point.h"

namespace Netlist {


  class Box {
    public:
      inline                    Box             ();
      inline                    Box             ( int x1, int y1, int x2, int y2 );
      inline                    Box             ( const Box& );
      inline                   ~Box             ();
      inline bool               isEmpty         () const;
      inline int                getX1           () const;
      inline int                getY1           () const;
      inline int                getX2           () const;
      inline int                getY2           () const;
      inline int                getWidth        () const;
      inline int                getHeight       () const;
      inline bool               intersection    ( const Box& ) const;
      inline Box&               inflate         ( int dxy );
      inline Box&               inflate         ( int dx, int dy );
      inline Box&               inflate         ( int dx1, int dy1, int dx2, int dy2 );
      inline Box&               translate       ( int dx, int dy );
      inline Box&               translate       ( const Point& );
      inline Box                getIntersection ( const Box& );
      inline Box&               setX1           ( int );
      inline Box&               setY1           ( int );
      inline Box&               setX2           ( int );
      inline Box&               setY2           ( int );
             Box&               merge           ( const Box& );
      inline void               makeEmpty       ();
      friend inline std::ostream&  operator<< ( std::ostream&, const Box& );
    private:
      int  x1_;
      int  y1_;
      int  x2_;
      int  y2_;
  };
  
  
  inline Box::Box () : x1_(1), y1_(1), x2_(-1), y2_(-1) { }
  
  
  inline Box::Box ( int x1, int y1, int x2, int y2 )
     : x1_(x1), y1_(y1), x2_(x2), y2_(y2)
  {
    if ( x1_ > x2_ ) std::swap(x1_,x2_);
    if ( y1_ > y2_ ) std::swap(y1_,y2_);
  }
  
  
  inline Box::Box ( const Box& other )
     : x1_(other.x1_), y1_(other.y1_), x2_(other.x2_), y2_(other.y2_)
  { }
  
  
  inline Box::~Box () { }
  
  
  inline bool               Box::isEmpty   () const { return (x1_ > x2_) or (y1_ > y2_); }
  inline int                Box::getX1     () const { return x1_; }
  inline int                Box::getY1     () const { return y1_; }
  inline int                Box::getX2     () const { return x2_; }
  inline int                Box::getY2     () const { return y2_; }
  inline int                Box::getWidth  () const { return x2_ - x1_; }
  inline int                Box::getHeight () const { return y2_ - y1_; }
  inline Box&               Box::setX1     ( int x1 ) { x1_ = x1; return *this; }
  inline Box&               Box::setY1     ( int y1 ) { y1_ = y1; return *this; }
  inline Box&               Box::setX2     ( int x2 ) { x2_ = x2; return *this; }
  inline Box&               Box::setY2     ( int y2 ) { y2_ = y2; return *this; }
  inline Box&               Box::inflate   ( int dxy ) { return inflate ( dxy, dxy, dxy, dxy ); }
  inline Box&               Box::inflate   ( int dx, int dy ) { return inflate ( dx, dy, dx, dy ); }
  inline Box&               Box::translate ( int dx, int dy ) { x1_+=dx; x2_+=dx; y1_+=dy; y2_+=dy; return *this; }
  inline Box&               Box::translate ( const Point& p ) { return translate( p.getX(), p.getY() ); }
  
  
  bool  Box::intersection ( const Box& other ) const
  {
    if ( isEmpty() or other.isEmpty() ) return false;
    if (   ((x2_ < other.x1_) or (x1_ > other.x2_))
       and ((y2_ < other.y1_) or (y1_ > other.y2_)) ) return false;
    return true;
  }
  
  
  Box  Box::getIntersection ( const Box& other )
  {
    if (not intersection(other) ) return Box();
    return Box ( std::max(x1_,other.x1_)
               , std::max(y1_,other.y1_)
               , std::min(x2_,other.x2_)
               , std::min(y2_,other.y2_)
               );
  }
  
  
  Box& Box::inflate ( int dx1, int dy1, int dx2, int dy2 )
  {
    x1_ -= dx1;
    y1_ -= dy1;
    x2_ += dx2;
    y2_ += dy2;
  
    return *this;
  }
  
  
  std::ostream&  operator<< ( std::ostream& o, const Box& box )
  {
    o << "<Box " << box.x1_ << " " << box.y1_ << " " << box.x2_ << " " << box.y2_ << "/>";
    return o;
  }


} // Netlist namespace.

#endif  // NETLIST_BOX_H