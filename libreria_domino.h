#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//estructuras de datos

//fichas
struct Piedra {
    int valor1;
    int valor2;
    bool fueUsada; 
};

//nodos del pozo 
struct NodoPozo {
    Piedra ficha;
    NodoPozo* siguiente;
};

//pozo
struct Pozo {
    NodoPozo* tope;
    int num_piedras;
};

//mano del jugador
struct NodoPiedra {
    Piedra ficha;
    NodoPiedra* siguiente;
};

//jugadores
struct Jugador {
    int id;
    int puntosAcumulados;
    NodoPiedra* mano;
    int num_piedras;
    Jugador* sigJugador;
};

//mesas
struct NodoMesa {
    Piedra piece;
    NodoMesa* sigFicha; 
    NodoMesa* antFicha; 
};

//punteros para la mesa
NodoMesa* inicioMesa = nullptr;
NodoMesa* finMesa = nullptr;

//funciones auxiliares
//intercambio de fichas
void swapPiedra(Piedra* a, Piedra* b) {
    Piedra temp = *a;
    *a = *b;
    *b = temp;
}

//mostrar ficha
void mostrarPiedra(Piedra p) {
    if (p.valor1 == -1) {
        cout << "(VACIO)";
    } else {
        cout << "[" << p.valor1 << "|" << p.valor2 << "]";
    }
}