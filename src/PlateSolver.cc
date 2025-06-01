#include "PlateSolver.h"
#include <vector>
#include "Constants.h"
#include "Node.h"
#include "Plate.h"
#include <iostream>
#include <algorithm>

using namespace std;

PlateSolver::PlateSolver(Plate &plate_) : plate(plate_)
{
    int height = static_cast<int>(PLATE_HEIGHT / GRID_STEP) + 1;
    int width = static_cast<int>(PLATE_WIDTH / GRID_STEP) + 1;
    size = height * width;


    currentTemp.resize(size, 0.0f);
    previousTemp.resize(size, 0.0f);
    initMatrix();
    initTempVector();
    previousTemp = currentTemp;
}

void PlateSolver::initMatrix()
{
    coeffMatrix.assign(size, vector<float>(size, 0.0));
    
    int height = static_cast<int>(PLATE_HEIGHT / GRID_STEP) + 1;
    int width = static_cast<int>(PLATE_WIDTH / GRID_STEP) + 1;
    
    for (int i = 0; i < plate.size(); i++)
    {
        for (int j = 0; j < plate[i].size(); j++)
        {
            int currentIndex = i * width + j;
            
            if (currentIndex >= size) {
                continue;
            }
            
            Node &currNode = plate[i][j];
            
            if (!currNode.isExisting()) {
                coeffMatrix[currentIndex][currentIndex] = 1.0;
                continue;
            }
            
            BorderCondition bc = currNode.getBorderCondition();
            
            if (bc == BorderCondition::FIRST) {
                // ГУ первого рода - температура фиксирована
                coeffMatrix[currentIndex][currentIndex] = 1.0;
                
            }
            else if (bc == BorderCondition::SECOND) {
                // ГУ второго рода - градиент температуры = 0 (теплоизоляция)
                coeffMatrix[currentIndex][currentIndex] = 1.0 / GRID_STEP;
                
                // Определяем направление в зависимости от положения
                if (i == 0) {
                    // Нижняя граница
                    int upperIndex = (i + 1) * width + j;
                    if (upperIndex < size && i + 1 < height && plate[i+1][j].isExisting()) {
                        coeffMatrix[currentIndex][upperIndex] = -1.0 / GRID_STEP;
                    }
                }
                else if (i == height - 1) {
                    // Верхняя граница 
                    int lowerIndex = (i - 1) * width + j;
                    if (lowerIndex >= 0 && i - 1 >= 0 && plate[i-1][j].isExisting()) {
                        coeffMatrix[currentIndex][lowerIndex] = -1.0 / GRID_STEP;
                    }
                }
                else if (j == 0) {
                    // Левая граница
                    int rightIndex = i * width + (j + 1);
                    if (rightIndex < size && j + 1 < width && plate[i][j+1].isExisting()) {
                        coeffMatrix[currentIndex][rightIndex] = -1.0 / GRID_STEP;
                    }
                }
                else if (j == width - 1) {
                    // Правая граница
                    int leftIndex = i * width + (j - 1);
                    if (leftIndex >= 0 && j - 1 >= 0 && plate[i][j-1].isExisting()) {
                        coeffMatrix[currentIndex][leftIndex] = -1.0 / GRID_STEP;
                    }
                }
                
            }
            else if (bc == BorderCondition::NONE) {
                float muX = currNode.getMuX();
                float muY = currNode.getMuY();
                
                // Левый сосед
                if (j > 0 && plate[i][j-1].isExisting()) {
                    int leftIndex = i * width + (j - 1);
                    coeffMatrix[currentIndex][leftIndex] = -ALPHA * muX / (GRID_STEP * GRID_STEP);
                }
                
                // Правый сосед
                if (j < width - 1 && plate[i][j+1].isExisting()) {
                    int rightIndex = i * width + (j + 1);
                    coeffMatrix[currentIndex][rightIndex] = -ALPHA * muX / (GRID_STEP * GRID_STEP);
                }
                
                // Нижний сосед
                if (i > 0 && plate[i-1][j].isExisting()) {
                    int lowerIndex = (i - 1) * width + j;
                    coeffMatrix[currentIndex][lowerIndex] = -ALPHA * muY / (GRID_STEP * GRID_STEP);
                }
                
                // Верхний сосед
                if (i < height - 1 && plate[i+1][j].isExisting()) {
                    int upperIndex = (i + 1) * width + j;
                    coeffMatrix[currentIndex][upperIndex] = -ALPHA * muY / (GRID_STEP * GRID_STEP);
                }
                
                // Центральный коэффициент с учетом мю
                coeffMatrix[currentIndex][currentIndex] = 
                    (ALPHA * (1.0f + muX) / (GRID_STEP * GRID_STEP)) +  // по x
                    (ALPHA * (1.0f + muY) / (GRID_STEP * GRID_STEP)) +  // по y
                    (1.0f / TIME_STEP);                                 // временная производная
            }
            else {
                coeffMatrix[currentIndex][currentIndex] = 1.0f;
            }
        }
    }
    
}

void PlateSolver::initTempVector()
{
    
    int height = static_cast<int>(PLATE_HEIGHT / GRID_STEP) + 1;
    int width = static_cast<int>(PLATE_WIDTH / GRID_STEP) + 1;
    
    for (int i = 0; i < plate.size(); i++)
    {
        for (int j = 0; j < plate[i].size(); j++)
        {
            int currentIndex = i * width + j;
            
            if (currentIndex >= size) {
                continue;
            }
            
            Node &currNode = plate[i][j];
            
            if (!currNode.isExisting()) {
                currentTemp[currentIndex] = 0.0;
                continue;
            }
            
            currentTemp[currentIndex] = currNode.getTemp();
            
        }
    }
    
}

void PlateSolver::updateTempVector()
{
    
    int height = static_cast<int>(PLATE_HEIGHT / GRID_STEP) + 1;
    int width = static_cast<int>(PLATE_WIDTH / GRID_STEP) + 1;
    
    for (int i = 0; i < plate.size(); i++)
    {
        for (int j = 0; j < plate[i].size(); j++)
        {
            int currentIndex = i * width + j;
            
            if (currentIndex >= size) {
                continue;
            }
            
            Node &currNode = plate[i][j];
            
            if (!currNode.isExisting()) {
                currentTemp[currentIndex] = 0.0;
                continue;
            }
            
            BorderCondition bc = currNode.getBorderCondition();
            
            if (bc == BorderCondition::FIRST) {
                // ГУ первого рода - температура остается фиксированной
                currentTemp[currentIndex] = currNode.getTemp();
            }
            else if (bc == BorderCondition::SECOND) {
                // ГУ второго рода - изменение потока = 0
                currentTemp[currentIndex] = 0.0;
            }
            else if (bc == BorderCondition::NONE) {
                // Внутренние узлы - температура с предыдущего шага / dt
                currentTemp[currentIndex] = previousTemp[currentIndex] / TIME_STEP;
            }
            else {
                // Другие типы ГУ
                currentTemp[currentIndex] = currNode.getTemp();
            }
        }
    }
    
}

void PlateSolver::timeStep()
{
    
    previousTemp = currentTemp;
    
    
    // Обновляем правую часть с учетом предыдущего шага
    updateTempVector();
    
    // Решаем СЛАУ
    solveGauss();
    
    // Обновляем температуры в узлах пластины
    updatePlateTemperatures();
    
}

void PlateSolver::simulate(int timeSteps)
{
    
    for (int step = 0; step < timeSteps; step++) {
        cout << "\n--- Time step " << (step + 1) << " ---" << endl;
        
        timeStep();
        
    }
    
}


void PlateSolver::solveGauss()
{
    
    vector<vector<float>> A = coeffMatrix;
    vector<float> b = currentTemp;
    vector<float> solution(size, 0.0f);
    
    // Прямой ход
    for (int j = 0; j < size - 1; j++)
    {
        // Поиск максимального элемента для устойчивости
        int maxRow = j;
        for (int i = j + 1; i < size; i++)
        {
            if (abs(A[i][j]) > abs(A[maxRow][j]))
            {
                maxRow = i;
            }
        }
        
        // Перестановка строк
        if (maxRow != j)
        {
            swap(A[j], A[maxRow]);
            swap(b[j], b[maxRow]);
        }
        
        // Проверка на вырожденность
        if (abs(A[j][j]) < 1e-10)
        {
            continue;
        }
        
        // Исключение
        for (int i = j + 1; i < size; i++)
        {
            float coeff = A[i][j] / A[j][j];
            
            for (int k = j; k < size; k++)
            {
                A[i][k] -= coeff * A[j][k];
            }
            b[i] -= coeff * b[j];
        }
        
    }
    
    
    // Обратный ход
    for (int i = size - 1; i >= 0; i--)
    {
        if (abs(A[i][i]) < 1e-10)
        {
            solution[i] = 0.0f;
            continue;
        }
        
        float sum = 0.0f;
        for (int j = i + 1; j < size; j++)
        {
            sum += A[i][j] * solution[j];
        }
        
        solution[i] = (b[i] - sum) / A[i][i];
    }
    
    currentTemp = solution;
    
}

void PlateSolver::updatePlateTemperatures()
{
    
    int height = static_cast<int>(PLATE_HEIGHT / GRID_STEP) + 1;
    int width = static_cast<int>(PLATE_WIDTH / GRID_STEP) + 1;
    int updatedCount = 0;
    
    for (int i = 0; i < plate.size(); i++)
    {
        for (int j = 0; j < plate[i].size(); j++)
        {
            int currentIndex = i * width + j;
            
            if (currentIndex >= size) {
                continue;
            }
            
            Node &currNode = plate[i][j];
            
            if (!currNode.isExisting()) {
                continue;
            }
            
            float oldTemp = currNode.getTemp();
            float newTemp = currentTemp[currentIndex];
            
            // Обновляем температуру только для узлов без ГУ первого рода
            // (ГУ первого рода должны сохранять свою температуру)
            if (currNode.getBorderCondition() != BorderCondition::FIRST) {
                currNode.setTemp(newTemp);
                updatedCount++;
                
            }
        }
    }
    
}
