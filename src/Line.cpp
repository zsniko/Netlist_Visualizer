// -*- explicit-buffer-name: "Line.cpp<M1-MOBJ/7>" -*-

#include "XmlUtil.h"
#include "Line.h"
#include "Cell.h"
#include "Net.h"


namespace Netlist {

  using namespace std;


  Line::Line ( Node* source, Node* target )
    : source_(source)
    , target_(target)
  {
    source_->attach( this );
    target_->attach( this );
  }


  Line::~Line ()
  {
    source_->detach( this );
    target_->detach( this );
    target_->getNet()->remove( this );
  }


  void  Line::toXml ( ostream& stream ) const
  {
    stream << indent << "<Line source=\"" << source_->getId()
                     <<    "\" target=\"" << target_->getId() << "\"/>\n";
  }


  bool   Line::fromXml ( Net* net, xmlTextReaderPtr reader )
  {
    const xmlChar* lineTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"line" );
    const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );

    if (lineTag == nodeName) {
      int idSource = 0;
      int idTarget = 0;
      xmlGetIntAttribute( reader, "source", idSource );
      xmlGetIntAttribute( reader, "target", idTarget );

      Node*      source = net->getNode( idSource );
      Node*      target = net->getNode( idTarget );

      if (not source) {
        cerr << "[ERROR] Line::fromXml(): Unknown source node id:" << idSource << " (line:"
             << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
        return false;
      }
      if (not target) {
        cerr << "[ERROR] Line::fromXml(): Unknown target node id:" << idTarget << " (line:"
             << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
        return false;
      }

      net->add( new Line(source,target) );
      return true;
    }

    return false;
  }


}  // Netlist namespace.