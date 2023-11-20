#include<iostream>
#include<vector>

using namespace std;

#ifndef CATEGORIA_H
#define CATEGORIA_H

class Categoria {

    private:
    
        string nombre;
        int id;
    
    public:
    
        Categoria();
        Categoria(string _nombre, int _id);

        string getNombre();
        int getId();
        void agregar_categoria(string n, int _id);

};

Categoria::Categoria() {
    nombre = "";
    id = 0;
}

Categoria::Categoria(string _nombre, int _id) {
    nombre = _nombre;
    id = _id;
}

string Categoria::getNombre() {
    return nombre;
}

int Categoria::getId() {
    return id;
}

void Categoria::agregar_categoria(string n, int _id) {
    nombre = n;
    id = _id;
}

#endif