// -*- explicit-buffer-name: "SaveCellDialog.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_SAVECELLDIALOG_H
#define NETLIST_SAVECELLDIALOG_H

#include <QDialog> // QDialog is a widget that is used to create a custom dialog window
#include <QLineEdit> // QLineEdit is a widget that allows to edit one line of text

namespace Netlist{


    class SaveCellDialog: public QDialog{
            Q_OBJECT;

        public:
                                SaveCellDialog( QWidget* parent = NULL );
                bool            run( QString& name );
                const QString   getCellName () const;
                void            setCellName ( const QString& );
        protected:
                QLineEdit*      lineEdit_;
    };

}

#endif