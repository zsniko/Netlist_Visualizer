// -*- explicit-buffer-name: "CellViewer.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELLVIEWER_H
#define NETLIST_CELLVIEWER_H

#include <QMainWindow>
#include "Cell.h"
#include "CellWidget.h"
#include "InstancesWidget.h"
#include "CellsLib.h"

namespace Netlist{

class Cell;
class CellWidget;
class SaveCellDialog;
class CellsLib;

class CellViewer : public QMainWindow { // inheritance
        Q_OBJECT ;
    public :
                            CellViewer  ( QWidget * parent = NULL );
        virtual             ~CellViewer ();
                Cell*       getCell     () const;
        inline  CellsLib*   getCellsLib () const;

    public slots :
                void        setCell             ( Cell* );
                void        saveCell            ();
                void        openCell            ();
                void        showCellsLib        ();
                void        showInstancesWidget ();
    private :
        CellWidget*         cellWidget_;
        CellsLib*           cellsLib_;
        InstancesWidget*    instancesWidget_;
        SaveCellDialog*     saveCellDialog_ ;
};

inline CellsLib* CellViewer::getCellsLib() const { return cellsLib_; }

}

#endif