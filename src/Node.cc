#include "Node.h"

Node::Node()
    : temp(0.0f), xCoordinate(0.0f), yCoordinate(0.0f),
      xIndex(0), yIndex(0), exists(false),
      borderCondition(BorderCondition::NONE), muX(1.0f), muY(1.0f)
{
}

Node::Node(float temperature, int xIdx, int yIdx, bool nodeExists, BorderCondition bc, float mux, float muy, float step) : temp(temperature), xIndex(xIdx), yIndex(yIdx), exists(nodeExists), borderCondition(bc), muX(mux), muY(muy)
{

    this->xCoordinate = xIdx * step;
    this->yCoordinate = yIdx * step;
}

BorderCondition Node::getBorderCondition() const
{
    return borderCondition;
}

float Node::getXCoordinate() const
{
    return xCoordinate;
}

float Node::getYCoordinate() const
{
    return yCoordinate;
}

float Node::getXIndex() const
{
    return xIndex;
}

float Node::getYIndex() const
{
    return yIndex;
}

float Node::getMuX() const
{
    return muX;
}

void Node::setMux(float mux)
{
    this->muX = mux;
}

void Node::setBorderCondition(BorderCondition bc){
    borderCondition = bc;
}


void Node::setMuY(float muy)
{
    this->muY = muy;
}

Node::~Node()
{
}

float Node::getTemp() const
{
    return temp;
}

void Node::setTemp(float temp)
{
    this->temp = temp;
}

bool Node::isExisting() const
{
    return exists;
}

void Node::setIsExitsting(bool existsing)
{
    this->exists = existsing;
}
