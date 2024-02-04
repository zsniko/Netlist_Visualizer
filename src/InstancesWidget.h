// -*- explicit-buffer-name: "InstancesWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_INSTANCESWIDGET_H
#define NETLIST_INSTANCESWIDGET_H

#include "InstancesModel.h"
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Netlist{

    class Cell;
    class CellViewer;

    class InstancesWidget: public QWidget{
            Q_OBJECT;  
        public:
                                InstancesWidget ( QWidget* parent=NULL );
                void            setCellViewer   ( CellViewer* );
                int             getSelectedRow  () const;
        inline  void            setCell         ( Cell* cell );
        public slots:
                void            load            ();
        private:
                CellViewer*     cellViewer_;
                InstancesModel* baseModel_;
                QTableView*     view_;
                QPushButton*    load_;
    };
    inline void InstancesWidget::setCell( Cell* cell ) { baseModel_->setCell(cell); }
}

#endif