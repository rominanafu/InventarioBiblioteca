#include "Libro.cpp"
#include "Revista.cpp"

using namespace std;

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
        //bool quitarTexto(int pos);

};

Repisa::Repisa() {
    capacidad = 10;
}

Repisa::Repisa(int _capacidad) {
    capacidad = _capacidad;
}

bool Repisa::agregarLibro(string titulo, int anio, string autor, string editorial, int edicion, vector<Categoria> c) {

    if (tipoTexto.size() == capacidad) {
        return false;
    }

    tipoTexto.push_back(1);

    Libro nuevoLibro(titulo, anio);

    nuevoLibro.setAutor(autor);
    nuevoLibro.setEditorial(editorial);
    nuevoLibro.setEdicion(edicion);

    for(int i=0; i<c.size(); i++) {
        nuevoLibro.agregarCategoria(c[i]);
    }

    libros.push_back(nuevoLibro);

    return true;

}

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

string Repisa::consultarTextos() {

    int pos_libros=0, pos_revistas=0;

    if (tipoTexto.size() == 0) {
        return "-\n";
    }

    string ret = "";

    for(int pos=0; pos<tipoTexto.size(); pos++) {
        ret += to_string(pos+1)+". ";
        if (tipoTexto[pos] == 1) {
            ret += libros[pos_libros++].getTitulo();
        } else {
            ret += revistas[pos_revistas++].getTitulo();
        }
        ret += "\n";
    }

    return ret;

}

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

bool Repisa::reservarTexto(int op, int pos, Usuario u) {
    
    bool posible;
    if (op == 1) {
        posible = libros[pos].reservar(u);
    } else {
        posible = revistas[pos].reservar(u);
    }
    return posible;

}

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

void Repisa::regresarTexto(int op, int pos) {

    if (op == 1) {
        libros[pos].regresar();
    } else {
        revistas[pos].regresar();
    }

}

/*
bool Repisa::quitarTexto(int pos) {

    if (tipoTexto.size() < pos) {
        return false;
    }

    int posLibro = 0, posRevista = 0;

    for(int i=0; i<pos; i++) {
        if (tipoTexto[pos] == 1 && tipoTexto[i] == 1) {
            posLibro++;
        } else if (tipoTexto[pos] == 2 && tipoTexto[i] == 2) {
            posRevista++;
        }
    }

    if (tipoTexto[pos] == 1) {
        for (posLibro; posLibro < libros.size()-1; posLibro++) {
            libros[posLibro] = libros[posLibro+1];
        }
        libros.pop_back();
    } else {
        for (posRevista; posRevista < revistas.size()-1; posRevista++) {
            revistas[posRevista] = revistas[posRevista+1];
        }
        revistas.pop_back();
    }

    for(int i=pos; i<tipoTexto.size()-1; i++) {
        tipoTexto[i] = tipoTexto[i+1];
    }

    tipoTexto.pop_back();

    return true;

}
*/