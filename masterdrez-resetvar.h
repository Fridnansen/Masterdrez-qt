#ifndef MASTERDREZRESETVAR
#define MASTERDREZRESETVAR

/**
* Pone en 0 todas las variables de soplo
*
*/
void resetSoplos() {
  for (int i = 0; i < 16; i++) {
    soploBlancas[i] = 0;
    soploAmarillas[i] = 0;
    soploNegras[i] = 0;
    soploRojas[i] = 0;
  }
}

/**
* Ajusta todas las variables de estado a sus valores iniciales
*
*/
void resetVariablesEstado() {
  piezasColocadas = 0;
  partidaComenzada = 0;
  partidaHM = 0; // 1
  editando = 0;
  editado = 0;
  seleccionandoPieza = 0;
  seleccionandoCasilla = 0;
  turno = 0;
  piezaSeleccionada = -1;
  casillaSeleccionada = -1;
  casillaSeleccionadaActualmente = -1;
  jaqueBlancas = 0;
  jaqueNegras = 0;
  jaqueAmarillas = 0;
  jaqueRojas = 0;
  enroqueBlancas = -1;
  enroqueNegras = -1;
  enroqueAmarillas = -1;
  enroqueRojas = -1;
  reyBlancoMovido = 0;
  reyNegroMovido = 0;
  reyAmarilloMovido = 0;
  reyRojoMovido = 0;
  torreBIMovida = 0;
  torreBDMovida = 0;
  torreNIMovida = 0;
  torreNDMovida = 0;
  torreAIMovida = 0;
  torreADMovida = 0;
  torreRIMovida = 0;
  torreRDMovida = 0;
  MasterBlancas = 0;
  MasterNegras = 0;
  MasterAmarillas = 0;
  MasterRojas = 0;
  blancasInmovilizadas = 0;
  negrasInmovilizadas = 0;
  amarillasInmovilizadas = 0;
  rojasInmovilizadas = 0;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        controla[i][j] = 1;
        amenaza[i][j] = 0;
      } else {
        controla[i][j] = 0;
        amenaza[i][j] = 1;
      }
    }

  if (Pacto == ALIANZA) {
    amenaza[0][2] = 0;
    amenaza[2][0] = 0;
    amenaza[1][3] = 0;
    amenaza[3][1] = 0;
  }

  resetSoplos();

  num_movimientos_amarillas = 0;
  num_movimientos_negras = 0;
  num_movimientos_rojas = 0;
}

#endif // MASTERDREZRESETVAR
