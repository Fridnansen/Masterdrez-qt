#ifndef INTELIGENCIAARTIFICIAL4X4
#define INTELIGENCIAARTIFICIAL4X4

// Coste4wc - modificación para el masterdrez.
// Divirtiendome un poco por aqui :)

// http://stackoverflow.com/questions/10372585/a-simple-chess-minimax
// Funciones de coste

int coste4wcBlancas(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == BLANCO) {
          peso += -t[i][j].tipo;
          casilla += -(t[i][j].x + t[i][j].y);
        } else {
          peso += t[i][j].tipo;
          casilla += t[i][j].x + t[i][j].y;
        }
      }
    }

  resultado = peso + casilla;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

int coste4wcAmarillas(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == AMARILLO) {
          peso += -t[i][j].tipo;
          casilla += -(t[i][j].x + t[i][j].y);
        } else {
          peso += t[i][j].tipo;
          casilla += t[i][j].x + t[i][j].y;
        }
      }
    }

  resultado = peso + casilla;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

int coste4wcNegras(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == NEGRO) {
          peso += -t[i][j].tipo;
          casilla += -(t[i][j].x + t[i][j].y);
        } else {
          peso += t[i][j].tipo;
          casilla += t[i][j].x + t[i][j].y;
        }
      }
    }

  resultado = peso + casilla;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

int coste4wcRojas(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == ROJO) {
          peso += -t[i][j].tipo;
          casilla += -(t[i][j].x + t[i][j].y);
        } else {
          peso += t[i][j].tipo;
          casilla += t[i][j].x + t[i][j].y;
        }
      }
    }

  resultado = peso + casilla;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

/**
  * Calcula costo/beneficio de un movimiento en el tablero generado
  automaticamente por la maquina mediante procedimiento MiniMax con horizonte
  a
  profundidad it  * Modifica: *p --> pieza a mover, *c --> casilla a donde
  mover.
  * @param p pieza a mover
  * @param c casilla destino
  * @param b Vector de piezas blancas
  * @param a Vector de piezas amarillas
  * @param n Vector de piezas negras
  * @param r Vector de piezas rojas
  * @param t Matriz que representa el tablero
  * @param turnoActual
  * @param it
  */

// Divirtiendome un poco por aqui :)

// Todos contra blancas
int movimientoMaquinaBlancas(int *p, int *c, pieza b[16], pieza a[16],
                             pieza n[16], pieza r[16], pieza t[16][16],
                             int turnoActual, int it) {
  int i, j, k;
  undo des[1];
  int p2, c2, costeActual;
  int mejorP, mejorC;
  int costeMejor = -10000;
  int valor = INT_MIN;

  // Variables para no perder el estado del enroque
  int enroque = 0;
  int a1[1], a2[1];
  int tBDM, tBIM, tNDM, tNIM, tVDM, tVIM, tRDM, tRIM;
  int encontrado = 0;
  tBDM = torreBDMovida;
  tBIM = torreBIMovida;
  tNDM = torreNDMovida;
  tNIM = torreNIMovida;
  tVDM = torreADMovida;
  tVIM = torreAIMovida;
  tRDM = torreRDMovida;
  tRIM = torreRIMovida;

  encontrado = 0;
  for (i = 0; i < 16; i++) {
    if ((turnoActual == 0) && (b[i].tipo > 0)) {
      p2 = b[i].x * 16 + b[i].y; // mejorPieza

      // 16x16
      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k; // mejorCasilla
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaBlancas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancas(t);
            if ((encontrado == 0) || (costeActual > costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }

            if (enroqueBlancas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueBlancas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 1) && (a[i].tipo > 0)) {
      p2 = a[i].x * 16 + a[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaBlancas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancas(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueAmarillas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueAmarillas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 2) && (n[i].tipo > 0)) {
      p2 = n[i].x * 16 + n[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaBlancas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancas(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueNegras != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueNegras = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 3) && (r[i].tipo > 0)) {
      p2 = r[i].x * 16 + r[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaBlancas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancas(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueRojas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueRojas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }
    }
  }
  valor = costeMejor;
  *p = mejorP;
  *c = mejorC;
  if (enroque == 0) // Restaurar valores en caso de no haber enroque
  {
    enroqueBlancas = -1;
    enroqueNegras = -1;
    enroqueAmarillas = -1;
    enroqueRojas = -1;
    torreBDMovida = tBDM;
    torreBIMovida = tBIM;
    torreNDMovida = tNDM;
    torreNIMovida = tNIM;
    torreADMovida = tVDM;
    torreAIMovida = tVIM;
    torreRDMovida = tRDM;
    torreRIMovida = tRIM;
  }

  return valor;
}

// Todos contra amarillas
int movimientoMaquinaAmarillas(int *p, int *c, pieza b[16], pieza a[16],
                               pieza n[16], pieza r[16], pieza t[16][16],
                               int turnoActual, int it) {
  int i, j, k;
  undo des[1];
  int p2, c2, costeActual;
  int mejorP, mejorC;
  int costeMejor = -10000;
  int valor = INT_MIN;

  // Variables para no perder el estado del enroque
  int enroque = 0;
  int a1[1], a2[1];
  int tBDM, tBIM, tNDM, tNIM, tVDM, tVIM, tRDM, tRIM;
  int encontrado = 0;
  tBDM = torreBDMovida;
  tBIM = torreBIMovida;
  tNDM = torreNDMovida;
  tNIM = torreNIMovida;
  tVDM = torreADMovida;
  tVIM = torreAIMovida;
  tRDM = torreRDMovida;
  tRIM = torreRIMovida;

  encontrado = 0;
  for (i = 0; i < 16; i++) {
    if ((turnoActual == 1) && (a[i].tipo > 0)) {
      p2 = a[i].x * 16 + a[i].y; // mejorPiezaAmarilla

      // 16x16
      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k; // mejorCasilla
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaAmarillas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcAmarillas(t);
            if ((encontrado == 0) || (costeActual > costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }

            if (enroqueAmarillas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueAmarillas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 2) && (n[i].tipo > 0)) {
      p2 = n[i].x * 16 + n[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaAmarillas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcAmarillas(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueNegras != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueNegras = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 3) && (r[i].tipo > 0)) {
      p2 = r[i].x * 16 + r[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaAmarillas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcAmarillas(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueRojas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueRojas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 0) && (b[i].tipo > 0)) {
      p2 = b[i].x * 16 + b[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaAmarillas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcAmarillas(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueBlancas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueBlancas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }
    }
  }

  valor = costeMejor;
  *p = mejorP;
  *c = mejorC;
  if (enroque == 0) // Restaurar valores en caso de no haber enroque
  {
    enroqueBlancas = -1;
    enroqueNegras = -1;
    enroqueAmarillas = -1;
    enroqueRojas = -1;
    torreBDMovida = tBDM;
    torreBIMovida = tBIM;
    torreNDMovida = tNDM;
    torreNIMovida = tNIM;
    torreADMovida = tVDM;
    torreAIMovida = tVIM;
    torreRDMovida = tRDM;
    torreRIMovida = tRIM;
  }

  return valor;
}

// Todos contra negras
int movimientoMaquinaNegras(int *p, int *c, pieza b[16], pieza a[16],
                            pieza n[16], pieza r[16], pieza t[16][16],
                            int turnoActual, int it) {
  int i, j, k;
  undo des[1];
  int p2, c2, costeActual;
  int mejorP, mejorC;
  int costeMejor = -10000;
  int valor = INT_MIN;

  // Variables para no perder el estado del enroque
  int enroque = 0;
  int a1[1], a2[1];
  int tBDM, tBIM, tNDM, tNIM, tVDM, tVIM, tRDM, tRIM;
  int encontrado = 0;
  tBDM = torreBDMovida;
  tBIM = torreBIMovida;
  tNDM = torreNDMovida;
  tNIM = torreNIMovida;
  tVDM = torreADMovida;
  tVIM = torreAIMovida;
  tRDM = torreRDMovida;
  tRIM = torreRIMovida;

  encontrado = 0;
  for (i = 0; i < 16; i++) {
    if ((turnoActual == 2) && (n[i].tipo > 0)) {
      p2 = n[i].x * 16 + n[i].y; // mejorPiezaNegras

      // 16x16
      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k; // mejorCasilla
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaNegras(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcNegras(t);
            if ((encontrado == 0) || (costeActual > costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }

            if (enroqueNegras != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueNegras = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 3) && (r[i].tipo > 0)) {
      p2 = r[i].x * 16 + r[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaNegras(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcNegras(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueRojas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueRojas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 0) && (b[i].tipo > 0)) {
      p2 = b[i].x * 16 + b[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaNegras(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcNegras(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueBlancas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueBlancas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 1) && (a[i].tipo > 0)) {
      p2 = a[i].x * 16 + a[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaNegras(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcNegras(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueAmarillas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueAmarillas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }
    }
  }

  valor = costeMejor;
  *p = mejorP;
  *c = mejorC;
  if (enroque == 0) // Restaurar valores en caso de no haber enroque
  {
    enroqueBlancas = -1;
    enroqueNegras = -1;
    enroqueAmarillas = -1;
    enroqueRojas = -1;
    torreBDMovida = tBDM;
    torreBIMovida = tBIM;
    torreNDMovida = tNDM;
    torreNIMovida = tNIM;
    torreADMovida = tVDM;
    torreAIMovida = tVIM;
    torreRDMovida = tRDM;
    torreRIMovida = tRIM;
  }

  return valor;
}

// Todos contra rojas
int movimientoMaquinaRojas(int *p, int *c, pieza b[16], pieza a[16],
                           pieza n[16], pieza r[16], pieza t[16][16],
                           int turnoActual, int it) {
  int i, j, k;
  undo des[1];
  int p2, c2, costeActual;
  int mejorP, mejorC;
  int costeMejor = -10000;
  int valor = INT_MIN;

  // Variables para no perder el estado del enroque
  int enroque = 0;
  int a1[1], a2[1];
  int tBDM, tBIM, tNDM, tNIM, tVDM, tVIM, tRDM, tRIM;
  int encontrado = 0;
  tBDM = torreBDMovida;
  tBIM = torreBIMovida;
  tNDM = torreNDMovida;
  tNIM = torreNIMovida;
  tVDM = torreADMovida;
  tVIM = torreAIMovida;
  tRDM = torreRDMovida;
  tRIM = torreRIMovida;

  encontrado = 0;
  for (i = 0; i < 16; i++) {
    if ((turnoActual == 3) && (r[i].tipo > 0)) {
      p2 = r[i].x * 16 + r[i].y; // mejorPieza

      // 16x16
      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k; // mejorCasilla
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcRojas(t);
            if ((encontrado == 0) || (costeActual > costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }

            if (enroqueRojas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueRojas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 0) && (b[i].tipo > 0)) {
      p2 = b[i].x * 16 + b[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcRojas(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueBlancas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueBlancas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 1) && (a[i].tipo > 0)) {
      p2 = a[i].x * 16 + a[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcRojas(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueAmarillas != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueAmarillas = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }

    } else if ((turnoActual == 2) && (n[i].tipo > 0)) {
      p2 = n[i].x * 16 + n[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcRojas(t);
            if ((encontrado == 0) || (costeActual < costeMejor)) {
              mejorP = p2;
              mejorC = c2;
              costeMejor = costeActual;
              encontrado = 1;
            }
            if (enroqueNegras != -1)
              enroque = 1;
            else
              enroque = 0;
            enroqueNegras = -1;
            deshacerMovimientoPrueba(des, t);
          }
        }
    }
  }

  valor = costeMejor;
  *p = mejorP;
  *c = mejorC;
  if (enroque == 0) // Restaurar valores en caso de no haber enroque
  {
    enroqueBlancas = -1;
    enroqueNegras = -1;
    enroqueAmarillas = -1;
    enroqueRojas = -1;
    torreBDMovida = tBDM;
    torreBIMovida = tBIM;
    torreNDMovida = tNDM;
    torreNIMovida = tNIM;
    torreADMovida = tVDM;
    torreAIMovida = tVIM;
    torreRDMovida = tRDM;
    torreRIMovida = tRIM;
  }

  return valor;
}

#endif // INTELIGENCIAARTIFICIAL4X4
