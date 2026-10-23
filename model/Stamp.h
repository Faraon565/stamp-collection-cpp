#pragma once
#include "Item.h"
#include <string>

class Stamp : public Item {
private:
    std::string name;
    std::string country;
    int year;
    double nominalValue;
    bool isUsed;

public:
    Stamp(const std::string& name, const std::string& country, 
          int year, double val, bool used, double x, double y);

    std::string getInfo() const override final;

    
    const std::string& getName() const;
    const std::string& getCountry() const;
    int getYear() const;
    double getValue() const;
    bool getIsUsed() const;

    
    void setName(const std::string& name);
    void setCountry(const std::string& country);
    void setYear(int year);
    void setNominal(double val);
    void setUsed(bool used);
};