#include "Texto.cpp"

using namespace std;

#ifndef LIBRO_CPP
#define LIBRO_CPP

/*
La clase Libro es un tipo de texto
que contiene un número de edición,
una editorial y un autor.
*/

class Libro : public Texto {

    private:
    
        int edicion;
        string editorial;
        string autor;
    
    public:
    
        Libro();
        Libro(string titulo, int anio);

        void setEdicion(int _edicion);
        void setEditorial(string _editorial);
        void setAutor(string _autor);
        int getEdicion();
        string getEditorial();
        string getAutor();
        string consultarInformacion();

};

Libro::Libro():Texto() {
    edicion = 0;
    editorial = "";
    autor = "";
}

Libro::Libro(string _titulo, int _anio):Texto(_titulo, _anio) {
    edicion = 0;
    editorial = "";
    autor = "";
}

void Libro::setEdicion(int _edicion) {
    edicion = _edicion;
}

void Libro::setEditorial(string _editorial) {
    editorial = _editorial;
}

void Libro::setAutor(string _autor) {
    autor = _autor;
}

int Libro::getEdicion() {
    return edicion;
}

string Libro::getEditorial() {
    return editorial;
}

string Libro::getAutor() {
    return autor;
}

/*
Método para consultar toda la información del libro.
Salida:
    ret (string) // String con toda la información del libro
*/
string Libro::consultarInformacion() {
    
    string ret = "";

    ret += "Titulo: " + titulo;
    ret += "\nAutor: " + autor;
    ret += "\nEditorial: " + editorial;
    ret += "\nEdicion: " + to_string(edicion);
    ret += "\nAnio de publicacion: " + to_string(anio);
    ret += "\nCategorias a las que pertenece:\n";

    for (int i=0; i<categorias.size(); i++) {
        ret += "- " + categorias[i].getNombre() + "\n";
    }
    
    if (categorias.size() == 0) {
        ret += "No se le asigno ninguna categoria.\n";
    }

    return ret;
}

#endif