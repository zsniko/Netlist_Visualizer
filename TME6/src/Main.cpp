// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/4-5>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
using namespace Netlist;


int main ( int argc, char* argv[] )
{
//  cout << "Chargement des modeles:" << endl;
//  cout << "- <and2> ..." << endl;
//  Cell::load( "and2" );
//
//  cout << "- <or2> ..." << endl;
//  Cell::load( "or2" );
//
//  cout << "- <xor2> ..." << endl;
//  Cell::load( "xor2" );
//
//  cout << "- <halfadder> ..." << endl;
//  Cell* halfadder = Cell::load( "halfadder" );
//
//  cout << "\nContenu du <halfadder>:" << endl;
//  halfadder->toXml( cout );
    string cellName = "and2";
    string cellFile = "./cells/" + cellName + ".xml";
    cout << (cellFile);

  return 0;
}
