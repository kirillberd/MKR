#include "Node.h"


Node::Node() 
    : temp(0.0f), xCoordinate(0.0f), yCoordinate(0.0f), 
      xIndex(0), yIndex(0), exists(false), 
      borderCondition(BorderCondition::NONE), muCoeff(1.0f) {
}



Node::Node(float temperature, int xIdx, int yIdx, bool nodeExists, BorderCondition bc, float mu, float step) : temp(temperature), xIndex(xIdx), yIndex(yIdx), exists(nodeExists), borderCondition(bc), muCoeff(mu) 
{

    this->xCoordinate = xIdx * step;
    this->yCoordinate = yIdx * step;
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
