// -*- explicit-buffer-name: "Symbol.cpp<M1-MOBJ/7>" -*-#include  <libxml/xmlreader.h>
#include  <string>
#include  <vector>
#include  <iostream>
#include  <libxml/xmlreader.h>
#include "Cell.h"
#include "Symbol.h"
#include "Term.h"
#include "Shape.h"
using namespace std;

namespace Netlist{

    Symbol::Symbol ( Cell* cell )
    : owner_(cell)
    , shapes_( )
    { }

    Symbol::~Symbol ()
    { }

    Cell* Symbol::getCell () const 
    { 
        return owner_; 
    }


    Point Symbol::getTermPosition ( Term* t ) const 
    {
        return t->getPosition();
    }

    TermShape* Symbol::getTermShape ( Term* t ) const 
    {
        for ( std::vector<Shape*>::const_iterator ishape = shapes_.begin(); ishape != shapes_.end(); ++ishape ){
            TermShape* termShape = dynamic_cast<TermShape*>(*ishape);
            if ( termShape )
                if ( t->getName() == termShape->getTerm()->getName() )
                    return termShape;
        }
        return NULL;
    }

    void Symbol::add( Shape* s )
    {
        if (s) shapes_.push_back(s);
    }

    void Symbol::remove( Shape* s )
    {
        for(std::vector<Shape*>::const_iterator ishape = shapes_.begin(); ishape != shapes_.end(); ++ishape){
            if ( *ishape == s )
                shapes_.erase(ishape);
        }
    }

    void Symbol::toXml( std::ostream& stream ) const
    {
        stream << indent++ << "<symbol>" << endl;
        for ( std::vector<Shape*>::const_iterator ishape=shapes_.begin(); ishape!=shapes_.end(); ++ishape){
            (*ishape)->toXml(stream);
        }
        stream << --indent << "</symbol>" << endl;
    }

    Symbol* Symbol::fromXml( Cell* cell, xmlTextReaderPtr reader)
    {
        const xmlChar* symbolTag = xmlTextReaderConstString( reader, (const xmlChar*)"symbol");
        Symbol* symbol = cell->getSymbol();

        while(true){

            int status = xmlTextReaderRead(reader);
            if (status != 1){
                if (status != 0){ // erreur syntaxe
                    cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << endl;
                }
                break;
            }
            switch (xmlTextReaderNodeType(reader)){
                case XML_READER_TYPE_COMMENT:
                case XML_READER_TYPE_WHITESPACE:
                case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                    continue;
            }
            
            const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );

            if ((nodeName == symbolTag) && xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT){
                return symbol; // !!
            }
            else {
                if(Shape::fromXml(symbol, reader)) continue;
            }


        }
        return symbol;
    }




}






