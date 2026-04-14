#ifndef MEB_HPP
#define MEB_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

class Mebel {
private:
    string name;
    string color;
    int art;
    Mebel* next;
public:
    Mebel();
    Mebel(const string& n, const string& c, int a);
    ~Mebel();
    string getName() const;
    string getColor() const;
    int getArt() const;
    Mebel* getNext() const;
    void setName(const string& n);
    void setColor(const string& c);
    void setArt(int a);
    void setNext(Mebel* n);
    friend ostream& operator<<(ostream& os, const Mebel& m);
    friend istream& operator>>(istream& is, Mebel& m);
};
class Baza {
private:
    Mebel* first;
    Mebel* last;
    string currentFilename;
public:
    Baza();
    ~Baza();
    void print();
    void add();
    void remove(const string& name);
    void search(const string& name, int art);
    void edit(const string& name);
    void save();
    void load(const string& filename);
    void setFilename(const string& filename);
    Mebel& operator[](int index);
    friend ostream& operator<<(ostream& os, Baza& b);
    friend istream& operator>>(istream& is, Baza& b);
};
int check1();
int check2();
#endif
