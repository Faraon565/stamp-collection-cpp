#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../model/Stamp.h"

class CollectionSheet {
private:
    double width;
    double height;
    std::vector<std::shared_ptr<Item>> items;

public:
    CollectionSheet(double w, double h);

    bool addItem(const std::shared_ptr<Item>& item);
    bool removeItem(size_t index);
    std::shared_ptr<Item> getItem(size_t index) const;
    size_t getCount() const;
    
    std::vector<std::string> getAllItemsInfo() const;
    void sortByYear(); 

    void exportToCsv(const std::string& filename) const;
    void importFromCsv(const std::string& filename);
};