#include "Stamp.h"
#include <sstream>
#include <iomanip>

Stamp::Stamp(const std::string& n, const std::string& c, 
             int y, double v, bool u, double xPos, double yPos)
    : Item(xPos, yPos), name(n), country(c), 
      year(y), nominalValue(v), isUsed(u) {
}

std::string Stamp::getInfo() const {
    std::string status = isUsed ? "Гашеная" : "Чистая";
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << name << " (" << country << ", " << year << ") - "
       << nominalValue << " [" << status << "] "
       << "X:" << xCoord << " Y:" << yCoord;
    return ss.str();
}

const std::string& Stamp::getName() const { return name; }
const std::string& Stamp::getCountry() const { return country; }
int Stamp::getYear() const { return year; }
double Stamp::getValue() const { return nominalValue; }
bool Stamp::getIsUsed() const { return isUsed; }


void Stamp::setName(const std::string& n) { name = n; }
void Stamp::setCountry(const std::string& c) { country = c; }
void Stamp::setYear(int y) { year = y; }
void Stamp::setNominal(double v) { nominalValue = v; }
void Stamp::setUsed(bool u) { isUsed = u; }