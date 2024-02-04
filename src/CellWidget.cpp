// -*- explicit-buffer-name: "CellWidget.cpp<M1-MOBJ/8-10>" -*-

#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QApplication>
#include  "CellWidget.h"
#include  "Term.h"
#include  "Instance.h"
#include  "Symbol.h"
#include  "Shape.h"
#include  "Cell.h"
#include  "Line.h"
#include  "Node.h"
#include  "Net.h"


namespace Netlist {

  using namespace std;


  ostream& operator<< ( ostream& o, const QRect& rect )
  {
    o << "<QRect x:" << rect.x()
      <<       " y:" << rect.y()
      <<       " w:" << rect.width()
      <<       " h:" << rect.height() << ">";
    return o;
  }


  ostream& operator<< ( ostream& o, const QPoint& p )
  { o << "<QRect x:" << p.x() << " y:" << p.y() << ">"; return o; }



  CellWidget::CellWidget ( QWidget* parent )
    : QWidget(parent)
    , cell_  (NULL)
    , viewport_( Box(0, 0, 500, 500) ) 
  {
    setAttribute    ( Qt::WA_OpaquePaintEvent );
    setAttribute    ( Qt::WA_NoSystemBackground );
    setSizePolicy   ( QSizePolicy::Expanding,   // X direction.
                      QSizePolicy::Expanding ); // Y direction.
    setFocusPolicy  ( Qt::StrongFocus );
    setMouseTracking( true );
  }


  CellWidget::~CellWidget ()
  { }


  void  CellWidget::setCell ( Cell* cell )
  {
    cell_ = cell;
    repaint(); // Qt method to repaint a cell.
  }


  QSize  CellWidget::minimumSizeHint () const
  { return QSize(500,500); }


  void  CellWidget::resizeEvent ( QResizeEvent* event )
  { 
    const QSize& size = event->size();
    // Assume the esize is always done by drawing the bottom right corner.
    viewport_.setX2( viewport_.getX1() + size.width() );
    viewport_.setY1( viewport_.getY2() - size.height() );
    cerr << "CellWidget::resizeEvent() viewport_:" << viewport_ << endl; 
  }

  void CellWidget::keyPressEvent( QKeyEvent* event )
  {
    event->ignore();
    if (event->modifiers() & (Qt::ControlModifier|Qt::ShiftModifier))
      return;
    switch (event->key()) {
      case Qt::Key_Up:    goUp(); break;
      case Qt::Key_Down:  goDown(); break;
      case Qt::Key_Left:  goLeft(); break;
      case Qt::Key_Right: goRight(); break;
      default: return;
    }
    event->accept();
  }

  void CellWidget::goRight()
  {
    viewport_.translate( Point(20, 0));
    repaint();
  }

  void CellWidget::goUp()
  {
    viewport_.translate( Point(0, 20));
    repaint();
  }

  void CellWidget::goDown()
  {
    viewport_.translate( Point(0, -20));
    repaint();
  }

  void CellWidget::goLeft()
  {
    viewport_.translate( Point(-20, 0));
    repaint();
  }

  void  CellWidget::paintEvent ( QPaintEvent* event )
  {
    QFont  bigFont = QFont( "URW Bookman L", 36 );

    QString cellName = "NULL";
    if (cell_) cellName = cell_->getName().c_str();

    QPainter painter(this);
    painter.setFont      ( bigFont );
    painter.setBackground( QBrush( Qt::black ) );
    painter.eraseRect    ( QRect( QPoint(0,0), size() ) );

    int frameWidth  = 460;
    int frameHeight = 100;
    QRect nameRect ( (size().width ()-frameWidth )/2
                   , (size().height()-frameHeight)/2
                   , frameWidth
                   , frameHeight
                   );

    painter.drawRect( nameRect );
    painter.drawText( nameRect, Qt::AlignCenter, cellName );

    QRect rect = boxToScreenRect( Box(0,0,0,0) );
    painter.drawRect( rect );
    
    painter.setPen( QPen ( Qt::red, 0 ));
    painter.setBrush( QBrush( Qt::red ));
    query(1, painter);

  }

  void CellWidget::query( unsigned int flags, QPainter& painter )
  {
    if ((not cell_) or (not flags)) return;

    // Display Shapes:
    const vector<Instance*>& instances = cell_->getInstances();

    if (instances.size() != 0){ // if there is instance
      for (size_t i=0; i<instances.size(); ++i){
        Point         instPos = instances[i]->getPosition();
        const Symbol* symbol = instances[i]->getMasterCell()->getSymbol();
        if (not symbol) continue;

        const vector<Shape*>& shapes = symbol->getShapes();
        for(size_t j=0; j<shapes.size(); ++j){
          // LineShape
          LineShape* lineShape = dynamic_cast<LineShape*>(shapes[j]);
          if (lineShape){
            Point p1 = Point(lineShape->getX1(), lineShape->getY1());
            Point p2 = Point(lineShape->getX2(), lineShape->getY2());
            p1 = p1.translate(instPos);
            p2 = p2.translate(instPos);
            QLine line = QLine(xToScreenX(p1.getX()), yToScreenY(p1.getY()), xToScreenX(p2.getX()), yToScreenY(p2.getY()));
            painter.setPen( QPen( Qt::darkGreen, 3));
            painter.drawLine(line);
          }
          // BoxShape 
          BoxShape* boxShape = dynamic_cast<BoxShape*>(shapes[j]);
          if (boxShape){
            Box box = boxShape->getBoundingBox();
            QRect rect = boxToScreenRect(box.translate(instPos));
            painter.setPen( QPen( Qt::darkGreen, 3));
            painter.drawRect(rect);
          }
          // EllipseShape
          EllipseShape* ellipseShape = dynamic_cast<EllipseShape*>(shapes[j]);
          if (ellipseShape){
            QRect rect = boxToScreenRect(ellipseShape->getBoundingBox().translate(instPos));
            painter.setPen( QPen( Qt::darkGreen, 3));
            painter.drawEllipse(rect);
          }
          // ArcShape
          ArcShape* arcShape = dynamic_cast<ArcShape*>(shapes[j]);
          if (arcShape){
            QRect rect = boxToScreenRect(arcShape->getBoundingBox().translate(instPos));
            painter.setPen( QPen( Qt::darkGreen, 3));
            painter.drawArc(rect, arcShape->getStart()*16, arcShape->getSpan()*16);
          }
          // TermShape
          TermShape* termShape = dynamic_cast<TermShape*>(shapes[j]);
          if (termShape){
            QRect rect = boxToScreenRect(termShape->getBoundingBox().translate(instPos).inflate(4));
            painter.setPen( QPen( Qt::red, 0));
            painter.drawRect(rect);
            // Display node:
            QFont font = painter.font();
            font.setPixelSize(12);
            painter.setFont(font);
            QString nodet = termShape->getTerm()->getName().c_str();
            painter.setPen( QPen( Qt::red, 0));
            painter.drawText(xToScreenX(termShape->getBoundingBox().translate(instPos).translate(-10, 12).getX1()), yToScreenY(termShape->getBoundingBox().translate(instPos).translate(-10,12).getY1()), nodet); // translate 2 times to correctly display 
          }
          else{
            // Display instance names:
            QFont font = painter.font();
            font.setPixelSize(12);
            painter.setFont(font);
            QString instName = instances[i]->getName().c_str(); // find instance name
            painter.setPen( QPen( Qt::darkGreen, 3));
            painter.drawText(xToScreenX(instances[i]->getPosition().translate(0, -15).getX()), yToScreenY(instances[i]->getPosition().translate(0, -15).getY()), instName);
          }
          // Display Terms:
          std::vector<Term*> terms = cell_->getTerms();
          for (std::vector<Term*>::iterator it = terms.begin(); it != terms.end(); ++it){
              Term* term = *it;
              // input polygone
              if (term->getDirection() == Term::In){
                  QPolygon poly = createPolygon(term, -10, -30);
                  painter.setPen ( QPen ( Qt :: red , 0 ) );
                  painter.setBrush ( QBrush ( Qt :: red ) );
                  painter.drawPolygon(poly);
              }
              // output polygone
              if (term->getDirection() == Term::Out){
                  QPolygon poly = createPolygon(term, 10, 30);
                  painter.setPen ( QPen ( Qt :: red , 0 ) );
                  painter.setBrush ( QBrush ( Qt :: red ) );
                  painter.drawPolygon(poly);
              }
              // Display term Names:
              QFont font = painter.font();
              font.setPixelSize(12);
              painter.setFont(font);
              QString termName = term->getName().c_str(); // find term name
              painter.setPen( QPen( Qt::red, 0));
              painter.drawText(xToScreenX(term->getPosition().translate(5, 10).getX()), yToScreenY(term->getPosition().translate(5, 10).getY()), termName);
          }
        }
      }
    }
    else{ // if no instance
      const vector<Shape*>& shapes = cell_->getSymbol()->getShapes();
      for(size_t j=0; j<shapes.size(); ++j){
        // LineShape
        LineShape* lineShape = dynamic_cast<LineShape*>(shapes[j]);
        if (lineShape){
          Point p1 = Point(lineShape->getX1(), lineShape->getY1());
          Point p2 = Point(lineShape->getX2(), lineShape->getY2());
          QLine line = QLine(xToScreenX(p1.getX()), yToScreenY(p1.getY()), xToScreenX(p2.getX()), yToScreenY(p2.getY()));
          painter.setPen( QPen( Qt::darkGreen, 3));
          painter.drawLine(line);
        }
        // BoxShape 
        BoxShape* boxShape = dynamic_cast<BoxShape*>(shapes[j]);
        if (boxShape){
          Box box = boxShape->getBoundingBox();
          QRect rect = boxToScreenRect(box);
          painter.setPen(QPen( Qt::darkGreen, 3));
          painter.drawRect(rect);
        }
        // EllipseShape
        EllipseShape* ellipseShape = dynamic_cast<EllipseShape*>(shapes[j]);
        if (ellipseShape){
          QRect rect = boxToScreenRect(ellipseShape->getBoundingBox());
          painter.setPen( QPen( Qt::darkGreen, 3));
          painter.drawEllipse(rect);
        }
        // ArcShape
        ArcShape* arcShape = dynamic_cast<ArcShape*>(shapes[j]);
        if (arcShape){
          QRect rect = boxToScreenRect(arcShape->getBoundingBox());
          painter.setPen( QPen( Qt::darkGreen, 3));
          painter.drawArc(rect, arcShape->getStart()*16, arcShape->getSpan()*16);
        }
        // TermShape
        TermShape* termShape = dynamic_cast<TermShape*>(shapes[j]);
        if (termShape){
          QRect rect = boxToScreenRect(termShape->getBoundingBox().inflate(4));
          painter.setPen( QPen( Qt::red, 0));
          painter.drawRect(rect);
        }
      }
    }

    // Display Lines:
    std::vector<Net*> nets = cell_->getNets();

    for(std::vector<Net*>::iterator it = nets.begin(); it != nets.end(); ++it) {

        std::vector<Line*> it_lines = (*it)->getLines();
        std::vector<Node*> it_nodes = (*it)->getNodes();

        for(std::vector<Line*>::iterator it_line = it_lines.begin(); it_line != it_lines.end(); ++it_line) {

            Point position_source = (*it_line)->getSourcePosition();
            Point position_target = (*it_line)->getTargetPosition();

            QLine line1 = QLine(xToScreenX(position_source.getX()), yToScreenY(position_source.getY()), xToScreenX(position_target.getX()), yToScreenY(position_target.getY()));
            painter.setPen(QPen(Qt::cyan, 1));
            painter.drawLine(line1);
        }

        for(std::vector<Node*>::iterator it_node = it_nodes.begin(); it_node != it_nodes.end(); ++it_node) {

            NodePoint* node_point = dynamic_cast<NodePoint*>(*it_node);

            if(node_point) {
                int compteur = 0;
                std::vector<Line*> lines = (*it)->getLines();

                for(std::vector<Line*>::iterator it_line = lines.begin(); it_line != lines.end(); ++it_line) {

                    if(node_point == dynamic_cast<NodePoint*>((*it_line)->getSource()) || node_point == dynamic_cast<NodePoint*>((*it_line)->getTarget())) {
                        compteur++;
                    }

                    if(compteur > 2) {
                        QPoint point = QPoint(xToScreenX(node_point->getPosition().getX()), yToScreenY(node_point->getPosition().getY()));
                        painter.setPen(QPen(Qt::cyan, 1));
                        painter.drawEllipse(point, 3, 3);
                        break;
                    }
                }
            }
        }
    }
  }

  // Helper function for drawing input and output polygons
  QPolygon CellWidget::createPolygon(Term* term, int offset1, int offset2) {
    QPolygon poly;
    Point p1,p2,p3,p4,p5;                                   
    p1.setX(0 + term->getPosition().getX());
    p1.setY(0 + term->getPosition().getY());
    p2.setX(offset1 + term->getPosition().getX());
    p2.setY(10 + term->getPosition().getY());
    p3.setX(offset2 + term->getPosition().getX());
    p3.setY(10 + term->getPosition().getY());
    p4.setX(offset2 + term->getPosition().getX());
    p4.setY(-10 + term->getPosition().getY());
    p5.setX(offset1 + term->getPosition().getX());
    p5.setY(-10 + term->getPosition().getY());
    
    poly << pointToScreenPoint(p1)
        << pointToScreenPoint(p2)
        << pointToScreenPoint(p3)
        << pointToScreenPoint(p4)
        << pointToScreenPoint(p5)
        << pointToScreenPoint(p1);
    return poly;
}

}  // Netlist namespace.




















