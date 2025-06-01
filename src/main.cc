#include "Plate.h"
#include "Node.h"
#include "initPlate.h"
#include "WritePlateTemp.h"
#include "PlateSolver.h"
#include "Constants.h"


int main(){

    Plate plate = initPlate();

    clearAndInitFile("test.txt");
    writePlateTemp(plate, "test.txt");

    PlateSolver solver(plate);

    solver.simulate(25);
    writePlateTemp(plate, "test.txt");


}