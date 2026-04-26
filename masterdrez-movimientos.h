#ifndef MASTERDREZMOVIMIENTOS
#define MASTERDREZMOVIMIENTOS

/**
* Devuelve 1 si la pieza seleccionada es valida segun el turno para ser
*movida.
*
*/
int piezaYTurnoValidos() {
  int xact, yact;
  pieza *p1;
  int i;
  int valor = 1;

  xact = piezaSeleccionada / 16;
  yact = piezaSeleccionada % 16;

  // encontrar pieza a mover
  p1 = NULL;
  for (i = 0; i < 16; i++) {
    if ((blancas[i].tipo > 0) && (blancas[i].x == xact) &&
        (blancas[i].y) == yact)
      p1 = &(blancas[i]);
    if ((negras[i].tipo > 0) && (negras[i].x == xact) && (negras[i].y) == yact)
      p1 = &(negras[i]);
    if ((rojas[i].tipo > 0) && (rojas[i].x == xact) && (rojas[i].y) == yact)
      p1 = &(rojas[i]);
    if ((amarillas[i].tipo > 0) && (amarillas[i].x == xact) &&
        (amarillas[i].y) == yact)
      p1 = &(amarillas[i]);
  }

  if (coronando) {
    for (i = 0; i < 4; i++) {
      if ((coronables[i].tipo > 0) && (coronables[i].x == xact) &&
          (coronables[i].y) == yact)
        p1 = &(coronables[i]);
    }
  }

  // if((p1 == NULL) || (p1->color != (turno + 1)))
  if ((p1 == NULL) || (controla[turno][p1->color - 1] != 1))
    valor = 0;
  else
    valor = 1;

  return valor;
}

/**
* Devuelve 1 si la pieza seleccionada existe en el tablero.
*
*/
int piezaValida() {
  int xact, yact;
  pieza *p1;
  int valor;

  xact = piezaSeleccionada / 16;
  yact = piezaSeleccionada % 16;

  // encontrar pieza a mover
  p1 = NULL;
  for (int i = 0; i < 16; i++) {
    if ((blancas[i].tipo > 0) && (blancas[i].x == xact) &&
        (blancas[i].y) == yact)
      p1 = &(blancas[i]);
    if ((negras[i].tipo > 0) && (negras[i].x == xact) && (negras[i].y) == yact)
      p1 = &(negras[i]);
    if ((amarillas[i].tipo > 0) && (amarillas[i].x == xact) &&
        (amarillas[i].y) == yact)
      p1 = &(amarillas[i]);
    if ((rojas[i].tipo > 0) && (rojas[i].x == xact) && (rojas[i].y) == yact)
      p1 = &(rojas[i]);
  }
  if (p1 == NULL)
    valor = 0;
  else
    valor = 1;

  return valor;
}

int tieneMasterBlancas(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                       pieza t[16][16], int tur) {
  int i;
  int valor = 0;
  int rey = -1;

  // Encontrar rey blanco:
  for (i = 0; i < 16; i++)
    if (b[i].tipo == REY)
      rey = b[i].x * 16 + b[i].y;

  // Si existe rey amarillo en el tablero:
  if (rey != -1) {
    if (tur == 1) {
      for (i = 0; i < 16; i++)
        if (a[i].tipo > 0 &&
            movimientoValido(a[i].x * 16 + a[i].y, rey, b, n, a, r, t)) {
          soploBlancas[i] = 1;
          valor = 1;
        }
    } else if (tur == 2) {
      for (i = 0; i < 16; i++)
        if (n[i].tipo > 0 &&
            movimientoValido(n[i].x * 16 + n[i].y, rey, b, n, a, r, t)) {
          soploNegras[i] = 1;
          valor = 1;
        }
    } else if (tur == 3) {
      for (i = 0; i < 16; i++)
        if (r[i].tipo > 0 &&
            movimientoValido(r[i].x * 16 + r[i].y, rey, b, n, a, r, t)) {
          soploRojas[i] = 1;
          valor = 1;
        }
    }
  }
  return valor;
}

int tieneMasterAmarillas(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                         pieza t[16][16], int tur) {
  int i;
  int valor = 0;
  int rey = -1;

  // Encontrar rey amarillo:
  for (i = 0; i < 16; i++)
    if (a[i].tipo == REY)
      rey = a[i].x * 16 + a[i].y;

  // Si existe rey amarillo en el tablero:
  if (rey != -1) {
    if (tur == 0) {
      for (i = 0; i < 16; i++)
        if (b[i].tipo > 0 &&
            movimientoValido(b[i].x * 16 + b[i].y, rey, b, n, a, r, t)) {
          soploBlancas[i] = 1;
          valor = 1;
        }
    } else if (tur == 2) {
      for (i = 0; i < 16; i++)
        if (n[i].tipo > 0 &&
            movimientoValido(n[i].x * 16 + n[i].y, rey, b, n, a, r, t)) {
          soploNegras[i] = 1;
          valor = 1;
        }
    } else if (tur == 3) {
      for (i = 0; i < 16; i++)
        if (r[i].tipo > 0 &&
            movimientoValido(r[i].x * 16 + r[i].y, rey, b, n, a, r, t)) {
          soploRojas[i] = 1;
          valor = 1;
        }
    }
  }
  return valor;
}

int tieneMasterNegras(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                      pieza t[16][16], int tur) {
  int i;
  int valor = 0;
  int rey = -1;

  // Encontrar rey negro:
  for (i = 0; i < 16; i++)
    if (n[i].tipo == REY)
      rey = n[i].x * 16 + n[i].y;

  // Si existe rey negro en el tablero:
  if (rey != -1) {
    if (tur == 0) {
      for (i = 0; i < 16; i++)
        if (b[i].tipo > 0 &&
            movimientoValido(b[i].x * 16 + b[i].y, rey, b, n, a, r, t)) {
          soploBlancas[i] = 1;
          valor = 1;
        }
    } else if (tur == 1) {
      for (i = 0; i < 16; i++)
        if (a[i].tipo > 0 &&
            movimientoValido(a[i].x * 16 + a[i].y, rey, b, n, a, r, t)) {
          soploAmarillas[i] = 1;
          valor = 1;
        }
    } else if (tur == 3) {
      for (i = 0; i < 16; i++)
        if (r[i].tipo > 0 &&
            movimientoValido(r[i].x * 16 + r[i].y, rey, b, n, a, r, t)) {
          soploRojas[i] = 1;
          valor = 1;
        }
    }
  }
  return valor;
}

int tieneMasterRojas(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                     pieza t[16][16], int tur) {
  int i;
  int valor = 0;
  int rey = -1;

  // Encontrar rey rojo:
  for (i = 0; i < 16; i++)
    if (r[i].tipo == REY)
      rey = r[i].x * 16 + r[i].y;

  // Si existe rey amarillo en el tablero:
  if (rey != -1) {
    if (tur == 0) {
      for (i = 0; i < 16; i++)
        if (b[i].tipo > 0 &&
            movimientoValido(b[i].x * 16 + b[i].y, rey, b, n, a, r, t)) {
          soploBlancas[i] = 1;
          valor = 1;
          break;
        }
    } else if (tur == 1) {
      for (i = 0; i < 16; i++)
        if (a[i].tipo > 0 &&
            movimientoValido(a[i].x * 16 + a[i].y, rey, b, n, a, r, t)) {
          soploAmarillas[i] = 1;
          valor = 1;
          break;
        }
    } else if (tur == 2) {
      for (i = 0; i < 16; i++)
        if (n[i].tipo > 0 &&
            movimientoValido(n[i].x * 16 + n[i].y, rey, b, n, a, r, t)) {
          soploNegras[i] = 1;
          valor = 1;
          break;
        }
    }
  }

  return valor;
}

/**
    * Devuelve 0 si el movimiento no corresponde al de un peon coronando.
    * En caso contrario, devuelve el color del territorio en el cual se
    * esta coronando.
    *
    * @param xact coordenada X de la casilla origen
    * @param yact coordenada Y de la casilla origen
    * @param xfin coordenada X de la casilla destino
    * @param yfin coordenada Y de la casilla destino
    * @param t matriz que representa el tablero
    * @param p apuntador a la pieza que se esta moviendo
    *
    * return color del reino en el cual se esta coronando o 0 (cero) cuando
  *el
  *movimiento no es de coronacion
    */
int promotingPawn(int xfin, int yfin, pieza *p) {
  int valor = 0;

  if (p->tipo != PEON)
    return valor;

  if (!casillaValida(xfin, yfin))
    return valor;

  switch (p->color) {
  case BLANCO:
    if (yfin == 15 || xfin == 0 || xfin == 15)
      valor = 1;
    break;
  case NEGRO:
    if (yfin == 0 || xfin == 0 || xfin == 15)
      valor = 1;
    break;
  case AMARILLO:
    if (xfin == 15 || yfin == 0 || yfin == 15)
      valor = 1;
    break;
  case ROJO:
    if (xfin == 0 || yfin == 0 || yfin == 15)
      valor = 1;
    break;
  }
  if (valor == 1) {
    if (yfin == 15)
      valor = NEGRO;
    else if (xfin == 15)
      valor = ROJO;
    else if (xfin == 0)
      valor = AMARILLO;
  }

  return valor;
}

//=========================================================

/**
* Devuelve 1 si el reino esta en situacion de inmovilizado. Esto es:
* que no exista ningún movimiento valido, que no deje al rey en
* situacion de Jaque Master.
*
* @param turno reino de turno
*/
int inmovilizado(int turno) {
  int valor = 0;

  switch (turno) {
  case 0: // blancas
    if (blancasEnJaqueMaster(blancas, negras, amarillas, rojas, tablero, turno))
      valor = 1;
    break;

  case 1: // amarillas
    if (amarillasEnJaqueMaster(blancas, negras, amarillas, rojas, tablero,
                               turno))
      valor = 1;
    break;

  case 2: // negras
    if (negrasEnJaqueMaster(blancas, negras, amarillas, rojas, tablero, turno))
      valor = 1;
    break;

  case 3: // rojas
    if (rojasEnJaqueMaster(blancas, negras, amarillas, rojas, tablero, turno))
      valor = 1;
    break;
  }

  return valor;
}

/**
* Devuelve el numero de piezas actuales del reino,
* independientemente de si el rey esta vivo o no.
* No incluye piezas de los otros reinos que controla.
*/
int piezas_actuales(pieza reino[16]) {
  int piezas = 0;
  for (int i = 0; i < 16; i++)
    if (reino[i].tipo != -1)
      piezas++;
  return piezas;
}

/**
* Devuelve el numero de piezas activas del reino,
* incluye piezas que controla de otros reinos.
* Devuelve 0 si el rey ha derrotado, independientemente de
* la cantidad de piezas de su reino que puedan quedar en el tablero.
*/
int piezas_activas(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                   int controla[4][4], int reino) {
  int turn = reino - 1;
  int piezas = 0;

  if (controla[turn][0] == 1)
    piezas = piezas + piezas_actuales(b);
  if (controla[turn][1] == 1)
    piezas = piezas + piezas_actuales(a);
  if (controla[turn][2] == 1)
    piezas = piezas + piezas_actuales(n);
  if (controla[turn][3] == 1)
    piezas = piezas + piezas_actuales(r);

  return piezas;
}

/**
* Devuelve el numero de piezas actuales de tipo tipoPieza del reino,
* independientemente de si el rey esta vivo o no.
* No incluye piezas de los otros reinos que controla.
*/
int piezas_actuales(pieza reino[16], int tipoPieza) {
  int piezas = 0;
  for (int i = 0; i < 16; i++)
    if (reino[i].tipo == tipoPieza)
      piezas++;
  return piezas;
}

/**
* Devuelve el numero de piezas activas de tipo tipoPieza del reino,
* incluye piezas que controla de otros reinos.
* Devuelve 0 si el rey ha derrotado, independientemente de
* la cantidad de piezas de su reino que puedan quedar en el tablero.
*/
int piezas_activas(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                   int controla[4][4], int reino, int tipoPieza) {
  int turn = reino - 1;
  int piezas = 0;

  if (controla[turn][0] == 1)
    piezas = piezas + piezas_actuales(b, tipoPieza);
  if (controla[turn][1] == 1)
    piezas = piezas + piezas_actuales(a, tipoPieza);
  if (controla[turn][2] == 1)
    piezas = piezas + piezas_actuales(n, tipoPieza);
  if (controla[turn][3] == 1)
    piezas = piezas + piezas_actuales(r, tipoPieza);

  return piezas;
}

//==========================================================
/**
    * Devuelve 1 si la casilla no esta ocupada por ningúna otra ficha o si
  *esta fuera del tablero.
    *
    * @param casilla
    * @param t Matriz que representa el tablero
    */
int casillaValida(int casilla, pieza t[16][16]) { // Edición
  int xfin, yfin;
  int valor;

  xfin = casilla / 16;
  yfin = casilla % 16;

  if ((xfin >= 0) && (xfin < 16) && (yfin >= 0) && (yfin < 16)) {
    if (t[xfin][yfin].tipo > 0)
      valor = 0; // casilla ocupada (invalida)
    else
      valor = 1; // casilla desocupada (-1)
  } else
    valor = 1; // casilla desocupada

  return valor;
}

/**
    * Devuelve 1 si el movimiento de piezaSeleccionada a casillaSeleccionada
  *es valido para el Peon
    * en movimiento de coronacion
    *
    * @param b Vector de piezas blancas
    * @param n Vector de piezas negras
    * @param a Vector de piezas amarillas
    * @param r Vector de piezas rojas
    * @param t Matriz que representa el tablero
    * @param xact coordenada X de la casilla origen
    * @param yact coordenada Y de la casilla origen
    * @param xfin coordenada X de la casilla destino
    * @param yfin coordenada Y de la casilla destino
    * @param p1
    */
int movimientoValidoCoronacion(pieza t[16][16], int xact, int yact, int xfin,
                               int yfin, pieza *p1) {
  int valor = 0;

  for (int i = 0; i < 4; i++) {
    if (coronables[i].x == xact && coronables[i].y == yact &&
        coronables[i].color == p1->color && coronables[i].tipo > 0)
      if (xfin == xCoronando && yfin == yCoronando &&
          t[xfin][yfin].tipo == PEON)
        valor = 1;
  }
  return valor;
}

/**
* retorna cierto si la casilla selecciona esta en las esquinas
*
* @param x
* @param y
*/
bool blackSpot(int x, int y) {
  return (x >= 0 && x <= 3 && y >= 0 && y <= 3) ||   // cuadro derecho abajo
         (x >= 12 && x <= 15 && y >= 0 && y <= 3) || // cuadro izquierdo abajo
         (x >= 0 && x <= 3 && y >= 12 && y <= 15) || // cuadro dereho arriba
         (x >= 12 && x <= 15 && y >= 12 && y <= 15); // cuadro izquierdo arriba
}

/**
* Devuelve 1 si el movimiento corresponde al de una captura al paso
*
* Adicionalmente devuelve en los parametros xpassant, ypassant y colorpassant
* los valores de x, y, y color del peon que esta capturando
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param xact coordenada X de la casilla origen
* @param yact coordenada y de la casilla origen
* @param xfin coordenada X de la casilla destino
* @param yfin coordenada y de la casilla destino
* @param t
* @param p
* @param xpassant
* @param ypassant
*/
int CapturaAlPaso(int xact, int yact, int xfin, int yfin, pieza t[16][16],
                  pieza *p, int &xpassant, int &ypassant, int &colorpassant) {
  int valor = 0;

  if (p->tipo != PEON)
    return valor;

  if ((abs(yfin - yact) == 1) && (abs(xact - xfin) == 1)) {
    if (middlePassantBlanco->isPassant(xfin, yfin) && p->color != BLANCO) {
      int xpas, ypas;
      passantBlanco->getPos(xpas, ypas);
      if (xpas < 0 || ypas < 0)
        valor = 0;
      else if (t[xpas][ypas].tipo == PEON && t[xpas][ypas].color == BLANCO) {
        valor = 1;
        xpassant = xpas;
        ypassant = ypas;
        colorpassant = t[xact][yact].color;
      }
    }

    if (middlePassantAmarillo->isPassant(xfin, yfin) && p->color != AMARILLO) {
      int xpas, ypas;
      passantAmarillo->getPos(xpas, ypas);
      if (xpas < 0 || ypas < 0)
        valor = 0;
      else if (t[xpas][ypas].tipo == PEON && t[xpas][ypas].color == AMARILLO) {
        valor = 1;
        xpassant = xpas;
        ypassant = ypas;
        colorpassant = t[xact][yact].color;
      }
    }

    if (middlePassantNegro->isPassant(xfin, yfin) && p->color != NEGRO)

    {
      int xpas, ypas;
      passantNegro->getPos(xpas, ypas);
      if (xpas < 0 || ypas < 0)
        valor = 0;
      else if (t[xpas][ypas].tipo == PEON && t[xpas][ypas].color == NEGRO) {
        valor = 1;
        xpassant = xpas;
        ypassant = ypas;
        colorpassant = t[xact][yact].color;
      }
    }

    if (middlePassantRojo->isPassant(xfin, yfin) && p->color != ROJO) {
      int xpas, ypas;
      passantRojo->getPos(xpas, ypas);
      if (xpas < 0 || ypas < 0)
        valor = 0;
      else if (t[xpas][ypas].tipo == PEON && t[xpas][ypas].color == ROJO) {
        valor = 1;
        xpassant = xpas;
        ypassant = ypas;
        colorpassant = t[xact][yact].color;
      }
    }
  }
  return valor;
}

/**
* Devuelve 1 si el movimiento de piezaSeleccionada a casillaSeleccionada es
*valido para el Peon
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param xact coordenada X de la casilla origen
* @param yact coordenada Y de la casilla origen
* @param xfin coordenada X de la casilla destino
* @param yfin coordenada Y de la casilla destino
* @param p1
*/
int movimientoValidoPeon(pieza t[16][16], int xact, int yact, int xfin,
                         int yfin, pieza *p1) {
  int valor = 0;

  if (blackSpot(xfin, yfin))
    return valor;

  switch (p1->color) {
  case BLANCO:

    // izquierda
    if (xfin > xact && (xfin - xact == 1 || xfin - xact == 2) && yfin == yact) {
      if (t[xfin][yfin].tipo <= 0) {
        valor = 1;
        // Si se saltan 2 casillas no puede haber ningúna pieza en
        // el medio
        if ((xfin - xact == 2) && (t[xfin - 1][yfin].tipo > 0))
          valor = 0;
      }
      break;
    } // derecha
    else if (xfin < xact && (xfin - xact == -1 || xfin - xact == -2) &&
             yfin == yact) {
      if (t[xfin][yfin].tipo <= 0) {
        valor = 1;
        // Si se saltan 2 casillas no puede haber ningúna pieza en
        // el medio
        if ((xfin - xact == -2) && (t[xfin + 1][yfin].tipo > 0))
          valor = 0;
      }
      break;
    } // vertical
    else if (yfin > yact && (yfin - yact == 1 || yfin - yact == 2) &&
             xfin == xact) {
      if (t[xfin][yfin].tipo <= 0) {
        valor = 1;
        // Si se saltan 2 casillas no puede haber ningúna pieza en el medio
        if ((yfin - yact == 2) && (t[xfin][yfin - 1].tipo > 0))
          valor = 0;
      }
      break;
    }

    // Movimiento Diagonal (1 casilla)
    if (((yfin - yact) == 1 && abs(xact - xfin) == 1)) {

      int xpas, ypas, colorpas;
      // capturando
      if ((t[xfin][yfin].tipo > 0) &&
          ((t[xfin][yfin].color == AMARILLO) ||
           (t[xfin][yfin].color == NEGRO) || (t[xfin][yfin].color == ROJO)))
        valor = 1;
      // Peon al paso
      else if (CapturaAlPaso(xact, yact, xfin, yfin, t, p1, xpas, ypas,
                             colorpas)) {
        valor = 1;
      }
    }

    break;

  case AMARILLO:

    // Solo hacia adelante.
    if (xfin > xact && ((xfin - xact) == 1 || (xfin - xact) == 2) &&
        (yact == yfin) && (t[xfin][yfin].tipo <= 0)) {
      valor = 1;
      // Si se saltan 2 casillas no puede haber ningúna pieza en el medio
      if ((xfin - xact == 2) && (t[xfin - 1][yfin].tipo > 0))
        valor = 0;
      break;
    }

    if ((abs(yfin - yact) == 1 || abs(yfin - yact) == 2) && (xfin == xact) &&
        (t[xfin][yfin].tipo <= 0)) {
      valor = 1;
      // Si se saltan 2 casillas no puede haber ningúna pieza en el medio
      if ((yfin - yact == 2) && (t[xfin][yfin - 1].tipo > 0))
        valor = 0;
      if ((yfin - yact == -2) && (t[xfin][yfin + 1].tipo > 0))
        valor = 0;

      break;
    }

    // Movimiento Diagonal (1 casilla)
    if ((abs(yact - yfin) == 1 && (xfin - xact) == 1)) {
      int xpas, ypas, colorpas;
      // capturando:
      if ((t[xfin][yfin].tipo > 0) &&
          ((t[xfin][yfin].color == BLANCO) || (t[xfin][yfin].color == NEGRO) ||
           (t[xfin][yfin].color == ROJO)))
        valor = 1;

      // Peon al paso
      else if (CapturaAlPaso(xact, yact, xfin, yfin, t, p1, xpas, ypas,
                             colorpas)) {
        valor = 1;
      }
    }

    break;

  case NEGRO:

    if ((abs(xfin - xact) == 1 || abs(xfin - xact) == 2) && (yfin == yact) &&
        t[xfin][yfin].tipo <= 0) {
      valor = 1;
      // Si se saltan 2 casillas no puede haber ningúna pieza en el medio
      if ((xfin - xact == 2) && (t[xfin - 1][yfin].tipo > 0))
        valor = 0;
      if ((xfin - xact == -2) && (t[xfin + 1][yfin].tipo > 0))
        valor = 0;
      break;
    }

    // Solo hacia adelante.
    if (yfin < yact && ((yfin - yact) == -1 || (yfin - yact) == -2) &&
        (xfin == xact) && (t[xfin][yfin].tipo <= 0)) {
      valor = 1;
      // Si se saltan 2 casillas no puede haber ningúna pieza en el medio
      if ((yfin - yact == -2) && (t[xfin][yfin + 1].tipo > 0))
        valor = 0;
      break;
    }

    // Movimiento Diagonal (1 casilla)
    if (((yfin - yact) == -1) && (abs(xact - xfin) == 1)) {
      int xpas, ypas, colorpas;
      // capturando
      if ((t[xfin][yfin].tipo > 0) &&
          ((t[xfin][yfin].color == AMARILLO) ||
           (t[xfin][yfin].color == BLANCO) || (t[xfin][yfin].color == ROJO)))
        valor = 1;

      // Peon al paso
      else if (CapturaAlPaso(xact, yact, xfin, yfin, t, p1, xpas, ypas,
                             colorpas)) {
        valor = 1;
      }
    }

    break;

  case ROJO:

    // Solo hacia adelante.
    if (xfin < xact && ((xfin - xact) == -1 || (xfin - xact) == -2) &&
        (yact == yfin) && (t[xfin][yfin].tipo <= 0)) {
      valor = 1;

      // Si se saltan 2 casillas no puede haber ningúna pieza en el medio
      if ((xfin - xact == -2) && (t[xfin + 1][yfin].tipo > 0))
        valor = 0;
      break;
    }

    if ((abs(yfin - yact) == 1 || abs(yfin - yact) == 2) && (xfin == xact) &&
        (t[xfin][yfin].tipo <= 0)) {
      valor = 1;
      // Si se saltan 2 casillas no puede haber ningúna pieza en el medio
      if ((yfin - yact == 2) && (t[xfin][yfin - 1].tipo > 0))
        valor = 0;
      if ((yfin - yact == -2) && (t[xfin][yfin + 1].tipo > 0))
        valor = 0;

      break;
    }

    // Movimiento Diagonal (1 casilla)
    if (((xfin - xact) == -1) && (abs(yact - yfin) == 1)) {
      int xpas, ypas, colorpas;
      // capturando:
      if ((t[xfin][yfin].tipo > 0) &&
          ((t[xfin][yfin].color == BLANCO) || (t[xfin][yfin].color == NEGRO) ||
           (t[xfin][yfin].color == AMARILLO)))
        valor = 1;

      // Peon al paso
      else if (CapturaAlPaso(xact, yact, xfin, yfin, t, p1, xpas, ypas,
                             colorpas)) {
        valor = 1;
      }
    }

    break;
  }

  return valor;
}

/**
* Devuelve 1 si el movimiento de piezaSeleccionada a casillaSeleccionada es
*valido para el Caballo
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param xact coordenada X de la casilla origen
* @param yact coordenada Y de la casilla origen
* @param xfin coordenada X de la casilla destino
* @param yfin coordenada Y de la casilla destino
* @param p1
*/
int movimientoValidoCaballo(int xact, int yact, int xfin, int yfin) {
  int i;
  int valor = 0;

  if ((xfin - xact == 2) || (xfin - xact == -2)) {
    if ((yfin - yact == 1) || (yfin - yact == -1))
      valor = 1;
  }

  if ((yfin - yact == 2) || (yfin - yact == -2)) {
    if ((xfin - xact == 1) || (xfin - xact == -1))
      valor = 1;
  }

  if (valor == 0 || blackSpot(xfin, yfin))
    valor = 0;
  else {
    int xl = (xact < xfin) ? xact : xfin;
    int zl = (yact < yfin) ? yact : yfin;
    int xh = (xl == xact) ? xfin : xact;
    int zh = (zl == yact) ? yfin : yact;

    bool trueRoute = true;

    bool diffMinX = abs(xfin - xact) == 1 ? true : false;

    if (diffMinX) {
      for (i = zl; i <= zh; i++)
        if (blackSpot(xl, i)) {
          trueRoute = false;
          break;
        }

      if (!trueRoute) {
        trueRoute = true;
        for (i = zl; i <= zh; i++)
          if (blackSpot(xh, i)) {
            trueRoute = false;
            break;
          }
      }
    } else {
      for (i = xl; i <= xh; i++)
        if (blackSpot(i, zl)) {
          trueRoute = false;
          break;
        }

      if (!trueRoute) {
        trueRoute = true;
        for (i = xl; i <= xh; i++)
          if (blackSpot(i, xh)) {
            trueRoute = false;
            break;
          }
      }
    }

    valor = trueRoute ? 1 : 0;
  }

  return valor;
}

/**
* Devuelve 1 si el movimiento de piezaSeleccionada a casillaSeleccionada es
*valido para el Alfil
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param xact coordenada X de la casilla origen
* @param yact coordenada Y de la casilla origen
* @param xfin coordenada X de la casilla destino
* @param yfin coordenada Y de la casilla destino
* @param p1
*/
int movimientoValidoAlfil(pieza t[16][16], int xact, int yact, int xfin,
                          int yfin) {
  int i;
  int valor = 0;

  if (((xfin - xact) == (yfin - yact)) || ((xfin - xact) == -(yfin - yact)))
    valor = 1;

  if (valor == 1) {
    if (xfin - xact > 0) {
      if (yfin - yact > 0) {
        for (i = 1; i < (xfin - xact); i++)
          if (t[xact + i][yact + i].tipo > 0)
            valor = 0;
      } else {
        for (i = 1; i < (xfin - xact); i++)
          if (t[xact + i][yact - i].tipo > 0)
            valor = 0;
      }
    } else {
      if (yfin - yact > 0) {
        for (i = 1; i < (xact - xfin); i++)
          if (t[xact - i][yact + i].tipo > 0)
            valor = 0;
      } else {
        for (i = 1; i < (xact - xfin); i++)
          if (t[xact - i][yact - i].tipo > 0)
            valor = 0;
      }
    }
  }

  if (valor == 1) {
    int xl = (xact < xfin) ? xact : xfin;
    int zl = (xl == xact) ? yact : yfin;
    int xh = (xl == xact) ? xfin : xact;
    int zh = (xl == xact) ? yfin : yact;

    while (xl <= xh) {
      if (blackSpot(xl, zl)) {
        valor = 0;
        break;
      }
      xl++;
      zl = (zh - zl > 0) ? zl + 1 : zl - 1;
    }
  }

  return valor;
}

/**
* Devuelve 1 si el movimiento de piezaSeleccionada a casillaSeleccionada es
*valido para la Torre
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param xact coordenada X de la casilla origen
* @param yact coordenada Y de la casilla origen
* @param xfin coordenada X de la casilla destino
* @param yfin coordenada Y de la casilla destino
* @param p1
*/
int movimientoValidoTorre(pieza t[16][16], int xact, int yact, int xfin,
                          int yfin) {
  int i;
  int valor = 0;

  if ((((xfin - xact) == 0) && ((yfin - yact) != 0)) ||
      (((xfin - xact) != 0) && ((yfin - yact) == 0)))
    valor = 1;

  // Comprobar que no hay piezas en el camino a recorrer
  if (valor == 1) {
    // Movimiento sobre X
    if (xfin - xact != 0) {
      if (xfin - xact > 0) {
        for (i = 1; i < (xfin - xact); i++)
          if (t[xact + i][yact].tipo > 0)
            valor = 0;
      } else {
        for (i = 1; i < (xact - xfin); i++)
          if (t[xact - i][yact].tipo > 0)
            valor = 0;
      }
    }
    // Movimiento sobre Y
    else {
      if (yfin - yact > 0) {
        for (i = 1; i < (yfin - yact); i++)
          if (t[xact][yact + i].tipo > 0)
            valor = 0;
      } else {
        for (i = 1; i < (yact - yfin); i++)
          if (t[xact][yact - i].tipo > 0)
            valor = 0;
      }
    }
  }

  if (valor == 1) {
    if (xact == xfin) {
      int zl = yact < yfin ? yact : yfin;
      int zh = zl == yact ? yfin : yact;
      for (i = zl; i <= zh; i++)
        if (blackSpot(xact, i)) {
          valor = 0;
          break;
        }
    } else {
      int xl = xact < xfin ? xact : xfin;
      int xh = xl == xact ? xfin : xact;
      for (i = xl; i <= xh; i++)
        if (blackSpot(i, yact)) {
          valor = 0;
          break;
        }
    }
  }

  return valor;
}

/**
* Devuelve 1 si el movimiento de piezaSeleccionada a casillaSeleccionada es
*valido para la Dama
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param xact coordenada X de la casilla origen
* @param yact coordenada Y de la casilla origen
* @param xfin coordenada X de la casilla destino
* @param yfin coordenada Y de la casilla destino
* @param p1
*/
int movimientoValidoDama(pieza t[16][16], int xact, int yact, int xfin,
                         int yfin) {
  int i, j;
  int valor = 0;

  // Movimiento tipo alfil
  if (((xfin - xact) == (yfin - yact)) || ((xfin - xact) == -(yfin - yact)))
    valor = 1;

  // Comprobar que no hay piezas en el camino a recorrer
  if (valor == 1) {
    if (xfin - xact > 0) {
      if (yfin - yact > 0) {
        for (i = 1; i < (xfin - xact); i++)
          if (t[xact + i][yact + i].tipo > 0)
            valor = 0;
      } else {
        for (i = 1; i < (xfin - xact); i++)
          if (t[xact + i][yact - i].tipo > 0)
            valor = 0;
      }
    } else {
      if (yfin - yact > 0) {
        for (i = 1; i < (xact - xfin); i++)
          if (t[xact - i][yact + i].tipo > 0)
            valor = 0;
      } else {
        for (i = 1; i < (xact - xfin); i++)
          if (t[xact - i][yact - i].tipo > 0)
            valor = 0;
      }
    }
  }

  if (valor == 0) {
    // Movimiento tipo torre
    j = 0;
    if ((((xfin - xact) == 0) && ((yfin - yact) != 0)) ||
        (((xfin - xact) != 0) && ((yfin - yact) == 0)))
      j = 1;

    // Comprobar que no hay piezas en el camino a recorrer
    if (j == 1) {
      // Moviemiento sobre X
      if (xfin - xact != 0) {
        if (xfin - xact > 0) {
          for (i = 1; i < (xfin - xact); i++)
            if (t[xact + i][yact].tipo > 0)
              j = 0;
        } else {
          for (i = 1; i < (xact - xfin); i++)
            if (t[xact - i][yact].tipo > 0)
              j = 0;
        }
      }
      // Movimiento sobre Y
      else {
        if (yfin - yact > 0) {
          for (i = 1; i < (yfin - yact); i++)
            if (t[xact][yact + i].tipo > 0)
              j = 0;
        } else {
          for (i = 1; i < (yact - yfin); i++)
            if (t[xact][yact - i].tipo > 0)
              j = 0;
        }
      }
    }

    if (j == 1)
      valor = 1;
  }

  // Si se ha movido como un alfil o como una torre: movimento valido
  if (valor == 1 || j == 1)
    valor = 1;
  else
    valor = 0;

  if (valor == 1 && xact != xfin) {
    int xl = xact < xfin ? xact : xfin;
    int zl = xl == xact ? yact : yfin;
    int xh = xl == xact ? xfin : xact;
    int zh = xl == xact ? yfin : yact;

    while (xl <= xh) {
      if (blackSpot(xl, zl)) {
        valor = 0;
        break;
      }
      xl++;
      zl = zh - zl > 0 ? zl + 1 : zl - 1;
    }
  }

  else if (valor == 1 && (xact == xfin || yact == yfin)) {
    bool xMove = (xact == xfin) ? true : false;
    if (xMove) {
      int zl = (yact < yfin) ? yact : yfin;
      int zh = (zl == yact) ? yfin : yact;
      for (i = zl; i <= zh; i++)
        if (blackSpot(xact, i)) {
          valor = 0;
          break;
        }
    } else {
      int xl = (xact < xfin) ? xact : xfin;
      int xh = (xl == xact) ? xfin : xact;
      for (i = xl; i <= xh; i++)
        if (blackSpot(i, yact)) {
          valor = 0;
          break;
        }
    }
  }

  return valor;
}

/**
    * retorna cierto si la casilla selecciona no esta en las esquinas ni
  *fuera
  *del tablero
    *
    * @param x coordenada X de la casilla
    * @param z coordenada Y de la casilla
    */
bool casillaValida(int x, int z) {
  if (x < 0 || x > 15)
    return false;
  if (z < 0 || z > 15)
    return false;
  if (blackSpot(x, z))
    return false;
  return true;
}

/**
* Devuelve 1 si la casilla es alcanzable (capturable) por un peon
*
* @param x Coordenada X de la casilla
* @param z coordenada Y de la casilla
* @param t Matriz que representa el tablero
* @param tur turno actual (equivalente a color+1)
*/
int capturablePorPeon(int x, int z, pieza t[16][16], int tur) {
  int xtry[4];
  int ztry[4];

  xtry[0] = x + 1;
  xtry[1] = x + 1;
  xtry[2] = x - 1;
  xtry[3] = x - 1;
  ztry[0] = z + 1;
  ztry[1] = z - 1;
  ztry[2] = z + 1;
  ztry[3] = z - 1;

  for (int i = 0; i < 4; i++) {
    if (casillaValida(xtry[i], ztry[i]))
      if ((t[xtry[i]][ztry[i]].tipo == PEON) &&
          (t[xtry[i]][ztry[i]].color != (tur + 1)))
        return 1;
  }

  return 0;
}

/**
    * Devuelve 1 si el movimiento de piezaSeleccionada a casillaSeleccionada
  *es valido para el Rey
    *
    * @param b Vector de piezas blancas
    * @param n Vector de piezas negras
    * @param a Vector de piezas amarillas
    * @param r Vector de piezas rojas
    * @param t Matriz que representa el tablero
    * @param xact coordenada X de la casilla origen
    * @param yact coordenada Y de la casilla origen
    * @param xfin coordenada X de la casilla destino
    * @param yfin coordenada Y de la casilla destino
    * @param p1
    */
int movimientoValidoRey(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                        pieza t[16][16], int xact, int yact, int xfin, int yfin,
                        pieza *p1) {
  int valor = 0;

  if (blackSpot(xfin, yfin))
    return valor;

  // Movimiento basico (1 paso en cualquier direccion)
  if (((xact - xfin == 1) &&
       ((yact - yfin == -1) || (yact - yfin == 1) || (yact - yfin == 0))) ||
      ((xact - xfin == -1) &&
       ((yact - yfin == -1) || (yact - yfin == 1) || (yact - yfin == 0))) ||
      ((xact - xfin == 0) &&
       ((yact - yfin == -1) || (yact - yfin == 1) || (yact - yfin == 0))))
    valor = 1;

  // Movimiento de enroque
  switch (p1->color) {
  case BLANCO:
    if ((yfin - yact == 0) && (abs(xfin - xact) == 2) && (!reyBlancoMovido) &&
        (xact == 8) && (yact == 0)) {
      if ((xfin == 6) && (!torreBDMovida) && (t[4][0].tipo == TORRE) &&
          (t[4][0].color == BLANCO) && (t[7][0].tipo <= 0) &&
          (t[6][0].tipo <= 0) && (t[5][0].tipo <= 0) &&
          (!capturable(7, 0, b, n, a, r, t, BLANCO)))
        valor = 1;
      else if ((xfin == 10) && (!torreBIMovida) && (t[11][0].tipo == TORRE) &&
               (t[11][0].color == BLANCO) && (t[9][0].tipo <= 0) &&
               (t[10][0].tipo <= 0) &&
               (!capturable(9, 0, b, n, a, r, t, BLANCO)))
        valor = 1;
    }
    break;

  case AMARILLO:
    if ((xfin - xact == 0) && (abs(yfin - yact) == 2) && (!reyAmarilloMovido) &&
        (xact == 0) && (yact == 8)) {
      if ((yfin == 10) && (!torreADMovida) && (t[0][11].tipo == TORRE) &&
          (t[0][11].color == AMARILLO) && (t[0][9].tipo <= 0) &&
          (t[0][10].tipo <= 0) && (!capturable(0, 9, b, n, a, r, t, AMARILLO)))
        valor = 1;
      else if ((yfin == 6) && (!torreAIMovida) && (t[0][4].tipo == TORRE) &&
               (t[0][4].color == AMARILLO) && (t[0][5].tipo <= 0) &&
               (t[0][6].tipo <= 0) && (t[0][7].tipo <= 0) &&
               (!capturable(0, 7, b, n, a, r, t, AMARILLO)))
        valor = 1;
    }
    break;

  case NEGRO:
    if ((yfin - yact == 0) && (abs(xfin - xact) == 2) && (!reyNegroMovido) &&
        (xact == 7) && (yact == 15)) {
      if ((xfin == 9) && (!torreNDMovida) && (t[11][15].tipo == TORRE) &&
          (t[11][15].color == NEGRO) && (t[8][15].tipo <= 0) &&
          (t[9][15].tipo <= 0) && (t[10][15].tipo <= 0) &&
          (!capturable(8, 15, b, n, a, r, t, NEGRO)))
        valor = 1;
      else if ((xfin == 5) && (!torreNIMovida) && (t[4][15].tipo == TORRE) &&
               (t[4][15].color == NEGRO) && (t[6][15].tipo <= 0) &&
               (t[5][15].tipo <= 0) &&
               (!capturable(6, 15, b, n, a, r, t, NEGRO)))
        valor = 1;
    }
    break;

  case ROJO:
    if ((xfin - xact == 0) && (abs(yfin - yact) == 2) && (!reyRojoMovido) &&
        (xact == 15) && (yact == 7)) {
      if ((yfin == 5) && (!torreRDMovida) && (t[15][4].tipo == TORRE) &&
          (t[15][4].color == ROJO) && (t[15][6].tipo <= 0) &&
          (t[15][5].tipo <= 0) && (!capturable(15, 6, b, n, a, r, t, ROJO)))
        valor = 1;
      else if ((yfin == 9) && (!torreRIMovida) && (t[15][11].tipo == TORRE) &&
               (t[15][11].color == ROJO) && (t[15][8].tipo <= 0) &&
               (t[15][9].tipo <= 0) && (t[15][10].tipo <= 0) &&
               (!capturable(15, 8, b, n, a, r, t, ROJO)))
        valor = 1;
    }
    break;
  }

  return valor;
}

/**
* Devuelve 1 si el movimiento desde mipieza a casilla es valido segun la
*pieza.
*
* @param mipieza
* @param casilla
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
*/
int movimientoValido(int mipieza, int casilla, pieza b[16], pieza n[16],
                     pieza a[16], pieza r[16], pieza t[16][16]) {
  int xact, yact, xfin, yfin;
  pieza *p1 = NULL;
  int i;
  int valor = 0;

  xact = mipieza / 16;
  yact = mipieza % 16;
  xfin = casilla / 16;
  yfin = casilla % 16;

  // Buscar pieza a mover:
  for (i = 0; i < 16; i++) {
    if ((b[i].tipo > 0) && (b[i].x == xact) && (b[i].y) == yact)
      p1 = &(b[i]);
    if ((n[i].tipo > 0) && (n[i].x == xact) && (n[i].y) == yact)
      p1 = &(n[i]);
    if ((a[i].tipo > 0) && (a[i].x == xact) && (a[i].y) == yact)
      p1 = &(a[i]);
    if ((r[i].tipo > 0) && (r[i].x == xact) && (r[i].y) == yact)
      p1 = &(r[i]);
  }

  if (coronando == 1) {
    for (i = 0; i < 4; i++)
      if ((coronables[i].tipo > 0) && (coronables[i].x == xact) &&
          (coronables[i].y == yact))
        p1 = &(coronables[i]);

    return movimientoValidoCoronacion(t, xact, yact, xfin, yfin, p1);
  }

  // Si existe una pieza en la casilla destino: verificar si las piezas de
  // ese
  // reino son capturables por el reino que efectua el movimiento
  if (t[xfin][yfin].tipo != -1) {
    if (amenaza[t[xact][yact].color - 1][t[xfin][yfin].color - 1] == 0)
      return 0;
  }

  if (!p1)
    return 0;

  if (p1->tipo == PEON)
    return movimientoValidoPeon(t, xact, yact, xfin, yfin, p1);

  else if (p1->tipo == CABALLO)
    return movimientoValidoCaballo(xact, yact, xfin, yfin);

  else if (p1->tipo == ALFIL)
    return movimientoValidoAlfil(t, xact, yact, xfin, yfin);

  else if (p1->tipo == TORRE)
    return movimientoValidoTorre(t, xact, yact, xfin, yfin);

  else if (p1->tipo == DAMA)
    return movimientoValidoDama(t, xact, yact, xfin, yfin);

  else if (p1->tipo == REY)
    return movimientoValidoRey(b, n, a, r, t, xact, yact, xfin, yfin, p1);

  return valor;
}

/**
* Devuelve 1 si la casilla es alcanzable (capturable) por alguna pieza
*contraria
*
* @param x Coordenada X de la casilla
* @param z coordenada Y de la casilla
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param colorp color de la pieza de turno
*/
int capturable(int x, int z, pieza b[16], pieza n[16], pieza a[16], pieza r[16],
               pieza t[16][16], int colorp) {
  int i;
  int valor = 0;

  // Verificar si la pieza es alcanzable por un peon contrario
  if (capturablePorPeon(x, z, t, colorp - 1)) {
    valor = 1;
    return valor;
  }

  // Verificar si la pieza es alcanzable por otra pieza contraria
  for (i = 0; i < 16; i++) {
    if ((b[i].tipo > 1) && (b[i].color != colorp) &&
        movimientoValido(b[i].x * 16 + b[i].y, x * 16 + z, b, n, a, r, t)) {
      valor = 1;
      break;
    }

    if ((a[i].tipo > 1) && (a[i].color != colorp) &&
        movimientoValido(a[i].x * 16 + a[i].y, x * 16 + z, b, n, a, r, t)) {
      valor = 1;
      break;
    }

    if ((r[i].tipo > 1) && (r[i].color != colorp) &&
        movimientoValido(r[i].x * 16 + r[i].y, x * 16 + z, b, n, a, r, t)) {
      valor = 1;
      break;
    }

    if ((n[i].tipo > 1) && (n[i].color != colorp) &&
        movimientoValido(n[i].x * 16 + n[i].y, x * 16 + z, b, n, a, r, t)) {
      valor = 1;
      break;
    }
  }

  return valor;
}

/**
* Realiza un movimiento en el tablero de la ficha en casilla inicial a
*casillaFinal.
* Los cambios se almacenan en la estructura deshacer para poder desacerlos
*posteriormente.
*
* @param des
* @param casillaInicial
* @param casillaFinal
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
*/
void movimientoPrueba(undo *des, int casillaInicial, int casillaFinal,
                      pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                      pieza t[16][16]) {
  int xact, yact, xfin, yfin;
  pieza *p1;
  pieza *p2;
  int i;

  xact = casillaInicial / 16;
  yact = casillaInicial % 16;
  xfin = casillaFinal / 16;
  yfin = casillaFinal % 16;

  // encontrar pieza a mover
  p1 = NULL;
  for (i = 0; i < 16; i++) {
    if ((b[i].x == xact) && (b[i].y) == yact)
      p1 = &(b[i]);
    if ((n[i].x == xact) && (n[i].y) == yact)
      p1 = &(n[i]);
    if ((a[i].x == xact) && (a[i].y) == yact)
      p1 = &(a[i]);
    if ((r[i].x == xact) && (r[i].y) == yact)
      p1 = &(r[i]);
  }

  // Encontrar la pieza que nos capturamos (si existe)
  p2 = NULL;
  for (i = 0; i < 16; i++) {
    if ((b[i].tipo > 0) && (b[i].x == xfin) && (b[i].y) == yfin)
      p2 = &(b[i]);
    if ((n[i].tipo > 0) && (n[i].x == xfin) && (n[i].y) == yfin)
      p2 = &(n[i]);
    if ((a[i].tipo > 0) && (a[i].x == xfin) && (a[i].y) == yfin)
      p2 = &(a[i]);
    if ((r[i].tipo > 0) && (r[i].x == xfin) && (r[i].y) == yfin)
      p2 = &(r[i]);
  }

  if (p2 != NULL) {
    // Si capturamos alguna pieza: almacenarla para luego deshacer
    des->capturada = 1;
    des->p2 = p2;
    des->tipocapturada = p2->tipo;
    des->colorcapturada = p2->color;
    p2->tipo = -1; // eliminamos la ficha
    p2->x = -1;
    p2->y = -1;
    t[xact][yact].tipo = -1;
    t[xact][yact].color = -1;
  } else
    des->capturada = 0;

  if ((xfin >= 0) && (xfin < 16) && (yfin >= 0) && (yfin < 16)) {
    // Si movemos alguna pieza: almacenarla para luego deshacer.
    des->p1 = p1;
    des->tipo = p1->tipo;
    des->color = p1->color;
    des->casillaInicial = p1->x * 16 + p1->y;
    des->casillaFinal = xfin * 16 + yfin;
    p1->x = xfin;
    p1->y = yfin;
    t[xact][yact].tipo = -1;
    t[xact][yact].color = -1;
    t[xfin][yfin].tipo = des->p1->tipo;
    t[xfin][yfin].color = des->p1->color;
  } else {
    // En el caso de editar:
    if (p1->tipo != REY) // Se pueden quitar todas las piezas menos el rey
    {
      p1->tipo = -1; // eliminar la ficha.
      p1->x = -1;
      p1->y = -1;
      t[xact][yact].tipo = -1;
      t[xact][yact].color = -1;
    }
  }
}

/**
* Devuelve 1 si el rey blanco esta en jaque, en caso contrario devuelve 0.
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
*/
int blancasEnJaque(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                   pieza t[16][16]) {
  int i;
  int valor = 0;
  int rey;

  // Encontrar rey blanco:
  for (i = 0; i < 16; i++)
    if (b[i].tipo == REY)
      rey = b[i].x * 16 + b[i].y;

  for (i = 0; i < 16; i++)
    if ((n[i].tipo > 0 &&
         movimientoValido(n[i].x * 16 + n[i].y, rey, b, n, a, r, t)) ||
        (a[i].tipo > 0 &&
         movimientoValido(a[i].x * 16 + a[i].y, rey, b, n, a, r, t)) ||
        (r[i].tipo > 0 &&
         movimientoValido(r[i].x * 16 + r[i].y, rey, b, n, a, r, t))) {
      valor = 1;
      break;
    }

  return valor;
}

/**
* Deshace el ultimo movimiento de prueba segun la estructura deshacer (des).
*
* @param des
* @param t
*/
void deshacerMovimientoPrueba(undo *des, pieza t[16][16]) {
  pieza *p1;
  pieza *p2;
  p1 = des->p1;
  p2 = des->p2;

  // Restaurar pieza movida
  p1->tipo = des->tipo;
  p1->x = des->casillaInicial / 16;
  p1->y = des->casillaInicial % 16;
  t[des->casillaInicial / 16][des->casillaInicial % 16].tipo = des->tipo;
  t[des->casillaInicial / 16][des->casillaInicial % 16].color = des->color;

  // Restaurar pieza capturada
  if (des->capturada) {
    p2->tipo = des->tipocapturada;
    p2->color = des->colorcapturada;
    p2->x = des->casillaFinal / 16;
    p2->y = des->casillaFinal % 16;
    t[des->casillaFinal / 16][des->casillaFinal % 16].tipo = des->tipocapturada;
    t[des->casillaFinal / 16][des->casillaFinal % 16].color =
        des->colorcapturada;
  } else {
    t[des->casillaFinal / 16][des->casillaFinal % 16].tipo = -1;
    t[des->casillaFinal / 16][des->casillaFinal % 16].color = -1;
  }
}

/**
    * Devuelve 1 si el rey amarillo esta en jaque, en caso contrario
   devuelve
   0.

    *
    * @param b Vector de piezas blancas
    * @param n Vector de piezas negras
    * @param a Vector de piezas amarillas
    * @param r Vector de piezas rojas

    * @param t Matriz que representa el tablero
    */
int amarillasEnJaque(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                     pieza t[16][16]) {
  int i;
  int valor = 0;
  int rey;

  // Encontrar rey amarillo:
  for (i = 0; i < 16; i++)
    if (a[i].tipo == REY)
      rey = a[i].x * 16 + a[i].y;

  for (i = 0; i < 16; i++)
    if ((n[i].tipo > 0 &&
         movimientoValido(n[i].x * 16 + n[i].y, rey, b, n, a, r, t)) ||
        (b[i].tipo > 0 &&
         movimientoValido(b[i].x * 16 + b[i].y, rey, b, n, a, r, t)) ||
        (r[i].tipo > 0 &&
         movimientoValido(r[i].x * 16 + r[i].y, rey, b, n, a, r, t))) {
      valor = 1;
      break;
    }

  return valor;
}

/**
    * Devuelve 1 si el rey negro esta en jaque, en caso contrario devuelve
  *0.
    *
    * @param b Vector de piezas blancas
    * @param n Vector de piezas negras
    * @param a Vector de piezas amarillas
    * @param r Vector de piezas rojas
    * @param t Matriz que representa el tablero
    */
int negrasEnJaque(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                  pieza t[16][16]) {
  int i;
  int valor = 0;
  int rey;

  // Encontrar rey negro:
  for (i = 0; i < 16; i++)
    if (n[i].tipo == REY)
      rey = n[i].x * 16 + n[i].y;

  for (i = 0; i < 16; i++)
    if ((b[i].tipo > 0 &&
         movimientoValido(b[i].x * 16 + b[i].y, rey, b, n, a, r, t)) ||
        (a[i].tipo > 0 &&
         movimientoValido(a[i].x * 16 + a[i].y, rey, b, n, a, r, t)) ||
        (r[i].tipo > 0 &&
         movimientoValido(r[i].x * 16 + r[i].y, rey, b, n, a, r, t))) {
      valor = 1;
      break;
    }

  return valor;
}

/**
    * Devuelve 1 si el rey negro esta en Jaque Master, en caso contrario
  *devuelve 0.
    *
    * @param b Vector de piezas blancas
    * @param n Vector de piezas negras
    * @param a Vector de piezas amarillas
    * @param r Vector de piezas rojas
    * @param t Matriz que representa el tablero
    * @param tur
    */
int negrasEnJaqueMaster(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                        pieza t[16][16], int tur) {
  int i, j, k;
  int valor = 1;
  int rey;

  // Encontrar rey negro
  for (i = 0; i < 16; i++)
    if (n[i].tipo == REY)
      rey = n[i].x * 16 + n[i].y;

  // Buscar si hay alguna casilla en la que se pueda colocar el rey sin que
  // haya jaque
  for (i = 0; i < 16; i++)
    for (j = 0; j < 16; j++)
      if (casillaYTurnoValidos(rey, i * 16 + j, b, n, a, r, t, tur, false))
        valor = 0;

  if (valor == 1) {
    // Buscar si alguna pieza puede hacer un movimiento que libere al rey
    for (i = 0; i < 16; i++)
      if (n[i].tipo != -1)
        for (j = 0; j < 16; j++)
          for (k = 0; k < 16; k++)
            if (casillaYTurnoValidos(n[i].x * 16 + n[i].y, j * 16 + k, b, n, a,
                                     r, t, tur, false))
              valor = 0;
  }

  return valor;
}

/**
* Devuelve 1 si el rey rojo esta en jaque, en caso contrario devuelve 0.
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
*/
int rojasEnJaque(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                 pieza t[16][16]) {
  int i;
  int valor = 0;
  int rey;

  // Encontrar rey rojo:
  for (i = 0; i < 16; i++)
    if (r[i].tipo == REY)
      rey = r[i].x * 16 + r[i].y;

  for (i = 0; i < 16; i++)
    if ((n[i].tipo > 0 &&
         movimientoValido(n[i].x * 16 + n[i].y, rey, b, n, a, r, t)) ||
        (a[i].tipo > 0 &&
         movimientoValido(a[i].x * 16 + a[i].y, rey, b, n, a, r, t)) ||
        (b[i].tipo > 0 &&
         movimientoValido(b[i].x * 16 + b[i].y, rey, b, n, a, r, t))) {
      valor = 1;
      break;
    }

  return valor;
}

/**
* Devuelve 1 si el rey rojo esta en Jaque Máster, en caso contrario devuelve
*0.
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param tur
*/
int rojasEnJaqueMaster(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                       pieza t[16][16], int tur) {
  int i, j, k;
  int valor = 1;
  int rey;

  // Encontrar rey rojo
  for (i = 0; i < 16; i++)
    if (r[i].tipo == REY)
      rey = r[i].x * 16 + r[i].y;

  // Buscar si hay alguna casilla en la que se pueda colocar el rey sin que
  // haya jaque
  for (i = 0; i < 16; i++)
    for (j = 0; j < 16; j++)
      if (casillaYTurnoValidos(rey, i * 16 + j, b, n, a, r, t, tur, false))
        valor = 0;

  // Buscar si alguna pieza puede hacer un movimiento que libere al rey
  if (valor == 1)
    for (i = 0; i < 16; i++)
      if (r[i].tipo != -1)

        for (j = 0; j < 16; j++)

          for (k = 0; k < 16; k++)
            if (casillaYTurnoValidos(r[i].x * 16 + r[i].y, j * 16 + k, b, n, a,
                                     r, t, tur, false))
              valor = 0;

  return valor;
}

/**
* Devuelve 1 si La casilla esta desocupada o esta ocupada por una ficha
*contraria.
*
* @param p
* @param casilla
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param tur
*/
int casillaYTurnoValidos(int p, int casilla, pieza b[16], pieza n[16],
                         pieza a[16], pieza r[16], pieza t[16][16], int tur,
                         bool checkMaster) {
  int xfin, yfin;
  int valor = 1;
  undo des[1];
  xfin = casilla / 16;
  yfin = casilla % 16;

  // Fuera del tablero
  if ((xfin < 0) || (xfin >= 16) || (yfin < 0) || (yfin >= 16) ||
      (t[xfin][yfin].color == (tur + 1)))
    valor = 0;

  // Caso coronacion
  if ((xfin >= 0) && (xfin < 16) && (yfin >= 0) && (yfin < 16) &&
      (t[xfin][yfin].color == (tur + 1)) && (coronando == 1))
    valor = 1;

  if ((valor == 1) && (movimientoValido(p, casilla, b, n, a, r, t)))
    valor = 1;
  else
    valor = 0;

  // Comprobar que no se haga un movimiento que deje al rey en jaque:
  if (valor == 1 && coronando == 0) {
    if (tur == 0) {
      movimientoPrueba(des, p, casilla, b, n, a, r, t);
      if (blancasEnJaque(b, n, a, r, t))
        valor = 0;
      deshacerMovimientoPrueba(des, t);
      if (checkMaster && blancasEnJaqueMaster(b, n, a, r, t, tur))
        valor = 1;
    } else if (tur == 1) {
      movimientoPrueba(des, p, casilla, b, n, a, r, t);
      if (amarillasEnJaque(b, n, a, r, t))
        valor = 0;
      deshacerMovimientoPrueba(des, t);
      if (checkMaster && amarillasEnJaqueMaster(b, n, a, r, t, tur))
        valor = 1;
    } else if (tur == 2) {
      movimientoPrueba(des, p, casilla, b, n, a, r, t);
      if (negrasEnJaque(b, n, a, r, t))
        valor = 0;
      deshacerMovimientoPrueba(des, t);
      if (checkMaster && negrasEnJaqueMaster(b, n, a, r, t, tur))
        valor = 1;
    } else if (tur == 3) {
      movimientoPrueba(des, p, casilla, b, n, a, r, t);
      if (rojasEnJaque(b, n, a, r, t))
        valor = 0;
      deshacerMovimientoPrueba(des, t);
      if (checkMaster && rojasEnJaqueMaster(b, n, a, r, t, tur))
        valor = 1;
    }
  }

  return valor;
}

/**
* Devuelve 1 si el rey amarillo esta en jaque Master, en caso contrario
devuelve 0.
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param tur

*/
int amarillasEnJaqueMaster(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                           pieza t[16][16], int tur) {
  int i, j, k;
  int valor = 1;
  int rey;

  // Encontrar rey amarillo
  for (i = 0; i < 16; i++)
    if (a[i].tipo == REY)
      rey = a[i].x * 16 + a[i].y;

  // Buscar si hay alguna casilla en la que se pueda colocar el rey sin que
  // haya jaque
  for (i = 0; i < 16; i++)
    for (j = 0; j < 16; j++)
      if (casillaYTurnoValidos(rey, i * 16 + j, b, n, a, r, t, tur, false))
        valor = 0;

  // Buscar si alguna pieza puede hacer un movimiento que libere al rey
  if (valor == 1)
    for (i = 0; i < 16; i++)
      if (a[i].tipo != -1)
        for (j = 0; j < 16; j++)
          for (k = 0; k < 16; k++)
            if (casillaYTurnoValidos(a[i].x * 16 + a[i].y, j * 16 + k, b, n, a,
                                     r, t, tur, false))
              valor = 0;

  return valor;
}

/**
* Devuelve 1 si el rey blanco esta en Jaque Master, en caso contrario
*devuelve
*0.
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param a Vector de piezas amarillas
* @param r Vector de piezas rojas
* @param t Matriz que representa el tablero
* @param tur
*/
int blancasEnJaqueMaster(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
                         pieza t[16][16], int tur) {
  int i, j, k;
  int valor = 1;
  int rey;

  // Encontrar rey blanco
  for (i = 0; i < 16; i++)
    if (b[i].tipo == REY)
      rey = b[i].x * 16 + b[i].y;

  // Buscar si hay alguna casilla en la que se pueda colocar el rey sin que
  // haya jaque
  for (i = 0; i < 16; i++)
    for (j = 0; j < 16; j++)
      if (casillaYTurnoValidos(rey, i * 16 + j, b, n, a, r, t, tur, false))
        valor = 0;

  // Buscar si alguna pieza puede hacer un movimiento que libere al rey
  if (valor == 1) {
    for (i = 0; i < 16; i++)
      if (b[i].tipo != -1)
        for (j = 0; j < 16; j++)
          for (k = 0; k < 16; k++)
            if (casillaYTurnoValidos(b[i].x * 16 + b[i].y, j * 16 + k, b, n, a,
                                     r, t, tur, false))
              valor = 0;
  }

  return valor;
}

/**
    * Ejecuta el Master de acuerdo al Convenio del juego
    *
    * @param p1 pieza que realiza el Master
    * @param p2 reino que recibe el Master
    */
void ejecutarMaster(pieza *&p1, pieza *&p2) {
  if (Convenio == REMOCION) {
    for (int i = 0; i < 4; i++) {
      controla[i][p2->color - 1] =
          0; // ningún otro reino controla al reino derrotado
      controla[p2->color - 1][i] =
          0; // el reino derrotado no controla a ningún otro
      amenaza[i][p2->color - 1] =
          0; // ningún otro reino puede capturar piezas del reino derrotado
      amenaza[p2->color - 1][i] = 0; // el reino derrotado no puede capturar
                                     // piezas a ningún otro reino
    }

    if (p2->color == BLANCO)
      for (int i = 0; i < 16; i++) {
        blancas[i].tipo = -1;
        blancas[i].x = -1;
        blancas[i].y = -1;
      }
    else if (p2->color == AMARILLO)
      for (int i = 0; i < 16; i++) {
        amarillas[i].tipo = -1;
        amarillas[i].x = -1;
        amarillas[i].y = -1;
      }
    else if (p2->color == NEGRO)
      for (int i = 0; i < 16; i++) {
        negras[i].tipo = -1;
        negras[i].x = -1;
        negras[i].y = -1;
      }
    else if (p2->color == ROJO)
      for (int i = 0; i < 16; i++) {
        rojas[i].tipo = -1;
        rojas[i].x = -1;
        rojas[i].y = -1;
      }
  } else if (Convenio == PAZ) {
    for (int i = 0; i < 4; i++) {
      controla[i][p2->color - 1] =
          0; // ningún otro reino controla al reino derrotado
      controla[p2->color - 1][i] =
          0; // el reino derrotado no controla a ningún otro
      amenaza[i][p2->color - 1] =
          0; // ningún otro reino puede capturar piezas del reino derrotado
      amenaza[p2->color - 1][i] = 0; // el reino derrotado no puede capturar
                                     // piezas a ningún otro reino
    }
  } else if (Convenio == ASIMILACION) {
    for (int i = 0; i < 4; i++) {
      controla[i][p2->color - 1] =
          0; // ningún otro reino controla al reino derrotado
      controla[p2->color - 1][i] =
          0; // el reino derrotado no controla a ningún otro
      amenaza[i][p2->color - 1] =
          1; // todos los reinos pueden capturar piezas del reino derrotado
      amenaza[p2->color - 1][i] =
          1; // el reino derrotado puede capturar piezas a todos los reinos
    }
    controla[p1->color - 1][p2->color - 1] =
        1; // solo el reino que hizo el Master controla al reino derrotado
    amenaza[p2->color - 1][p2->color - 1] =
        0; // el reino derrotado no se amenaza a si mismo
    amenaza[p2->color - 1][p1->color - 1] =
        0; // el reino derrotado no amenaza al que lo asimilo
    amenaza[p1->color - 1][p2->color - 1] =
        0; // el reino que lo asimilo no lo amenaza

    if (Pacto == ALIANZA) {
      switch (p1->color) {
      case BLANCO:
        amenaza[p2->color - 1][NEGRO - 1] = 0;
        break;
      case AMARILLO:
        amenaza[p2->color - 1][ROJO - 1] = 0;
        break;
      case NEGRO:
        amenaza[p2->color - 1][BLANCO - 1] = 0;
        break;
      case ROJO:
        amenaza[p2->color - 1][AMARILLO - 1] = 0;
        break;
      }
    }

  } else if (Convenio == DEFACTO) {
    for (int i = 0; i < 4; i++) {
      controla[i][p2->color - 1] =
          1; // todos los reinos controlan al reino derrotado
      controla[p2->color - 1][i] =
          0; // el reino derrotado no controla a ningún otro
      amenaza[i][p2->color - 1] =
          1; // todos los reinos pueden capturar piezas del reino derrotado
      amenaza[p2->color - 1][i] =
          1; // el reino derrotado puede capturar piezas a todos los reinos
    }
    controla[p2->color - 1][p2->color - 1] =
        0; // el reino derrotado no se controla a si mismo
    amenaza[p2->color - 1][p2->color - 1] =
        0; // el reino derrotado no se amenaza a si mismo
  }
}

/**
* Realiza el movimiento de la piezaSeleccionada a la casillaSeleccionada.
*
* @param b Vector de piezas blancas
* @param n Vector de piezas negras
* @param r Vector de piezas rojas
* @param a Vector de piezas amarillas
* @param t Matriz que representa el tablero
*/
void movimiento(pieza b[16], pieza n[16], pieza r[16], pieza a[16],
                pieza t[16][16]) {
  int xact, yact, xfin, yfin;
  pieza *p1; // pieza que se va a mover
  pieza *p2; //(posible) pieza contraria en la casilla destino
  pieza *p3; //(posible) peon del reino en la casilla destino (para coronacion)
  int i;

  xact = piezaSeleccionada / 16;
  yact = piezaSeleccionada % 16;
  xfin = casillaSeleccionada / 16;
  yfin = casillaSeleccionada % 16;

  // encontrar pieza a mover
  p1 = NULL;
  for (i = 0; i < 16; i++) {
    if ((b[i].x == xact) && (b[i].y) == yact)
      p1 = &(b[i]);
    if ((n[i].x == xact) && (n[i].y) == yact)
      p1 = &(n[i]);
    if ((a[i].x == xact) && (a[i].y) == yact)
      p1 = &(a[i]);
    if ((r[i].x == xact) && (r[i].y) == yact)
      p1 = &(r[i]);
  }
  if (coronando == 1) {
    for (i = 0; i < 4; i++)
      if ((coronables[i].x == xact) && (coronables[i].y) == yact)
        p1 = &(coronables[i]);
  }

  if (p1 == NULL) {
    std::cout << get_message(curr_lang,
                             "P1 = NULL - NO_SE_HA_SELECCIONADO_PIEZA") << "\n";
    return;
  }

  p2 = NULL;
  for (i = 0; i < 16; i++) {
    if ((b[i].tipo > 0) && (b[i].x == xfin) && (b[i].y) == yfin &&
        b[i].color != p1->color)
      p2 = &(b[i]);
    if ((n[i].tipo > 0) && (n[i].x == xfin) && (n[i].y) == yfin &&
        n[i].color != p1->color)
      p2 = &(n[i]);
    if ((a[i].tipo > 0) && (a[i].x == xfin) && (a[i].y) == yfin &&
        a[i].color != p1->color)
      p2 = &(a[i]);
    if ((r[i].tipo > 0) && (r[i].x == xfin) && (r[i].y) == yfin &&
        r[i].color != p1->color)
      p2 = &(r[i]);
  }

  p3 = NULL;
  for (i = 0; i < 16; i++) {
    if ((b[i].tipo > 0) && (b[i].x == xfin) && (b[i].y) == yfin &&
        b[i].color == p1->color)
      p3 = &(b[i]);
    if ((n[i].tipo > 0) && (n[i].x == xfin) && (n[i].y) == yfin &&
        n[i].color == p1->color)
      p3 = &(n[i]);
    if ((a[i].tipo > 0) && (a[i].x == xfin) && (a[i].y) == yfin &&
        a[i].color == p1->color)
      p3 = &(a[i]);
    if ((r[i].tipo > 0) && (r[i].x == xfin) && (r[i].y) == yfin &&
        r[i].color == p1->color)
      p3 = &(r[i]);
  }

  int coronandoPaso2 = 0;
  if ((coronando == 1) && (t[xfin][yfin].color == colorCoronando))
    coronandoPaso2 = 1;

  if (p2 == NULL && p1->tipo == PEON) {
    switch (p1->color) {
    case BLANCO:
      if (eatenPassantBlanco->isAsignado())
        for (i = 0; i < 16; i++) {
          if ((n[i].tipo > 0) && (n[i].x == eatenPassantBlanco->x) &&
              (n[i].y) == eatenPassantBlanco->y)
            p2 = &(n[i]);
          if ((a[i].tipo > 0) && (a[i].x == eatenPassantBlanco->x) &&
              (a[i].y) == eatenPassantBlanco->y)
            p2 = &(a[i]);
          if ((r[i].tipo > 0) && (r[i].x == eatenPassantBlanco->x) &&
              (r[i].y) == eatenPassantBlanco->y)
            p2 = &(r[i]);
        }
      break;

    case AMARILLO:
      if (eatenPassantAmarillo->isAsignado())
        for (i = 0; i < 16; i++) {
          if ((b[i].tipo > 0) && (b[i].x == eatenPassantAmarillo->x) &&
              (b[i].y) == eatenPassantAmarillo->y)
            p2 = &(b[i]);
          if ((n[i].tipo > 0) && (n[i].x == eatenPassantAmarillo->x) &&
              (n[i].y) == eatenPassantAmarillo->y)
            p2 = &(n[i]);
          if ((r[i].tipo > 0) && (r[i].x == eatenPassantAmarillo->x) &&
              (r[i].y) == eatenPassantAmarillo->y)
            p2 = &(r[i]);
        }
      break;

    case NEGRO:
      if (eatenPassantNegro->isAsignado())
        for (i = 0; i < 16; i++) {
          if ((b[i].tipo > 0) && (b[i].x == eatenPassantNegro->x) &&
              (b[i].y) == eatenPassantNegro->y)
            p2 = &(b[i]);
          if ((a[i].tipo > 0) && (a[i].x == eatenPassantNegro->x) &&
              (a[i].y) == eatenPassantNegro->y)
            p2 = &(a[i]);
          if ((r[i].tipo > 0) && (r[i].x == eatenPassantNegro->x) &&
              (r[i].y) == eatenPassantNegro->y)
            p2 = &(r[i]);
        }
      break;

    case ROJO:
      if (eatenPassantRojo->isAsignado())
        for (i = 0; i < 16; i++) {
          if ((b[i].tipo > 0) && (b[i].x == eatenPassantRojo->x) &&
              (b[i].y) == eatenPassantRojo->y)
            p2 = &(b[i]);
          if ((n[i].tipo > 0) && (n[i].x == eatenPassantRojo->x) &&
              (n[i].y) == eatenPassantRojo->y)
            p2 = &(n[i]);
          if ((a[i].tipo > 0) && (a[i].x == eatenPassantRojo->x) &&
              (a[i].y) == eatenPassantRojo->y)
            p2 = &(a[i]);
        }
      break;
    }
  }

  // eliminar la pieza contraria capturada
  if (p2 != NULL) {
    // Si se come un rey, se ejecuta el Master, de acuerdo al tipo
    // de juego
    if (p2->tipo == REY) {
      ejecutarMaster(p1, p2);
      reyderrotado = p2->color;
    } else
      reyderrotado = -1;

    p2->tipo = -1;
    p2->x = -1;
    p2->y = -1;
    t[xact][yact].tipo = -1;
    t[xact][yact].color = -1;
  } else {
    reyderrotado = -1;
  }

  // Coronacion: cambiar solo el tipo de la pieza destino
  if (p3 != NULL) {
    p3->tipo = p1->tipo;
  }

  // Ya corono: reestablecer piezas a coronar y poner bandera de
  // coronamiento
  // en off
  if (coronandoPaso2 == 1) {

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
    coronando = 0;
  }

  // Pieza destino valida --> mover la pieza
  if ((xfin >= 0) && (xfin < 16) && (yfin >= 0) && (yfin < 16)) {
    if (coronandoPaso2 == 0) {
      p1->x = xfin;
      p1->y = yfin;
      t[xact][yact].tipo = -1;
      t[xact][yact].color = -1;
    }
  }
  // Pieza destino invalida --> eliminar la pieza si no es un rey (por
  // edicion
  // de tablero)
  else if (editando) {
    if (p1->tipo != REY) {
      p1->tipo = -1;
      p1->x = -1;
      p1->y = -1;
      t[xact][yact].tipo = -1;
      t[xact][yact].color = -1;
    }
  }

  // Actualizar si se ha movido el rey
  if (p1->tipo == REY) {
    switch (p1->color) {
    case BLANCO:
      reyBlancoMovido = 1;
      break;

    case NEGRO:
      reyNegroMovido = 1;
      break;

    case AMARILLO:
      reyAmarilloMovido = 1;
      break;

    case ROJO:
      reyRojoMovido = 1;
      break;
    }
    if (enroqueBlancas == TORRED) {
      for (i = 0; i < 16; i++)
        if ((b[i].tipo == TORRE) && (b[i].x == 4) && (b[i].y == 0))
          p2 = &(b[i]);
      if (p2) {
        t[4][0].tipo = -1;
        t[4][0].color = -1;
        p2->x = 7;
        p2->y = 0;
        torreBDMovida = 1;
      }
    }

    else if (enroqueBlancas == TORREI) {
      for (i = 0; i < 16; i++)
        if ((b[i].tipo == TORRE) && (b[i].x == 11) && (b[i].y == 0))
          p2 = &(b[i]);
      if (p2) {
        t[11][0].tipo = -1;
        t[11][0].color = -1;
        p2->x = 9;
        p2->y = 0;
        torreBIMovida = 1;
      }
    }

    if (enroqueAmarillas == TORRED) {
      for (i = 0; i < 16; i++)
        if ((a[i].tipo == TORRE) && (a[i].x == 0) && (a[i].y == 11))
          p2 = &(a[i]);
      if (p2) {
        t[0][11].tipo = -1;
        t[0][11].color = -1;
        p2->x = 0;
        p2->y = 9;
        torreADMovida = 1;
      }
    }

    else if (enroqueAmarillas == TORREI) {
      for (i = 0; i < 16; i++)
        if ((a[i].tipo == TORRE) && (a[i].x == 0) && (a[i].y == 4))
          p2 = &(a[i]);
      if (p2) {
        t[0][4].tipo = -1;
        t[0][4].color = -1;
        p2->x = 0;
        p2->y = 7;
        torreAIMovida = 1;
      }
    }

    if (enroqueNegras == TORRED) {
      for (i = 0; i < 16; i++)
        if ((n[i].tipo == TORRE) && (n[i].x == 11) && (n[i].y == 15))
          p2 = &(n[i]);
      if (p2) {
        t[11][15].tipo = -1;
        t[11][15].color = -1;
        p2->x = 8;
        p2->y = 15;
        torreNDMovida = 1;
      }
    }

    else if (enroqueNegras == TORREI) {
      for (i = 0; i < 16; i++)
        if ((n[i].tipo == TORRE) && (n[i].x == 4) && (n[i].y == 15))
          p2 = &(n[i]);
      if (p2) {
        t[4][15].tipo = -1;
        t[4][15].color = -1;
        p2->x = 6;
        p2->y = 15;
        torreNIMovida = 1;
      }
    }

    if (enroqueRojas == TORRED) {
      for (i = 0; i < 16; i++)
        if ((r[i].tipo == TORRE) && (r[i].x == 15) && (r[i].y == 4))
          p2 = &(r[i]);
      if (p2) {
        t[15][4].tipo = -1;
        t[15][4].color = -1;
        p2->x = 15;
        p2->y = 6;
        torreRDMovida = 1;
      }
    }

    else if (enroqueRojas == TORREI) {
      for (i = 0; i < 16; i++)
        if ((r[i].tipo == TORRE) && (r[i].x == 15) && (r[i].y == 11))
          p2 = &(r[i]);
      if (p2) {
        t[15][11].tipo = -1;
        t[15][11].color = -1;
        p2->x = 15;
        p2->y = 8;
        torreRIMovida = 1;
      }
    }
  }

  // Actualizar si se ha movido alguna torre
  if (p1->tipo == TORRE) {
    switch (p1->color) {
    case BLANCO:
      if (p1->x == 4)
        torreBDMovida = 1;
      else if (p1->x == 11)
        torreBIMovida = 1;
      break;

    case NEGRO:
      if (p1->x == 4)
        torreNIMovida = 1;
      else if (p1->x == 11)
        torreNDMovida = 1;
      break;

    case AMARILLO:
      if (p1->y == 4)
        torreAIMovida = 1;
      else if (p1->y == 11)
        torreADMovida = 1;
      break;

    case ROJO:
      if (p1->y == 4)
        torreRDMovida = 1;
      else if (p1->y == 11)
        torreRIMovida = 1;
      break;
    }
  }

  piezaSeleccionada = -1;

  actualizarTablero(b, n, r, a, t);
}

/**
* retorna cierto si el turnoActual es aliado
*
* @param turnoActual
*/
int aliado(int turnoActual) {
  if (turnoActual == 0)
    return 2;
  if (turnoActual == 1)
    return 3;
  if (turnoActual == 2)
    return 0;
  if (turnoActual == 3)
    return 1;

  return -1;
}

/**
* Funcion que devuelve el siguiente turno de acuerdo a las reglas
* de Masterdrez
*
* @param turnoActual
*/
int calcular_turno(int turnoActual) {
  int turnoNuevo = -1;

  if (Pacto == AISLADO) {
    turnoNuevo = (turnoActual + 1) % 4;
    while (!activo(turnoNuevo) || inmovilizado(turnoNuevo))
      turnoNuevo = (turnoNuevo + 1) % 4;
    return turnoNuevo;
  }

  if (Pacto == ALIANZA) {
    int activos = activo(0) + activo(1) + activo(2) + activo(3);
    if (activos == 2 || activos == 4) {
      turnoNuevo = (turnoActual + 1) % 4;
      while (!activo(turnoNuevo) || inmovilizado(turnoNuevo))
        turnoNuevo = (turnoNuevo + 1) % 4;
      return turnoNuevo;
    }

    if (activos == 3) {
      // Calculo del reino que juega solo
      int reino_solitario = -1;
      if (activo(0) && activo(2)) {
        if (activo(1))
          reino_solitario = 1;
        else
          reino_solitario = 3;
      }
      if (activo(1) && activo(3)) {
        if (activo(0))
          reino_solitario = 0;
        else
          reino_solitario = 2;
      }

      if (turnoActual == reino_solitario) {
        if (reino_solitario == 0 || reino_solitario == 2) {
          if (amarillasEnJaque(blancas, negras, amarillas, rojas, tablero)) {
            jaquePase = 1;
            return 1;
          }
          if (rojasEnJaque(blancas, negras, amarillas, rojas, tablero)) {
            jaquePase = 1;
            return 3;
          }

        } else if (reino_solitario == 1 || reino_solitario == 3) {
          if (blancasEnJaque(blancas, negras, amarillas, rojas, tablero)) {
            turnoNuevo = 0;
            jaquePase = 1;
            return turnoNuevo;
          }
          if (negrasEnJaque(blancas, negras, amarillas, rojas, tablero)) {
            turnoNuevo = 2;
            jaquePase = 1;
            return turnoNuevo;
          }
        }

        // Si no salio por ningúno de los anteriores
        // no hay jaque a ningúno de los aliados
        // haga movimiento en V
        turnoNuevo = aliado(turnoRetorno);
        turnoRetorno = turnoNuevo;
        return turnoNuevo;
      }
      // turno de uno de los reinos aliados
      else {
        if (jaquePase == 1) {
          turnoNuevo = aliado(turnoActual);
          turnoRetorno = turnoNuevo;
          jaquePase = 0;
          return turnoNuevo;
        }

        // Si no hay jaque-pase, haga movimiento en V
        turnoNuevo = reino_solitario;
        turnoRetorno = turnoActual;
        return turnoNuevo;
      }
    }
  }

  return -1;
}

int elegir_apertura() {
  int apertura = mtRandom.randInt() % 3; // entre 0 y 2. (3 aperturas posibles).
  return apertura;
}

#endif // MASTERDREZMOVIMIENTOS
