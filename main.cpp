int main() {
    int numjugadores = 2;
    Pozo boneyard;
    inicializarPozo(&boneyard);

    // Inicializar jugadores
    Jugador* primerJugador = inicializarJugadores(num_jugadores);
    if (!primerJugador) {
        cout << "Número de jugadores inválido." << endl;
        return 1;
    }

    // Repartir fichas
    repartirPiedras(primerJugador, numjugadores, &boneyard);

    // Inicializar mesa
    inicializarMesa(&inicioMesa, &finMesa);

    // Buscar piedra más alta para iniciar
    Piedra fichaInicial;
    Jugador* jugadorInicial = buscarPiedraMasAlta(primerJugador, numjugadores, &fichaInicial);
    if (jugadorInicial) {
        cout << "Jugador " << jugadorInicial->id << " inicia con ";
        mostrarPiedra(fichaInicial);
        cout << endl;

        Piedra jugada = jugarPiedra(jugadorInicial, fichaInicial);
        colocarPrimeraPiedra(&inicioMesa, &finMesa, jugada);
    }

    // Simulación de turnos
    Jugador* jugadorActual = jugadorInicial;
    int turnosSinJugar = 0;

    while (!rondaTerminada(primerJugador, num_jugadores, &boneyard, turnosSinJugar)) {
        cout << "\nTurno del jugador " << jugadorActual->id << endl;

        if (puedeJugar(jugadorActual, inicioMesa, finMesa)) {
            NodoPiedra* nodo = jugadorActual->mano;
            while (nodo != nullptr) {
                int validez = jugadaValida(inicioMesa, finMesa, nodo->ficha);
                if (validez != 0) {
                    Piedra jugada = jugarPiedra(jugadorActual, nodo->ficha);
                    if (validez == 1) {
                        colocarPiedraEnMesa(&inicioMesa, &finMesa, jugada, false, inicioMesa->piece.valor1);
                    } else if (validez == 2) {
                        colocarPiedraEnMesa(&inicioMesa, &finMesa, jugada, true, finMesa->piece.valor2);
                    } else {
                        // Puede ir en ambos extremos, elegimos uno
                        colocarPiedraEnMesa(&inicioMesa, &finMesa, jugada, true, finMesa->piece.valor2);
                    }
                    cout << "  > Jugador " << jugadorActual->id << " juega ";
                    mostrarPiedra(jugada);
                    cout << endl;
                    break;
                }
                nodo = nodo->siguiente;
            }
            turnosSinJugar = 0;
        } else {
            agarrarPiedraDelPozo(&boneyard, jugadorActual);
            turnosSinJugar++;
        }

        pasarTurno(&jugadorActual);
    }

    // Mostrar puntos finales
    cout << "\n Fin de la ronda " << endl;
    Jugador* temp = primerJugador;
    for (int i = 0; i < num_jugadores; ++i) {
        int puntos = contarPuntosEnMano(temp);
        cout << "Jugador " << temp->id << " tiene " << puntos << " puntos en mano." << endl;
        temp = temp->sigJugador;
    }

    return 0;
}
