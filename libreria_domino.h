//estructura de datos para las fichas
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

//estructura de datos para el pozo (boneyard)
struct Pozo{
    Piedra* piedras;
    int num_piedras;
};
