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


  void Cell::toXml( std::ostream& stream )
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
}  // Netlist namespace.