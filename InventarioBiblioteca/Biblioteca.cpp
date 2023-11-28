#include "Repisa.cpp"

using namespace std;

vector<Repisa> repisas(2);
vector<Categoria> categorias;
vector<Usuario> usuarios;

// Función que inicializa los valores del vector categorias
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

// Función que muestra las categorías disponibles
void imprimirCategorias() {
    
    cout << "\nCategorias disponibles:\n";
    for(int i=0; i<categorias.size(); i++) {
        printf("%3i. ", categorias[i].getId());
        cout << categorias[i].getNombre() << '\n';
    }

}

// Función que muestra las acciones disponibles
void desplegarMenu() {

    cout << "\n 1. Registrar usuario\n";
    cout << " 2. Registrar texto\n";
    cout << " 3. Reservar texto\n";
    cout << " 4. Renovar texto\n";
    cout << " 5. Regresar texto\n";
    cout << " 6. Ver textos en la biblioteca\n";
    cout << " 7. Salir\n";

}

/*
Función para buscar un texto en la biblioteca.
Entrada:
    op (int) // Tipo de texto
    mostrarInfo (bool) // Si se quiere mostrar la
                       // información del texto encontrado
Salida:
    {posRepisa, posTexto} (pair<int,int>)
       // Posición de la repisa y del libro/revista
*/
pair<int,int> posiciones(int op, bool mostrarInfo=true) {
    
    if (op == 1) cout << "\nIngrese el titulo del libro:\n";
    else cout << "\nIngrese el titulo de la revista:\n";

    cin.ignore();
    string titulo="";
    int posRepisa=0, posTexto=-1;
    getline(cin, titulo);

    for(posRepisa=0; posRepisa<repisas.size(); posRepisa++) {
        pair<int, string> res = repisas[posRepisa].buscarTexto(op, titulo);
        if (mostrarInfo) cout << res.second;
        posTexto = res.first;
        if (posTexto != -1) {
            break;
        }
    }

    return {posRepisa, posTexto};

}

/*
Función para registrar un nuevo texto en la biblioteca.
Entrada:
    op (int) // Tipo de texto
*/
void registrarTexto(int op) {

    bool agregado=false;
    Repisa RepisaNueva;
    if (op == 1) {

        string titulo="", autor="", editorial="";
        int anio=0, edicion=0, codigo=0;

        cout << "Ingrese el titulo:\n";
        cin.ignore();
        getline(cin, titulo);
        cout << "Ingrese anio de publicacion:\n";
        cin >> anio;
        cout << "Ingrese el nombre del autor:\n";
        cin.ignore();
        getline(cin, autor);
        cout << "Ingrese el nombre de la editorial:\n";
        getline(cin, editorial);
        cout << "Ingrese numero de edicion:\n";
        cin >> edicion;

        cout << "A que categorias pertenece este libro?\n";
        imprimirCategorias();
        cout << "Favor de ingresar el codigo de las categorias a agregar.";
        cout << "\nPara dejar de agregar categorias, ingrese 0.\n";
        
        cin >> codigo;
        vector<Categoria> c;
        while (codigo != 0) {
            if (codigo > categorias.size()) {
                cout << "Codigo no valido.\n";
            } else {
                c.push_back(categorias[codigo-1]);
            }
            cin >> codigo;
        }

        agregado = repisas.back().agregarLibro(titulo, anio, autor, editorial, edicion, c);
        if (!agregado) {
            repisas.push_back(RepisaNueva);
            repisas.back().agregarLibro(titulo, anio, autor, editorial, edicion, c);
        }

    } else {

        string titulo="", nombreRevista="";
        int anio=0, volumen=0, codigo=0;

        cout << "Ingrese el titulo:\n";
        cin.ignore();
        getline(cin, titulo);
        cout << "Ingrese anio de publicacion:\n";
        cin >> anio;
        cout << "Ingrese el nombre de la revista:\n";
        cin.ignore();
        getline(cin, nombreRevista);
        cout << "Ingrese numero de volumen:\n";
        cin >> volumen;

        cout << "A que categorias pertenece esta revista?\n";
        imprimirCategorias();
        cout << "Favor de ingresar el codigo de las categorias a agregar.";
        cout << "\nPara dejar de agregar categorias, ingrese 0.\n";
        
        cin >> codigo;
        vector<Categoria> c;
        while (codigo != 0) {
            if (codigo > categorias.size()) {
                cout << "Codigo no valido.\n";
            } else {
                c.push_back(categorias[codigo-1]);
            }
            cin >> codigo;
        }

        agregado = repisas.back().agregarRevista(titulo, anio, nombreRevista, volumen, c);
        if (!agregado) {
            repisas.push_back(RepisaNueva);
            repisas.back().agregarRevista(titulo, anio, nombreRevista, volumen, c);
        }

    }

}

/*
Función para reservar un texto de la biblioteca.
Entrada:
    op (int) // Tipo de texto
*/
void reservar(int op) {
    
    pair<int,int> p = posiciones(op);
    int posRepisa = p.first, posTexto = p.second;
    
    int posUsuario = -1;
    string nombre="";

    if (posTexto == -1) {

        if (op == 1) cout << "\nEl libro no se encuentra en esta biblioteca.\n";
        else cout << "\nLa revista no se encuentra en esta biblioteca.\n";

    } else {

        cout << "\nIngrese el nombre del usuario: ";
        getline(cin, nombre);

        for(int i=0; i<usuarios.size(); i++) {
            if (usuarios[i].getNombre() == nombre) {
                posUsuario = i;
            }
        }
        
        if (posUsuario == -1) {
            Usuario nuevoUsuario;
            
            string telefono="";
            cout << "Ingrese numero de telefono:\n";
            getline(cin, telefono);

            nuevoUsuario.setNombre(nombre);
            nuevoUsuario.setTelefono(telefono);

            usuarios.push_back(nuevoUsuario);

            posUsuario = usuarios.size()-1;
        }

        bool reservado = repisas[posRepisa].reservarTexto(op, posTexto, usuarios[posUsuario]);
        if (reservado) {
            cout << "\nReserva exitosa\n";
            cout << repisas[posRepisa].consultarReserva(op, posTexto);
        } else {
            cout << "La reserva no se ha podido ejecutar.\n";
            if (op == 1) cout << "El libro no esta disponible por el momento.\n";
            else cout << "La revista no esta disponible por el momento.\n";
        }

    }
    
}

/*
Función para renovar la fecha de regreso de un libro.
Entrada:
    op (int) // Tipo de texto
*/
void renovar(int op) {
    
    pair<int,int> p = posiciones(op, false);
    int posRepisa = p.first, posTexto = p.second;

    if (posTexto == -1) {

        if (op == 1) cout << "\nEl libro no se encuentra en esta biblioteca.\n";
        else cout << "\nLa revista no se encuentra en esta biblioteca.\n";

    } else {

        string fechaRegreso = repisas[posRepisa].renovarTexto(op, posTexto);

        if (fechaRegreso == "-1") {
            if (op == 1) cout << "Este libro no ha sido reservado.\n";
            else cout << "Esta revista no ha sido reservada.\n";
        } else {
            cout << fechaRegreso;
        }

    }

}

/*
Función para regresar un texto de la biblioteca.
Entrada:
    op (int) // Tipo de texto
*/
void regresar(int op) {
    
    pair<int,int> p = posiciones(op, false);
    int posRepisa = p.first, posTexto = p.second;

    if (posTexto == -1) {

        if (op == 1) cout << "\nEl libro no es de esta biblioteca.\n";
        else cout << "\nLa revista no es de esta biblioteca.\n";

    } else {

        repisas[posRepisa].regresarTexto(op, posTexto);
        cout << "Proceso concluido.\n";

    }

}

int main() {

    inicializarCategorias();

    cout << "\nHola, este es un inventario de biblioteca.\n";

    bool continuar = true;
    int opcion=0, op=0;

    while (continuar) {

        desplegarMenu();
        
        cout << "\nSelecciona la opcion que quieres realizar: ";
        cin >> opcion;

        if (opcion >= 2 && opcion <= 5) {

            // Preguntar por el tipo de texto
            string accion[] = {"registrar", "reservar", "renovar", "regresar"};
            cout << "El texto que quiere " << accion[opcion-2] << " es libro (1) o revista (2)?\n";
            cin >> op;
            if (op != 1 && op != 2) {
                cout << "Opcion no valida.\n";
                continue;
            }

        }

        if (opcion == 1) { // Registrar usuario

            Usuario nuevoUsuario;
            
            string nombre="", telefono="";
            cout << "Ingrese nombre del usuario:\n";
            cin.ignore();
            getline(cin, nombre);

            bool registrado=false;
            for(int i=0; i<usuarios.size(); i++) {
                if (usuarios[i].getNombre() == nombre) {
                    cout << "Este usuario ya ha sido registrado.\n";
                    cout << "Informacion:\n" << usuarios[i].consultarInformacion();
                    registrado = true;
                }
            }

            if (!registrado) {

                cout << "Ingrese numero de telefono:\n";
                cin.ignore();
                getline(cin, telefono);

                nuevoUsuario.setNombre(nombre);
                nuevoUsuario.setTelefono(telefono);

                usuarios.push_back(nuevoUsuario);

            }

        } else if (opcion == 2) { // Registrar texto

            registrarTexto(op);

        } else if (opcion == 3) { // Reservar texto

            reservar(op);

        } else if (opcion == 4) { // Renovar texo

            renovar(op);
        
        } else if (opcion == 5) { // Regresar texto
            
            regresar(op);

        } else if (opcion == 6) { // Ver textos en la biblioteca

            string repisaInfo="";

            for (int i=1; i<repisas.size(); i++) {

                cout << "\nRepisa " << i << ":\n";
                repisaInfo = repisas[i].consultarTextos();
                cout << repisaInfo;

            }

            if (repisaInfo == "-\n") {
                cout << "\nLa biblioteca aun no cuenta con textos.\n";
            }

        } else if (opcion == 7) { // Salir

            cout << "Vuelva pronto :)\n";
            continuar = false;
        
        } else {

            cout << "Opcion no valida.\n";
        
        }

    }

    return 0;

}