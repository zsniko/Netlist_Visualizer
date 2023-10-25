// -*- explicit-buffer-name: "XmlUtil.h<M1-MOBJ/6>" -*-

#ifndef NETLIST_XMLUTIL_H
#define NETLIST_XMLUTIL_H

#include <libxml/xmlreader.h>
#include <string>

namespace Netlist {


  std::string  xmlCharToString    ( xmlChar* );
  bool         xmlGetIntAttribute ( xmlTextReaderPtr, const std::string& attribute, int& value );


}  // Netlist namespace.

#endif  // NETLIST_XMLUTIL_H