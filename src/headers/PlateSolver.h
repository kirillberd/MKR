#pragma once
#include "Plate.h"
#include <vector>

class PlateSolver {
private:
    std::vector<std::vector<float>> coeffMatrix;
    std::vector<float> currentTemp;
    std::vector<float> previousTemp; 
    Plate& plate;
    int size;
    

public:
    PlateSolver(Plate& inputPlate);
    
    void initMatrix();
    void initTempVector();
    void updateTempVector();  // Обновление правой части с учетом предыдущего шага
    void solveGauss();
    void updatePlateTemperatures();
    void timeStep();  // Один временной шаг
    void simulate(int timeSteps);  // Полное моделирование
    
    int getSize() const { return size; }
    const std::vector<float>& getCurrentTemp() const { return currentTemp; }
};