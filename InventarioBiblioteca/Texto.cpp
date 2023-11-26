#include <ctime>
#include <tuple>
#include "Categoria.cpp"
#include "Usuario.cpp"

using namespace std;

#ifndef TEXTO_CPP
#define TEXTO_CPP

/*
La clase Texto tendrá los atributos y métodos que
tendrán los recursos de la biblioteca
(como libros y revistas), y permitirá
reservar, renovar y regresar cada texto
*/

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
        Texto(string _titulo, int _anio);

        bool reservar(Usuario u);
        bool renovar();
        void setTitulo(string t);
        void setAnio(int a);
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

Texto::Texto(string _titulo, int _anio) {
    titulo = _titulo;
    anio = _anio;
    disponible = true;
}

/*
Método para reservar el texto, estableciendo
una fecha de regreso con un plazo de un mes.
Entrada:
    u (Usuario) // Usuario reservando el texto
Salida:
    (bool) // Si el texto pudo ser reservado o no
*/
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

/*
Método para agregar un mes a la fecha de devolución del texto.
Salida:
    (bool) // Si el texto pudo o no ser renovado
*/
bool Texto::renovar() {

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

void Texto::setTitulo(string t) {
    titulo = t;
}

void Texto::setAnio(int a) {
    anio = a;
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

/*
Método para registrar una nueva categoría al texto.
Entrada:
    c (Categoria) // Categoría a agregar
*/
void Texto::agregarCategoria(Categoria c) {
    for(int i=0; i<categorias.size(); i++) {
        if (categorias[i].getNombre() == c.getNombre()) {
            return;
        }
    }
    categorias.push_back(c);
}

#endif