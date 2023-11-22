#include "Texto.cpp"

using namespace std;

class Revista : public Texto {

    private:

        int volumen;
        string nombreRevista;

    public:

        Revista();
        Revista(string titulo, int anio);

        void setVolumen(int _volumen);
        void setNombreRevista(string _nombre);
        int getVolumen();
        string getNombreRevista();
        string consultarInformacion();

};

Revista::Revista() {
    volumen = 0;
    nombreRevista = "";
}

Revista::Revista(string _titulo, int _anio):Texto(_titulo, _anio) {
    volumen = 0;
    nombreRevista = "";
}

void Revista::setVolumen(int _volumen) {
    volumen = _volumen;
}

void Revista::setNombreRevista(string _nombre) {
    nombreRevista = _nombre;
}

int Revista::getVolumen() {
    return volumen;
}

string Revista::getNombreRevista() {
    return nombreRevista;
}

string Revista::consultarInformacion() {
    string ret = "";
    ret += "Titulo: " + titulo;
    ret += "\nNombre de la revista: " + nombreRevista;
    ret += "\nVolumen: " + volumen;
    ret += "\nAnio de publicacion: " + anio;
    ret += "\nCategorias a las que pertenece:\n";
    for (int i=0; i<categorias.size(); i++) {
        ret += "- " + categorias[i].getNombre() + '\n';
    }
    if (categorias.size() == 0) {
        ret += "No se le ha asignado ninguna categoria hasta el momento.\n";
    }
    return ret;
}