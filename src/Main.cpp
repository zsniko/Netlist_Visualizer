// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/8-10>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include "Cell.h"
#include <QApplication>
#include <QtGui>
#include "CellViewer.h"
using namespace Netlist;
using namespace std;

int main ( int argc, char* argv[] )
{
    cout << "Chargement des modeles..." << endl;
    Cell::load( "vdd" );
    Cell::load( "gnd" );
    Cell::load( "TransistorN" );
    Cell::load( "TransistorP" );
    Cell::load( "and2" );
    Cell::load( "or2" );
    Cell::load( "xor2" );
    Cell* halfadder = Cell::load( "halfadder" );
    Cell* fulladder = Cell::load( "fulladder" );

    QApplication* qa = new QApplication( argc, argv );
    CellViewer* viewer = new CellViewer(); // CellViewer Inherits from QMainWindow
    viewer->setCell( halfadder );
    viewer->show(); // Make the viewer visible on screen
    int rvalue = qa->exec(); // Start the Qt event loop (and return the exit value of the application when loop ends)
    delete qa; // Delete the QApplication object
    return rvalue;
    
}