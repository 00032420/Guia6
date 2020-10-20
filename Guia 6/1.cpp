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

T solicitarDato(){
    Persona unaPersona;
    cout << "Introduzca los siguientes datos:\n";

    cout << "Carnet: ";
    int c = validarEntero(to_string(c));
    unaPersona.carnet = c;

    cout << "Nombre: ";
    string n = validarString();
    unaPersona.nombre = n;

    cout << "Apellido: ";
    string a = validarString();
    unaPersona.apellido = a;

    cout << "Edad: ";
    int e = validarNatural(to_string(e));
    unaPersona.edad = e;

    cout << "Numero de telefono: ";
    int t = validarEntero(to_string(t));
    unaPersona.telefono = t;

    cout << "Correo electronico: ";
    string email = validarString();
    unaPersona.email = email;

    return unaPersona;
}

bool comparar(const T& a, const T& b){
    return (a.carnet == b.carnet) &&
            (a.email == b.email) &&
            (a.telefono == b.telefono) &&
            (a.edad == b.edad) &&
            (a.apellido == b.apellido) &&
            (a.nombre == b.nombre);
}

void mostrarDato(const T& dato){
    cout << endl << dato.nombre << " " << dato.apellido << ": " << endl;
    cout << "\tCarnet : " << dato.carnet << endl;
    cout << "\tEdad: " << dato.edad << endl;
    cout << "\tTelefono: " << dato.telefono << endl;
    cout << "\tCorreo Electronico: " << dato.email << endl;
}


//Prototopos de funciones de la lista

void init(Nodo *lista);
bool empty(Nodo*);
int cantidadDatos(Nodo*);
void insertarInicio(T);
void insertarFinal(T);
void insertarDespuesDe(T);
void insertarAntesDe(T);
void agregar();
void mostrar(Nodo*);
void eliminar(Nodo*);
void buscar(Nodo*);
void invertir(Nodo**);
void vaciar(Nodo**);
int contarOcurrencias(Nodo**);
T acceder(Nodo**);


int main(){
    Nodo lista;

    cout << "Inicializando";
    return 0;
}

void init(Nodo *lista){
    *lista = NULL;
}

bool empty(Nodo *lista){
    return lista == nullptr;
}

int cantidadDatos(Nodo *inicio){
    Nodo *unNodo = inicio;

    int contador = 0;
    while(unNodo != nullptr){
        unNodo = unNodo->siguiente;
        contador++;
    }
    cout << "\nHay un total de " << contador << " datos.ºn";
    return contador;
}

void * insertarInicio(T dato, Nodo* inicioLista){
    Nodo *nuevo = new Nodo;
    nuevo->dato = dato;
    nuevo->siguiente = inicioLista;
    inicioLista = nuevo;
}

void insertarFinal(T dato, Nodo* inicioLista){
    Nodo *nuevo = new Nodo;
    nuevo->dato = dato;
    nuevo->siguiente = nullptr;

    if(inicioLista == nullptr) inicioLista = nuevo;
    else{
        Nodo *unNodo = inicioLista;
        Nodo *aux = nullptr;
        while(unNodo != nullptr){
            aux = unNodo;
            unNodo = unNodo->siguiente;
        }
        aux->siguiente = nuevo;
    }

}

void insertarDespuesDe(T dato, Nodo* inicioLista){
    cout << "Dato de referencia: ";
    T ref = solicitarDato();

    Nodo *unNodo = inicioLista;

    while (unNodo != nullptr && !comparar(unNodo->dato, ref))
        unNodo = unNodo->siguiente;
    if(unNodo == nullptr){
        cout << "\nEl dato de referencia no existe.\n";
        return;
    }

    Nodo *nuevo = new Nodo;
    nuevo->dato = dato;
    nuevo->siguiente = unNodo->siguiente;
    unNodo->siguiente = nuevo;
    cout << "\nDato insertado con exito" << endl;
}

void insertarAntesDe(T dato, Nodo* inicioLista){
    cout << "\nDato de referencia: ";
    T ref = solicitarDato();

    Nodo *unNodo = inicioLista, *aux = nullptr;

    while(unNodo != nullptr && !comparar(unNodo->dato, ref)){
        aux = unNodo;
        unNodo = unNodo->siguiente;
    }
    if(unNodo == nullptr){
        cout << "\nDato de referencia no existe" << endl;
        return;
    }

    Nodo *nuevo = new Nodo;
    nuevo->dato = dato;
    nuevo->siguiente = unNodo;

    if(aux == nullptr) inicioLista = nuevo;
    else aux->siguiente = nuevo;

    cout << "\nDato insertado con exito\n";
}


void agregar(Nodo *inicio){
    T unaPersona = solicitarDato();
    bool continuar = true;
    do{
        cout << "\n1] Al principio\n";
        cout << "2] Al final\n";
        cout << "3] Despues de\n";
        cout << "4] Antes de\n";
        cout << "\nDigite su opcion: ";
        int opcion = validarRango(to_string(opcion),1, 4);
        switch(opcion){
            case 1: insertarInicio(unaPersona); continuar = false; break;
            case 2: insertarFinal(unaPersona); continuar = false; break;
            case 3: insertarDespuesDe(unaPersona); continuar = false; break;
            case 4: insertarAntesDe(unaPersona); continuar = false; break;
            default: cout << "\nOpcion invalida\n"; break;
        }
    }while(continuar);
}

