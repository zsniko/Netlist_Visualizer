// -*- explicit-buffer-name: "Instance.cpp<M1-MOBJ/7>" -*-

#include "Instance.h"
#include "Term.h"
#include "Symbol.h"

namespace Netlist{

    // CTOR
    Instance::Instance( Cell* owner, Cell* model, const std::string& name )
        : owner_(owner), masterCell_(model), name_(name), terms_(), position_()
    {   
        // On parcourt le vecteur des Termes du modele de l'instance pour dupliquer les Termes
        for ( std::vector<Term*>::const_iterator it = model->getTerms().begin(); it != model->getTerms().end(); ++it ){
            Term* term = new Term(this, *it); // On cree un nouveau Term
            terms_.push_back(term); // On l'ajoute au vecteur des Termes de l'instance
        }
        owner->add(this);// On ajoute l'instance a la Cell
    }

    // DTOR
    Instance::~Instance()
    {
        for ( std::vector<Term*>::const_iterator it = terms_.begin(); it != terms_.end(); ++it ){
            delete *it;
        }
        owner_->remove(this); // On retire l'instance de la Cell
    }

    // Fonctions Accesseurs
    Term* Instance::getTerm( const std::string& s ) const
    {   
        // On parcourt le vecteur des Termes de l'instance pour trouver le Term de nom s
        for ( std::vector<Term*>::const_iterator it = terms_.begin(); it != terms_.end(); ++it ){
            if ( (*it)->getName() == s ) 
                return *it;
        }
        return NULL;
    }
    
    // Fonctions Modificateurs

    // Connecter un terminal de l'instance a un Net
    bool Instance::connect( const std::string& s, Net* n )
    { 
        if ( getTerm(s) != NULL ){
            getTerm(s)->setNet(n);
            return true;
        }
        else
            return false;
    }

    // Ajouter un terminal a l'instance
    void Instance::add( Term* t )
    { 
        if ( t !=  NULL ){
            for ( std::vector<Term*>::const_iterator it = terms_.begin(); it != terms_.end(); ++it ){
                if ( *it == NULL ) {
                    terms_[it - terms_.begin()] = t;
                    return; 
                }
            }
            terms_.push_back(t);
        }
    }

    // Retirer un terminal de l'instance
    void Instance::remove( Term* t )
    { 
        if ( t != NULL){
            for ( std::vector<Term*>::iterator it = terms_.begin(); it != terms_.end(); ++it ){
                if ( *it == t ) {
                    terms_.erase(it);
                    return;
                }
            }
        }
    }
    
    // Definir la position de l'instance
    void Instance::setPosition( const Point& p ) 
    { 
        std::vector<Term*> terms = getTerms(); // Recuperer le vecteur de Terms de l'instance
        for (std::vector<Term*>::const_iterator iterms = terms.begin(); iterms != terms.end(); ++iterms){
            Shape* shape = getMasterCell()->getSymbol()->getTermShape(*iterms); // Recuperer le TermShape associe au Term
            TermShape* termshape = dynamic_cast<TermShape*>(shape);
            
            if(termshape) (*iterms)->setPosition(p.getX() + termshape->getX1(), p.getY() + termshape->getY1());
        }
        position_ = p;
    }

    // Definir la position de l'instance
    void Instance::setPosition( int x, int y ) 
    { 
        std::vector<Term*> terms = getTerms(); // Recuperer le vecteur de Terms de l'instance
        for (std::vector<Term*>::const_iterator iterms = terms.begin(); iterms != terms.end(); ++iterms){
            Shape* shape = getMasterCell()->getSymbol()->getTermShape(*iterms); // Recuperer le TermShape associe au Term
            TermShape* termshape = dynamic_cast<TermShape*>(shape);
            
            if(termshape) (*iterms)->setPosition(termshape->getX1() + x, termshape->getY1() + y);  
        }
        position_ = Point(x, y);
    }

    // XML driver
    void Instance::toXml( std::ostream& stream ) const
    { 
        stream << indent << "<instance name=\"" << getName() 
        << "\" mastercell=\"" << getMasterCell()->getName() 
        << "\" x=\"" << getPosition().getX() 
        <<"\" y=\"" << getPosition().getY() <<"\"/>" << std::endl;
    }

    // XML parseur
    Instance* Instance::fromXml( Cell* cell, xmlTextReaderPtr reader )
    {
        std::string name_s        = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"name") );
        std::string masterCell_s  = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"mastercell") );
        std::string x_s           = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"x") );
        std::string y_s           = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"y") );
        if (not name_s.empty()){
            Instance* inst = new Instance (cell, Cell::find(masterCell_s), name_s);
            inst->setPosition(atoi(x_s.c_str()), atoi(y_s.c_str()));
            return inst;
        }
        else{
            std::cerr << "Echec de chargement de 'Instance'" << std::endl;
            return NULL; // En cas d'erreur la fonction renverra un pointeur NULL.
        }

    } 
    
}


