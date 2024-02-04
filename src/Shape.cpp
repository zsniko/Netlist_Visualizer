// -*- explicit-buffer-name: "shape.cpp<M1-MOBJ/8-10>" -*-

#include "Shape.h"
#include "Cell.h"
#include "Term.h"
#include "XmlUtil.h"
#include "Indentation.h"
using namespace std;

namespace Netlist{


    Shape::Shape(Symbol* s):owner_(s){ owner_->add(this); } // CTOR

    Shape::~Shape(){ owner_->remove(this); } // DTOR

    Shape* Shape::fromXml ( Symbol* owner, xmlTextReaderPtr reader )
    {
        // Factory-like method.
        const xmlChar* boxTag
            = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
        const xmlChar* ellipseTag
            = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
        const xmlChar* arcTag
            = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
        const xmlChar* lineTag
            = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
        const xmlChar* termTag
            = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
        const xmlChar* nodeName
            = xmlTextReaderConstLocalName( reader );

        Shape* shape = NULL;
        if (boxTag == nodeName)
            shape = BoxShape::fromXml( owner, reader );
        if (ellipseTag == nodeName)
            shape = EllipseShape::fromXml( owner, reader );
        if (arcTag == nodeName)
            shape = ArcShape::fromXml( owner, reader );
        if (lineTag == nodeName)
            shape = LineShape::fromXml( owner, reader );
        if (termTag == nodeName)
            shape = TermShape::fromXml( owner, reader );

        if (shape == NULL)
            cerr << "[ERROR] Unknown or misplaced tag <" << nodeName << "> (line:"
                << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;

        return shape;
    }

    Box Shape::getBoundingBox() const
    {
        return Box();
    }

    /*LineShape*/ 
    LineShape::LineShape(Symbol* s, int x1, int y1, int x2, int y2)
        :Shape(s), x1_(x1), y1_(y1), x2_(x2), y2_(y2)
    { } // CTOR
    LineShape::~LineShape(){ } // DTOR

    Box LineShape::getBoundingBox() const
    {
        return Box(x1_, y1_, x2_, y2_); 
    }

    // XML Driver for LineShape
    void LineShape::toXml(std::ostream& stream) const
    {
        stream << indent << "<line x1=\"" << LineShape::getX1() << "\" y1=\"" << LineShape::getY1() 
                << "\" x2=\"" << LineShape::getX2() << "\" y2=\"" << LineShape::getY2() << "\"/>" << endl;
    }

    // XML Parser for LineShape
    LineShape* LineShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
    {
        std::string x1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string y1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string x2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x2"));
        std::string y2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y2"));
        if ((not (x1.empty() and x2.empty() and y1.empty() and y2.empty()))){
            // Create a new LineShape
            LineShape* lineshape = new LineShape(owner, atoi(x1.c_str()), atoi(y1.c_str()), atoi(x2.c_str()), atoi(y2.c_str()));
            return lineshape;
        }
        else{
            std::cerr << "Echec de chargement de 'line'" << std::endl;
            return NULL; 
        }
    }

    /*BoxShape*/
    BoxShape::BoxShape(Symbol* s, const Box& b)
        :Shape(s), box_(b)
    { } // CTOR
    BoxShape::~BoxShape(){ } // DTOR

    Box BoxShape::getBoundingBox() const
    {
        return box_;
    }

    // XML Driver for BoxShape
    void BoxShape::toXml(std::ostream& stream) const
    {
        stream << indent << "<box x1=\"" << box_.getX1() << "\" y1=\"" << box_.getY1() 
                << "\" x2=\"" << box_.getX2() << "\" y2=\"" << box_.getY2() << "\"/>" << endl;
    }

    // XML Parser for BoxShape
    BoxShape* BoxShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
    {

        std::string x1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string y1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string x2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x2"));
        std::string y2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y2"));
        if ((not (x1.empty() and x2.empty() and y1.empty() and y2.empty()))){
            // Create a new BoxShape
            BoxShape* boxshape = new BoxShape(owner, Box(atoi(x1.c_str()), atoi(y1.c_str()), atoi(x2.c_str()), atoi(y2.c_str())));
            return boxshape;
        }
        else{
            std::cerr << "Echec de chargement de 'box'" << std::endl;
            return NULL; 
        }
    }

    /*EllipseShape*/
    EllipseShape::EllipseShape(Symbol* s, const Box& b)
        :Shape(s), box_(b)
    { } // CTOR
    EllipseShape::~EllipseShape(){ } // DTOR

    Box EllipseShape::getBoundingBox() const
    {
        return box_;
    }

    // XML Driver for EllipseShape
    void EllipseShape::toXml(std::ostream& stream) const
    {
        stream << indent << "<ellipse x1=\"" << box_.getX1() << "\" y1=\"" << box_.getY1() 
                << "\" x2=\"" << box_.getX2() << "\" y2=\"" << box_.getY2() << "\"/>" << endl;
    }

    // XML Parser for EllipseShape
    EllipseShape* EllipseShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
    {
        std::string x1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string y1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string x2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x2"));
        std::string y2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y2"));
        if ((not (x1.empty() and x2.empty() and y1.empty() and y2.empty()))){
            // Create a new EllipseShape
            EllipseShape* ellipseshape = new EllipseShape(owner, Box(atoi(x1.c_str()), atoi(y1.c_str()), atoi(x2.c_str()), atoi(y2.c_str())));
            return ellipseshape;
        }
        else{
            std::cerr << "Echec de chargement de 'ellipse'" << std::endl;
            return NULL; 
        }
    }

    /*ArcShape*/
    ArcShape::ArcShape(Symbol* s, const Box& b, int start, int span)
        :Shape(s), box_(b), start_(start), span_(span)
    { } // CTOR
    ArcShape::~ArcShape(){ } // DTOR

    Box ArcShape::getBoundingBox() const
    {
        return box_;
    }

    // XML Driver for ArcShape
    void ArcShape::toXml(std::ostream& stream) const
    {
        stream << indent << "<arc x1=\"" << box_.getX1() << "\" y1=\"" << box_.getY1() 
                << "\" x2=\"" << box_.getX2() << "\" y2=\"" << box_.getY2() 
                << "\" srart=\"" << ArcShape::getStart() << "\" span=\"" << ArcShape::getSpan() << "\"/>" << endl;
    }

    // XML Parser for ArcShape
    ArcShape* ArcShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
    {
        std::string x1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string y1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string x2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x2"));
        std::string y2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y2"));
        std::string start = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"start"));
        std::string span = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"span"));

        if ((not (x1.empty() and x2.empty() and y1.empty() and y2.empty()))){
            // Create a new ArcShape
            ArcShape* arcshape = new ArcShape(owner, Box(atoi(x1.c_str()), atoi(y1.c_str()), atoi(x2.c_str()), atoi(y2.c_str())), atoi(start.c_str()), atoi(span.c_str()));
            return arcshape;
        }
        else{
            std::cerr << "Echec de chargement de 'arc'" << std::endl;
            return NULL; 
        }
    }

    /*TermShape*/

    TermShape::TermShape(Symbol* s, const std::string& name, int x1, int y1, NameAlign align)
        :Shape(s), term_(NULL), x1_(x1), y1_(y1), align_(align) // CTOR
    {
        term_ = s->getCell()->getTerm(name);
    }

    TermShape::~TermShape(){ } // DTOR

    Box TermShape::getBoundingBox() const
    {
        return Box(x1_, y1_, x1_, y1_);
    }

    // Convert from NameAlign to string
    std::string TermShape::toString(NameAlign align) 
    {   
        switch(align){
            case TopLeft:
                return "top_left";
            case TopRight:
                return "top_right";
            case BottomLeft:
                return "bottom_left";
            case BottomRight:
                return "bottom_right";
            default:
                cerr << "Erreur conversion toString" << endl;
                exit (1);
        }
    }

    // Convert from string to NameAlign
    TermShape::NameAlign TermShape::toNameAlign(std::string align) 
    {
        if      (align == "top_left")        return TopLeft;
        else if (align == "top_right")       return TopRight;
        else if (align == "bottom_left")     return BottomLeft;
        else if (align == "bottom_right")    return BottomRight;
        else{
            cerr << "Erreur conversion toNameAlign" << endl;
            exit (1);
        }
    }

    // XML Driver for TermShape
    void TermShape::toXml(std::ostream& stream) const
    {
         stream << indent << "<term name=\"" << TermShape::getTerm()->getName() << "\" x1=\"" << TermShape::getX1() 
                << "\" y1=\"" << TermShape::getY1() << "\" align=\"" << this->toString(TermShape::getNameAlign())
                 << "\"/>" << endl;
    }

    // XML Parser for TermShape
    TermShape* TermShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
    {
        std::string x1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string y1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string name = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
        std::string align = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"align"));

        if ((not (x1.empty() and y1.empty() and name.empty() and align.empty()))){
            // Create a new TermShape
            TermShape* termshape = new TermShape(owner, name, atoi(x1.c_str()), atoi(y1.c_str()), TermShape::toNameAlign(align));
            return termshape;
        }
        else{
            std::cerr << "Echec de chargement de 'term'" << std::endl;
            return NULL; 
        }
    }


}