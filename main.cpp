#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

#include "model/Stamp.h"
#include "logic/CollectionSheet.h"
#include "memory/MemoryUtils.h"

void runAllTests();

void printMenu() {
    std::cout << "\n--- Меню ---\n";
    std::cout << "1. Добавить марку\n";
    std::cout << "2. Показать коллекцию\n";
    std::cout << "3. Удалить марку\n";
    std::cout << "4. Сортировать по году\n";
    std::cout << "5. Сохранить в CSV\n";
    std::cout << "6. Загрузить из CSV\n";
    std::cout << "7. Проверить память\n";
    std::cout << "8. Редактировать марку \n"; 
    std::cout << "0. Выход\n";
    std::cout << "> ";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int mode = 0;
    std::cout << "1. Тесты\n2. Программа\n0. Выход\n> ";
    if (!(std::cin >> mode)) {
        std::cin.clear(); std::cin.ignore(10000, '\n'); return 0;
    }

    if (mode == 0) return 0;
    if (mode == 1) {
        runAllTests();
        std::cout << "Нажмите Enter...";
        std::cin.ignore(); std::cin.get();
        return 0;
    }

    double sheetW, sheetH;
    std::cout << "\n--- Настройка Листа ---\n";
    std::cout << "Введите ширину листа: ";
    while (!(std::cin >> sheetW) || sheetW <= 0) {
        std::cout << "Ошибка. Введите число > 0: ";
        std::cin.clear(); std::cin.ignore(10000, '\n');
    }
    std::cout << "Введите высоту листа: ";
    while (!(std::cin >> sheetH) || sheetH <= 0) {
        std::cout << "Ошибка. Введите число > 0: ";
        std::cin.clear(); std::cin.ignore(10000, '\n');
    }

    CollectionSheet myCollection(sheetW, sheetH); 
    int choice;

    do {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear(); std::cin.ignore(10000, '\n'); choice = -1;
        }

        switch (choice) {
        case 1: { 
            std::string name, country;
            int year;
            double val, x, y;
            bool used;
            
            std::cout << "Название: "; std::cin >> name; 
            std::cout << "Страна: "; std::cin >> country;

            std::cout << "Год: ";
            if (!(std::cin >> year)) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Ошибка ввода!\n"; break; }

            std::cout << "Номинал: ";
            if (!(std::cin >> val)) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Ошибка ввода!\n"; break; }

            std::cout << "Гашеная (1/0): ";
            if (!(std::cin >> used)) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Ошибка ввода!\n"; break; }

            std::cout << "X: ";
            if (!(std::cin >> x)) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Ошибка ввода!\n"; break; }

            std::cout << "Y: ";
            if (!(std::cin >> y)) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Ошибка ввода!\n"; break; }

            auto newStamp = std::make_shared<Stamp>(name, country, year, val, used, x, y);
            if (myCollection.addItem(newStamp)) std::cout << "[ОК] Добавлено.\n";
            else std::cout << "[ОШИБКА] Не влезает на лист!\n";
            break;
        }
        case 2: { 
            auto lines = myCollection.getAllItemsInfo();
            std::cout << "\n--- Список ---\n";
            if (lines.empty()) std::cout << "(Пусто)\n";
            for (size_t i = 0; i < lines.size(); ++i) std::cout << i << ". " << lines[i] << "\n";
            break;
        }
        case 3: { 
            size_t idx; std::cout << "Индекс: "; std::cin >> idx;
            if (myCollection.removeItem(idx)) std::cout << "[ОК] Удалено.\n";
            else std::cout << "[ОШИБКА]\n";
            break;
        }
        case 4: myCollection.sortByYear(); std::cout << "[ОК] Отсортировано.\n"; break;
        case 5: myCollection.exportToCsv("collection.csv"); std::cout << "[ОК] Сохранено.\n"; break;
        case 6: myCollection.importFromCsv("collection.csv"); std::cout << "[ОК] Загружено.\n"; break;
        case 7:
            printMemoryUsageWrapper(); 
            break;
        case 8: { 
            size_t idx;
            std::cout << "Введите индекс марки для изменения: ";
            if (!(std::cin >> idx)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }

            auto item = myCollection.getItem(idx);
            if (!item) {
                std::cout << "[ОШИБКА] Марка с таким индексом не найдена.\n";
                break;
            }

            auto stamp = std::dynamic_pointer_cast<Stamp>(item);
            if (!stamp) {
                std::cout << "[ОШИБКА] Это не марка.\n";
                break;
            }

            std::cout << "Текущая: " << stamp->getInfo() << "\n";
            std::cout << "--- Введите новые данные ---\n";

            std::string name, country;
            int year;
            double val, x, y;
            bool used;

            std::cout << "Название: "; std::cin >> name; 
            std::cout << "Страна: "; std::cin >> country;
            std::cout << "Год: "; std::cin >> year;
            std::cout << "Номинал: "; std::cin >> val;
            std::cout << "Гашеная (1/0): "; std::cin >> used;
            std::cout << "X: "; std::cin >> x;
            std::cout << "Y: "; std::cin >> y;

            if (x < 0 || x > sheetW || y < 0 || y > sheetH) {
                std::cout << "[ОШИБКА] Новые координаты выходят за пределы листа! Изменение отменено.\n";
            } else {

                stamp->setName(name);
                stamp->setCountry(country);
                stamp->setYear(year);
                stamp->setNominal(val);
                stamp->setUsed(used);
                stamp->setPosition(x, y); 
                std::cout << "[ОК] Марка обновлена.\n";
            }
            break;
        }

        case 0: std::cout << "Пока!\n"; break;
        default: std::cout << "Неверный ввод.\n";
        }
    } while (choice != 0);

    return 0;
}