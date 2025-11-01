//estructura de datos para las fichas (pila)
struct Piedra{
    int valor1;
    int valor2;
    bool fueUsada;
};

//estructura de datos para los jugadores (lista ciclica)
struct Jugador{
    int num_piedras;
    Piedra* mano;
    Jugador* sigJugador;
};

//estructura de datos para la mesa (lista ciclica doblemente enlazada)
struct Mesa{
    Piedra piece;
    Mesa* sigFicha;
    Mesa* antFicha;
};

//estructura de datos para el pozo (pila)
struct Pozo{
    Piedra* piedras;
    int num_piedras;
};

//primitivas de la libreria
//inicializar el pozo al inicio de una partida
void inicializarPozo(Pozo* boneyard){
    
}

//inicializar la mesa al inicio de una partida
void inicializarMesa(Mesa** inicioMesa){

}

//inicializar los jugadores
void inicializarJugadores(Jugador** players, int num_jugadores){

}

//repartir las piedras entre los jugadores al inicio de una partida
void repartirPiedras(Jugador** player, Piedra piece){
    
}

//buscar la piedra mas alta en la mano de un jugador
Jugador* buscarPiedraMasAlta(Jugador* player){
    return nullptr;
}

//agarrar una piedra del pozo cuando un jugador no puede jugar
void agarrarPiedraDelPozo(Pozo* boneyard, Jugador* player){
    
}

//verificar si una piedra se puede jugar
bool jugadaValida(Mesa* table, Piedra piece){
    return false;
}

//recorre todas las piedras de un jugador para saber si puede jugar una ficha
bool puedeJugar(Jugador* player, Mesa* table){
    return false;
}

//saltarse un turno en caso de que no se pueda jugar nada
void pasarTurno(Jugador** currentPlayer){

}

//buscar y jugar una piedra de la mano del jugador
Piedra* jugarPiedra(Jugador* player, Piedra piece){
    return nullptr;
}

//colocar la piedra jugada en la mesa
void colocarPiedraEnMesa(Mesa** inicioMesa, Mesa** finMesa, Piedra piece){
    
}

//contar los puntos en la mano de un jugador
int contarPuntosEnMano(Jugador* player){
    return 0;
}

Jugador* determinarGanador(Jugador* players, int num_jugadores){
    return nullptr;
}

//sumar puntos al jugador que gana la ronda
int sumarPuntos(Jugador* player, int puntos){
    return 0;   
}

//saber si ya el juego termino
bool juegoTerminado(Jugador* players, Pozo* boneyard){
    return false;
}
