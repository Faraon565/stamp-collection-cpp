#include "Item.h"

Item::Item(double x, double y) : xCoord(x), yCoord(y) {}

std::string Item::getInfo() const {
    return "Item: (" + std::to_string(xCoord) + ", " + 
           std::to_string(yCoord) + ")";
}

double Item::getX() const { return xCoord; }
double Item::getY() const { return yCoord; }

void Item::setPosition(double x, double y) {
    xCoord = x;
    yCoord = y;
}