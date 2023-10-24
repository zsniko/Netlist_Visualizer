// -*- explicit-buffer-name: "Net.h<M1-MOBJ/4-5>" -*-

#ifndef NETLIST_NET_H
#define NETLIST_NET_H

#include "Term.h"

namespace Netlist{
    
    class Cell;
    class Node;

    class Net{

        public:
            // CTOR et DTOR 
                                                Net             ( Cell*, const std::string&, Term::Type );  
                                                ~Net            ();    
            
            // Accesseurs
            inline Cell*                        getCell         () const;           // recuperer la Cell a laquelle appartient le Net
            inline const std::string&           getName         () const;           // recuperer le nom du Net
            inline unsigned int                 getId           () const;           // recuperer l'id du Net
            inline Term::Type                   getType         () const;           // recuperer le type du Net (External ou Internal)
            inline const std::vector<Node*>&    getNodes        () const;           // recuperer le vecteur des Nodes du Net
            size_t                              getFreeNodeId   () const;           // recuperer l'id du premier Node NULL du vecteur des Nodes du Net

            // Modificateurs
            void                                add             ( Node* );          // ajouter un Node au Net
            bool                                remove          ( Node* );          // retirer un Node du Net

            // XML 
            void                                toXml           ( std::ostream& );  // driver XML

        private:
            // Attributs
            Cell*               owner_;         // Cell* a laquelle appartient le Net
            const std::string   name_;          // Nom du Net
            unsigned int        id_;            // ID du Net
            Term::Type          type_;          // Type du Net
            std::vector<Node*>  nodes_;         // Vecteur des Nodes du Net

    };

    // Fonctions inline Accesseurs
    inline Cell*                        Net::getCell        () const { return owner_; }
    inline const std::string&           Net::getName        () const { return name_; }
    inline unsigned int                 Net::getId          () const { return id_; }
    inline Term::Type                   Net::getType        () const { return type_; }
    inline const std::vector<Node*>&    Net::getNodes       () const { return nodes_; }

}

#endif  // NETLIST_NET_H