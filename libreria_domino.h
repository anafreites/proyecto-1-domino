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

//funciones relacionadas con la logica de las manos de los jugadores
void agregarPiedraAMano(Jugador* player, Piedra piece) {
    NodoPiedra* nuevoNodo = new NodoPiedra;
    nuevoNodo->ficha = piece;
    nuevoNodo->siguiente = player->mano;
    player->mano = nuevoNodo;
    player->num_piedras++;
}

Piedra jugarPiedra(Jugador* player, Piedra piece) {
    NodoPiedra* actual = player->mano;
    NodoPiedra* anterior = nullptr;
    while (actual != nullptr) {
        if ((actual->ficha.valor1 == piece.valor1 && actual->ficha.valor2 == piece.valor2) || 
            (actual->ficha.valor1 == piece.valor2 && actual->ficha.valor2 == piece.valor1)) {
            
            Piedra fichaJugada = actual->ficha;
            
            if (anterior == nullptr) {
                player->mano = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            
            delete actual;
            player->num_piedras--;
            return fichaJugada;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return {-1, -1, false};
}

void agarrarPiedraDelPozo(Pozo* boneyard, Jugador* player) {
    if (boneyard->num_piedras > 0) {
        Piedra fichaTomada = sacarPiedraDelPozo(boneyard);
        if (fichaTomada.valor1 != -1) {
             agregarPiedraAMano(player, fichaTomada);
             cout << "  > Jugador " << player->id << " toma la ficha y tiene " << player->num_piedras << " fichas." << endl;
        }
    }
}

void repartirPiedras(Jugador* primerJugador, int num_jugadores, Pozo* boneyard) {
    llenarPozo(boneyard);
    Jugador* actual = primerJugador;
    for (int ronda = 0; ronda < 7; ++ronda) { 
        for (int i = 0; i < num_jugadores; ++i) {
            if (boneyard->num_piedras > 0) {
                Piedra ficha = sacarPiedraDelPozo(boneyard);
                agregarPiedraAMano(actual, ficha);
            }
            actual = actual->sigJugador;
        }
    }
    cout << "  > Reparto completado. Cada jugador tiene 7 fichas." << endl;
    cout << "  > El pozo tiene " << boneyard->num_piedras << " fichas restantes." << endl;
}

//logica del juego
int jugadaValida(NodoMesa* inicioMesaPtr, NodoMesa* finMesaPtr, Piedra piece) {
    if (inicioMesaPtr == nullptr) return 1;

    int valor_extremo1 = inicioMesaPtr->piece.valor1;
    int valor_extremo2 = finMesaPtr->piece.valor2;
    
    int validez = 0;
    if (piece.valor1 == valor_extremo1 || piece.valor2 == valor_extremo1) {
        validez = 1;
    }
    if (piece.valor1 == valor_extremo2 || piece.valor2 == valor_extremo2) {
        if (validez == 1) validez = 3;
        else validez = 2; 
    }
    return validez;
}

bool puedeJugar(Jugador* player, NodoMesa* inicioMesaPtr, NodoMesa* finMesaPtr) {
    NodoPiedra* actual = player->mano;
    while (actual != nullptr) {
        if (jugadaValida(inicioMesaPtr, finMesaPtr, actual->ficha) != 0) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

Jugador* buscarPiedraMasAlta(Jugador* primerJugador, int num_jugadores, Piedra* fichaInicial) {
    Jugador* actual = primerJugador;
    Jugador* jugadorQueInicia = nullptr;
    Piedra maxPiedra = {-1, -1, false};

    for (int i = 0; i < num_jugadores; ++i) {
        NodoPiedra* nodoActual = actual->mano;
        while (nodoActual != nullptr) {
            Piedra ficha = nodoActual->ficha;
            int valorTotal = ficha.valor1 + ficha.valor2;
            bool esDoble = (ficha.valor1 == ficha.valor2);
            int maxValorTotal = maxPiedra.valor1 + maxPiedra.valor2;
            bool esMaxDoble = (maxPiedra.valor1 == maxPiedra.valor2);

            if (ficha.valor1 == 6 && ficha.valor2 == 6) {
                *fichaInicial = ficha;
                return actual;
            }

            if (esDoble && (!esMaxDoble || valorTotal > maxValorTotal)) {
                maxPiedra = ficha;
                jugadorQueInicia = actual;
            } else if (!esDoble && !esMaxDoble && valorTotal > maxValorTotal) {
                maxPiedra = ficha;
                jugadorQueInicia = actual;
            }
            nodoActual = nodoActual->siguiente;
        }
        actual = actual->sigJugador;
    }

    if (jugadorQueInicia != nullptr) {
        *fichaInicial = maxPiedra;
        return jugadorQueInicia;
    }
    return nullptr;
}

int contarPuntosEnMano(Jugador* player) {
    int puntos = 0;
    NodoPiedra* actual = player->mano;
    while (actual != nullptr) {
        puntos += actual->ficha.valor1 + actual->ficha.valor2;
        actual = actual->siguiente;
    }
    return puntos;
}

bool rondaTerminada(Jugador* primerJugador, int num_jugadores, Pozo* boneyard, int& turnosSinJugar) {
    Jugador* actual = primerJugador;
    for (int i = 0; i < num_jugadores; ++i) {
        if (actual->num_piedras == 0) {
            return true; 
        }
        actual = actual->sigJugador;
    }
    if (boneyard->num_piedras == 0 && turnosSinJugar >= num_jugadores) {
        return true;
    }
    return false;
}