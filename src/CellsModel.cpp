// -*- explicit-buffer-name: "CellsModel.cpp<M1-MOBJ/8-10>" -*-

#include "CellsModel.h"

using namespace std;

namespace Netlist
{

    // CTOR
    CellsModel::CellsModel(QObject *parent)
    : QAbstractTableModel(parent), cell_(NULL)
    { }

    // DTOR
    CellsModel::~CellsModel()
    { }

    void CellsModel::setCell(Cell* c)
    {
        emit layoutAboutToBeChanged();
        cell_ = c;
        emit layoutChanged();
    }

    Cell* CellsModel::getModel(int row)
    {
        if (!cell_ || row >= (int)cell_->getAllCells().size()) return NULL;
        return cell_->getAllCells()[row];
    }

    int CellsModel::rowCount(const QModelIndex& parent) const
    {
        return cell_ ? cell_->getAllCells().size() : 0;
    }

    int CellsModel::columnCount(const QModelIndex& parent) const
    {
        return 1;
    }

    QVariant CellsModel::data(const QModelIndex& index, int role) const
    {
        if (!cell_) return QVariant();
        if (!index.isValid()) return QVariant();
        if (role == Qt::DisplayRole)
        {
            if (index.column() == 0)
                return Cell::getAllCells()[index.row()]->getName().c_str();
        }
        return QVariant();
    }

    QVariant CellsModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (orientation == Qt::Horizontal || role == Qt::DisplayRole)
        {
            switch (section)
            {
                case 0: return "Cell";
            }
        }
        return QVariant();
    }

    void CellsModel::updateDatas()
    {
        emit layoutAboutToBeChanged();
        cell_ = Cell::getAllCells()[rowCount()];
        emit layoutChanged();
    }




















    
}