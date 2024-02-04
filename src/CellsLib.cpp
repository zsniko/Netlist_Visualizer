// -*- explicit-buffer-name: "CellsLib.cpp<M1-MOBJ/8-10>" -*-

#include "CellsLib.h"

namespace Netlist
{
    CellsLib::CellsLib(QWidget *parent)
    : QWidget(parent), cellViewer_(NULL), baseModel_(new CellsModel(this)),
    view_(new QTableView(this)), load_(new QPushButton("Load", this))
    {
        setAttribute(Qt::WA_QuitOnClose, false);
        setAttribute(Qt::WA_DeleteOnClose, false);
        setContextMenuPolicy(Qt::ActionsContextMenu);
        view_->setShowGrid(false); // hide grid 
        view_->setAlternatingRowColors(true);
        view_->setSelectionBehavior(QAbstractItemView::SelectRows);
        view_->setSelectionMode(QAbstractItemView::SingleSelection); 
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
        QHBoxLayout * hLayout = new QHBoxLayout();
        hLayout->addStretch();
        hLayout->addWidget(load_);
        QVBoxLayout * vLayout = new QVBoxLayout();
        vLayout->addWidget(view_);
        vLayout->addLayout(hLayout);
        setLayout(vLayout);
    } 

    void CellsLib::setCellViewer(CellViewer* cellviewer)
    {
        cellViewer_ = cellviewer;
    }

    int CellsLib::getSelectedRow() const
    {
        QModelIndexList selecteds = view_->selectionModel()->selection().indexes();
        if (selecteds.empty()) return -1;
        return selecteds.first().row(); // QModelIndex: row and column. first() returns the first element. row() returns the row of the element
    }

    void CellsLib::load()
    {
        int selectedRow = getSelectedRow();
        if (selectedRow < 0) return;
        cellViewer_->setCell( baseModel_->getModel(selectedRow) );
    }

}