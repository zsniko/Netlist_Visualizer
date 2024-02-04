// -*- explicit-buffer-name: "OpenCellDialog.cpp<M1-MOBJ/8-10>" -*-

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "OpenCellDialog.h"

namespace Netlist{

    OpenCellDialog::OpenCellDialog ( QWidget* parent ) // Constructor
        : QDialog(parent)
        , lineEdit_(NULL)
    {
        setWindowTitle( tr("Open Cell") ); // Set the title of the dialog window to "Save Cell"
        
        QLabel* label = new QLabel(); // Create a new QLabel widget
        label->setText( tr("Entrez le nom de la Cell") ); // Set the text of the label widget
        
        lineEdit_ = new QLineEdit(); // Create a new QLineEdit widget
        lineEdit_->setMinimumWidth( 400 ); //Set the minimum width of the line edit widget to 400 pixels

        QPushButton* okButton = new QPushButton(); // Create a new QPushbutton widget for the OK button
        okButton->setText( tr("OK") ); // Set the text of the OK button to "OK"
        okButton->setDefault( true ); // Set the OK button as the default button of the dialog window

        QPushButton* cancelButton = new QPushButton(); 
        cancelButton->setText( tr("Cancel") );

        QHBoxLayout* hLayout = new QHBoxLayout(); // Create a new horizontal box layout
        hLayout->addStretch(); // Add stretchable space to the left of the layout, pushing the buttons to the right
        hLayout->addWidget( okButton ); // Add the OK button to the layout
        hLayout->addStretch(); 
        hLayout->addWidget( cancelButton ); // Add the Cancel button to the layout
        hLayout->addStretch();

        QFrame* separator = new QFrame(); // Create a new frame widget to be used as a separator
        separator->setFrameShape( QFrame::HLine ); // Set the shape of the frame to a horizontal line
        separator->setFrameShadow( QFrame::Sunken ); // Set the shadow of the frame to sunken, giving it a 3D look
        
        QVBoxLayout* vLayout = new QVBoxLayout(); // Create a new vertical box layout
        vLayout->setSizeConstraint( QLayout::SetFixedSize ); // Set the size constraint of the layout to fixed size, it will not resize to fit its contents
        vLayout->addWidget( label ); // Add the label widget to the layout
        vLayout->addWidget( lineEdit_ ); // Add the line edit widget to the layout
        vLayout->addLayout( hLayout ); // Add the HORIZONTAL LAYOUT to the vertical layout
        
        setLayout( vLayout ); // Set the layout of the dialog to the vertical layout

        connect( okButton, SIGNAL(clicked()), this, SLOT(accept()) );
        connect( cancelButton, SIGNAL(clicked()), this, SLOT(reject()) );
        
    }

    const QString OpenCellDialog::getCellName () const{
        return lineEdit_->text(); 
    }

    void OpenCellDialog::setCellName ( const QString& name ){
        return lineEdit_->setText(name);
    }

    bool OpenCellDialog::run ( QString& name ){
        OpenCellDialog* d = new OpenCellDialog();
        d->setCellName(name);
        int dialogResult = d->exec(); // Dialog remains open until the user clicks on OK or Cancel
        name = d->getCellName();
        delete d; 
        return (dialogResult == Accepted); 
    }












}