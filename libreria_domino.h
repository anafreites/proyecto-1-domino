//estructura de datos para las fichas
struct Piedra{
    int valor1;
    int valor2;
    bool fueUsada;
};

//estructura de datos para los jugadores
struct Jugador{
    int num_piedras;
    Piedra* mano;
    Jugador* sigJugador;
    Jugador* antJugador;
};