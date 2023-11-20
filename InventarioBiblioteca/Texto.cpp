#include <ctime>
#include <tuple>
#include "Categoria.cpp"
#include "Usuario.cpp"

using namespace std;

#ifndef TEXTO_H
#define TEXTO_H

class Texto {

    protected:

        string titulo;
        int anio;
        bool disponible;
        tuple<int, string, int> fechaRegreso; // dia, mes, año
        vector<Categoria> categorias;
        Usuario usuario;

    public:

        Texto();

        void registrar();
        bool reservar(Usuario u);
        bool renovar();
        string getTitulo();
        string getFechaRegreso();
        string getNombreUsuario();
        void regresar();
        void agregarCategoria(Categoria c);

};

Texto::Texto() {
    titulo = "";
    anio = 0;
    disponible = true;
}

void Texto::registrar() {
    cout << "Ingrese el titulo:\n";
    cin.ignore();
    getline(cin, titulo);
    cout << "Ingrese anio de publicacion:\n";
    cin >> anio;
}

bool Texto::reservar(Usuario u) {

    if (disponible == false)
        return false;

    usuario = u;

    time_t now = time(0);
    string date_time = ctime(&now);
    get<0>(fechaRegreso) = stoi(date_time.substr(8, 2));
    get<1>(fechaRegreso) = date_time.substr(4, 3);
    get<2>(fechaRegreso) = stoi(date_time.substr(20, 4));
    disponible = false;
    renovar();

    return true;

}

bool Texto::renovar() {
    // Método para agregar un mes a la fecha de devolución del texto

    if (disponible == true)
        return false;

    string meses[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dec"};
    if (get<1>(fechaRegreso) == "Dec") {
        get<2>(fechaRegreso) += 1;
        get<1>(fechaRegreso) = "Jan";
    } else {
        for(int i=0; i<12; i++) {
            if (get<1>(fechaRegreso) == meses[i]) {
                get<1>(fechaRegreso) = meses[i+1];
                break;
            }
        }
    }
    return true;
}

string Texto::getTitulo() {
    return titulo;
}

string Texto::getFechaRegreso() {
    if (disponible == true) {
        return "00 00 0000";
    }
    string f = to_string(get<0>(fechaRegreso)) + ' ' + get<1>(fechaRegreso);
    f += ' ' + to_string(get<2>(fechaRegreso));
    return f;
}

string Texto::getNombreUsuario() {
    return usuario.getNombre();
}

void Texto::regresar() {
    disponible = true;
}

void Texto::agregarCategoria(Categoria c) {
    for(int i=0; i<categorias.size(); i++) {
        if (categorias[i].getNombre() == c.getNombre()) {
            return;
        }
    }
    categorias.push_back(c);
}

#endif