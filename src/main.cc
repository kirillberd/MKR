#include "Plate.h"
#include "Node.h"
#include "InitPlate.h"
#include "WritePlateTemp.h"
#include "PlateSolver.h"
#include "Constants.h"


int main(){

    Plate plate = initPlate();

    clearAndInitFile("initial_plate.txt");
    clearAndInitFile("solution.txt");
    writePlateTemp(plate, "initial_plate.txt");

    PlateSolver solver(plate);

    solver.simulate(25);
    writePlateTemp(plate, "solution.txt");


}