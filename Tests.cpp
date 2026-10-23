#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <algorithm>
#include "model/Item.h"
#include "model/Stamp.h"
#include "logic/CollectionSheet.h"

void runAllTests() {
    std::cout << "\n>>> [РЕЖИМ ТЕСТА] Запуск модульных тестов...\n";


    std::shared_ptr<Item> item = std::make_shared<Stamp>("Test", "C", 2020, 10, false, 50, 60);
    assert(item->getX() == 50);
    assert(item->getY() == 60);
    
    item->setPosition(100, 120);
    assert(item->getX() == 100);

    Stamp s1("Penny Black", "UK", 1840, 100.5, true, 10, 20);
    assert(s1.getName() == "Penny Black");
    assert(s1.getYear() == 1840);
    assert(s1.getIsUsed() == true);
    
    std::string info = s1.getInfo();
    assert(info.find("Penny Black") != std::string::npos);

    CollectionSheet sheet(500, 500);
    
    auto stamp = std::make_shared<Stamp>("S", "C", 2000, 1, false, 100, 100);
    
    assert(sheet.addItem(stamp) == true);
    assert(sheet.getCount() == 1);
    
    assert(sheet.removeItem(0) == true);
    assert(sheet.getCount() == 0);

    auto st1 = std::make_shared<Stamp>("A", "A", 1990, 1, false, 0, 0);
    auto st2 = std::make_shared<Stamp>("B", "B", 1980, 1, false, 0, 0);
    
    sheet.addItem(st1);
    sheet.addItem(st2);
    
    sheet.sortByYear();
    

    auto first = std::dynamic_pointer_cast<Stamp>(sheet.getItem(0));
    assert(first->getYear() == 1980);

    std::cout << ">>> [УСПЕХ] Все тесты пройдены успешно!\n";
}