#include<iostream>
#include<vector>

using namespace std;

#ifndef USUARIO_CPP
#define USUARIO_CPP

/*
La clase Usuario servirá para tener un registro del nombre
y número de teléfono de cada usuario que se registre en la
biblioteca.
*/

class Usuario {

    private:

        string nombre;
        string telefono;
        int id;

    public:

        Usuario();
        Usuario(int _id);

        void setNombre(string n);
        void setTelefono(string t);
        string consultarInformacion();
        string getNombre();

};

Usuario::Usuario() {
    nombre = "";
    telefono = "";
    id = 0;
}

Usuario::Usuario(int _id) {
    nombre = "";
    telefono = "";
    id = _id;
}

void Usuario::setNombre(string n) {
    nombre = n;
}

void Usuario::setTelefono(string t) {
    telefono = t;
}

string Usuario::consultarInformacion() {
    return "Nombre: " + nombre + "\nTelefono: " + telefono + '\n';
}

string Usuario::getNombre() {
    return nombre;
}

#endif