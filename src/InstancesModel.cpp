// -*- explicit-buffer-name: "InstancesModel.cpp<M1-MOBJ/8-10>" -*-

#include "InstancesModel.h"
#include "Instance.h"
#include "Cell.h"

namespace Netlist{

    InstancesModel::InstancesModel( QObject* parent )
    : QAbstractTableModel(parent)
    , cell_(NULL)
    { }

    InstancesModel::~InstancesModel()
    { }

    void InstancesModel::setCell( Cell* cell )
    {
        emit layoutAboutToBeChanged(); // emit a signal to stop refreshing the widget 
        cell_ = cell; 
        emit layoutChanged(); 
    }

    // Count the number of rows 
    int InstancesModel::rowCount( const QModelIndex& parent ) const
    { return (cell_)? cell_->getInstances().size() : 0; }

    // Count the number of columns: always 2
    int InstancesModel::columnCount( const QModelIndex& parent ) const
    { return 2; }

    // Select row, return MasterCell
    Cell* InstancesModel::getModel( int row )
    {
        if (not cell_) return NULL; 
        if (row >= (int)cell_->getInstances().size()) return NULL;
        return cell_->getInstances()[row]->getMasterCell();
    }

    // QVariant: a type-safe union for Qt
    QVariant InstancesModel::data( const QModelIndex& index, int role ) const 
    {   
        // role: which type of data to return (Qt:DisplayRole: the data will be displayed in the view)
        if(not cell_ or not index.isValid()) return QVariant(); 
        if(role == Qt::DisplayRole){ 
            int row = index.row();
            switch(index.column()){
                case 0: return cell_->getInstances()[row]->getName().c_str();
                case 1: return cell_->getInstances()[row]->getMasterCell()->getName().c_str();
            }
        }
        return QVariant();
    }

    QVariant InstancesModel::headerData( int section, Qt::Orientation orientation, int role ) const 
    {      
        if (orientation == Qt::Vertical) return QVariant(); // no vertical header, only horizontal header
        if (role != Qt::DisplayRole) return QVariant(); 
        switch(section){
            case 0: return "Instance";
            case 1: return "MasterCell";
        }
        return QVariant();
    }
}