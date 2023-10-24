// -*- explicit-buffer-name: "Net.cpp<M1-MOBJ/4-5>" -*-

#include "Net.h"
#include "Cell.h"

namespace Netlist{

    // CTOR
    Net::Net ( Cell* c, const std::string& s, Term::Type t)
    : owner_(c), name_(s), id_(), type_(t), nodes_()
    { c->add(this); } // Surcharge - Net

    // DTOR
    Net::~Net()
    { 
        for (std::vector<Node*>::iterator it = nodes_.begin() ; it != nodes_.end() ; ++it){
            if ( *it != NULL ) {
                (*it)->getTerm()->setNet(NULL);
            }
        }
        owner_->remove(this); // retirer le Net de la Cell
    }

    // Fonctions Accesseurs
    // recuperer le vecteur des Nodes du Net
    size_t Net::getFreeNodeId() const
    { 
        for ( std::vector<Node*>::const_iterator it = nodes_.begin() ; it != nodes_.end() ; ++it){
            if ( *it == NULL ) return it - nodes_.begin();  // indice de l'element dans le vecteur
        }
        return nodes_.size(); // Si tous les elements du vecteur sont non NULL, on retourne la taille du vecteur
    }

    // Fonctions Modificateurs
    // ajouter un Node au Net
    void Net::add( Node* n )
    {  
        if (n != NULL){
            size_t id = getFreeNodeId(); // get l'indice du premier element NULL
            n->setId(id); // On set l'id du Node
            if (id < nodes_.size()) // Si l'indice est inferieur a la taille du vecteur
                nodes_[id] = n; // On remplace l'element NULL par le Node
            else
                nodes_.push_back(n); // Sinon on insere le Node a la fin du vecteur
        }
    }

    // retirer un Node du Net
    bool Net::remove( Node* n )
    {   
        if ( n != NULL ) {
            for (std::vector<Node*>::iterator it = nodes_.begin() ; it != nodes_.end() ; ++it){
                if (*it == n){
                    nodes_.erase(it);
                    return true;
                }
            }
            return false;
        }
        else 
            return false;
    }

    // XML driver
    void Net::toXml( std::ostream& stream )
    { 
        stream << indent++ << "<net name=\"" << name_ << "\" type=\"" << Term::toString(type_) << "\">" << std::endl; // <net name = "xxx" type = "xxx">

        for ( std::vector<Node*>::const_iterator inode = nodes_.begin(); inode != nodes_.end(); ++inode ){
            (*inode)->toXml(stream);
        }
        
        stream << --indent << "</net>" << std::endl; // </net>
    }

}