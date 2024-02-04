// -*- explicit-buffer-name: "Net.cpp<M1-MOBJ/8-10>" -*-

#include "Net.h"
#include "Cell.h"
using namespace std;

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
                NodeTerm* node = dynamic_cast<NodeTerm*> (*it) ; 
                (node)->getTerm()->setNet(NULL);
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

    // void Net::add( Node* n )
    // {  
    //     if (n != NULL){
    //         size_t id = getFreeNodeId(); // get l'indice du premier element NULL
    //         n->setId(id); // On set l'id du Node
    //         if (id < nodes_.size()) // Si l'indice est inferieur a la taille du vecteur
    //             nodes_[id] = n; // On remplace l'element NULL par le Node
    //         else
    //             nodes_.push_back(n); // Sinon on insere le Node a la fin du vecteur
    //     }
    // }

    void Net::add ( Node* n )
    {
        if (n){
            size_t id = n->getId();
            if (id == Node::noid){
                id = getFreeNodeId();
                n->setId(id);
            }
            if (id < nodes_.size())
                nodes_[id] = n;
            else{
                for (size_t i=nodes_.size(); i<id; ++i){
                    nodes_.push_back(NULL); // On ajoute des elements NULL au vecteur jusqu'a ce que l'indice soit egal a l'id du Node.  
                }
                nodes_.push_back(n);
            }
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

     // ajouter un Line au Net
    void  Net::add ( Line* line )
    { if (line) lines_.push_back( line ); }

    // retirer un Line du Net
    bool  Net::remove ( Line* line )
    {
        if (line) {
            for ( vector<Line*>::iterator il = lines_.begin(); il != lines_.end() ; ++il ) {
                if (*il == line) {
                    lines_.erase( il );
                    return true;
                }
            }
        }
        return false;
    }

    // XML driver
    void Net::toXml( std::ostream& stream ) const
    { 
        stream << indent++ << "<net name=\"" << name_ << "\" type=\"" << Term::toString(type_) << "\">" << std::endl; // <net name = "xxx" type = "xxx">

        for ( std::vector<Node*>::const_iterator inode = nodes_.begin(); inode != nodes_.end(); ++inode ){
            if (*inode != NULL) 
                (*inode)->toXml(stream);
        }
        for ( std::vector<Line*>::const_iterator iline = lines_.begin(); iline != lines_.end(); ++iline ){
            if (*iline != NULL)
                (*iline)->toXml(stream);
        }
        
        stream << --indent << "</net>" << std::endl; // </net>
    }

    // XML parseur 
    Net* Net::fromXml( Cell* cell, xmlTextReaderPtr reader)
    {   

        enum State  { Init, Begin }; // Machine a deux etats
        const xmlChar* netTag = xmlTextReaderConstString ( reader, (const xmlChar*)"net" );

        Net* net = NULL;
        State state = Init;        

        // Lire le 1er net pour qu'il ne soit pas neglige
        const xmlChar* nodeName = xmlTextReaderConstLocalName(reader);
        if ((nodeName == netTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT)){       
            std::string name_s        = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"name") );
            std::string type_s        = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"type") );
            if (!name_s.empty() && !type_s.empty()){
                net = new Net (cell, name_s, Term::toType(type_s)); // creer Net
                state = Begin;
            }   
        } 

        while (true) {
            
            int status = xmlTextReaderRead(reader);
            if (status != 1){
                if (status != 0) {
                    std::cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << std::endl;
                }
                break;
            }

            switch ( xmlTextReaderNodeType(reader) ) {
                case XML_READER_TYPE_COMMENT:
                case XML_READER_TYPE_WHITESPACE:
                case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                continue;
            } 

            switch (state){
                case Init:
                    if ((nodeName == netTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT)){
                       
                        std::string name_s        = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"name") );
                        std::string type_s        = xmlCharToString ( xmlTextReaderGetAttribute ( reader, (const xmlChar*)"type") );
                        if (!name_s.empty() && !type_s.empty()){
                            net = new Net (cell, name_s, Term::toType(type_s)); // creer Net
                            state = Begin; // state change a Begin
                            continue;
                        }   
                    }
                break; 

                case Begin:
                    if ((nodeName == netTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)){
                        state = Init; // state change a Init
                        return net; 
                        continue;
                    }
                    else{
                        if (Node::fromXml( net, reader )) continue;
                        if (Line::fromXml( net, reader )) continue;
                    }
                break;

                default:
                break;
        
            }
        }
        return NULL;
    }
    
}

