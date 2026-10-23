#include "CollectionSheet.h"
#include <fstream>
#include <sstream>
#include <algorithm>

CollectionSheet::CollectionSheet(double w, double h) 
    : width(w), height(h) {}

bool CollectionSheet::addItem(const std::shared_ptr<Item>& item) {
    if (item->getX() < 0 || item->getX() > width || 
        item->getY() < 0 || item->getY() > height) {
        return false;
    }
    items.push_back(item);
    return true;
}

bool CollectionSheet::removeItem(size_t index) {
    if (index >= items.size()) return false;
    items.erase(items.begin() + index);
    return true;
}

std::shared_ptr<Item> CollectionSheet::getItem(size_t index) const {
    if (index >= items.size()) return nullptr;
    return items[index];
}

size_t CollectionSheet::getCount() const { return items.size(); }

std::vector<std::string> CollectionSheet::getAllItemsInfo() const {
    std::vector<std::string> infoList;
    for (const auto& item : items) {
        infoList.push_back(item->getInfo());
    }
    return infoList;
}

void CollectionSheet::sortByYear() {
    std::sort(items.begin(), items.end(), 
        [](const std::shared_ptr<Item>& a, const std::shared_ptr<Item>& b) {
            auto s1 = std::dynamic_pointer_cast<Stamp>(a);
            auto s2 = std::dynamic_pointer_cast<Stamp>(b);
            if (s1 && s2) return s1->getYear() < s2->getYear();
            return false;
        });
}

void CollectionSheet::exportToCsv(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& item : items) {
        auto s = std::dynamic_pointer_cast<Stamp>(item);
        if (s) {
            file << "Stamp," << s->getName() << "," << s->getCountry() << ","
                 << s->getYear() << "," << s->getValue() << "," 
                 << s->getIsUsed() << ","
                 << s->getX() << "," << s->getY() << "\n";
        }
    }
}

void CollectionSheet::importFromCsv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    items.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type, name, country, segment;
        int year;
        double val, x, y;
        bool used;

        std::getline(ss, type, ',');
        if (type == "Stamp") {
            std::getline(ss, name, ',');
            std::getline(ss, country, ',');
            std::getline(ss, segment, ','); year = std::stoi(segment);
            std::getline(ss, segment, ','); val = std::stod(segment);
            std::getline(ss, segment, ','); used = (std::stoi(segment) != 0);
            std::getline(ss, segment, ','); x = std::stod(segment);
            std::getline(ss, segment, ','); y = std::stod(segment);

            addItem(std::make_shared<Stamp>(name, country, year, val, used, x, y));
        }
    }
}