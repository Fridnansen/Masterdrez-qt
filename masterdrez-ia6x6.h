#ifndef INTELIGENCIAARTIFICIAL6X6
#define INTELIGENCIAARTIFICIAL6X6

// 6 costes x 6 minimax/coste

int coste4wcBlancasxAmarillas(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == BLANCO) {
          peso += -t[i][j].tipo;
          casilla += -(i * 16 + j);
        } else if (t[i][j].color == AMARILLO) {
          peso += t[i][j].tipo;
          casilla += i * 16 + j;
        }
      }
    }

  resultado = peso + casilla / 10;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

int coste4wcBlancasxNegras(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == BLANCO) {
          peso += -t[i][j].tipo;
          casilla += -(i * 16 + j);
        } else if (t[i][j].color == NEGRO) {
          peso += t[i][j].tipo;
          casilla += i * 16 + j;
        }
      }
    }

  resultado = peso + casilla / 10;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

int coste4wcBlancasxRojas(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == BLANCO) {
          peso += -t[i][j].tipo;
          casilla += -(i * 16 + j);
        } else if (t[i][j].color == ROJO) {
          peso += t[i][j].tipo;
          casilla += i * 16 + j;
        }
      }
    }

  resultado = peso + casilla / 10;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

int coste4wcAmarillasxNegras(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == AMARILLO) {
          peso += -t[i][j].tipo;
          casilla += -(i * 16 + j);
        } else if (t[i][j].color == NEGRO) {
          peso += t[i][j].tipo;
          casilla += i * 16 + j;
        }
      }
    }

  resultado = peso + casilla / 10;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

int coste4wcAmarillasxRojas(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == AMARILLO) {
          peso += -t[i][j].tipo;
          casilla += -(i * 16 + j);
        } else if (t[i][j].color == ROJO) {
          peso += t[i][j].tipo;
          casilla += i * 16 + j;
        }
      }
    }

  resultado = peso + casilla / 10;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

int coste4wcNegrasxRojas(pieza t[16][16]) {

  int resultado = 0, peso = 0, casilla = 0;

  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++) {
      if (t[i][j].tipo != -1) {
        if (t[i][j].color == NEGRO) {
          peso += -t[i][j].tipo;
          casilla += -(i * 16 + j);
        } else if (t[i][j].color == ROJO) {
          peso += t[i][j].tipo;
          casilla += i * 16 + j;
        }
      }
    }

  resultado = peso + casilla / 10;
  // resultado += Randint(0, 2); // Algo de aleatoridad en el movimiento

  return resultado;
}

//=================================================================================
// Divirtiendome un poco por aqui :)

// Blancas x Amarillas
int movimientoMaquinaBlancasxAmarillas(int *p, int *c, pieza b[16], pieza a[16],
                                       pieza n[16], pieza r[16],
                                       pieza t[16][16], int turnoActual,
                                       int it) {
  int i, j, k;
  undo des[1];
  int p2, c2, costeActual;
  int mejorP, mejorC;
  int costeMejor = -10000;
  int valor = INT_MIN;

  // Variables para no perder el estado del enroque
  int enroque = 0;
  int a1[1], a2[1];
  int tBDM, tBIM, tADM, tAIM;
  int encontrado = 0;
  tBDM = torreBDMovida;
  tBIM = torreBIMovida;
  tADM = torreADMovida;
  tAIM = torreAIMovida;

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
              costeActual = movimientoMaquinaBlancasxAmarillas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancasxAmarillas(t);
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
              costeActual = movimientoMaquinaBlancasxAmarillas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancasxAmarillas(t);
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
    enroqueAmarillas = -1;
    torreBDMovida = tBDM;
    torreBIMovida = tBIM;
    torreADMovida = tADM;
    torreAIMovida = tAIM;
  }

  return valor;
}

// Blancas x Negras
int movimientoMaquinaBlancasxNegras(int *p, int *c, pieza b[16], pieza a[16],
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
  int tBDM, tBIM, tNDM, tNIM;
  int encontrado = 0;
  tBDM = torreBDMovida;
  tBIM = torreBIMovida;
  tNDM = torreNDMovida;
  tNIM = torreNIMovida;

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
              costeActual = movimientoMaquinaBlancasxNegras(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancasxNegras(t);
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

    } else if ((turnoActual == 2) && (n[i].tipo > 0)) {
      p2 = n[i].x * 16 + n[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaBlancasxNegras(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancasxNegras(t);
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
    torreBDMovida = tBDM;
    torreBIMovida = tBIM;
    torreNDMovida = tNDM;
    torreNIMovida = tNIM;
  }

  return valor;
}

// Blancas x Rojas
int movimientoMaquinaBlancasxRojas(int *p, int *c, pieza b[16], pieza a[16],
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
  int tBDM, tBIM, tRDM, tRIM;
  int encontrado = 0;
  tBDM = torreBDMovida;
  tBIM = torreBIMovida;
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
              costeActual = movimientoMaquinaBlancasxRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancasxRojas(t);
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

    } else if ((turnoActual == 3) && (r[i].tipo > 0)) {
      p2 = r[i].x * 16 + r[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaBlancasxRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcBlancasxRojas(t);
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
    enroqueRojas = -1;
    torreBDMovida = tBDM;
    torreBIMovida = tBIM;
    torreRDMovida = tRDM;
    torreRIMovida = tRIM;
  }

  return valor;
}

// Amarillas x Negras
int movimientoMaquinaAmarillasxNegras(int *p, int *c, pieza b[16], pieza a[16],
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
  int tADM, tAIM, tNDM, tNIM;
  int encontrado = 0;
  tADM = torreADMovida;
  tAIM = torreAIMovida;
  tNDM = torreNDMovida;
  tNIM = torreNIMovida;

  encontrado = 0;
  for (i = 0; i < 16; i++) {
    if ((turnoActual == 1) && (a[i].tipo > 0)) {
      p2 = a[i].x * 16 + a[i].y; // mejorPieza

      // 16x16
      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k; // mejorCasilla
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaAmarillasxNegras(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcAmarillasxNegras(t);
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
              costeActual = movimientoMaquinaAmarillasxNegras(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcAmarillasxNegras(t);
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
    enroqueAmarillas = -1;
    enroqueNegras = -1;
    torreADMovida = tADM;
    torreAIMovida = tAIM;
    torreNDMovida = tNDM;
    torreNIMovida = tNIM;
  }

  return valor;
}

// Amarillas x Rojas
int movimientoMaquinaAmarillasxRojas(int *p, int *c, pieza b[16], pieza a[16],
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
  int tADM, tAIM, tRDM, tRIM;
  int encontrado = 0;
  tADM = torreADMovida;
  tAIM = torreAIMovida;
  tRDM = torreRDMovida;
  tRIM = torreRIMovida;

  encontrado = 0;
  for (i = 0; i < 16; i++) {
    if ((turnoActual == 1) && (a[i].tipo > 0)) {
      p2 = a[i].x * 16 + a[i].y; // mejorPieza

      // 16x16
      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k; // mejorCasilla
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaAmarillasxRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcAmarillasxRojas(t);
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

    } else if ((turnoActual == 3) && (r[i].tipo > 0)) {
      p2 = r[i].x * 16 + r[i].y;

      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k;
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaAmarillasxRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcAmarillasxRojas(t);
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
    enroqueAmarillas = -1;
    enroqueRojas = -1;
    torreADMovida = tADM;
    torreAIMovida = tAIM;
    torreRDMovida = tRDM;
    torreRIMovida = tRIM;
  }

  return valor;
}

// Negras x Rojas
int movimientoMaquinaNegrasxRojas(int *p, int *c, pieza b[16], pieza a[16],
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
  int tNDM, tNIM, tRDM, tRIM;
  int encontrado = 0;
  tNDM = torreNDMovida;
  tNIM = torreNIMovida;
  tRDM = torreRDMovida;
  tRIM = torreRIMovida;

  encontrado = 0;
  for (i = 0; i < 16; i++) {
    if ((turnoActual == 2) && (n[i].tipo > 0)) {
      p2 = n[i].x * 16 + n[i].y; // mejorPieza

      // 16x16
      for (j = 0; j < 16; j++)
        for (k = 0; k < 16; k++) {
          c2 = j * 16 + k; // mejorCasilla
          if (casillaYTurnoValidos(p2, c2, b, n, a, r, t, turnoActual, true)) {
            movimientoPrueba(des, p2, c2, b, n, a, r, t);
            if (it > 0)
              costeActual = movimientoMaquinaNegrasxRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcNegrasxRojas(t);
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
              costeActual = movimientoMaquinaNegrasxRojas(
                  a1, a2, b, a, n, r, t, (turnoActual + 1) % 4, it - 1);
            else
              costeActual = coste4wcNegrasxRojas(t);
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
    enroqueNegras = -1;
    enroqueRojas = -1;
    torreNDMovida = tNDM;
    torreNIMovida = tNIM;
    torreRDMovida = tRDM;
    torreRIMovida = tRIM;
  }

  return valor;
}

//=================================================================================

#endif // INTELIGENCIAARTIFICIAL6X6
