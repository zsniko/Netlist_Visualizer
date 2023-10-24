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
                                                Instance        ( Cell* owner, Cell* model, const std::string& ); 
                                                ~Instance       (); 

            // Accesseurs
            inline  const std::string&          getName         () const;                           // recuperer le nom de l'instance
            inline  Cell*                       getMasterCell   () const;                           // recuperer la Cell (interne)
            inline  Cell*                       getCell         () const;                           // recuperer la Cell (externe)
            inline  const std::vector<Term*>&   getTerms        () const;                           // recuperer le vecteur des terminaux de l'instance
                    Term*                       getTerm         ( const std::string& ) const;       // recuperer un terminal de l'instance
            inline  Point                       getPosition     () const;                           // recuperer la position de l'instance

            // Modificateurs
            bool                                connect         ( const std::string& name, Net* );  // connecter un terminal de l'instance a un Net
            void                                add             ( Term* );                          // ajouter un terminal a l'instance
            void                                remove          ( Term* );                          // retirer un terminal de l'instance
            void                                setPosition     ( const Point& );                   // definir la position de l'instance
            void                                setPosition     ( int x, int y );                   // definir la position de l'instance
            
            // XML
            void                                toXml           ( std::ostream& );                  // driver XML 
        
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