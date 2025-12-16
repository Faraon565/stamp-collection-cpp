#pragma once
#include <string>


class Item {
protected:
    double xCoord;
    double yCoord;

public:
    Item(double x, double y);
    virtual ~Item() = default;

    virtual std::string getInfo() const;

    double getX() const;
    double getY() const;
    void setPosition(double x, double y);
};