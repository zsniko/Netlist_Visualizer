// -*- explicit-buffer-name: "Box.cpp<M1-MOBJ/7>" -*-

#include "Box.h"

namespace Netlist {


  Box& Box::merge ( const Box& other )
  {
    if (not other.isEmpty()) {
      if (isEmpty()) {
        x1_ = other.x1_;
        y1_ = other.y1_;
        x2_ = other.x2_;
        y2_ = other.y2_;
      } else {
        x1_ = std::min( x1_, other.x1_ );
        y1_ = std::min( y1_, other.y1_ );
        x2_ = std::max( x2_, other.x2_ );
        y2_ = std::max( y2_, other.y2_ );
      }
    }
    return *this;
  }


}  // Netlist namespace.