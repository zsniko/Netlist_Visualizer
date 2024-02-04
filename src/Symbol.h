// -*- explicit-buffer-name: "Symbol.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_SYMBOL_H
#define NETLIST_SYMBOL_H

#include  <libxml/xmlreader.h>
#include  "Shape.h"
#include  <string>
#include  <vector>
#include  "Box.h"

namespace Netlist {

  class Term;
  class Cell;
  class Shape;
  class TermShape;


  class Symbol {
    public:
                                        Symbol          ( Cell* );
                                       ~Symbol          ();
             Cell*                      getCell         () const;
             Box                        getBoundingBox  () const;
             Point                      getTermPosition ( Term* ) const;
             TermShape*                 getTermShape    ( Term* ) const;
      inline const std::vector<Shape*>  getShapes       () const;
             void                       add             ( Shape* );
             void                       remove          ( Shape* );
             void                       toXml           ( std::ostream& ) const;
             static Symbol*             fromXml         ( Cell*, xmlTextReaderPtr );
    private:                                            
                                        Symbol          ( const Symbol& );
             Symbol&                    operator=       ( const Symbol& );
    private:
      Cell*                owner_;
      std::vector<Shape*>  shapes_;
  };


  inline const std::vector<Shape*>  Symbol::getShapes () const { return shapes_; }


}  // Netlist namespace.

#endif  // NETLIST_SYMBOL_H