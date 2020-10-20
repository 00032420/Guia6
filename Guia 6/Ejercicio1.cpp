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

void init(Lista*);
bool empty(Lista*);
int cantidadDatos(Nodo*);
void insertarInicio(T, Lista*);
void insertarFinal(T, Lista*);
void insertarDespuesDe(T);
void insertarAntesDe(T);
void agregar();
void mostrar(Lista*);
void eliminar(Nodo*);
void buscar(Nodo*);
void invertir(Nodo**);
void vaciar(Nodo**);
int contarOcurrencias(Nodo**);
T acceder(Nodo**);


int main(){
    Lista unaLista;
    cout << "Inicializando";
    init(&unaLista);
    cout << empty(&unaLista) << endl;
    T dato = solicitarDato();
    insertarInicio(dato, &unaLista);
    mostrar(&unaLista);
    T dato2 = solicitarDato();
    insertarFinal(dato2, &unaLista);
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

void mostrar(Lista *inicioLista){
    Nodo *unNodo = *inicioLista;
    while(unNodo != nullptr){
        mostrarDato(unNodo->dato);
        unNodo = unNodo->siguiente;
    }
}

