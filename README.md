# Netlist Visualizer

Netlist Visualizer is a C++ application that implements a data structure to design a circuit and uses Qt for visualization. 

## Implementation

The application uses a custom `Cell` class to represent the components of the circuit. Each cell can be loaded with a predefined model such as "vdd", "gnd", "TransistorN", "TransistorP", "and2", "or2", "xor2", "halfadder", and "fulladder". 

The main function initializes a `QApplication` and a `CellViewer` (which inherits from `QMainWindow`). The `CellViewer` is set to display a specific cell and then shown on the screen. The Qt event loop is started with `qa->exec()`, and the application runs until the event loop ends.

```cpp
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
    CellViewer* viewer = new CellViewer();
    viewer->setCell( halfadder );
    viewer->show();
    int rvalue = qa->exec();
    delete qa;
    return rvalue;
}
```
## Example Execution
![pipeline](example_and.png)
