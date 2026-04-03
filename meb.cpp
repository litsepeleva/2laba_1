#include "meb.hpp"
Mebel::Mebel() {
    name[0] = '\0';
    color[0] = '\0';
    art = 0;
    next = nullptr;
}
Mebel::Mebel(const char* n, const char* c, int a) {
    strcpy(name, n);
    strcpy(color, c);
    art = a;
    next = nullptr;
}
Mebel::~Mebel() {}
const char* Mebel::getName() const { return name; }
const char* Mebel::getColor() const { return color; }
int Mebel::getArt() const { return art; }
Mebel* Mebel::getNext() const { return next; }
void Mebel::setName(const char* n) { strcpy(name, n); }
void Mebel::setColor(const char* c) { strcpy(color, c); }
void Mebel::setArt(int a) { art = a; }
void Mebel::setNext(Mebel* n) { next = n; }
ostream& operator<<(ostream& os, const Mebel& m) {
    os << "Вид: " << m.name << ", Цвет: " << m.color << ", Артикул: " << m.art;
    return os;
}
istream& operator>>(istream& is, Mebel& m) {
    cout << "Введите вид мебели: ";
    is >> m.name;
    cout << "Введите цвет: ";
    is >> m.color;
    cout << "Введите артикул: ";
    is >> m.art;
    return is;
}
Baza::Baza() {
    first = nullptr;
    last = nullptr;
    currentFilename[0] = '\0';
}
Baza::~Baza() {
    Mebel* current = first;
    while (current != nullptr) {
        Mebel* temp = current;
        current = current->getNext();
        delete temp;
    }
}
void Baza::print() {
    Mebel* con = first;
    if (con == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    cout << "\n========== БАЗА ДАННЫХ ==========" << endl;
    int i = 1;
    while (con != nullptr) {
        cout << i++ << ". " << *con << endl;
        con = con->getNext();
    }
    cout << "==================================" << endl;
}
void Baza::add() {
    Mebel* one = new Mebel();
    cin >> *one;
    one->setNext(nullptr);
    if (first == nullptr) {
        first = one;
        last = one;
    } else {
        last->setNext(one);
        last = one;
    }
    cout << "Элемент добавлен!" << endl;
}
void Baza::remove(const char* name) {
    Mebel* con = first;
    Mebel* prev = nullptr;
    while (con != nullptr) {
        if (strcmp(con->getName(), name) == 0) {
            if (prev == nullptr) {
                first = con->getNext();
            } else {
                prev->setNext(con->getNext());
            }
            if (con == last) {
                last = prev;
            }
            delete con;
            cout << "Удалено: " << name << endl;
            return;
        }
        prev = con;
        con = con->getNext();
    }
    cout << name << " не найден" << endl;
}
void Baza::search(const char* name, int art) {
    Mebel* con = first;
    int found = 0;
    cout << "\n========== РЕЗУЛЬТАТЫ ПОИСКА ==========" << endl;
    while (con != nullptr) {
        if (strcmp(con->getName(), name) == 0 && con->getArt() == art) {
            cout << "ТОЧНОЕ СОВПАДЕНИЕ: " << *con << endl;
            found = 1;
        }
        else if (strcmp(con->getName(), name) == 0 || con->getArt() == art) {
            cout << "ПОХОЖЕЕ: " << *con << endl;
            found = 1;
        }
        con = con->getNext();
    }
    if (!found) {
        cout << "Ничего не найдено" << endl;
    }
    cout << "=========================================" << endl;
}
void Baza::edit(const char* name) {
    Mebel* con = first;
    while (con != nullptr) {
        if (strcmp(con->getName(), name) == 0) {
            cout << "\nРедактирование: " << *con << endl;
            cout << "Введите новые данные:" << endl;
            char newName[50];
            char newColor[50];
            int newArt;
            cout << "Новый вид мебели: ";
            cin >> newName;
            cout << "Новый цвет: ";
            cin >> newColor;
            cout << "Новый артикул: ";
            cin >> newArt;
            con->setName(newName);
            con->setColor(newColor);
            con->setArt(newArt);
            cout << "Элемент изменен!" << endl;
            return;
        }
        con = con->getNext();
    }
    cout << "Элемент не найден" << endl;
}
void Baza::save() {
    if (currentFilename[0] == '\0') {
        cout << "Ошибка: имя файла не задано" << endl;
        return;
    }
    ofstream file(currentFilename);
    if (!file) {
        cout << "Ошибка: не удалось открыть файл" << endl;
        return;
    }
    Mebel* con = first;
    while (con != nullptr) {
        file << con->getName() << " " << con->getColor() << " " << con->getArt() << endl;
        con = con->getNext();
    }
    file.close();
    cout << "Сохранено в файл: " << currentFilename << endl;
}
void Baza::load(const char* filename) {
    setFilename(filename);
    ifstream file(filename);
    if (!file) {
        cout << "Файл не найден, будет создан новый" << endl;
        return;
    }
    char name[50], color[50];
    int art;
    while (file >> name >> color >> art) {
        Mebel* one = new Mebel(name, color, art);
        one->setNext(nullptr);
        if (first == nullptr) {
            first = one;
            last = one;
        } else {
            last->setNext(one);
            last = one;
        }
    }
    file.close();
    cout << "Загружено из файла: " << filename << endl;
}
void Baza::setFilename(const char* filename) {
    strcpy(currentFilename, filename);
}
Mebel& Baza::operator[](int index) {
    Mebel* con = first;
    int i = 0;
    while (con != nullptr) {
        if (i == index) {
            return *con;
        }
        con = con->getNext();
        i++;
    }
    throw out_of_range("Индекс вне диапазона");
}
ostream& operator<<(ostream& os, Baza& b) {
    b.print();
    return os;
}
istream& operator>>(istream& is, Baza& b) {
    b.add();
    return is;
}
