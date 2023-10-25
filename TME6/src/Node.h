// -*- explicit-buffer-name: "Node.h<M1-MOBJ/4-5>" -*-

#ifndef NETLIST_NODE_H
#define NETLIST_NODE_H

#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Point.h"
#include <fstream>
#include "XmlUtil.h"
#include <libxml/xmlreader.h>


namespace Netlist {
  class Term;
  class Net;
  class Node {
    public:
      static const size_t  noid;
    public:
                      Node        ( Term*, size_t id=noid );
                     ~Node        ();
      inline  Point   getPosition () const;
      inline  void    setPosition ( const Point& P);
      inline  void    setPosition ( int x, int y );
      inline  size_t  getId       () const;
              Net*    getNet      () const;
      inline  Term*   getTerm     () const;
      inline  void    setId       ( size_t );
              void    toXml       ( std::ostream& );
    private:
                      Node        ( const Node& );
              Node&   operator=   ( const Node& );
      static  bool    fromXml     ( Net*, xmlTextReaderPtr );
    protected:
      size_t  id_;
      Term*   term_;
      Point   position_;
  };


  inline size_t  Node::getId       () const { return id_; }
  inline Term*   Node::getTerm     () const { return term_; }
  inline Point   Node::getPosition () const { return position_; }
  inline void    Node::setId       ( size_t id ) { id_=id; }
  inline void    Node::setPosition ( const Point& pos ) { position_ = pos; }
  inline void    Node::setPosition ( int x, int y )     { position_ = Point(x,y); }


}  // Netlist namespace.

#endif  // NETLIST_NODE_H