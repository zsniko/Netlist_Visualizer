// -*- explicit-buffer-name: "CellViewer.cpp<M1-MOBJ/8-10>" -*-

#include "CellViewer.h"
#include "SaveCellDialog.h"
#include "OpenCellDialog.h"
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QDialog>

namespace Netlist {

    CellViewer::CellViewer( QWidget* parent )
    : QMainWindow(parent)
    , cellWidget_(NULL)
    , cellsLib_(NULL)
    , instancesWidget_(NULL)
    , saveCellDialog_(NULL)
    {
        cellWidget_ = new CellWidget(); // Create a new CellWidget
        saveCellDialog_ = new SaveCellDialog( this ); // Create a new SaveCellDialog with the CellViewer as its parent

        setCentralWidget( cellWidget_ ); 
        
        QMenu* fileMenu = menuBar()->addMenu( "&File" ); 
        // Action 'Save As'
        QAction* action = new QAction ( "&Save As", this );
        action->setStatusTip( "Save to disk (rename) the Cell" );
        action->setShortcut ( QKeySequence("CTRL+S") );
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL(triggered()), this, SLOT(saveCell()));
        // Action 'Open Cell'
        action = new QAction( "&Open Cell", this );
        action->setStatusTip( "Open a Cell" );
        action->setShortcut( QKeySequence("CTRL+O"));
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL(triggered()), this, SLOT(openCell()));
        // Action Quit 
        action = new QAction( "&Quit", this );
        action->setStatusTip( "Quit application" );
        action->setShortcut( QKeySequence("CTRL+Q"));
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL(triggered()), this, SLOT(close()));
        // Action 'Open Instances
        instancesWidget_ = new InstancesWidget() ; // Create a new InstancesWidget with the CellViewer as its parent
        instancesWidget_->setCellViewer(this);
        action = new QAction( "&Open Instances List", this );
        action->setStatusTip( "Open the Instances List" );
        action->setShortcut( QKeySequence("CTRL+I"));
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL(triggered()), this, SLOT(showInstancesWidget()));

        // +: Action 'Open CellLib'
        cellsLib_ = new CellsLib() ; // Create a new CellsLib with the CellViewer as its parent
        cellsLib_->setCellViewer(this);
        action = new QAction( "&Open CellLib", this );
        action->setStatusTip( "Open the CellLib" );
        action->setShortcut( QKeySequence("CTRL+L"));
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL(triggered()), this, SLOT(showCellsLib()));

    }

    CellViewer::~CellViewer()
    { }

    Cell* CellViewer::getCell() const{
        return cellWidget_->getCell();
    }
    
    void CellViewer::saveCell(){
        Cell* cell = getCell();
        if (cell == NULL) return;

        QString cellName = cell->getName().c_str();
        
        if (saveCellDialog_->run(cellName)){
            cell->setName(cellName.toStdString());
            cell->save(cellName.toStdString());
        }
    }

    void CellViewer::setCell(Cell* cell){
        cellWidget_->setCell(cell);
        instancesWidget_->setCell(cell);
        //+ 
        cellsLib_->getBaseModel()->setCell(cell);
    }

    void CellViewer::openCell(){ 
        QString cellName; 
        Cell* cell;
        if (OpenCellDialog::run(cellName)){
            cell = Cell::find(cellName.toStdString());
            if(cell){ // If the cell already exists
                std::cerr << "Duplicate cell found" << std::endl; 
            }
            else{
                cell = Cell::load(cellName.toStdString());
                if(cell){
                    cell->setName(cellName.toStdString()); 
                    this->setCell(cell);
                }
                else return;
            }
        }
    }

    void CellViewer::showInstancesWidget(){
        instancesWidget_->show();
    }

    // +: Show the CellsLib
    void CellViewer::showCellsLib(){
        cellsLib_->show();
    }
}
