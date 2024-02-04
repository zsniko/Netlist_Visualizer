// -*- explicit-buffer-name: "CellsLib.h<M1-MOBJ/8-10>" -*-

#ifndef CELLSLIB_H
#define CELLSLIB_H

#include "CellViewer.h"
#include "CellsModel.h"
#include <QTableView>
#include <QPushButton>
#include "InstancesModel.h"
#include "InstancesWidget.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>

namespace Netlist
{

class CellsLib : public QWidget {
    Q_OBJECT;
  public:
                       CellsLib       ( QWidget* parent=NULL );
           void        setCellViewer  ( CellViewer* );
           int         getSelectedRow () const;
    inline CellsModel* getBaseModel   ();
  public slots:
           void        load           ();
  private:
    CellViewer*  cellViewer_;
    CellsModel*  baseModel_;
    QTableView*  view_;
    QPushButton* load_;
};

inline CellsModel* CellsLib::getBaseModel() { return baseModel_; }

}
#endif 