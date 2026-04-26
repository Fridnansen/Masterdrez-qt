#ifndef MASTERDREZAPERTURAS
#define MASTERDREZAPERTURAS


//=================================================
// apertura de peones centrales cerrada
void apertura_peonescentrales_amarillas(int num_movimientos,int v=rand()%6) {
           // Apertura con enroque largo
    int a[6]= {12,12,12,12,11,11};
    int b[6]= { 8, 8, 8, 8, 7, 7};
    int c[6]= { 9, 9,11,11, 9, 9};
    int d[6]= { 5, 5, 7, 7, 5, 5};
    int e[6]= { 2, 3, 3, 2, 2, 3};
    int f[6]= { 2, 2, 3, 3, 2, 2};

  switch (num_movimientos) {
  case 1: // peon
    piezaSeleccionada = amarillas[a[v]].x * 16 + amarillas[a[v]].y;
    casillaSeleccionada = e[v] * 16 + b[v];
    break;

  case 2:  // Dama
      piezaSeleccionada = amarillas[3].x * 16 + amarillas[3].y;
      casillaSeleccionada = 1 * 16 + b[v];
      break;

  case 3:// caballo de rey
      piezaSeleccionada = amarillas[6].x * 16 + amarillas[6].y;
      casillaSeleccionada = 2 * 16 + 9;
      break;

  case 4: // peon de caballo de reina
    piezaSeleccionada = amarillas[c[v]].x * 16 + amarillas[c[v]].y;
    casillaSeleccionada = f[v] * 16 + d[v];
    break;

  case 5: // alfil de reina
    piezaSeleccionada = amarillas[2].x * 16 + amarillas[2].y;
    casillaSeleccionada = 1 * 16 + d[v];
    break;

  case 6: // caballo de reina
    piezaSeleccionada = amarillas[1].x * 16 + amarillas[1].y;
    casillaSeleccionada = 2 * 16 + 6;
    break;

  case 7: // enroque largo
      piezaSeleccionada = amarillas[4].x * 16 + amarillas[4].y;
      casillaSeleccionada = 0 * 16 + 6;
      enroqueAmarillas = TORREI;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

void apertura_peonescentrales_negras(int num_movimientos) {
  switch (num_movimientos) {
  case 1: // peon de rey
    piezaSeleccionada = negras[11].x * 16 + negras[11].y;
    casillaSeleccionada = 7 * 16 + 13;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = negras[1].x * 16 + negras[1].y;
    casillaSeleccionada = 6 * 16 + 13;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = negras[2].x * 16 + negras[2].y;
    casillaSeleccionada = 7 * 16 + 14;
    break;

  case 4: // enroque corto
    piezaSeleccionada = negras[3].x * 16 + negras[3].y;
    casillaSeleccionada = 5 * 16 + 15;
    enroqueNegras = TORREI;
    break;

  case 5: // peon de reina
    piezaSeleccionada = negras[12].x * 16 + negras[12].y;
    casillaSeleccionada = 8 * 16 + 13;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = negras[6].x * 16 + negras[6].y;
    casillaSeleccionada = 9 * 16 + 13;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = negras[5].x * 16 + negras[5].y;
    casillaSeleccionada = 8 * 16 + 14;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

void apertura_peonescentrales_rojas(int num_movimientos, int u=rand()%8) {
         // Aperturas con enroque corto
  int h[8]= {9, 9,11,11,11,11,11,11};
  int j[8]= {5, 5, 7, 7, 7, 7, 7, 7};
  int p[8]= {12,14,14,14,12,12,12,12};
  int q[8]= {8,10,10,10, 8, 8, 8, 8};
  int n[8]= {13,13,13,12,13,13,12,12};
  int r[8]= {13,13,13,13,13,12,13,12};

  switch (num_movimientos) {
  case 1: // peon
    piezaSeleccionada = rojas[h[u]].x * 16 + rojas[h[u]].y;
    casillaSeleccionada = n[u] * 16 + j[u];
    break;

  case 2: // caballo de rey
    piezaSeleccionada = rojas[1].x * 16 + rojas[1].y;
    casillaSeleccionada = 13 * 16 + 6;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = rojas[2].x * 16 + rojas[2].y;
    casillaSeleccionada = 14 * 16 + j[u];
    break;

  case 4: // caballo de reina
    piezaSeleccionada = rojas[6].x * 16 + rojas[6].y;
    casillaSeleccionada = 13 * 16 + 9;
    break;

  case 5: // peon
    piezaSeleccionada = rojas[p[u]].x * 16 + rojas[p[u]].y;
    casillaSeleccionada = r [u]* 16 + q[u];
    break;

  case 6: // alfil de reina
    piezaSeleccionada = rojas[5].x * 16 + rojas[5].y;
    casillaSeleccionada = 14 * 16 + q[u];
    break;

  case 7: // enroque corto
     piezaSeleccionada = rojas[3].x * 16 + rojas[3].y;
     casillaSeleccionada = 15 * 16 + 5;
     enroqueRojas = TORRED;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

//=================================================
// apertura fianchetto simple


//void apertura_fianchetto_simple_amarillas(int num_movimientos) {
    /* Aperturas con enroque corto amaillas
  int a[8]= {14,14,12,12,12,12,12,12};
  int b[8]= {10,10, 8, 8, 8, 8, 8, 8};
  int c[8]= {11, 9, 9, 9,11,11,11,11};
  int d[8]= { 7, 5, 5, 5, 7, 7, 7, 7};
  int e[8]= { 2, 2, 2, 3, 2, 2, 3, 3};
  int f[8]= { 2, 2, 2, 2, 2, 3, 2, 3}; */

  /*switch (num_movimientos) {
  case 1: // peon de caballo de rey
    piezaSeleccionada = amarillas[a[3]].x * 16 + amarillas[a[3]].y;
    casillaSeleccionada = e[3] * 16 + b[3];
    break;

  case 2: // caballo de rey
    piezaSeleccionada = amarillas[6].x * 16 + amarillas[6].y;
    casillaSeleccionada = 2 * 16 + 9;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = amarillas[5].x * 16 + amarillas[5].y;
    casillaSeleccionada = 1 * 16 + b[3];
    break;

  case 4: // enroque corto
    piezaSeleccionada = amarillas[4].x * 16 + amarillas[4].y;
    casillaSeleccionada = 0 * 16 + 10;
    enroqueAmarillas = TORRED;
    break;

  case 5: // peon de reina
    piezaSeleccionada = amarillas[c[3]].x * 16 + amarillas[c[3]].y;
    casillaSeleccionada = f[3] * 16 + d[3];
    break;

  case 6: // caballo de reina
    piezaSeleccionada = amarillas[1].x * 16 + amarillas[1].y;
    casillaSeleccionada = 2 * 16 + 6;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = amarillas[2].x * 16 + amarillas[2].y;
    casillaSeleccionada = 1 * 16 + d[3];
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}*/

void apertura_fianchetto_simple_negras(int num_movimientos) {

  switch (num_movimientos) {
  case 1: // peon de caballo de rey
    piezaSeleccionada = negras[9].x * 16 + negras[9].y;
    casillaSeleccionada = 5 * 16 + 13;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = negras[1].x * 16 + negras[1].y;
    casillaSeleccionada = 6 * 16 + 13;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = negras[2].x * 16 + negras[2].y;
    casillaSeleccionada = 5 * 16 + 14;
    break;

  case 4: // enroque corto
    piezaSeleccionada = negras[3].x * 16 + negras[3].y;
    casillaSeleccionada = 5 * 16 + 15;
    enroqueNegras = TORREI;
    break;

  case 5: // peon de reina
    piezaSeleccionada = negras[12].x * 16 + negras[12].y;
    casillaSeleccionada = 8 * 16 + 13;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = negras[6].x * 16 + negras[6].y;
    casillaSeleccionada = 9 * 16 + 13;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = negras[5].x * 16 + negras[5].y;
    casillaSeleccionada = 8 * 16 + 14;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

void apertura_fianchetto_simple_rojas(int num_movimientos) {
  switch (num_movimientos) {
  case 1: // peon de caballo de rey
    piezaSeleccionada = rojas[9].x * 16 + rojas[9].y;
    casillaSeleccionada = 13 * 16 + 5;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = rojas[1].x * 16 + rojas[1].y;
    casillaSeleccionada = 13 * 16 + 6;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = rojas[2].x * 16 + rojas[2].y;
    casillaSeleccionada = 14 * 16 + 5;
    break;

  case 4: // enroque corto
    piezaSeleccionada = rojas[3].x * 16 + rojas[3].y;
    casillaSeleccionada = 15 * 16 + 5;
    enroqueRojas = TORRED;
    break;

  case 5: // peon de reina
    piezaSeleccionada = rojas[12].x * 16 + rojas[12].y;
    casillaSeleccionada = 13 * 16 + 8;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = rojas[6].x * 16 + rojas[6].y;
    casillaSeleccionada = 13 * 16 + 9;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = rojas[5].x * 16 + rojas[5].y;
    casillaSeleccionada = 14 * 16 + 8;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

//=================================================
// apertura fianchetto doble
void apertura_Fianchetto_x2_Amarillas(int num_movimientos) {

  switch (num_movimientos) {
  case 1: // peon de caballo de rey
    piezaSeleccionada = amarillas[14].x * 16 + amarillas[14].y;
    casillaSeleccionada = 2 * 16 + 10;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = amarillas[6].x * 16 + amarillas[6].y;
    casillaSeleccionada = 2 * 16 + 9;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = amarillas[5].x * 16 + amarillas[5].y;
    casillaSeleccionada = 1 * 16 + 10;
    break;

  case 4: // enroque corto
    piezaSeleccionada = amarillas[4].x * 16 + amarillas[4].y;
    casillaSeleccionada = 0 * 16 + 10;
    enroqueAmarillas = TORRED;
    break;

  case 5: // peon de caballo de reina
    piezaSeleccionada = amarillas[9].x * 16 + amarillas[9].y;
    casillaSeleccionada = 2 * 16 + 5;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = amarillas[1].x * 16 + amarillas[1].y;
    casillaSeleccionada = 2 * 16 + 6;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = amarillas[2].x * 16 + amarillas[2].y;
    casillaSeleccionada = 1 * 16 + 5;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

void apertura_Fianchetto_x2_Negras(int num_movimientos, int t=rand()%7) {
       // Aperturas sin enroque
  int g[7]= { 9, 9, 9,11,11,11, 9};
  int i[7]= {14,14,12,14,14,14,14};
  int k[7]= { 5, 5, 5, 7, 7, 7, 5};
  int l[7]= {10,10, 8,10,10,10,10};
  int m[7]= {12, 8, 8, 8,12,13,11};
  int o[7]= { 8, 4, 4, 4, 8, 9, 7};

  switch (num_movimientos) {
  case 1: // peon de caballo de rey
    piezaSeleccionada = negras[g[t]].x * 16 + negras[g[t]].y;
    casillaSeleccionada = k[t] * 16 + 13;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = negras[1].x * 16 + negras[1].y;
    casillaSeleccionada = 6 * 16 + 13;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = negras[2].x * 16 + negras[2].y;
    casillaSeleccionada = k[t] * 16 + 14;
    break;

  case 4: // peon
    piezaSeleccionada = negras[m[t]].x * 16 + negras[m[t]].y;
    casillaSeleccionada = o[t] * 16 + 12;
    //enroqueNegras = TORREI;
    break;

  case 5: // peon de caballo de reina
    piezaSeleccionada = negras[i[t]].x * 16 + negras[i[t]].y;
    casillaSeleccionada = l[t] * 16 + 13;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = negras[5].x * 16 + negras[5].y;
    casillaSeleccionada = l[t] * 16 + 14;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = negras[6].x * 16 + negras[6].y;
    casillaSeleccionada = 9 * 16 + 13;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

void apertura_Fianchetto_x2_Rojas(int num_movimientos) {

    switch (num_movimientos) {
    case 1: // peon de caballo de rey
        piezaSeleccionada = rojas[9].x * 16 + rojas[9].y;
        casillaSeleccionada = 13 * 16 + 5;
        break;

    case 2: // caballo de rey
        piezaSeleccionada = rojas[1].x * 16 + rojas[1].y;
        casillaSeleccionada = 13 * 16 + 6;
        break;

    case 3: // alfil de rey
        piezaSeleccionada = rojas[2].x * 16 + rojas[2].y;
        casillaSeleccionada = 14 * 16 + 5;
        break;

    case 4: // enroque corto
        piezaSeleccionada = rojas[3].x * 16 + rojas[3].y;
        casillaSeleccionada = 15 * 16 + 5;
        enroqueRojas = TORRED;
        break;

    case 5: // peon de caballo de reina
        piezaSeleccionada = rojas[14].x * 16 + rojas[14].y;
        casillaSeleccionada = 13 * 16 + 10;
        break;

    case 6: // caballo de reina
        piezaSeleccionada = rojas[6].x * 16 + rojas[6].y;
        casillaSeleccionada = 13 * 16 + 9;
        break;

    case 7: // alfil de reina
        piezaSeleccionada = rojas[5].x * 16 + rojas[5].y;
        casillaSeleccionada = 14 * 16 + 10;
        break;

    default:
        return;
    }

    // Se ejecuta el movimiento...
    movimiento(blancas, negras, rojas, amarillas, tablero);
}

//=================================================
// apertura de peones centrales cerrada
void apertura_peones_amarillas(int num_movimientos) {

  switch (num_movimientos) {
  case 1: // peon de rey
    piezaSeleccionada = amarillas[12].x * 16 + amarillas[12].y;
    casillaSeleccionada = 3 * 16 + 8;
    break;
  case 2: // caballo de rey
    piezaSeleccionada = amarillas[6].x * 16 + amarillas[6].y;
    casillaSeleccionada = 2 * 16 + 9;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = amarillas[5].x * 16 + amarillas[5].y;
    casillaSeleccionada = 1 * 16 + 8;
    break;

  case 4: // enroque corto
    piezaSeleccionada = amarillas[4].x * 16 + amarillas[4].y;
    casillaSeleccionada = 0 * 16 + 10;
    enroqueAmarillas = TORRED;
    break;

  case 5: // peon de reina
    piezaSeleccionada = amarillas[11].x * 16 + amarillas[11].y;
    casillaSeleccionada = 3 * 16 + 7;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = amarillas[1].x * 16 + amarillas[1].y;
    casillaSeleccionada = 2 * 16 + 6;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = amarillas[2].x * 16 + amarillas[2].y;
    casillaSeleccionada = 1 * 16 + 7;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

void apertura_peones_negras(int num_movimientos) {
  switch (num_movimientos) {
  case 1: // peon de rey
    piezaSeleccionada = negras[11].x * 16 + negras[11].y;
    casillaSeleccionada = 7 * 16 + 13;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = negras[1].x * 16 + negras[1].y;
    casillaSeleccionada = 6 * 16 + 13;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = negras[2].x * 16 + negras[2].y;
    casillaSeleccionada = 7 * 16 + 14;
    break;

  case 4: // enroque corto
    piezaSeleccionada = negras[3].x * 16 + negras[3].y;
    casillaSeleccionada = 5 * 16 + 15;
    enroqueNegras = TORREI;
    break;

  case 5: // peon de reina
    piezaSeleccionada = negras[12].x * 16 + negras[12].y;
    casillaSeleccionada = 8 * 16 + 13;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = negras[6].x * 16 + negras[6].y;
    casillaSeleccionada = 9 * 16 + 13;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = negras[5].x * 16 + negras[5].y;
    casillaSeleccionada = 8 * 16 + 14;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

void apertura_peones_rojas(int num_movimientos) {

  switch (num_movimientos) {
  case 1: // peon de rey
    piezaSeleccionada = rojas[11].x * 16 + rojas[11].y;
    casillaSeleccionada = 13 * 16 + 7;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = rojas[1].x * 16 + rojas[1].y;
    casillaSeleccionada = 13 * 16 + 6;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = rojas[2].x * 16 + rojas[2].y;
    casillaSeleccionada = 14 * 16 + 7;
    break;

  case 4: // enroque corto
    piezaSeleccionada = rojas[3].x * 16 + rojas[3].y;
    casillaSeleccionada = 15 * 16 + 5;
    enroqueRojas = TORRED;
    break;

  case 5: // peon de reina
    piezaSeleccionada = rojas[12].x * 16 + rojas[12].y;
    casillaSeleccionada = 13 * 16 + 8;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = rojas[6].x * 16 + rojas[6].y;
    casillaSeleccionada = 13 * 16 + 9;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = rojas[5].x * 16 + rojas[5].y;
    casillaSeleccionada = 14 * 16 + 8;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

//=================================================
// apertura fianchetto simple
/*
void apertura_fianchetto_simple_amarillas(int num_movimientos) {

  switch (num_movimientos) {
  case 1: // peon de caballo de rey
    piezaSeleccionada = amarillas[14].x * 16 + amarillas[14].y;
    casillaSeleccionada = 2 * 16 + 10;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = amarillas[6].x * 16 + amarillas[6].y;
    casillaSeleccionada = 2 * 16 + 9;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = amarillas[5].x * 16 + amarillas[5].y;
    casillaSeleccionada = 1 * 16 + 10;
    break;

  case 4: // enroque corto
    piezaSeleccionada = amarillas[4].x * 16 + amarillas[4].y;
    casillaSeleccionada = 0 * 16 + 10;
    enroqueAmarillas = TORRED;
    break;

  case 5: // peon de reina
    piezaSeleccionada = amarillas[11].x * 16 + amarillas[11].y;
    casillaSeleccionada = 2 * 16 + 7;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = amarillas[1].x * 16 + amarillas[1].y;
    casillaSeleccionada = 2 * 16 + 6;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = amarillas[2].x * 16 + amarillas[2].y;
    casillaSeleccionada = 1 * 16 + 7;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

void apertura_fianchetto_simple_negras(int num_movimientos) {

  switch (num_movimientos) {
  case 1: // peon de caballo de rey
    piezaSeleccionada = negras[9].x * 16 + negras[9].y;
    casillaSeleccionada = 5 * 16 + 13;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = negras[1].x * 16 + negras[1].y;
    casillaSeleccionada = 6 * 16 + 13;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = negras[2].x * 16 + negras[2].y;
    casillaSeleccionada = 5 * 16 + 14;
    break;

  case 4: // enroque corto
    piezaSeleccionada = negras[3].x * 16 + negras[3].y;
    casillaSeleccionada = 5 * 16 + 15;
    enroqueNegras = TORREI;
    break;

  case 5: // peon de reina
    piezaSeleccionada = negras[12].x * 16 + negras[12].y;
    casillaSeleccionada = 8 * 16 + 13;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = negras[6].x * 16 + negras[6].y;
    casillaSeleccionada = 9 * 16 + 13;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = negras[5].x * 16 + negras[5].y;
    casillaSeleccionada = 8 * 16 + 14;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}

void apertura_fianchetto_simple_rojas(int num_movimientos) {
  switch (num_movimientos) {
  case 1: // peon de caballo de rey
    piezaSeleccionada = rojas[9].x * 16 + rojas[9].y;
    casillaSeleccionada = 13 * 16 + 5;
    break;

  case 2: // caballo de rey
    piezaSeleccionada = rojas[1].x * 16 + rojas[1].y;
    casillaSeleccionada = 13 * 16 + 6;
    break;

  case 3: // alfil de rey
    piezaSeleccionada = rojas[2].x * 16 + rojas[2].y;
    casillaSeleccionada = 14 * 16 + 5;
    break;

  case 4: // enroque corto
    piezaSeleccionada = rojas[3].x * 16 + rojas[3].y;
    casillaSeleccionada = 15 * 16 + 5;
    enroqueRojas = TORRED;
    break;

  case 5: // peon de reina
    piezaSeleccionada = rojas[12].x * 16 + rojas[12].y;
    casillaSeleccionada = 13 * 16 + 8;
    break;

  case 6: // caballo de reina
    piezaSeleccionada = rojas[6].x * 16 + rojas[6].y;
    casillaSeleccionada = 13 * 16 + 9;
    break;

  case 7: // alfil de reina
    piezaSeleccionada = rojas[5].x * 16 + rojas[5].y;
    casillaSeleccionada = 14 * 16 + 8;
    break;

  default:
    return;
  }

  // Se ejecuta el movimiento...
  movimiento(blancas, negras, rojas, amarillas, tablero);
}*/
#endif // MASTERDREZAPERTURAS
