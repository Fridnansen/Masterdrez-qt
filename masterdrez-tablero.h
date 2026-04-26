#ifndef MASTERDREZTABLERO
#define MASTERDREZTABLERO

/**
    * Actualiza el tablero t segunlo datos de las listas de pieas b,n,r,a
    *
   * @param b Vector de piezas blancas
    * @param n Vector de piezas negras
    * @param r Vector de piezas rojas
    * @param a Vector de piezas amarillas
    * @param t Matriz que representa el tablero
    */
void actualizarTablero(pieza b[16], pieza n[16], pieza r[16], pieza a[16],
                       pieza t[16][16]) {

  for (int i = 0; i < 16; i++) {
    if ((b[i].x >= 0) && (b[i].x < 16) && (b[i].y >= 0) && (b[i].y < 16)) {
      t[b[i].x][b[i].y].tipo = b[i].tipo;
      t[b[i].x][b[i].y].x = b[i].x;
      t[b[i].x][b[i].y].y = b[i].y;
      t[b[i].x][b[i].y].color = b[i].color;
    }
    if ((n[i].x >= 0) && (n[i].x < 16) && (n[i].y >= 0) && (n[i].y < 16)) {
      t[n[i].x][n[i].y].tipo = n[i].tipo;
      t[n[i].x][n[i].y].x = n[i].x;
      t[n[i].x][n[i].y].y = n[i].y;
      t[n[i].x][n[i].y].color = n[i].color;
    }
    if ((r[i].x >= 0) && (r[i].x < 16) && (r[i].y >= 0) && (r[i].y < 16)) {
      t[r[i].x][r[i].y].tipo = r[i].tipo;
      t[r[i].x][r[i].y].x = r[i].x;
      t[r[i].x][r[i].y].y = r[i].y;
      t[r[i].x][r[i].y].color = r[i].color;
    }
    if ((a[i].x >= 0) && (a[i].x < 16) && (a[i].y >= 0) && (a[i].y < 16)) {
      t[a[i].x][a[i].y].tipo = a[i].tipo;
      t[a[i].x][a[i].y].x = a[i].x;
      t[a[i].x][a[i].y].y = a[i].y;
      t[a[i].x][a[i].y].color = a[i].color;
    }
  }
}

/**
    * Pone las piezas en sus posiciones iniciales para comenzar la partida.
    *
    */
void inicializarTablero() {
  int i, j;
  for (i = 0; i < 16; i++) {
    for (j = 0; j < 16; j++) {
      tablero[i][j].tipo = -1;
      tablero[i][j].color = -1;
    }
  }

  // Peones:
  for (i = 8; i < 16; i++) {
    negras[i].tipo = blancas[i].tipo = rojas[i].tipo = amarillas[i].tipo = PEON;
    negras[i].x = blancas[i].x = i - 4;
    rojas[i].x = 14;
    amarillas[i].x = 1;

    rojas[i].y = amarillas[i].y = i - 4;
    negras[i].y = 14;
    blancas[i].y = 1;
  }

  blancas[0].tipo = TORRE;
  blancas[0].x = 4; // 4;
  blancas[0].y = 0; // 0;
  blancas[1].tipo = CABALLO;
  blancas[1].x = 5;
  blancas[1].y = 0;
  blancas[2].tipo = ALFIL;
  blancas[2].x = 6;
  blancas[2].y = 0;
  blancas[3].tipo = DAMA;
  blancas[3].x = 7;
  blancas[3].y = 0;
  blancas[4].tipo = REY;
  blancas[4].x = 8;
  blancas[4].y = 0;
  blancas[5].tipo = ALFIL;
  blancas[5].x = 9;
  blancas[5].y = 0;
  blancas[6].tipo = CABALLO;
  blancas[6].x = 10;
  blancas[6].y = 0;
  blancas[7].tipo = TORRE;
  blancas[7].x = 11;
  blancas[7].y = 0;

  negras[0].tipo = TORRE;
  negras[0].x = 4;
  negras[0].y = 15;
  negras[1].tipo = CABALLO;
  negras[1].x = 5;
  negras[1].y = 15;
  negras[2].tipo = ALFIL;
  negras[2].x = 6;
  negras[2].y = 15;
  negras[3].tipo = REY;
  negras[3].x = 7;
  negras[3].y = 15;
  negras[4].tipo = DAMA;
  negras[4].x = 8;
  negras[4].y = 15;
  negras[5].tipo = ALFIL;
  negras[5].x = 9;
  negras[5].y = 15;
  negras[6].tipo = CABALLO;
  negras[6].x = 10;
  negras[6].y = 15;
  negras[7].tipo = TORRE;
  negras[7].x = 11;
  negras[7].y = 15;

  rojas[0].tipo = TORRE;
  rojas[0].y = 4;
  rojas[0].x = 15;
  rojas[1].tipo = CABALLO;
  rojas[1].y = 5;
  rojas[1].x = 15;
  rojas[2].tipo = ALFIL;
  rojas[2].y = 6;
  rojas[2].x = 15;
  rojas[3].tipo = REY;
  rojas[3].y = 7;
  rojas[3].x = 15;
  rojas[4].tipo = DAMA;
  rojas[4].y = 8;
  rojas[4].x = 15;
  rojas[5].tipo = ALFIL;
  rojas[5].y = 9;
  rojas[5].x = 15;
  rojas[6].tipo = CABALLO;
  rojas[6].y = 10;
  rojas[6].x = 15;
  rojas[7].tipo = TORRE;
  rojas[7].y = 11;
  rojas[7].x = 15;

  amarillas[0].tipo = TORRE;
  amarillas[0].y = 4;
  amarillas[0].x = 0;
  amarillas[1].tipo = CABALLO;
  amarillas[1].y = 5;
  amarillas[1].x = 0;
  amarillas[2].tipo = ALFIL;
  amarillas[2].y = 6;
  amarillas[2].x = 0;
  amarillas[3].tipo = DAMA;
  amarillas[3].y = 7;
  amarillas[3].x = 0;
  amarillas[4].tipo = REY;
  amarillas[4].y = 8;
  amarillas[4].x = 0;
  amarillas[5].tipo = ALFIL;
  amarillas[5].y = 9;
  amarillas[5].x = 0;
  amarillas[6].tipo = CABALLO;
  amarillas[6].y = 10;
  amarillas[6].x = 0;
  amarillas[7].tipo = TORRE;
  amarillas[7].y = 11;
  amarillas[7].x = 0;

  coronables[0].tipo = DAMA;
  coronables[0].y = -1;
  coronables[0].x = -1;
  coronables[0].color = -1;
  coronables[1].tipo = ALFIL;
  coronables[1].y = -1;
  coronables[1].x = -1;
  coronables[1].color = -1;
  coronables[2].tipo = CABALLO;
  coronables[2].y = -1;
  coronables[2].x = -1;
  coronables[2].color = -1;
  coronables[3].tipo = TORRE;
  coronables[3].y = -1;
  coronables[3].x = -1;
  coronables[3].color = -1;

  for (i = 0; i < 16; i++) {
    negras[i].color = NEGRO;
    blancas[i].color = BLANCO;
    rojas[i].color = ROJO;
    amarillas[i].color = AMARILLO;
  }

  actualizarTablero(blancas, negras, rojas, amarillas, tablero);
}

#endif // MASTERDREZTABLERO
