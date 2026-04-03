#include "meb.hpp"
int main() {
    Baza myDB;
    char filename[100];
    cout << "Введите имя файла: ";
    cin >> filename;
    myDB.load(filename);
    int choice;
    char name[100];
    int art;
    do {
        cout << "1. Вывести базу данных" << endl;
        cout << "2. Добавить новый элемент" << endl;
        cout << "3. Удалить элемент" << endl;
        cout << "4. Найти элемент" << endl;
        cout << "5. Изменить элемент" << endl;
        cout << "6. Сохранить и выйти" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        
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
                cin >> art;
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
                cout << "До свидания!" << endl;
                break;
                
            default:
                cout << "Неверный выбор, попробуйте снова" << endl;
        }
    } 
    while(choice != 6);
    return 0;
}
