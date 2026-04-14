#include "meb.hpp"
int check2() {
    string input;
    bool valid = false;
    int number = 0;
    while (!valid) {
        cin >> input;
        valid = true;
        for (int i = 0; i < input.length(); i++) {
            if (!isdigit(input[i])) {
                valid = false;
                cout << "Ошибка, введите число: ";
                break;
            }
        }
        if (valid) {
            number = stoi(input);
        }
    }
    return number;
}
Mebel::Mebel() {
    name = "";
    color = "";
    art = 0;
    next = nullptr;
}
Mebel::Mebel(const string& n, const string& c, int a) {
    name = n;
    color = c;
    art = a;
    next = nullptr;
}
Mebel::~Mebel() {}
string Mebel::getName() const { return name; }
string Mebel::getColor() const { return color; }
int Mebel::getArt() const { return art; }
Mebel* Mebel::getNext() const { return next; }
void Mebel::setName(const string& n) { name = n; }
void Mebel::setColor(const string& c) { color = c; }
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
    m.art = check2();
    return is;
}
Baza::Baza() {
    first = nullptr;
    last = nullptr;
    currentFilename = "";
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
    int i = 1;
    while (con != nullptr) {
        cout << i++ << ". " << *con << endl;
        con = con->getNext();
    }
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
}
void Baza::remove(const string& name) {
    Mebel* con = first;
    Mebel* prev = nullptr;
    while (con != nullptr) {
        if (con->getName() == name) {
            if (prev == nullptr) {
                first = con->getNext();
            } else {
                prev->setNext(con->getNext());
            }
            if (con == last) {
                last = prev;
            }
            delete con;
            return;
        }
        prev = con;
        con = con->getNext();
    }
    cout << name << " не найден" << endl;
}
void Baza::search(const string& name, int art) {
    Mebel* con = first;
    int found = 0;
    while (con != nullptr) {
        if (con->getName() == name && con->getArt() == art) {
            cout << "ТОЧНОЕ СОВПАДЕНИЕ: " << *con << endl;
            found = 1;
        }
        else if (con->getName() == name || con->getArt() == art) {
            cout << "ПОХОЖЕЕ: " << *con << endl;
            found = 1;
        }
        con = con->getNext();
    }
    if (!found) {
        cout << "Ничего не найдено" << endl;
    }
}
void Baza::edit(const string& name) {
    Mebel* con = first;
    while (con != nullptr) {
        if (con->getName() == name) {
            cout << "\nРедактирование: " << *con << endl;
            cout << "Введите новые данные:" << endl;
            string newName, newColor;
            int newArt;
            cout << "Новый вид мебели: ";
            cin >> newName;
            cout << "Новый цвет: ";
            cin >> newColor;
            cout << "Новый артикул: ";
            newArt = check2();
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
    if (currentFilename.empty()) {
        cout << "Ошибка: не введено имя файла" << endl;
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
void Baza::load(const string& filename) {
    setFilename(filename);
    ifstream file(filename);
    if (!file) {
        cout << "Файл не найден, будет создан новый" << endl;
        return;
    }
    string name, color;
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
void Baza::setFilename(const string& filename) {
    currentFilename = filename;
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
    throw out_of_range("ошибка");
}
ostream& operator<<(ostream& os, Baza& b) {
    b.print();
    return os;
}
istream& operator>>(istream& is, Baza& b) {
    b.add();
    return is;
}
