#include "Plate.h"
#include "Node.h"
#include "initPlate.h"
#include "writePlateTemp.h"

int main(){

    Plate plate = initPlate();

    clearAndInitFile("test.txt");
    writePlateTemp(plate, "test.txt", 1);


}