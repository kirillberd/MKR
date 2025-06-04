#include <fstream>
#include <iomanip>
#include <iostream>
#include "WritePlateTemp.h"


void writePlateTemp(const Plate& plate, const string& filename) {
    ofstream file(filename, ios::app);
    
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }
    
    
    file << fixed << setprecision(5);
    
    for (int i = plate.size() - 1; i >= 0; i--) {
        for (int j = 0; j < plate[i].size(); j++) {
            file << plate[i][j].getTemp() << " ";
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