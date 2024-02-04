// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
class QPainter;
#include "Box.h"
#include "Term.h"


namespace Netlist {

  class Cell;
  class NodeTerm;


  class CellWidget : public QWidget {
      Q_OBJECT;
    public:
                        CellWidget         ( QWidget* parent=NULL );
      virtual           ~CellWidget        ();
              void      setCell            ( Cell* );
      inline  Cell*     getCell            () const;
      inline  int       xToScreenX         ( int x ) const;
      inline  int       yToScreenY         ( int y ) const;
      inline  QRect     boxToScreenRect    ( const Box& ) const;
      inline  QPoint    pointToScreenPoint ( const Point& ) const;
      inline  int       screenXToX         ( int x ) const;
      inline  int       screenYToY         ( int y ) const;
      inline  Box       screenRectToBox    ( const QRect& ) const;
      inline  Point     screenPointToPoint ( const QPoint& ) const;
      virtual QSize     minimumSizeHint    () const;
      virtual void      resizeEvent        ( QResizeEvent* );
              void      query              ( unsigned int flags, QPainter& painter );
              QPolygon  createPolygon(Term* term, int offset1, int offset2);
    protected:
      virtual void      paintEvent         ( QPaintEvent* );
      virtual void      keyPressEvent      ( QKeyEvent* );
    public slots:
              void      goLeft             ();
              void      goRight            ();
              void      goUp               ();
              void      goDown             ();
    private:
      Cell* cell_;
      Box   viewport_;
  };


  inline Cell* CellWidget::getCell () const { return cell_; }
  // Netlist to screen: 
  inline int   CellWidget::xToScreenX ( int x ) const { return x - viewport_.getX1(); }  // Xscreen = Xnetlist - X1_viewport
  inline int   CellWidget::yToScreenY ( int y ) const { return viewport_.getY2() - y; }  // Yscreen = Y2_viewport - Ynetlist
  // Screen to netlist:
  inline int   CellWidget::screenXToX ( int x ) const { return x + viewport_.getX1(); }  // Xnetlist = Xscreen + X1_viewport
  inline int   CellWidget::screenYToY ( int y ) const { return viewport_.getY2() + y; }  // Ynetlist = Y2_viewport - Yscreen

  inline QRect  CellWidget::boxToScreenRect( const Box& box ) const { return QRect(xToScreenX(box.getX1()), yToScreenY(box.getY1()), xToScreenX(box.getX2()) - xToScreenX(box.getX1()), yToScreenY(box.getY2()) - yToScreenY(box.getY1())); }
  inline QPoint CellWidget::pointToScreenPoint( const Point& pt ) const { return QPoint(xToScreenX(pt.getX()), yToScreenY(pt.getY())); }
  inline Box    CellWidget::screenRectToBox( const QRect& rect ) const { return Box(screenXToX(rect.x()), screenYToY(rect.y()), screenXToX(rect.x() + rect.width()), screenYToY(rect.y() + rect.height())); }
  inline Point  CellWidget::screenPointToPoint( const QPoint& qpt ) const { return Point(screenXToX(qpt.x()), screenYToY(qpt.y())); }

}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H






