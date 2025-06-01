#pragma once
#include "Plate.h"
#include <vector>

class PlateSolver
{
private:
    std::vector<std::vector<float>> coeffMatrix;
    std::vector<float> currentTemp;   // Текущие температуры
    std::vector<float> previousTemp;  // Температуры с предыдущего шага
    std::vector<float> rightHandSide; // Правая часть СЛАУ
    Plate &plate;
    int size;

    void initMatrix();
    void initTempVector();
    void updateRightHandSide(); // Формирование правой части СЛАУ
    void solveGauss();
    void updatePlateTemperatures();
    void timeStep(); // Один временной шаг

    int getSize() const { return size; }
    const std::vector<float> &getCurrentTemp() const { return currentTemp; }

public:
    PlateSolver(Plate &inputPlate);
    void simulate(int timeSteps); // Полное моделирование
};