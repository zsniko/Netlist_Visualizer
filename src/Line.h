// -*- explicit-buffer-name: "Line.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_LINE_H
#define NETLIST_LINE_H

#include <iostream>
#include <vector>
#include <libxml/xmlreader.h>
#include "Point.h"
#include "Node.h"

namespace Netlist {

  class Net;

  class Line {
    public:
                    Line              ( Node* source, Node* target );
                   ~Line              ();
      inline Node*  getSource         () const;
      inline Node*  getTarget         () const;
      inline Point  getSourcePosition () const;
      inline Point  getTargetPosition () const;
             void   toXml             ( std::ostream& ) const;
      static bool   fromXml           ( Net*, xmlTextReaderPtr );
    private:
                    Line              ( const Line& );
             Line&  operator=         ( const Line& );
    private:
      Node* source_;
      Node* target_;
  };


  inline Node*  Line::getSource         () const { return source_; }
  inline Node*  Line::getTarget         () const { return target_; }
  inline Point  Line::getSourcePosition () const { return source_->getPosition(); }
  inline Point  Line::getTargetPosition () const { return target_->getPosition(); }


}  // Netlist namespace.

#endif  // NETLIST_LINE_H