#pragma once

enum class BorderCondition
{
    NONE,
    FIRST,
    SECOND,
    THIRD
};

/*
Класс узла, с которыми будут проводиться операции
Параметры узла:
- Температура
- Координата по x (индекс, уможенный на шаг по сетке)
- Коодианата по y
- Индекс по x по сетке
- Индекс по y по сетке
- Коэффициент мю по x(доля от шага h). По умолчанию равен 1, изменяется для скруглений
- Коэффициент мю по y
*/
class Node
{
private:
    float temp, xCoordinate, yCoordinate, muX, muY;
    // индексы расположения по сетке
    int xIndex, yIndex;

    // индикатор, находится ли узел в рабочей области
    bool exists;

    // граничные условия узла
    BorderCondition borderCondition;

public:

    Node();
    Node(float temp, int xIdx, int yIdx, bool nodeExists = true, BorderCondition bc = BorderCondition::NONE, float muX = 1, float muY = 1, float step = 0.25);

    ~Node();

    float getTemp() const;
    void setTemp(float temperature);
    bool isExisting() const;
    void setIsExitsting(bool exitsting);
    BorderCondition getBorderCondition() const;
    void setBorderCondition(BorderCondition bc);
    float getYCoordinate() const;
    float getXCoordinate() const;
    float getXIndex() const;
    float getYIndex() const;
    float getMuX() const;
    float getMuY() const;
    void setMux(float muX);
    void setMuY(float muY);


};
