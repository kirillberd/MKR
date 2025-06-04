#include "Node.h"
#include <vector>
#include "Constants.h"
#include "InitPlate.h"
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

vector<Node *> getNodesForRoundCheck(Plate &plate)
{
    vector<Node *> matchingNodes;

    double threshold = PLATE_HEIGHT + PLATE_WIDTH - RADIUS;

    for (int i = 0; i < plate.size(); ++i)
    {
        for (int j = 0; j < plate[i].size(); ++j)
        {
            Node &node = plate[i][j];
            if (node.getXCoordinate() + node.getYCoordinate() > threshold)
            {
                std::cout << node.getXCoordinate() << " " << node.getYCoordinate() << " " << i << " " << j << "\n";
                matchingNodes.push_back(&node);
            }
        }
    }

    return matchingNodes;
}

void RoundCheckNodes(vector<Node *> nodes, Plate &plate)
{
    for (Node *node : nodes)
    {
        // Положение узла относительно начала координат окружности
        float currX = node->getXCoordinate() - (PLATE_WIDTH - RADIUS);
        float currY = node->getYCoordinate() - (PLATE_HEIGHT - RADIUS);

        if (currX * currX + currY * currY > RADIUS * RADIUS)
        {
            int xIndex = node->getXIndex();
            int yIndex = node->getYIndex();

            bool hasLeftNeighbor = (xIndex > 0);
            bool hasBottomNeighbor = (yIndex > 0);

            bool hasNeighborInside = false;

            if (hasLeftNeighbor)
            {
                Node &nearestX = plate[yIndex][xIndex - 1];

                float neighborX = nearestX.getXCoordinate() - (PLATE_WIDTH - RADIUS);
                float neighborY = nearestX.getYCoordinate() - (PLATE_HEIGHT - RADIUS);

                bool nearestXInsideCircle = (neighborX * neighborX + neighborY * neighborY <= RADIUS * RADIUS);

                if (nearestXInsideCircle && nearestX.isExisting())
                {
                    hasNeighborInside = true;
                }
            }

            if (hasBottomNeighbor)
            {
                Node &nearestY = plate[yIndex - 1][xIndex];

                float neighborX = nearestY.getXCoordinate() - (PLATE_WIDTH - RADIUS);
                float neighborY = nearestY.getYCoordinate() - (PLATE_HEIGHT - RADIUS);

                bool nearestYInsideCircle = (neighborX * neighborX + neighborY * neighborY <= RADIUS * RADIUS);

                if (nearestYInsideCircle && nearestY.isExisting())
                {
                    hasNeighborInside = true;
                }
            }

            if (hasNeighborInside)
            {
                float mu_x = 1.0, mu_y = 1.0;

                if (hasLeftNeighbor)
                {
                    Node &nearestX = plate[yIndex][xIndex - 1];
                    mu_x = (sqrt(RADIUS * RADIUS - currY * currY) -
                            (nearestX.getXCoordinate() - (PLATE_WIDTH - RADIUS))) /
                           GRID_STEP;
                }

                if (hasBottomNeighbor)
                {
                    Node &nearestY = plate[yIndex - 1][xIndex];
                    mu_y = (sqrt(RADIUS * RADIUS - currX * currX) -
                            (nearestY.getYCoordinate() - (PLATE_HEIGHT - RADIUS))) /
                           GRID_STEP;
                }

                node->setMux((mu_x <= 0) ? 1 : mu_x);
                node->setMuY((mu_y <= 0) ? 1 : mu_y);
                node->setBorderCondition(BorderCondition::FIRST);
                node->setTemp(RIGHT_BORDER_TEMP);
            }
            else
            {
                cout << "set node unexisting: " << node->getXCoordinate()
                     << " " << node->getYCoordinate() << "\n";
                node->setIsExitsting(false);
                node->setTemp(0);
            }
        }
    }
}

Plate initPlate()
{
    int height = static_cast<int>(PLATE_HEIGHT / GRID_STEP) + 1;
    int width = static_cast<int>(PLATE_WIDTH / GRID_STEP) + 1;

    Plate plate(height, vector<Node>(width));

    // первоначальная инициализация
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            BorderCondition bc = BorderCondition::NONE;
            float temp = INITIAL_TEMP;
            // нижняя граница
            if (i == 0)
            {
                bc = BorderCondition::SECOND;
            }
            // верхняя граница
            else if (i == height - 1)
            {
                bc = BorderCondition::FIRST;
                temp = UPPER_BORDER_TEMP;
            }

            // правая граница
            else if (j == width - 1)
            {
                bc = BorderCondition::FIRST;
                temp = RIGHT_BORDER_TEMP;
            }

            // левая граница
            else if(j == 0){
                bc = BorderCondition::FIRST;
                temp = LEFT_BORDER_TEMP;
            }

            if(i == height - 1 && j == 2)
            {
                bc = BorderCondition::THIRD;
                temp = INITIAL_TEMP;
            }

            plate[i][j] = Node(
                temp,
                j,
                i,
                true,
                bc,
                1,
                1,
                GRID_STEP);
        }
    }
    // обработка скругления
    RoundCheckNodes(getNodesForRoundCheck(plate), plate);

    return plate;
}
