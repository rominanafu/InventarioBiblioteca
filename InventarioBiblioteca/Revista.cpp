#include "Texto.cpp"

using namespace std;

class Revista : public Texto {

    private:

        int volumen;
        string nombreRevista;

    public:

        void setVolumen(int _volumen);
        void setNombreRevista(string _nombre);
        int getVolumen();
        string getNombreRevista();
        void consultarInformacion();

};

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

void Revista::consultarInformacion() {
    cout << "Titulo: " << titulo << endl;
    cout << "Nombre de la revista: " << nombreRevista << endl;
    cout << "Volumen: " << volumen << endl;
    cout << "Anio de publicacion: " << anio << endl;
    cout << "Categorias a las que pertenece: " << endl;
    for (int i=0; i<categorias.size(); i++) {
        cout << "- " << categorias[i].getNombre() << endl;
    }
    if (categorias.size() == 0) {
        cout << "No se le ha asignado ninguna categoria hasta el momento.\n";
    }
}