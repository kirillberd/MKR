#include "Node.h"
#include <vector>
#include "Constants.h"
#include "initPlate.h"

using namespace std;



Plate initPlate()
{
    int height = static_cast<int>(PLATE_HEIGHT / GRID_STEP);
    int width = static_cast<int>(PLATE_WIDTH / GRID_STEP);

    Plate plate(height, vector<Node>(width));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            plate[i][j] = Node(
                INITIAL_TEMP,
                j,                    
                i,                    
                true,                 
                BorderCondition::NONE, 
                1,
                GRID_STEP);
        }
    }

    return plate;
}


