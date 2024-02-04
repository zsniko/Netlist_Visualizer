// -*- explicit-buffer-name: "shape.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include "Symbol.h"
#include "Cell.h"
#include "Term.h"
#include "Box.h"
#include "XmlUtil.h"

namespace Netlist{


    class Cell;
    class Term;
    class Symbol;

    class Shape{
        public:
                                Shape ( Symbol* ); // CTOR
                                ~Shape(); // DTOR
        
            virtual     Box     getBoundingBox  () const = 0; 
            inline      Symbol* getSymbol       () const;
            virtual     void    toXml           (std::ostream&) const = 0;
            static      Shape*  fromXml         (Symbol*, xmlTextReaderPtr); // static so that it can be called without an instance of Shape

        private:
            Symbol*     owner_;
    };

    inline Symbol* Shape::getSymbol() const { return owner_; }

    class LineShape: public Shape{
        public: 
                                    LineShape       ( Symbol*, int x1, int y1, int x2, int y2 );
                                    ~LineShape      ();
                        Box         getBoundingBox  () const;
            inline      int         getX1           () const;
            inline      int         getY1           () const;
            inline      int         getX2           () const;
            inline      int         getY2           () const;
                        void        toXml           (std::ostream&) const;
            static      LineShape*  fromXml         (Symbol*, xmlTextReaderPtr); 
        
        private:
            int         x1_, y1_, x2_, y2_;
    };
    inline int                      LineShape::getX1        () const { return x1_; }
    inline int                      LineShape::getY1        () const { return y1_; }
    inline int                      LineShape::getX2        () const { return x2_; }
    inline int                      LineShape::getY2        () const { return y2_; }

    class BoxShape: public Shape{
        public: 
                                    BoxShape        ( Symbol*, const Box& );
                                    ~BoxShape       ();
                        Box         getBoundingBox  () const;
                        void        toXml           (std::ostream&) const;
            static      BoxShape*   fromXml         (Symbol*, xmlTextReaderPtr); 
        
        private:
            Box         box_;
    };

    class EllipseShape: public Shape{
        public: 
                                        EllipseShape    ( Symbol*, const Box& );
                                        ~EllipseShape   ();
                        Box             getBoundingBox  () const;
                        void            toXml           (std::ostream&) const;
            static      EllipseShape*   fromXml         (Symbol*, xmlTextReaderPtr); 
        
        private:
            Box         box_;
    };

    class ArcShape: public Shape{
        public: 
                                        ArcShape        ( Symbol*, const Box&, int start, int span );
                                        ~ArcShape       ();
                        Box             getBoundingBox  () const;
            inline      int             getStart        () const;
            inline      int             getSpan         () const;
                        void            toXml           (std::ostream&) const;
            static      ArcShape*       fromXml         (Symbol*, xmlTextReaderPtr); 
        
        private:
            Box         box_;
            int         start_, span_;
    };
    inline int                      ArcShape::getStart      () const { return start_; }
    inline int                      ArcShape::getSpan       () const { return span_; }

    class TermShape: public Shape{
        public: 
            enum NameAlign { TopLeft=1, TopRight, BottomLeft, BottomRight };

                                        TermShape       ( Symbol*, const std::string&, int x1, int y1, NameAlign );
                                        ~TermShape      ();
                        Box             getBoundingBox  () const;
            inline      Term*           getTerm         () const;
            inline      int             getX1           () const;
            inline      int             getY1           () const;
            inline      NameAlign       getNameAlign    () const;
            static      std::string     toString        ( NameAlign );
            static      NameAlign       toNameAlign     ( std::string );
                        void            toXml           (std::ostream&) const;
            static      TermShape*      fromXml         (Symbol*, xmlTextReaderPtr); 
        
        private:
            Term*       term_;
            int         x1_, y1_;
            NameAlign   align_;
    };
    inline Term*                    TermShape::getTerm      () const { return term_; }
    inline int                      TermShape::getX1        () const { return x1_; }
    inline int                      TermShape::getY1        () const { return y1_; }
    inline TermShape::NameAlign     TermShape::getNameAlign () const { return align_; }




















}

#endif  // NETLIST_SHAPE_H