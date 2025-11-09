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