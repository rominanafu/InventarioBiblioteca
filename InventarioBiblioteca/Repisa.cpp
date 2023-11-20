#include "Libro.cpp"
#include "Revista.cpp"

using namespace std;

class Repisa {

    private:

        vector<int> tipoTexto;
        vector<Libro> libros;
        vector<Revista> revistas;
        int capacidad;

        void imprimirCategorias(vector<Categoria> categorias);

    public:

        Repisa();
        Repisa(int _capacidad);

        bool agregarTexto(int op, vector<Categoria> categorias);
        void consultarTextos();
        int buscarTexto(int op, string titulo);
        bool reservarTexto(int op, int pos, Usuario u);
        bool renovarTexto(int op, int pos);
        void consultarReserva(int op, int pos);
        bool quitarTexto(int pos);

};

Repisa::Repisa() {
    capacidad = 10;
}

Repisa::Repisa(int _capacidad) {
    capacidad = _capacidad;
}

void Repisa::imprimirCategorias(vector<Categoria> categorias) {
    //cout << categorias[0].getNombre();
    cout << "\nCategorias disponibles:\n";
    for(int i=0; i<categorias.size(); i++) {
        printf("%3i. ", categorias[i].getId());
        cout << categorias[i].getNombre() << '\n';
    }

}

bool Repisa::agregarTexto(int op, vector<Categoria> categorias) {

    if (tipoTexto.size() == capacidad) {
        return false;
    }

    if (op == 1) { // Agregar y registrar libro

        tipoTexto.push_back(1);

        Libro NuevoLibro;
        string autor, editorial;
        int edicion, codigo;

        NuevoLibro.registrar();

        cout << "Ingrese el nombre del autor:\n";
        cin.ignore();
        getline(cin, autor);
        cout << "Ingrese el nombre de la editorial:\n";
        //cin.ignore();
        getline(cin, editorial);
        cout << "Ingrese número de edición:\n";
        cin >> edicion;

        NuevoLibro.setAutor(autor);
        NuevoLibro.setEditorial(editorial);
        NuevoLibro.setEdicion(edicion);

        cout << "A que categorias pertenece este libro?\n";
        imprimirCategorias(categorias);
        cout << "Favor de ingresar el codigo de las categorias a agregar.";
        cout << "\nPara dejar de agregar categorias, ingrese 0.\n";
        cin >> codigo;
        while (codigo != 0) {
            if (codigo > categorias.size()) {
                cout << "Codigo no valido.\n";
            } else {
                NuevoLibro.agregarCategoria(categorias[codigo-1]);
            }
            cin >> codigo;
        }

        libros.push_back(NuevoLibro);

    } else { // Agregar y registrar revista

        tipoTexto.push_back(2);

        Revista NuevaRevista;
        string nombreRevista;
        int volumen, codigo;

        NuevaRevista.registrar();

        cout << "Ingrese el nombre de la revista:\n";
        cin.ignore();
        getline(cin, nombreRevista);
        cout << "Ingrese numero de volumen:\n";
        cin >> volumen;

        NuevaRevista.setNombreRevista(nombreRevista);
        NuevaRevista.setVolumen(volumen);

        cout << "A que categorias pertenece esta revista?\n";
        imprimirCategorias(categorias);
        cout << "Favor de ingresar el codigo de las categorias a agregar.";
        cout << "\nPara dejar de agregar categorias, ingrese 0.\n";
        cin >> codigo;
        while (codigo != 0) {
            if (codigo > categorias.size()) {
                cout << "Codigo no valido.\n";
            } else {
                NuevaRevista.agregarCategoria(categorias[codigo-1]);
            }
            cin >> codigo;
        }

        revistas.push_back(NuevaRevista);

    }

    return true;

}

void Repisa::consultarTextos() {

    int pos_libros, pos_revistas;

    if (tipoTexto.size() == 0) {
        cout << "La repisa está vacía.\n";
    }

    for(int pos=0; pos<tipoTexto.size(); pos++) {
        if (tipoTexto[pos] == 1) {
            printf("%3i. %s", pos+1, libros[pos_libros++].getTitulo());
        } else {
            printf("%3i. %s", pos+1, revistas[pos_revistas++].getTitulo());
        }
    }

}

int Repisa::buscarTexto(int op, string titulo) {

    int posLibro = 0, posRevista = 0;
    
    for(int i=0; i<tipoTexto.size(); i++) {
        if (tipoTexto[i] == op) {
            if (op == 1) {
                if (libros[posLibro].getTitulo() == titulo) {
                    cout << "\nLos detalles del libro que busca son los siguientes:\n";
                    libros[posLibro].consultarInformacion();
                    return posLibro;
                }
                posLibro++;
            } else {
                if (revistas[posRevista].getTitulo() == titulo) {
                    cout << "\nLos detalles de la revista que busca son los siguientes:\n";
                    revistas[posRevista].consultarInformacion();
                    return posRevista;
                }
                posRevista++;
            }
        }
    }
    
    return -1;

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

bool Repisa::renovarTexto(int op, int pos) {
    
    bool posible;
    if (op == 1) {
        posible = libros[pos].renovar();
    } else {
        posible = revistas[pos].renovar();
    }
    return posible;

}

void Repisa::consultarReserva(int op, int pos) {

    if (op == 1) {
        cout << "El libro " << libros[pos].getTitulo() << " fue reservado por ";
        cout << libros[pos].getNombreUsuario() << endl;
        cout << "Se espera que el libro sea devuelto el ";
        cout << libros[pos].getFechaRegreso() << endl;
    } else {
        cout << "La revista " << revistas[pos].getTitulo() << " fue reservada por ";
        cout << revistas[pos].getNombreUsuario() << endl;
        cout << "Se espera que la revista sea devuelta en: ";
        cout << revistas[pos].getFechaRegreso() << endl;
    }

}

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