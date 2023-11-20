#include "Repisa.cpp"

using namespace std;

vector<Repisa> repisas(2);
vector<Categoria> categorias;
vector<Usuario> usuarios;

void inicializarCategorias() {

    string c[] = {"Filosofia", "Matematicas", "Politica", "Infantiles",
                  "Juveniles", "Literatura", "Ciencia Ficcion", "Arte",
                  "Derecho", "Finanzas", "Gastronomia", "Salud", "Cine",
                  "Lenguas", "Informatica", "Medicina"};

    for(int i=1; i<=16; i++) {
        Categoria nuevaCategoria(c[i-1], i);
        categorias.push_back(nuevaCategoria);
    }

}

void desplegarMenu() {

    cout << "\n1. Registrar libro\n";
    cout << "2. Registrar revista\n";
    cout << "3. Registrar usuario\n";
    cout << "4. Reservar libro\n";
    cout << "5. Reservar revista\n";
    cout << "6. Salir\n";

}

void reservar(int op) {
    
    if (op == 1) cout << "\nIngrese el nombre del libro:\n";
    else cout << "\nIngrese el nombre de la revista:\n";
    cin.ignore();
    string titulo, nombre;
    int posRepisa, posTexto=-1, posUsuario=-1;
    getline(cin, titulo);
    for(posRepisa=0; posRepisa<repisas.size(); posRepisa++) {
        posTexto = repisas[posRepisa].buscarTexto(op, titulo);
        if (posTexto != -1) {
            break;
        }
    }

    if (posTexto == -1) {
        if (op == 1) cout << "\nEl libro no se encuentra en esta biblioteca.\n";
        else cout << "\nLa revista no se encuentra en esta biblioteca.\n";
    } else {
        cout << "\nIngrese el nombre del usuario: ";
        //cin.ignore();
        getline(cin, nombre);
        for(int i=0; i<usuarios.size(); i++) {
            if (usuarios[i].getNombre() == nombre) {
                posUsuario = i;
                break;
            }
        }
        
        if (posUsuario == -1) {
            Usuario nuevoUsuario(nombre, usuarios.size()+1);
            usuarios.push_back(nuevoUsuario);
            posUsuario = usuarios.size()-1;
        }

        bool reservado = repisas[posRepisa].reservarTexto(op, posTexto, usuarios[posUsuario]);
        if (reservado) {
            cout << "\nReserva exitosa\n";
            repisas[posRepisa].consultarReserva(op, posTexto);
        } else {
            cout << "La reserva no se ha podido ejecutar.\n";
            if (op == 1) cout << "El libro no está disponible por el momento.\n";
            else cout << "La revista no está disponible por el momento.\n";
        }

    }
    
}

int main() {

    inicializarCategorias();

    cout << "Hola, este es un inventario de biblioteca.\n";

    bool continuar = true;
    int opcion;
    bool agregado;
    Repisa RepisaNueva;

    while (continuar) {

        desplegarMenu();
        
        cout << "\nSelecciona la opcion que quieres realizar: ";
        cin >> opcion;

        if (opcion == 1) { // Registrar libro

            agregado = repisas.back().agregarTexto(1, categorias);
            if (!agregado) {
                repisas.push_back(RepisaNueva);
                repisas.back().agregarTexto(1, categorias);
            }

        } else if (opcion == 2) { // Registrar revista

            agregado = repisas.back().agregarTexto(2, categorias);
            if (!agregado) {
                repisas.push_back(RepisaNueva);
                repisas.back().agregarTexto(2, categorias);
            }

        } else if (opcion == 3) { // Registrar usuario

            Usuario nuevoUsuario(usuarios.size()+1);
            usuarios.push_back(nuevoUsuario);

        } else if (opcion == 4) { // Reservar libro

            reservar(1);
        
        } else if (opcion == 5) { // Reservar revista
            
            reservar(2);

        } 
        else if (opcion == 6) { // Salir

            cout << "Vuelva pronto :)\n";
            continuar = false;
        
        } else {
            cout << "Opcion no valida.\n";
        }

    }

    return 0;

}