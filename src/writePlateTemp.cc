#include <fstream>
#include <iomanip>
#include <iostream>
#include "writePlateTemp.h"


void writePlateTemp(const Plate& plate, const string& filename, 
                             int iteration) {
    ofstream file(filename, ios::app);
    
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }
    
    file << "\n# Итерация: " << iteration;
    file << "\n";
    
    file << fixed << setprecision(2);
    
    for (int i = 0; i < plate.size(); ++i) {
        for (int j = 0; j < plate[i].size(); ++j) {
            file << setw(8) << plate[i][j].getTemp();
        }
        file << "\n";
    }
    
    file.close();
}


void clearAndInitFile(const string& filename) {
    ofstream file(filename, ios::out | ios::trunc);
    
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось создать/очистить файл " << filename << endl;
        return;
    }
    
    
    
    file.close();
}