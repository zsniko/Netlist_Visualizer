// -*- explicit-buffer-name: "Term.h<M1-MOBJ/4-5>" -*-

#ifndef NETLIST_TERM_H
#define NETLIST_TERM_H

#include "Node.h"
#include "Indentation.h"


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
                                        Term        ( Cell*, const std::string& name, Direction); //
                                        Term        ( Instance*, const Term* modelTerm ); //
                                        ~Term       (); // 
        
            // Accesseurs
            inline  bool                isInternal  () const; //
            inline  bool                isExternal  () const; //
            inline  const std::string&  getName     () const; //
            inline  Node*               getNode     ();       //
            inline  Net*                getNet      () const; // 
            inline  Cell*               getCell     () const;//
                    Cell*               getOwnerCell() const;// 
            inline  Instance*           getInstance () const; //
            inline  Direction           getDirection() const;//
            inline  Point               getPosition () const;//
            inline  Type                getType     () const;//

            // Modificateurs
                    void                setNet      ( Net* ); // 
                    void                setNet      ( const std::string& ); // 
            inline  void                setDirection( Direction );      // 
                    void                setPosition ( const Point& );  //
                    void                setPosition ( int x, int y ); //
            
            // Methodes statiques pour convertir depuis/vers string
            static  std::string         toString    ( Type ); // 
            static  std::string         toString    ( Direction ); //
            static  Direction           toDirection ( std::string ); //
            
            // Methodes pour le XML
            void                        toXml       ( std::ostream& ); // not finished

        private:
            // Attributs
            void*               owner_;         // Cell* ou Instance* a laquelle appartient le Term
            std::string         name_;          // Nom du Term
            Direction           direction_;     // Direction du Term
            Type                type_;          // Type du Term (Internal: Instance, External: Cell)
            Net*                net_;           // Net auquel est connecte le Term
            Node                node_;          // Node associe au Term

    };

// Fonctions inline Accesseurs
inline bool             Term::isInternal                ()      const { return getType() == Internal; }
inline bool             Term::isExternal                ()      const { return getType() == External; }
inline const            std::string& Term::getName      ()      const { return name_; }
inline Node*            Term::getNode                   ()            { return &node_; }
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