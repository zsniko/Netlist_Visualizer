// -*- explicit-buffer-name: "Cell.cpp<M1-MOBJ/4-5>" -*-

#include  <cstdlib>
#include  "Cell.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"


namespace Netlist {

  using namespace std;


  vector<Cell*>  Cell::cells_;


  Cell* Cell::find ( const string& name )
  {
    for ( vector<Cell*>::iterator icell=cells_.begin() ; icell != cells_.end() ; ++icell ) {
      if ((*icell)->getName() == name) return *icell;
    }
    return NULL;
  }


  Cell::Cell ( const string& name )
    : name_     (name) 
    , terms_    ()
    , instances_()
    , nets_     ()
    , maxNetIds_(0)
  {
    if (find(name)) {
      cerr << "[ERROR] Attempt to create duplicate of Cell <" << name << ">.\n"
           << "        Aborting..." << endl;
      exit( 1 );
    }
    cells_.push_back( this );
  }


  Cell::~Cell ()
  {
    for ( vector<Cell*>::iterator icell=cells_.begin() ; icell != cells_.end() ; ++icell ) {
      if (*icell == this) {
        cells_.erase( icell );
        break;
      }
    }

    while ( not nets_     .empty() ) delete *nets_     .begin();
    while ( not instances_.empty() ) delete *instances_.begin();
    while ( not terms_    .empty() ) delete *terms_    .begin();
  }


  Instance* Cell::getInstance ( const std::string& name ) const
  {
    for ( vector<Instance*>::const_iterator iinst=instances_.begin() ; iinst != instances_.end() ; ++iinst ) {
      if ((*iinst)->getName() == name)  return *iinst;
    }
    return NULL;
  }


  Term* Cell::getTerm ( const std::string& name ) const
  {
    for ( vector<Term*>::const_iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm ) {
      if ((*iterm)->getName() == name)  return *iterm;
    }
    return NULL;
  }


  Net* Cell::getNet ( const std::string& name ) const
  {
    for ( vector<Net*>::const_iterator inet=nets_.begin() ; inet != nets_.end() ; ++inet ) {
      if ((*inet)->getName() == name)  return *inet;
    }
    return NULL;
  }


  void  Cell::setName ( const string& cellName )
  {
    if (cellName == name_) return;
    if (find(cellName) != NULL) {
      cerr << "[ERROR] Cell::setName() - New Cell name <" << cellName << "> already exists."<< endl;
      return;
    }
    name_ = cellName;
  }


  void  Cell::add ( Instance* instance )
  {
    if (getInstance(instance->getName())) {
      cerr << "[ERROR] Attemp to add duplicated instance <" << instance->getName() << ">." << endl;
      exit( 1 );
    }
    instances_.push_back( instance );
  }


  void  Cell::add ( Term* term )
  {
    if (getTerm(term->getName())) {
      cerr << "[ERROR] Attemp to add duplicated terminal <" << term->getName() << ">." << endl;
      exit( 1 );
    }
    terms_.push_back( term );
  }


  void  Cell::add ( Net* net )
  {
    if (getNet(net->getName())) {
      cerr << "[ERROR] Attemp to add duplicated Net <" << net->getName() << ">." << endl;
      exit( 1 );
    }
    nets_.push_back( net );
  }


  bool  Cell::connect ( const string& name, Net* net )
  {
    Term* term = getTerm( name );
    if (term == NULL) return false;
 
    term->setNet( net );
    return true;
  }


  void  Cell::remove ( Instance* instance )
  {
    for ( vector<Instance*>::iterator iinst=instances_.begin() ; iinst != instances_.end() ; ++iinst ) {
      if (*iinst == instance){
        instances_.erase( iinst );
        break;
      }
    }
  }


  void  Cell::remove ( Term* term )
  {
    for ( vector<Term*>::iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm ) {
      if (*iterm == term){
        terms_.erase( iterm );
        break;
      }
    }
  }


  void  Cell::remove ( Net* net )
  {
    for ( vector<Net*>::iterator inet=nets_.begin() ; inet != nets_.end() ; ++inet ) {
      if (*inet == net){
        nets_.erase( inet );
        break;
      }
    }
  }


  unsigned int Cell::newNetId ()
  { return maxNetIds_++; }


  void Cell::toXml( std::ostream& stream ) const
  { 
      stream << indent++ << "<cell name=\"" << name_ << "\">" << endl; // <cell name = "xxx">

      //////////////////////////////////////////////////////////
      stream << indent++ << "<terms>" << endl; // <terms>
      for ( std::vector<Term*>::const_iterator iterm = terms_.begin(); iterm != terms_.end(); ++iterm ){
        if ( *iterm != NULL )
          (*iterm)->toXml(stream);
      } 
      stream << --indent << "</terms>" << endl; // </terms>
      //////////////////////////////////////////////////////////
      stream << indent++ << "<instances>" << endl; // <instances>
      for ( std::vector<Instance*>::const_iterator iinst = instances_.begin(); iinst != instances_.end(); ++iinst ){
        if ( *iinst != NULL )
          (*iinst)->toXml(stream);
      }
      stream<< --indent << "</instances>" << endl; // </instances>
      //////////////////////////////////////////////////////////
      stream << indent++ << "<nets>" << endl; // <nets>
      for ( std::vector<Net*>::const_iterator inet = nets_.begin(); inet != nets_.end(); ++inet){
        if ( *inet != NULL )
          (*inet)->toXml(stream);
      }
      stream << --indent << "</nets>" << endl; // </nets>
      //////////////////////////////////////////////////////////

      stream << --indent << "</cell>" << endl; // </cell>
  }

  Cell* Cell::fromXml ( xmlTextReaderPtr reader )
  {
    enum  State { Init           = 0
                , BeginCell
                , BeginTerms
                , EndTerms
                , BeginInstances
                , EndInstances
                , BeginNets
                , EndNets
                , EndCell
                };

    const xmlChar* cellTag      = xmlTextReaderConstString( reader, (const xmlChar*)"cell" );
    const xmlChar* netsTag      = xmlTextReaderConstString( reader, (const xmlChar*)"nets" );
    const xmlChar* termsTag     = xmlTextReaderConstString( reader, (const xmlChar*)"terms" );
    const xmlChar* instancesTag = xmlTextReaderConstString( reader, (const xmlChar*)"instances" );

    Cell* cell   = NULL;
    State state  = Init;

    while ( true ) {
      int status = xmlTextReaderRead(reader);
      if (status != 1) {
        if (status != 0) {
          cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << endl;
        }
        break;
      }

      switch ( xmlTextReaderNodeType(reader) ) {
        case XML_READER_TYPE_COMMENT:
        case XML_READER_TYPE_WHITESPACE:
        case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
          continue;
      }

      const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );

      switch ( state ) {
        case Init:
          if (cellTag == nodeName) {
            state = BeginCell;
            string cellName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
            if (not cellName.empty()) {
              cell = new Cell ( cellName );
              state = BeginTerms;
              continue;
            }
          }
          break;
        case BeginTerms:
          if ( (nodeName == termsTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) ) {
            state = EndTerms;
            continue;
          }
          break;
        case EndTerms:
          if ( (nodeName == termsTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) ) {
            state = BeginInstances;
            continue;
          } else {
            if (Term::fromXml(cell,reader)) continue;
          }
          break;
        case BeginInstances:
          if ( (nodeName == instancesTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) ) {
            state = EndInstances;
            continue;
          }
          break;
        case EndInstances:
          if ( (nodeName == instancesTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) ) {
            state = BeginNets;
            continue;
          } else {
            if (Instance::fromXml(cell,reader)) continue;
          }
          break;
        case BeginNets:
          if ( (nodeName == netsTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) ) {
            state = EndNets;
            continue;
          }
          break;
        case EndNets:
          if ( (nodeName == netsTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) ) {
            state = EndCell;
            continue;
          } else {
            if (Net::fromXml(cell,reader)) continue;
          }
          break;
        case EndCell:
          if ( (nodeName == cellTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) ) {
            continue;
          }
          break;
        default:
          break;
      }

      cerr << "[ERROR] Cell::fromXml(): Unknown or misplaced tag <" << nodeName
          << "> (line:" << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
      break;
    }

    return cell;
  }
  
  Cell* Cell::load ( const string& cellName )
  {
    string           cellFile = "./cells/" + cellName + ".xml";
    xmlTextReaderPtr reader;

    reader = xmlNewTextReaderFilename( cellFile.c_str() );
    if (reader == NULL) {
      cerr << "[ERROR] Cell::load() unable to open file <" << cellFile << ">." << endl;
      return NULL;
    }

    Cell* cell = Cell::fromXml( reader );
    xmlFreeTextReader( reader );

    return cell;
  }

  void  Cell::save () const
  {
    string  fileName   = getName() + ".xml";
    fstream fileStream ( fileName.c_str(), ios_base::out|ios_base::trunc );
    if (not fileStream.good()) {
      cerr << "[ERROR] Cell::save() unable to open file <" << fileName << ">." << endl;
      return;
    }

    cerr << "Saving <Cell " << getName() << "> in <" << fileName << ">" << endl;
    toXml( fileStream );

    fileStream.close();
  }



}  // Netlist namespace.
