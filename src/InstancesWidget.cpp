// -*- explicit-buffer-name: "InstancesWidget.cpp<M1-MOBJ/8-10>" -*-

#include "InstancesWidget.h"
#include "InstancesModel.h"
#include "CellViewer.h"
#include <QHeaderView>
#include <Cell.h>

namespace Netlist{

    InstancesWidget::InstancesWidget( QWidget* parent )
    : QWidget(parent)
    , cellViewer_(NULL)
    , baseModel_(new InstancesModel(this))
    , view_(new QTableView(this))
    , load_(new QPushButton("Load", this))
    {
        setAttribute(Qt::WA_QuitOnClose, false); // Just close the window, not the application
        setAttribute(Qt::WA_DeleteOnClose, false); // We keep the window in memory
        setContextMenuPolicy(Qt::ActionsContextMenu); 
        view_->setShowGrid(false); // Hide the grid
        view_->setAlternatingRowColors(true); // Alternate colors of rows
        view_->setSelectionBehavior(QAbstractItemView::SelectRows); 
        view_->setSelectionMode(QAbstractItemView::SingleSelection); // Select only one row at a time
        view_->setSortingEnabled(true); 
        view_->setModel(baseModel_); 
        
        QHeaderView* horizontalHeader = view_->horizontalHeader();
        horizontalHeader->setDefaultAlignment(Qt::AlignHCenter); 
        horizontalHeader->setMinimumSectionSize(300);
        horizontalHeader->setStretchLastSection(true);
        QHeaderView* verticalHeader = view_->verticalHeader();
        verticalHeader->setVisible(false); // Here no vertical header
        
        load_->setText("Load");
        connect(load_, SIGNAL(clicked()), this, SLOT(load()));
        
        // Add Layout
        QHBoxLayout * hLayout = new QHBoxLayout();
        hLayout->addStretch();
        hLayout->addWidget( load_ );
        hLayout->addStretch();
        QVBoxLayout* vLayout = new QVBoxLayout();
        vLayout->addWidget( view_ );
        vLayout->addLayout( hLayout );
        setLayout( vLayout );

    }


    int InstancesWidget::getSelectedRow() const 
    {
        QModelIndexList selecteds = view_->selectionModel()->selection().indexes();
        if (selecteds.empty()) return -1;
        return selecteds.first().row(); // QModelIndex: row and column. first() returns the first element. row() returns the row of the element
    }

    void InstancesWidget::load()
    {
        int selectedRow = getSelectedRow();
        if (selectedRow < 0) return;
        cellViewer_->setCell( baseModel_->getModel(selectedRow) );
    }

    void InstancesWidget::setCellViewer( CellViewer* cellviewer )
    {
        cellViewer_ = cellviewer;
    }

}