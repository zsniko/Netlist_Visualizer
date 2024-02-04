// -*- explicit-buffer-name: "OpenCellDialog.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_OPENCELLDIALOG_H
#define NETLIST_OPENCELLDIALOG_H

#include <QDialog> // QDialog is a widget that is used to create a custom dialog window
#include <QLineEdit> // QLineEdit is a widget that allows to edit one line of text

namespace Netlist{

    class OpenCellDialog: public QDialog{
            Q_OBJECT;

        public:
                                    OpenCellDialog( QWidget* parent = NULL );
            static  bool            run( QString& name );
                    const QString   getCellName () const;
                    void            setCellName ( const QString& );
        protected:
                QLineEdit*      lineEdit_;
    };

}
#endif