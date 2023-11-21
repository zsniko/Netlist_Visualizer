// -*- explicit-buffer-name: "Net.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_NET_H
#define NETLIST_NET_H

#include "Term.h"
#include "Line.h"
#include <fstream>
#include "XmlUtil.h"
#include <libxml/xmlreader.h>

namespace Netlist{
    
    class Cell;
    class Node;
    class Line;

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
            inline Node*                 	    getNode         ( size_t  id ) 	const;
            size_t                              getFreeNodeId   () const;           // recuperer l'id du premier Node NULL du vecteur des Nodes du Net
            inline const std::vector<Line*>&    getLines        () const;           // recuperer le vecteur des Lines du Net

            // Modificateurs
            void                                add             ( Node* );          // ajouter un Node au Net
            bool                                remove          ( Node* );          // retirer un Node du Net
            void                                add             ( Line* );          // ajouter une Line au Net
            bool                                remove          ( Line* );          // retirer une Line du Net
            
            // XML 
            void                                toXml           ( std::ostream& ) const;    // driver XML
            static  Net*                        fromXml         ( Cell*, xmlTextReaderPtr );// parseur XML

        private:
            // Attributs
            Cell*               owner_;         // Cell* a laquelle appartient le Net
            const std::string   name_;          // Nom du Net
            unsigned int        id_;            // ID du Net
            Term::Type          type_;          // Type du Net
            std::vector<Node*>  nodes_;         // Vecteur des Nodes du Net
            std::vector<Line*>  lines_;         // Vecteur des Lines du Net

    };

    // Fonctions inline Accesseurs
    inline Cell*                        Net::getCell        () const { return owner_; }
    inline const std::string&           Net::getName        () const { return name_; }
    inline unsigned int                 Net::getId          () const { return id_; }
    inline Term::Type                   Net::getType        () const { return type_; }
    inline const std::vector<Node*>&    Net::getNodes       () const { return nodes_; }
    inline Node*                        Net::getNode        ( size_t id ) const { return (id < nodes_.size()) ? nodes_[id] : NULL; }

    inline const std::vector<Line*>&    Net::getLines       () const{ return lines_; }

}

#endif  // NETLIST_NET_H