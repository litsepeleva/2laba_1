#ifndef MEB_HPP
#define MEB_HPP
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class Mebel {
private:
    char name[50];
    char color[50];
    int art;
    Mebel* next;
public:
    Mebel();
    Mebel(const char* n, const char* c, int a);
    ~Mebel()
    const char* getName() const;
    const char* getColor() const;
    int getArt() const;
    Mebel* getNext() const;
    void setName(const char* n);
    void setColor(const char* c);
    void setArt(int a);
    void setNext(Mebel* n);
    friend ostream& operator<<(ostream& os, const Mebel& m);
    friend istream& operator>>(istream& is, Mebel& m);
};
class Baza {
private:
    Mebel* first;
    Mebel* last;
    char currentFilename[100];
public:
    Baza();
    ~Baza();
    void print();
    void add();
    void remove(const char* name);
    void search(const char* name, int art);
    void edit(const char* name);
    void save();
    void load(const char* filename);
    void setFilename(const char* filename);
    Mebel& operator[](int index);
    friend ostream& operator<<(ostream& os, Baza& b);
    friend istream& operator>>(istream& is, Baza& b);
};

#endif
