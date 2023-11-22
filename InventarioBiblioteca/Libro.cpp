#include "Texto.cpp"

using namespace std;

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

Libro::Libro() {
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

string Libro::consultarInformacion() {
    
    string ret = "";

    ret += "Titulo: " + titulo;
    ret += "\nAutor: " + autor;
    ret += "\nEditorial: " + editorial;
    ret += "\nEdicion: " + to_string(edicion);
    ret += "\nAnio de publicacion: " + to_string(anio);
    ret += "Categorias a las que pertenece:\n";

    for (int i=0; i<categorias.size(); i++) {
        ret += "- " + categorias[i].getNombre() + "\n";
    }
    
    if (categorias.size() == 0) {
        ret += "No se le ha asignado ninguna categoria hasta el momento.\n";
    }

    return ret;
}