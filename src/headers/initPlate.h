#pragma once
#include "Plate.h"


Plate initPlate();
// функция для получения узлов, которые находятся за пределами координаты окружности
vector<Node *> getNodesForRoundCheck(Plate &plate);
// функция для проверки граничных узлов на окружности
void RoundCheckNodes(vector< Node*> nodes, Plate &plate);