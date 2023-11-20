#include<iostream>
#include<vector>

using namespace std;

#ifndef USUARIO_H
#define USUARIO_H

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
        Usuario(string n, int _id);

        void registrarUsuario(string, string t);
        void consultarInformacion();
        string getNombre();

};

Usuario::Usuario() {
    nombre = "";
    telefono = "";
    id = 0;
}

Usuario::Usuario(int _id) {
    string n, t;
    cout << "Ingrese nombre del usuario:\n";
    cin.ignore();
    getline(cin, n);
    cout << "Ingrese numero de telefono:\n";
    cin.ignore();
    getline(cin, t);
    nombre = n;
    telefono = t;
    id = _id;
}

Usuario::Usuario(string n, int _id) {
    string t;
    cout << "Ingrese numero de telefono:\n";
    cin.ignore();
    getline(cin, t);
    
    nombre = n;
    telefono = t;
    id = _id;
}

void Usuario::registrarUsuario(string n, string t) {
    nombre = n;
    telefono = t;
}

void Usuario::consultarInformacion() {
    cout << "Nombre: " << nombre << '\n';
    cout << "Teléfono: " << telefono << '\n';
}

string Usuario::getNombre() {
    return nombre;
}

#endif