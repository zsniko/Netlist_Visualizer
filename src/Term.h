// -*- explicit-buffer-name: "Term.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_TERM_H
#define NETLIST_TERM_H

#include "Node.h"
#include "Indentation.h"
#include <fstream>
#include "XmlUtil.h"
#include <libxml/xmlreader.h>


namespace Netlist{

    class Node;
    class Net;
    class Cell;
    class Instance;
    class Point;
    class Indentation;

    class Term{

        public:
                enum Type               { Internal=1, External=2 };  
                enum Direction          { In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6 };

        public:
            // CTOR et DTOR
                                        Term        ( Cell*, const std::string& name, Direction);  
                                        Term        ( Instance*, const Term* modelTerm );             
                                        ~Term       ();                                                
        
            // Accesseurs
            inline  bool                isInternal  () const;                   // si le Term est interne
            inline  bool                isExternal  () const;                   // si le Term est externe
            inline  const std::string&  getName     () const;                   // recuperer le nom du Term
            inline  NodeTerm*           getNode     ();                         // recuperer le Node du Term
            inline  Net*                getNet      () const;                   // recuperer le Net du Term
            inline  Cell*               getCell     () const;                   // recuperer la Cell a laquelle appartient le Term
                    Cell*               getOwnerCell() const;                   // recuperer la Cell a laquelle appartient le Term 
            inline  Instance*           getInstance () const;                   // recuperer l'Instance a laquelle appartient le Term
            inline  Direction           getDirection() const;                   // recuperer la direction du Term
            inline  Point               getPosition () const;                   // recuperer la position du Term
            inline  Type                getType     () const;                   // recuperer le type du Term (Internal ou External)

            // Modificateurs
                    void                setNet      ( Net* );                   // connecter le Term a un Net
                    void                setNet      ( const std::string& );     // connecter le Term a un Net de nom s 
            inline  void                setDirection( Direction );              // definir la direction du Term 
                    void                setPosition ( const Point& );           // definir la position du Term
                    void                setPosition ( int x, int y );           // definir la position du Term
            
            // Methodes statiques pour convertir depuis/vers string
            static  std::string         toString    ( Type );                   // convertir un Type en string
            static  std::string         toString    ( Direction );              // convertir une Direction en string
            static  Direction           toDirection ( std::string );            // convertir une string en Direction
            static  Type                toType      ( std::string );            // convertir une string en Type
            
            // Methodes pour le XML
            void                        toXml       ( std::ostream& ) const;          // driver XML 
            static  Term*               fromXml     ( Cell*, xmlTextReaderPtr );// parseur XML, static car on ne connait pas encore le Term

        private:
            // Attributs
            void*               owner_;         // Cell* ou Instance* a laquelle appartient le Term
            std::string         name_;          // Nom du Term
            Direction           direction_;     // Direction du Term
            Type                type_;          // Type du Term (Internal: Instance, External: Cell)
            Net*                net_;           // Net auquel est connecte le Term
            NodeTerm            node_;          // Node associe au Term

    };

// Fonctions inline Accesseurs
inline bool             Term::isInternal                ()      const { return getType() == Internal; }
inline bool             Term::isExternal                ()      const { return getType() == External; }
inline const            std::string& Term::getName      ()      const { return name_; }
inline NodeTerm*        Term::getNode                   ()            { return &node_; }
inline Net*             Term::getNet                    ()      const { return net_; }
inline Cell*            Term::getCell                   ()      const { return type_ == External ? static_cast<Cell*> (owner_) : NULL; }
inline Instance*        Term::getInstance               ()      const { return type_ == Internal ? static_cast<Instance*> (owner_): NULL; }
inline Term::Direction  Term::getDirection              ()      const { return direction_; }
inline Point            Term::getPosition               ()      const { return node_.getPosition(); }
inline Term::Type       Term::getType                   ()      const { return type_; }

// Fonctions inline Modificateurs
inline void             Term::setDirection              ( Direction d ) { direction_ = d; }


}

#endif 
