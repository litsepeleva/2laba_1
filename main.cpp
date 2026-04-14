#include "meb.hpp"
int check1() {
    string input;
    bool valid = false;
    int choice = 0;
    while (!valid) {
        cin >> input;
        valid = true;
        for (int i = 0; i < input.length(); i++) {
            if (!isdigit(input[i])) {
                valid = false;
                cout << "Ошибка, введите число от 1 до 6: ";
                break;
            }
        }
        if (valid) {
            choice = stoi(input);
            if (choice < 1 || choice > 6) {
                valid = false;
                cout << "Ошибка, введите число от 1 до 6: ";
            }
        }
    }
    return choice;
}
int main() {
    Baza myDB;
    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;
    myDB.load(filename);
    int choice;
    string name;
    int art;
    do {
        cout << "\n1. Вывести базу данных" << endl;
        cout << "2. Добавить новый элемент" << endl;
        cout << "3. Удалить элемент" << endl;
        cout << "4. Найти элемент" << endl;
        cout << "5. Изменить элемент" << endl;
        cout << "6. Сохранить и выйти" << endl;
        cout << "Выберите действие: ";
        choice = check1();
        switch(choice) {
            case 1:
                cout << myDB;
                break;
            case 2:
                cin >> myDB;
                myDB.save();
                break;
            case 3:
                cout << "Название элемента для удаления: ";
                cin >> name;
                myDB.remove(name);
                myDB.save();
                break;
            case 4:
                cout << "Название для поиска: ";
                cin >> name;
                cout << "Артикул: ";
                art = check2(); 
                myDB.search(name, art);
                break;
            case 5:
                cout << "Название элемента для редактирования: ";
                cin >> name;
                myDB.edit(name);
                myDB.save();
                break;
            case 6:
                myDB.save();
                cout << "Сохранено" << endl;
                break;
        }
    } 
    while(choice != 6);
    return 0;
}
