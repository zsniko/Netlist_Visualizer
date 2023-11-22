// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/7>" -*-

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

using namespace std;


int main ( int argc, char* argv[] )
{
  cout << "Chargement des modeles..." << endl;
  //Cell* vdd = Cell::load( "vdd" );
  // Symbol* s = vdd->getSymbol();
  // s->toXml( cout );
  //vdd->toXml(cout);
  Cell::load( "vdd" );
  Cell::load( "gnd" );
  Cell::load( "TransistorN" );
  Cell::load( "TransistorP" );
  Cell::load( "and2" );
  Cell::load( "or2" );
  Cell* xor2      = Cell::load( "xor2" );
  Cell* halfadder = Cell::load( "halfadder" );

  cout << "\nContenu du <xor2>:" << endl;
  xor2->toXml( cout );

  cout << "\nContenu du <halfadder>:" << endl;
  halfadder->toXml( cout );
  
  return 0;
}