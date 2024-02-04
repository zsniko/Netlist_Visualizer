// -*- explicit-buffer-name: "SaveCellDialog.cpp<M1-MOBJ/8-10>" -*-

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "SaveCellDialog.h"

namespace Netlist{

    SaveCellDialog::SaveCellDialog ( QWidget* parent ) // Constructor
        : QDialog(parent)
        , lineEdit_(NULL)
    {
        setWindowTitle( tr("Save Cell") ); // Set the title of the dialog window to "Save Cell"
        
        QLabel* label = new QLabel(); // Create a new QLabel widget
        label->setText( tr("Enter Cell name (without extension)") ); // Set the text of the label widget
        
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

        // Connect the OK button to the accept() slot of the dialog window
        // The accept() slot is a slot of QDialog that closes the dialog and sets its result code to Accepted
        // The result code is used by the run() method to know if the user clicked on OK or Cancel
        connect( okButton, SIGNAL(clicked()), this, SLOT(accept()) );
        // Connect the Cancel button to the reject() slot of the dialog window
        // The reject() slot is a slot of QDialog that closes the dialog and sets its result code to Rejected
        // The result code is used by the run() method to know if the user clicked on OK or Cancel
        connect( cancelButton, SIGNAL(clicked()), this, SLOT(reject()) );
        // The accept() and reject() methods are part of the QDialog class, which SaveCellDIalog inherits from.
        // accept() sets the dialog's result code to Accepted, and reject() sets it to Rejected.
    }

    const QString SaveCellDialog::getCellName () const{
        return lineEdit_->text(); 
    }

    void SaveCellDialog::setCellName ( const QString& name ){
        return lineEdit_->setText(name);
    }

    bool SaveCellDialog::run ( QString& name ){
        // Display the dialog to the user
        setCellName(name);
        int dialogResult = exec(); // to display the dialog and wait for the user to accept or reject it
        name = getCellName(); // after dialog is closed, get the name entered by the user
        return (dialogResult == Accepted); // returns whether the dialog was accepted
    }


}