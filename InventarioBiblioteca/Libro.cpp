#include "Texto.cpp"

using namespace std;

class Libro : public Texto {

    private:
    
        int edicion;
        string editorial;
        string autor;
    
    public:
    
        Libro();

        void setEdicion(int _edicion);
        void setEditorial(string _editorial);
        void setAutor(string _autor);
        int getEdicion();
        string getEditorial();
        string getAutor();
        void consultarInformacion();

};

Libro::Libro():Texto() {
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

void Libro::consultarInformacion() {
    
    cout << "Titulo: " << titulo << endl;
    cout << "Autor: " << autor << endl;
    cout << "Editorial: " << editorial << endl;
    cout << "Edicion: " << edicion << endl;
    cout << "Anio de publicacion: " << anio << endl;
    cout << "Categorias a las que pertenece: " << endl;

    for (int i=0; i<categorias.size(); i++) {
        cout << "- " << categorias[i].getNombre() << endl;
    }
    
    if (categorias.size() == 0) {
        cout << "No se le ha asignado ninguna categoria hasta el momento.\n";
    
    }
}