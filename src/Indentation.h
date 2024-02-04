// -*- explicit-buffer-name: "Indentation.h<M1-MOBJ/8-10>" -*-

#ifndef  NETLIST_INDENTATION_H
#define  NETLIST_INDENTATION_H

#include <string>
#include <iostream>

namespace Netlist {


  class Indentation {
    public:
                    Indentation ();
      Indentation&  operator++  ();
      Indentation   operator++  (int);
      Indentation&  operator--  ();
      Indentation   operator--  (int);
    private:
      size_t        _tabulationSize;
      std::string   _indentation;

      friend std::ostream& operator<< ( std::ostream&, const Indentation& );
  };


  extern Indentation  indent;


}  // Netlist namespace.

#endif //  NETLIST_INDENTATION_H
