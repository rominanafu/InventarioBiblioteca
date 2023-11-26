#include "Libro.cpp"
#include "Revista.cpp"

using namespace std;

/*
La clase Repisa contendrá hasta 10 textos
de la biblioteca (ya sean libros o revistas),
y podrá buscar si cierto titulo ha sido guardado
en dicha repisa, reservarlo, renovarlo, regresarlo,
entre otras acciones.
*/

class Repisa {

    private:

        vector<int> tipoTexto;
        vector<Libro> libros;
        vector<Revista> revistas;
        int capacidad;

    public:

        Repisa();
        Repisa(int _capacidad);

        bool agregarLibro(string titulo, int anio, string autor, string editorial, int edicion, vector<Categoria> c);
        bool agregarRevista(string titulo, int anio, string nombreRevista, int volumen, vector<Categoria> c);
        string consultarTextos();
        pair<int, string> buscarTexto(int op, string titulo);
        bool reservarTexto(int op, int pos, Usuario u);
        string renovarTexto(int op, int pos);
        string consultarReserva(int op, int pos);
        void regresarTexto(int op, int pos);

};

Repisa::Repisa() {
    capacidad = 10;
}

Repisa::Repisa(int _capacidad) {
    capacidad = _capacidad;
}

/*
Método para agregar un libro en la repisa
Entrada:
    titulo (string)
    año (int)
    autor (string)
    editorial (string)
    edicion (int)
    c (vector<Categoria>) // Categorías del libro
Salida:
    (bool) // Si el libro pudo ser agregado a la repisa o no
*/
bool Repisa::agregarLibro(string titulo, int anio, string autor, string editorial, int edicion, vector<Categoria> c) {

    if (tipoTexto.size() == capacidad) {
        return false;
    }

    tipoTexto.push_back(1);

    Libro nuevoLibro;

    nuevoLibro.setTitulo(titulo);
    nuevoLibro.setAnio(anio);
    nuevoLibro.setAutor(autor);
    nuevoLibro.setEditorial(editorial);
    nuevoLibro.setEdicion(edicion);

    for(int i=0; i<c.size(); i++) {
        nuevoLibro.agregarCategoria(c[i]);
    }

    libros.push_back(nuevoLibro);

    return true;

}

/*
Método para agregar una revista en la repisa
Entrada:
    titulo (string)
    año (int)
    nombreRevista (string)
    volumen (int)
    c (vector<Categoria>) // Categorías de la revista
Salida:
    (bool) // Si la revista pudo ser agregada a la repisa o no
*/
bool Repisa::agregarRevista(string titulo, int anio, string nombreRevista, int volumen, vector<Categoria> c) {

    if (tipoTexto.size() == capacidad) {
        return false;
    }

    tipoTexto.push_back(2);

    Revista nuevaRevista(titulo, anio);

    nuevaRevista.setNombreRevista(nombreRevista);
    nuevaRevista.setVolumen(volumen);

    for(int i=0; i<c.size(); i++) {
        nuevaRevista.agregarCategoria(c[i]);
    }

    revistas.push_back(nuevaRevista);

    return true;

}

/*
Método para obtener la lista de textos en la repisa
Salida:
    textos (string) // Lista de textos: posición y título
*/
string Repisa::consultarTextos() {

    int pos_libros=0, pos_revistas=0;

    if (tipoTexto.size() == 0) {
        return "-\n";
    }

    string textos = "";

    for(int pos=0; pos<tipoTexto.size(); pos++) {
        textos += to_string(pos+1)+". ";
        if (tipoTexto[pos] == 1) {
            textos += libros[pos_libros++].getTitulo();
        } else {
            textos += revistas[pos_revistas++].getTitulo();
        }
        textos += "\n";
    }

    return textos;

}

/*
Método para buscar un texto en la repisa.
Entrada:
    op (int) // Tipo de texto
    titulo (string)
Salida:
    {posición, detalles} (pair<int, string>)
    // Regresa posición del texto y la información de este
*/
pair<int, string> Repisa::buscarTexto(int op, string titulo) {

    int posLibro = 0, posRevista = 0;
    string res = "";
    
    for(int i=0; i<tipoTexto.size(); i++) {
        if (tipoTexto[i] == op) {
            if (op == 1) {
                if (libros[posLibro].getTitulo() == titulo) {
                    res += "\nLos detalles del libro que busca son los siguientes:\n";
                    res += libros[posLibro].consultarInformacion();
                    return {posLibro, res};
                }
                posLibro++;
            } else {
                if (revistas[posRevista].getTitulo() == titulo) {
                    res += "\nLos detalles de la revista que busca son los siguientes:\n";
                    res += revistas[posRevista].consultarInformacion();
                    return {posRevista, res};
                }
                posRevista++;
            }
        }
    }
    
    return {-1, res};

}

/*
Método para reservar un texto.
Entrada:
    op (int) // Tipo de texto
    pos (int) // Posición del texto
    u (Usuario) // Usuario reservando el texto
Salida:
    posible (bool) // Si el texto pudo ser reservado o no
*/
bool Repisa::reservarTexto(int op, int pos, Usuario u) {
    
    bool posible;
    if (op == 1) {
        posible = libros[pos].reservar(u);
    } else {
        posible = revistas[pos].reservar(u);
    }
    return posible;

}

/*
Método para renovar la fecha de regreso de un texto.
Entrada:
    op (int) // Tipo de texto
    pos (int) // Posición del texto
Salida:
    ret (string) // Nueva fecha de regreso
*/
string Repisa::renovarTexto(int op, int pos) {
    
    bool posible;
    string ret = "";
    if (op == 1) {
        posible = libros[pos].renovar();
    } else {
        posible = revistas[pos].renovar();
    }

    if (posible) {
        ret += "La nueva fecha de regreso es: ";
        if (op == 1) ret += libros[pos].getFechaRegreso() + '\n';
        else ret += revistas[pos].getFechaRegreso() + '\n';
    } else {
        ret = "-1";
    }

    return ret;

}

/*
Método para consultar la reserva de un texto.
Entrada:
    op (int) // Tipo de texto
    pos (int) // Posición del texto
Salida:
    ret (string) // Información de la reserva
*/
string Repisa::consultarReserva(int op, int pos) {

    string ret = "";
    if (op == 1) {
        ret += "El libro " + libros[pos].getTitulo() + " fue reservado por ";
        ret += libros[pos].getNombreUsuario();
        ret += "\nSe espera que el libro sea devuelto el ";
        ret += libros[pos].getFechaRegreso() + "\n";
    } else {
        ret += "La revista " + revistas[pos].getTitulo() + " fue reservada por ";
        ret += revistas[pos].getNombreUsuario();
        ret += "\nSe espera que la revista sea devuelta en: ";
        ret += revistas[pos].getFechaRegreso() + "\n";
    }
    return ret;

}

/*
Método para regresar un texto
Entrada:
    op (int) // Tipo de texto
    pos (int) // Posición del texto
*/
void Repisa::regresarTexto(int op, int pos) {

    if (op == 1) {
        libros[pos].regresar();
    } else {
        revistas[pos].regresar();
    }

}