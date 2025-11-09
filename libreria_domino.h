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

//lfunciones del pozo
void inicializarPozo(Pozo* boneyard) {
    boneyard->tope = nullptr;
    boneyard->num_piedras = 0;
}

void insertarEnPozo(Pozo* boneyard, Piedra piece) {
    NodoPozo* nuevoNodo = new NodoPozo;
    nuevoNodo->ficha = piece;
    nuevoNodo->siguiente = boneyard->tope;
    boneyard->tope = nuevoNodo;
    boneyard->num_piedras++;
}

Piedra sacarPiedraDelPozo(Pozo* boneyard) {
    if (boneyard->tope == nullptr) {
        return { -1, -1, false };
    }
    NodoPozo* nodoATomar = boneyard->tope;
    Piedra fichaTomada = nodoATomar->ficha;
    boneyard->tope = boneyard->tope->siguiente;
    boneyard->num_piedras--;
    delete nodoATomar;
    return fichaTomada;
}

void llenarPozo(Pozo* boneyard) {
    Piedra todasLasFichas[28];
    int k = 0;
    for (int i = 0; i <= 6; ++i) {
        for (int j = i; j <= 6; ++j) {
            todasLasFichas[k++] = {i, j, false};
        }
    }
    srand(time(0)); 
    for (int i = 0; i < 28; ++i) {
        int rand_index = rand() % (28 - i) + i;
        swapPiedra(&todasLasFichas[i], &todasLasFichas[rand_index]);
    }
    for (int i = 0; i < 28; ++i) {
        insertarEnPozo(boneyard, todasLasFichas[i]);
    }
}

//funciones de la mesa
void inicializarMesa(NodoMesa** inicioMesaPtr, NodoMesa** finMesaPtr) {
    *inicioMesaPtr = nullptr;
    *finMesaPtr = nullptr;
}

void colocarPrimeraPiedra(NodoMesa** inicioMesaPtr, NodoMesa** finMesaPtr, Piedra piece) {
    NodoMesa* nuevoNodo = new NodoMesa;
    nuevoNodo->piece = piece;
    nuevoNodo->sigFicha = nullptr;
    nuevoNodo->antFicha = nullptr;
    *inicioMesaPtr = nuevoNodo;
    *finMesaPtr = nuevoNodo;
}

void colocarPiedraEnMesa(NodoMesa** inicioMesaPtr, NodoMesa** finMesaPtr, Piedra piece, bool alFinal, int valorConectado) {
    if (*inicioMesaPtr == nullptr) {
        colocarPrimeraPiedra(inicioMesaPtr, finMesaPtr, piece);
        return;
    }
    NodoMesa* nuevoNodo = new NodoMesa;
    nuevoNodo->piece = piece;
    nuevoNodo->sigFicha = nullptr;
    nuevoNodo->antFicha = nullptr;

    if (alFinal) {
        if (nuevoNodo->piece.valor1 != valorConectado) {
            swapPiedra(&nuevoNodo->piece, &nuevoNodo->piece);
        }
        (*finMesaPtr)->sigFicha = nuevoNodo;
        nuevoNodo->antFicha = *finMesaPtr;
        *finMesaPtr = nuevoNodo;
    } else { 
        if (nuevoNodo->piece.valor2 != valorConectado) {
            swapPiedra(&nuevoNodo->piece, &nuevoNodo->piece);
        }
        (*inicioMesaPtr)->antFicha = nuevoNodo;
        nuevoNodo->sigFicha = *inicioMesaPtr;
        *inicioMesaPtr = nuevoNodo;
    }
}

//funciones de los jugadores
Jugador* inicializarJugadores(int num_jugadores) {
    if (num_jugadores < 2 || num_jugadores > 4) return nullptr;
    Jugador* primerJugador = nullptr;
    Jugador* ultimoJugador = nullptr;
    for (int i = 1; i <= num_jugadores; ++i) {
        Jugador* nuevoJugador = new Jugador;
        nuevoJugador->id = i;
        nuevoJugador->puntosAcumulados = 0;
        nuevoJugador->mano = nullptr;
        nuevoJugador->num_piedras = 0;
        
        if (primerJugador == nullptr) {
            primerJugador = nuevoJugador;
        } else {
            ultimoJugador->sigJugador = nuevoJugador;
        }
        ultimoJugador = nuevoJugador;
    }
    if (ultimoJugador != nullptr) {
        ultimoJugador->sigJugador = primerJugador; // Cerrar el ciclo
    }
    return primerJugador;
}

void pasarTurno(Jugador** currentPlayer) {
    if (*currentPlayer != nullptr) {
        *currentPlayer = (*currentPlayer)->sigJugador;
    }
}