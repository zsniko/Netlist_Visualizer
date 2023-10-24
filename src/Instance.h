// -*- explicit-buffer-name: "Instance.h<M1-MOBJ/4-5>" -*-

#ifndef NETLIST_INSTANCE_H
#define NETLIST_INSTANCE_H
#include "Term.h"
#include "Point.h"
#include "Cell.h"

namespace Netlist{

    class Cell;
    class Term;
    class Net;
    class Indentation;

    class Instance{

        public: 
            // CTOR et DTOR 
                                                Instance        ( Cell* owner, Cell* model, const std::string& );  // not finished
                                                ~Instance       (); // not finished

            // Accesseurs
            inline  const std::string&          getName         () const; //
            inline  Cell*                       getMasterCell   () const; //
            inline  Cell*                       getCell         () const; //
            inline  const std::vector<Term*>&   getTerms        () const; //
                    Term*                       getTerm         ( const std::string& ) const; // not finished 
            inline  Point                       getPosition     () const; //

            // Modificateurs
            bool                                connect         ( const std::string& name, Net* ); // not finished
            void                                add             ( Term* ); // not finished
            void                                remove          ( Term* ); // not finished
            void                                setPosition     ( const Point& ); // 
            void                                setPosition     ( int x, int y ); // 
            
            // XML
            void                                toXml           ( std::ostream& ); // not finished
        
        private:
            // Attributs
            Cell*               owner_;         // Cell* a laquelle appartient l'instance
            Cell*               masterCell_;    // Cell* du modele de l'instance
            std::string         name_;          // Nom de l'instance
            std::vector<Term*>  terms_;         // Vecteur des Termes de l'instance
            Point               position_;      // Position de l'instance

    };

    // Fonctions inline Accesseurs
    inline const std::string&           Instance::getName       () const { return name_; }
    inline Cell*                        Instance::getMasterCell () const { return masterCell_; }
    inline Cell*                        Instance::getCell       () const { return owner_; }
    inline const std::vector<Term*>&    Instance::getTerms      () const { return terms_; }
    inline Point                        Instance::getPosition   () const { return position_; }

}

#endif 