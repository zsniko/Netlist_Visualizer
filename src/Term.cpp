// -*- explicit-buffer-name: "Term.cpp<M1-MOBJ/8-10>" -*-

#include "Term.h"
#include "Cell.h"
#include "Instance.h"
#include "Net.h"
#include <cstdlib>

namespace Netlist{
    
    // CTOR: Term - Cell
    Term::Term (Cell* c, const std::string& name, Direction d )
    : owner_(c), name_(name), direction_(d), type_(External), net_(), node_(this, Node::noid) // A la creation d'un Term, l'id_ de node_ est initialise a noid.
    { c->add(this); } 

    // CTOR: Term - Instance
    Term::Term (Instance* i, const Term* modelTerm)
    : owner_(i), name_(modelTerm->getName()), direction_(modelTerm->getDirection()), type_(Internal), net_(), node_(this, Node::noid)
    { i->add(this); }

    // DTOR 
    Term::~Term ()
    { 
        if (type_ == External) // Si Term appartenant a une Instance 
            getCell()->remove(this); 
        else if (type_ == Internal) // Si Term appartenant a une Cell
            getInstance()->remove(this);
    }

    // Fonctions Accesseurs
    Cell* Term::getOwnerCell () const 
    { 
        if (type_ == Internal) // Si Term appartenant a une Instance
            return static_cast<Instance*>(owner_)->getCell(); 
        else if (type_ == External)            // Si Term appartenant a une Cell
            return static_cast<Cell*>(owner_);
        else 
            exit ( 1 );
    
    }

    // Fonctions Modificateurs
    void Term::setNet ( Net* n )
    {
        if (n != NULL){ 
            net_ = n; // On connecte le Term au Net
            n->add(&node_); // Ajouter le Node au Net
        }
        else{
            std::vector<Node*> nodes = net_->getNodes();    
            nodes[node_.getId()] = NULL; // On met a NULL le Node du Net
            net_ = NULL; // On deconnecte le Term du Net
        }        
    }

    void Term::setNet ( const std::string& s )
    {
        Net* n = getOwnerCell()->getNet(s); // On recupere le Net de la Cell
        if (n != NULL){ 
            net_ = n; // On connecte le Term au Net
            n->add(&node_); // Ajouter le Node au Net
        }
        else{
            std::vector<Node*> nodes = net_->getNodes();    
            nodes[node_.getId()] = NULL; // On met a NULL le Node du Net
            net_ = NULL; // On deconnecte le Term du Net
        }        
    }

    void Term::setPosition ( const Point& p )
    { node_.setPosition(p); }

    void Term::setPosition ( int x, int y )
    { node_.setPosition( x, y ); }

    // Fonctions conversions
    std::string Term::toString ( Type t )
    { 
        if (t == Internal) 
            return "Internal"; 
        else if (t == External)
            return "External"; 
        else    
            exit ( 1 );
    }

    std::string Term::toString ( Direction d )
    {
        switch (d)
        {
        case 1:
            return "In"; break;
        case 2:
            return "Out"; break;
        case 3:
            return "Inout"; break;
        case 4:
            return "Tristate"; break;
        case 5:
            return "Transcv"; break;
        case 6:
            return "Unknown"; break;
        default:
            exit ( 1 ); break;
        }
    }
    Term::Type Term::toType( std::string s )
    {
        if ( s == "Internal" )  
            return Internal;
        else if ( s == "External" )
            return External;
        else 
            exit ( 1 );
    }

    Term::Direction Term::toDirection ( std::string s )
    {
        if (s == "In") 
            return In;
        else if (s == "Out") 
            return Out;
        else if (s == "Inout") 
            return Inout;
        else if (s == "Tristate") 
            return Tristate;
        else if (s == "Transcv") 
            return Transcv;
        else if (s == "Unknown") 
            return Unknown;
        else 
            exit ( 1 );
    }

    // XML driver
    void  Term::toXml ( std::ostream& stream ) const {
        stream << indent << "<term name=\"" << name_ 
        << "\" direction=\"" << toString(direction_) 
        << "\" x=\"" << getPosition().getX()
        << "\" y=\"" << getPosition().getY()
        << "\"/>" << std::endl;
    }

    // XML Parseur
    Term* Term::fromXml( Cell* cell, xmlTextReaderPtr reader){
        std::string name_s        = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"name") );
        std::string direction_s   = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"direction" ) );
        std::string x_s           = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"x") );
        std::string y_s           = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"y") );
        if (not name_s.empty()){
            Term* term = new Term (cell, name_s, Term::toDirection(direction_s));
            term->setPosition(atoi(x_s.c_str()), atoi(y_s.c_str()));
            return term;
        }
        else{
            std::cerr << "Echec de chargement de Term" << std::endl;
            return NULL; // En cas d'erreur la fonction renverra un pointeur NULL.
        }
    }   

}


