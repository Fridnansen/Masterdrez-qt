#ifndef MASTERDREZAXIOMAS
#define MASTERDREZAXIOMAS

int mastertablas(pieza b[16], pieza n[16], pieza a[16], pieza r[16]) {
  int activos = 0;
  int inmovilizados = 0;
  for (int i = 0; i < 4; i++)
    if (activo(i)) {
      activos++;
      if (inmovilizado(i))
        inmovilizados++;
    }

  // Existe la posibilidad de mastertablas solo si hay 4 reinos activos
  if (activos == 4) {
    // Si 3 reinos estan inmovilizados: mastertablas
    if (inmovilizados == 3)
      return 1;

    // si solo quedan los 4 reyes en el tablero: mastertablas
    int reyes_solos = 0;
    if (piezas_activas(b, n, a, r, controla, BLANCO) == 1)
      reyes_solos++;
    if (piezas_activas(b, n, a, r, controla, NEGRO) == 1)
      reyes_solos++;
    if (piezas_activas(b, n, a, r, controla, AMARILLO) == 1)
      reyes_solos++;
    if (piezas_activas(b, n, a, r, controla, ROJO) == 1)
      reyes_solos++;
    if (reyes_solos == 4)
      return 1;
  }

  return 0;
}

int tritablas(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
              int mcontrola[4][4]) {
  int activos = 0;
  int inmovilizados = 0;
  for (int i = 0; i < 4; i++)
    if (activo(i)) {
      activos++;
      if (inmovilizado(i))
        inmovilizados++;
    }

  // Existe la posibilidad de mastertablas solo si hay 3 reinos activos
  if (activos == 3) {
    // Si 2 reinos estan inmovilizados: tritablas
    if (inmovilizados == 2)
      return 1;

    // si solo quedan los 3 reyes en el tablero: tritablas
    int reyes_solos = 0;
    if (piezas_activas(b, n, a, r, mcontrola, BLANCO) == 1)
      reyes_solos++;
    if (piezas_activas(b, n, a, r, mcontrola, NEGRO) == 1)
      reyes_solos++;
    if (piezas_activas(b, n, a, r, mcontrola, AMARILLO) == 1)
      reyes_solos++;
    if (piezas_activas(b, n, a, r, mcontrola, ROJO) == 1)
      reyes_solos++;
    if (reyes_solos == 3)
      return 1;
  }

  return 0;
}

int tablas(pieza b[16], pieza n[16], pieza a[16], pieza r[16],
           int mcontrola[4][4], int PactoJuego) {
  int activos = 0;
  int inmovilizados = 0;

  for (int i = 0; i < 4; i++)
    if (activo(i)) {
      activos++;
      if (inmovilizado(i))
        inmovilizados++;
    }

  if ((activos == 2) && ((PactoJuego == AISLADO) || (activo(0) && activo(1)) ||
                         (activo(0) && activo(3)) || (activo(2) && activo(1)) ||
                         (activo(2) && activo(3)))) {
    int activas[4];
    activas[0] = piezas_activas(b, n, a, r, mcontrola, BLANCO);
    activas[1] = piezas_activas(b, n, a, r, mcontrola, AMARILLO);
    activas[2] = piezas_activas(b, n, a, r, mcontrola, NEGRO);
    activas[3] = piezas_activas(b, n, a, r, mcontrola, ROJO);

    int reino_activo[2] = {-1, -1};
    for (int i = 0; i < 4; i++)
      if (activo(i) > 0) {
        if (reino_activo[0] == -1)
          reino_activo[0] = i;
        else if (reino_activo[1] == -1)
          reino_activo[1] = i;
      }

    // condicion 1: solo los reyes
    if (activas[reino_activo[0]] == 1 && activas[reino_activo[1]] == 1)
      return 1;

    int caballos_activos[2];
    caballos_activos[0] =
        piezas_activas(b, n, a, r, mcontrola, reino_activo[0] + 1, CABALLO);
    caballos_activos[1] =
        piezas_activas(b, n, a, r, mcontrola, reino_activo[1] + 1, CABALLO);

    int alfiles_activos[2];
    alfiles_activos[0] =
        piezas_activas(b, n, a, r, mcontrola, reino_activo[0] + 1, ALFIL);
    alfiles_activos[1] =
        piezas_activas(b, n, a, r, mcontrola, reino_activo[1] + 1, ALFIL);

    // condicion 2: reino inmovilizado
    if (inmovilizado(reino_activo[0]) || inmovilizado(reino_activo[1]))
      return 1;

    // condicion 2: reino1(rey, caballo) - reino2(rey)
    if (activas[reino_activo[0]] == 2 && caballos_activos[0] == 1 &&
        activas[reino_activo[1]] == 1)
      return 1;

    // condicion 3: reino1(rey, alfil) - reino2(rey)
    if (activas[reino_activo[0]] == 2 && alfiles_activos[0] == 1 &&
        activas[reino_activo[1]] == 1)
      return 1;

    // condicion 2: reino1(rey) - reino2(rey, caballo)
    if (activas[reino_activo[1]] == 2 && caballos_activos[1] == 1 &&
        activas[reino_activo[0]] == 1)
      return 1;

    // condicion 3: reino1(rey) - reino2(rey, alfil)
    if (activas[reino_activo[1]] == 2 && alfiles_activos[1] == 1 &&
        activas[reino_activo[0]] == 1)
      return 1;
  }

  return 0;
}

/**
* Devuelve 0 si el reino ya no esta activo (rey derrotado).
*
* @param turno reino de turno
*/
int activo(int turno) {
  if (controla[turno][turno] == 1)
    return 1;

  return 0;
}

int partida_ganada(int PactoJuego) {
  int activos = 0;

  for (int i = 0; i < 4; i++)
    if (activo(i)) {
      activos++;
    }

  if (PactoJuego == AISLADO) {
    if (activos == 1)
      return 1;
  }

  if (PactoJuego == ALIANZA) {
    if (activos == 1)
      return 1;

    if (activos == 2) {
      if (activo(0) && activo(2))
        return 1;
      if (activo(1) && activo(3))
        return 1;
    }
  }

  return 0;
}

#endif // MASTERDREZAXIOMAS
