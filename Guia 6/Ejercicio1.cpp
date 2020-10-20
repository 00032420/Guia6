#include <iostream>
#include <string>
#include <utility>
#include "utilidades.hpp"
using namespace std;

struct persona{
    int carnet{};
    string nombre;
    string apellido;
    int edad{};
    int telefono{};
    string email;
};

typedef struct persona Persona;
typedef Persona T;
const T noValido = {-1, {""}, {""}, -1, -1, {""}};

struct Nodo{
    T dato;
    struct Nodo *siguiente{};
};

typedef struct Nodo *Lista;


T solicitarDato(){
    Persona unaPersona;
    cout << "Introduzca los siguientes datos:\n";

    cout << "Carnet: ";
    int c = validarEntero(to_string(c));
    unaPersona.carnet = c;
    cin.ignore();

    cout << "Nombre: ";
    unaPersona.nombre = validarString();

    cout << "Apellido: ";
    string a = validarString();
    unaPersona.apellido = a;

    cout << "Edad: ";
    int e = validarNatural(to_string(e));
    unaPersona.edad = e;
    cin.ignore();

    cout << "Numero de telefono: ";
    int t = validarEntero(to_string(t));
    unaPersona.telefono = t;
    cin.ignore();

    cout << "Correo electronico: ";
    string email = validarString();
    unaPersona.email = email;

    return unaPersona;
}

bool comparar(T a, T b);

bool compararCarnet(const T& a, const int& carnet){
    return (a.carnet == carnet);
}

void mostrarDato(const T& dato){
    cout << endl << dato.nombre << " " << dato.apellido << ": " << endl;
    cout << "\tCarnet : " << dato.carnet << endl;
    cout << "\tEdad: " << dato.edad << endl;
    cout << "\tTelefono: " << dato.telefono << endl;
    cout << "\tCorreo Electronico: " << dato.email << endl;
}


//Prototopos de funciones de la lista

void init(Lista*);
bool empty(Lista*);
int cantidadDatos(Nodo*);
void insertarInicio(T, Lista*);
void insertarFinal(T, Lista*);
void insertarDespuesDe(T, Lista*);
void insertarAntesDe(T, Lista*);
void agregar(Lista*);
void mostrar(Lista*);
void eliminar(Lista*);
void buscar(Lista*);
void invertir(Lista*);
void vaciar(Lista**);
int contarOcurrencias(Lista**);
T acceder(Lista**);

int main(){
    Lista unaLista;
    cout << "Inicializando";
    init(&unaLista);
    cout << empty(&unaLista) << endl;
    agregar(&unaLista);
    agregar(&unaLista);
    agregar(&unaLista);
    mostrar(&unaLista);
    invertir(&unaLista);
    mostrar(&unaLista);
    return 0;
}

void init(Lista *lista){
    *lista = nullptr;
}

bool empty(Lista *lista){
    return *lista == nullptr;
}

int cantidadDatos(Lista *lista){
    Nodo *unNodo = *lista;
    int contador = 0;
    while(unNodo != nullptr){
        unNodo = unNodo->siguiente;
        contador++;
    }
    return contador;
}

void insertarInicio(T dato, Lista *inicioLista){
    Nodo *nuevo = new Nodo;
    nuevo->dato = move(dato);
    nuevo->siguiente = *inicioLista;

    *inicioLista = nuevo;
}

void insertarFinal(T dato, Lista *inicioLista){
    Nodo *nuevo = new Nodo;
    nuevo->dato = move(dato);
    nuevo->siguiente = nullptr;

    if(inicioLista == nullptr) *inicioLista = nuevo;
    else{
        Nodo *unNodo = *inicioLista;
        Nodo *aux = nullptr;
        while(unNodo!= nullptr){
            aux = unNodo;
            unNodo = unNodo->siguiente;
        }
        aux->siguiente = nuevo;
    }
}

void insertarDespuesDe(T dato, Lista *inicioLista){
    cout << "Dato de referencia: ";
    int c;
    cin >> c;
    Nodo *unNodo = *inicioLista;
    while(unNodo != nullptr && !compararCarnet(unNodo->dato, c)) unNodo = unNodo->siguiente;
    if(unNodo == nullptr){
        cout << "\nDato de referencia no existe\n";
        return;
    }

    Nodo *nuevo = new Nodo;
    nuevo->dato = move(dato);
    nuevo->siguiente = unNodo->siguiente;

    unNodo->siguiente = nuevo;
    cout << "\nDato insertado con exito" << endl;
}

void insertarAntesDe(T dato, Lista *inicioLista){
    cout << "Dato de referencia: ";
    int c;
    cin >> c;
    Nodo *unNodo = *inicioLista, *aux = nullptr;

    while(unNodo != nullptr && !compararCarnet(unNodo->dato, c)){
        aux = unNodo;
        unNodo = unNodo->siguiente;
    }
    if(unNodo == nullptr){
        cout << endl << "Dato de referencia no existe" << endl;
        return;
    }

    Nodo *nuevo = new Nodo;
    nuevo->dato = move(dato);
    nuevo->siguiente = unNodo;

    if(aux == nullptr) *inicioLista = nuevo;
    else{
        aux->siguiente = nuevo;
        cout << endl << "Dato insertado con exito" << endl;

    }

}

void agregar(Lista *unaLista){
    T unDato = solicitarDato();
    bool continuar = true;
    do{
        cout << endl << "1] Al principio" << endl;
        cout << "2] Al final" << endl;
        cout << "3] Despues de" << endl;
        cout << "4] Antes de" << endl;
        cout << endl << "Digite su opcion:";
        int opcion = validarRango(to_string(opcion), 1, 4);

        switch(opcion){
            case 1:insertarInicio(unDato, unaLista);
                continuar = false;
                break;

            case 2: insertarFinal(unDato, unaLista);
                continuar = false;
                break;

            case 3: insertarDespuesDe(unDato, unaLista);
                continuar = false;
                break;

            case 4: insertarAntesDe(unDato, unaLista);
                continuar = false;
                break;

            default: cout << endl << "Opcion invalida" << endl;
        }
    }while(continuar);
}

void mostrar(Lista *inicioLista){
    Nodo *unNodo = *inicioLista;
    while(unNodo != nullptr){
        mostrarDato(unNodo->dato);
        unNodo = unNodo->siguiente;
    }
}

void eliminar(Lista *inicioLista){
    cout << endl << "Dato a eliminar: ";
    T ref = solicitarDato();

    Nodo *unNodo = *inicioLista, *aux = nullptr;

    while(unNodo != nullptr &&  !comparar(unNodo->dato, ref)){
        aux = unNodo;
        unNodo = unNodo->siguiente;
    }

    if(unNodo == nullptr){
        cout << endl << "Dato a borrar no existe." << endl;
        return;
    }

    if(aux == nullptr) *inicioLista = unNodo->siguiente;
    else aux->siguiente = unNodo->siguiente;
    delete(unNodo);
    cout << endl << "Dato borrado" << endl;

}

void buscar(Lista *inicioLista){
    cout << endl << "Dato a buscar: ";
    T ref = solicitarDato();

    Nodo *unNodo = *inicioLista;

    while(unNodo != nullptr && !comparar(unNodo->dato, ref)) unNodo = unNodo->siguiente;

    if(unNodo != nullptr){
        cout << endl << "El dato si se encuentra" << endl;
        mostrarDato(unNodo->dato);
    } else{
        cout << endl << "El dato no se encuentra" << endl;
    }
}

void invertir(Lista* nodoInicio){
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

    cout << endl << "Lista invertida con exito" << endl;
}



bool comparar(T a,T b) {
    return (a.carnet == b.carnet) &&
           (a.email == b.email) &&
           (a.telefono == b.telefono) &&
           (a.edad == b.edad) &&
           (a.apellido == b.apellido) &&
           (a.nombre == b.nombre);
}



