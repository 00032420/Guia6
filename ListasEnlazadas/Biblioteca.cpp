#include <iostream>
#include <string>
using namespace std;

//Definicion del registro libro

enum generos{ciencia_ficcion, aventura, policial, romance, misterio};

struct libro{
    int isbn{};
    string titulo;
    string autor;
    generos genero;
    bool espanol{};
};
typedef struct libro Libro;

//Funciones propias de los libros

Libro solicitarDato(){
    Libro unLibro;

    //Solicitar ISBN, Titulo y Autor
    cout << "ISBN: "; cin >> unLibro.isbn;
    cin.ignore();

    cout << "Titulo: "; getline(cin, unLibro.titulo);
    cout << "Autor: "; getline(cin, unLibro.autor);

    //Solicitar genero del libro
    bool continuar = true;
    do{
        char opcion = 0;
        cout << "Generos: \n";
        cout << "\nC] Ciencia-Ficcion";
        cout << "\nA] Aventura";
        cout << "\nP] Policial";
        cout << "\nR] Romance";
        cout << "\nM] Misterio";
        cout << "\n\nIntroduzca la inicial del genero: ";

        cin >> opcion;
        switch(opcion) {
            case 'c':
            case 'C':
                unLibro.genero = ciencia_ficcion;
                continuar = false;
                break;

            case 'a':
            case 'A':
                unLibro.genero = aventura;
                continuar = false;
                break;

            case 'p':
            case 'P':
                unLibro.genero = policial;
                continuar = false;
                break;

            case 'r':
            case 'R':
                unLibro.genero = romance;
                continuar = false;
                break;

            case 'm':
            case 'M':
                unLibro.genero = misterio;
                continuar = false;
                break;

            default:
                cout << "\nOpcion invalida\n";
                break;
        }

        }while(continuar);

        //solicitar idioma del libro

        continuar = true;

        do{
            char letra = 0;
            cout << "Espanol (s/n): ";
            cin >> letra;

            switch(letra) {
                case 's':
                case 'S':
                    unLibro.espanol = true;
                    continuar = false;
                    break;

                case 'n':
                case 'N':
                    unLibro.espanol = false;
                    continuar = false;
                    break;

                default:
                    cout << "\nOpcion erronea\n";
            }

            } while(continuar);

            //Retornar libro ya poblado

            return unLibro;
}

void mostrarDato(const Libro& unLibro){
    cout << "\nISBN: " << unLibro.isbn << endl;
    cout << "Titulo: " << unLibro.titulo << endl;
    cout << "Autor: " << unLibro.autor << endl;

    cout << "Genero: ";

    switch (unLibro.genero) {
        case ciencia_ficcion: cout << "Ciencia-Ficcion: " << endl; break;
        case aventura: cout << "Aventura: " << endl; break;
        case policial: cout << "Policial: " << endl; break;
        case romance: cout << "Romance: " << endl; break;
        case misterio: cout << "Misterio: " << endl; break;
    }

    cout << "Idioma: " << (unLibro.espanol ? "Espanol" : "Otro") << endl;

}

bool comparar(const Libro& a, Libro b){
    return (a.isbn == b.isbn) && (a.titulo == b.titulo) && (a.autor == b.autor) && (a.genero == b.genero) && (a.espanol == b.espanol);
}

//Definicion de la lista simplemente enlazada

typedef Libro T;
const T noValido = {-1, {""}, {""}, misterio, false};

struct Nodo{
    T dato;
    struct Nodo *siguiente{};
};

Nodo *pInicio;

//Prototipos de funciones de la lista

int cantidadDatos();
void insertarInicio(T);
void insertarFinal(T);
void insertarDespuesDe(T);
void insertarAntesDe(T);
void agregar();
void mostrar();
void eliminar();
void buscar();
void invertir(Nodo*);
void vaciar(Nodo**);
int contarOcurrencias();
T acceder();

//Programa principal

int main(){
    cout << "Inicializando..." << endl;
    pInicio = nullptr;

    bool continuar = true;

    do{
        int opcion = 0;
        cout << "\nMenu: \n";
        cout << "\n1] Agregar\n";
        cout << "2] Mostrar Todos\n";
        cout << "3] Eliminar\n";
        cout << "4] Buscar\n";
        cout << "5] Invertir\n";
        cout << "6] Vaciar\n";
        cout << "7] Cantidad\n";
        cout << "8] Contar Ocurrencias\n";
        cout << "9] Acceder\n";
        cout << "10] Salir\n";

        cout << "\nIngrese el numero de su opcion: ";
        cin >> opcion;
        switch(opcion){
            case 1: agregar(); break;
            case 2: mostrar(); break;
            case 3: eliminar(); break;
            case 4: buscar(); break;
            case 5: invertir(&pInicio); break;
            case 6: vaciar(&pInicio); break;
            case 7: cout << "Hay " << cantidadDatos() << " datos.\n"; break;
            case 8: cout << "Esta " << contarOcurrencias() << " veces.\n"; break;
            case 9: acceder(); break;
            case 10: continuar = false; break;
            default: cout << "\nOpcion invalida" << endl; break;

        }
    }while (continuar);

    return 0;
}

//Implementacion de funciones de la lista

int cantidadDatos(){
    Nodo *unNodo = pInicio;

    int contador = 0;
    while(unNodo != nullptr){
        unNodo = unNodo->siguiente;
        contador ++;
    }
    return contador;
}

void mostrar(){
    Nodo *unNodo = pInicio;

    while(unNodo != nullptr){
        mostrarDato(unNodo->dato);
        unNodo = unNodo->siguiente;
    }
}

void insertarInicio(T dato){
    Nodo *nuevo = new Nodo;
    nuevo->dato = std::move(dato);
    nuevo->siguiente = pInicio;

    pInicio = nuevo;

}

void insertarFinal(T dato){
    Nodo *nuevo = new Nodo;
    nuevo->dato = std::move(dato);
    nuevo->siguiente = nullptr;

    if(pInicio == nullptr){
        pInicio = nuevo;
    } else{
        Nodo *aux = pInicio;
        Nodo *unNodo = nullptr;
        while(aux != nullptr){
            unNodo = aux;
            aux = aux->siguiente;
        }
        unNodo->siguiente = nuevo;
    }
}

void insertarDespuesDe(T dato){
    cout << "Dato de referencia: ";
    T ref = solicitarDato();

    Nodo *unNodo = pInicio;

    while(unNodo != nullptr && comparar(unNodo->dato, ref))
        unNodo = unNodo->siguiente;
    if(unNodo == nullptr){
        cout << "\nDato de referencia no existe" << endl;
        return;
    }
    Nodo *nuevo = new Nodo;
    nuevo->dato = dato;
    nuevo->siguiente = unNodo->siguiente;

    unNodo->siguiente = nuevo;
    cout << "Dato insertado con exito" << endl;

}

void insertarAntesDe(T dato){
    cout << "Dato de referencia: ";
    T ref = solicitarDato();

    Nodo *unNodo = pInicio, *aux = nullptr;

    while (unNodo != nullptr && !comparar(unNodo->dato, ref)){
        aux = unNodo;
        unNodo = unNodo->siguiente;
    }

    if(unNodo == nullptr){
        cout << "\nDato de referencia no existe.\n" << endl;
        return;
    }

    Nodo *nuevo = new Nodo;
    nuevo->dato = dato;
    nuevo->siguiente = unNodo;

    if(aux == nullptr) pInicio = nuevo;
    else aux->siguiente = nuevo;

    cout << "\nDato insertado con exito\n" << endl;
}

void agregar(){
    T dato = solicitarDato();
    bool continuar = true;
    do{
        int opcion = 0;
        cout << "\n1] Al principio\n";
        cout << "2] Al final\n";
        cout << "3] Despues de\n";
        cout << "4] Antes de\n";
        cin >> opcion;

        switch(opcion){
            case 1: insertarInicio(dato); continuar = false; break;
            case 2: insertarFinal(dato); continuar = false; break;
            case 3: insertarDespuesDe(dato); continuar = false; break;
            case 4: insertarAntesDe(dato); continuar = false; break;
            default: cout << "Opcion erronea" << endl; break;
        }
    }while(continuar);
}

void eliminar(){
    cout << "Datoa eliminar: ";
    T ref = solicitarDato();

    Nodo *unNodo = pInicio, *aux = nullptr;

    while(unNodo != nullptr && !comparar(unNodo->dato, ref)){
        aux = unNodo;
        unNodo = unNodo->siguiente;
    }

    if(unNodo == nullptr){
        cout << "\nDato a borrar ni existe\n";
        return ;
    }

    if(aux == nullptr) pInicio = unNodo->siguiente;
    else aux->siguiente = unNodo->siguiente;
    delete (unNodo);
    cout << "Dato borrado!" << endl;
}

void buscar(){
    cout << "Dato a buscar: ";
    T ref = solicitarDato();

    Nodo *unNodo = pInicio;

    while(unNodo != nullptr && !comparar(unNodo->dato, ref)) unNodo = unNodo->siguiente;

    if(unNodo != nullptr) cout << "El dato si se encuentra" << endl;
    else cout << "El dato no se encuentra" << endl;
}

void invertir(Nodo** nodoInicio){
    Nodo *resultante = nullptr;
    Nodo *actual = *nodoInicio;
    Nodo *siguiente;

    while(actual != nullptr){
        siguiente = actual->siguiente;

        actual->siguiente = resultante;
        resultante = actual;

        actual = siguiente;
    }
    *nodoInicio = resultante;
}

void vaciar(Nodo** nodoInicio){
    Nodo *actual = *nodoInicio;
    Nodo *siguiente;

    while (actual != nullptr){
        siguiente = actual->siguiente;
        delete(actual);
        actual = siguiente;
    }
    *nodoInicio = nullptr;
}

int contarOcurrencias(){
    cout << "Dato de referencia: ";
    T ref = solicitarDato();
    Nodo *actual = pInicio;
    int contador = 0;

    while(actual != nullptr){
        if(comparar(actual->dato, ref)) contador++;
        actual = actual->siguiente;
    }
    return contador;
}

T acceder(){
    int indice = 0;
    cout << "Indice a acceder: ";
    cin >> indice; cin.ignore();

    if(indice>=0 && indice<cantidadDatos()){
        Nodo *unNodo = pInicio;
        for(int i = 0; i < indice; i++) unNodo = unNodo->siguiente;
        mostrarDato(unNodo->dato);
        return unNodo->dato;
    }
    else{
        cout << "\nError, indice no validoºn";
        return noValido;
    }
}