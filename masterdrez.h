#ifndef MASTERDREZ
#define MASTERDREZ

#include "tinyxml2.h"
#include <iostream>
#include "mtrand.h"

typedef enum {
  peones_centrales,
  peones,
  fianchetto_simple,
  fianchetto_doble
} aperturas;

enum valorPieza {
  PEON = 100,
  CABALLO = 325,
  ALFIL = 350,
  TORRE = 500,
  DAMA = 900,
  REY = 99999 // infinito.
};

enum colorPieza { BLANCO = 1, AMARILLO, NEGRO, ROJO };

enum torres { TORREI = 1, TORRED };

enum convenio { PAZ = 1, ASIMILACION, REMOCION, DEFACTO };

enum pacto { AISLADO = 1, ALIANZA };

enum idiomas { LANG_ES, LANG_EN };

//====================================================================================

class t_masterdrez {

public:
  /*Estructura de pieza de ajedrez*/
  typedef struct {
    int tipo;
    int color;
    int x;
    int y;
  } pieza;

  /*Estructura de Peon al paso*/
  struct passant {
  public:
    int x;
    int y;
    passant() : x(-1), y(-1) {}
    void noAsignar() {
      x = -1;
      y = -1;
    }
    void Asignar(int x, int y) {
      this->x = x;
      this->y = y;
    }
    bool isPassant(int x, int y) { return this->x == x && this->y == y; }
    bool isAsignado() { return (this->x != -1) && (this->y != -1); }
    void getPos(int &xext, int &yext) {
      xext = x;
      yext = y;
    }
  };

  /*Estructura para almacenar los cambios a deshacer tras un movimiento de
   * prueba*/
  typedef struct {
    int tipo; // tipo de la pieza cambiada.
    int color;
    int casillaInicial; // casilla de la pieza cambiada inicialmente.
    int casillaFinal;   // casilla de la pieza cambiada finalmente.
    pieza *p1;          // puntero a la pieza cambiada;
    pieza *p2;          // puntero a la pieza capturada;
    int capturada;      // 0 si no se ha capturado ningúna pieza.
    int tipocapturada;  // tipo de la pieza capturada.
    int colorcapturada; // color de la pieza capturada.
  } undo;

  int piezasColocadas = 0;
  int partidaComenzada = 0;
  int partidaHM = 0; // 1
  int editando = 0;
  int editado = 0;
  int seleccionandoPieza = 0;
  int seleccionandoCasilla = 0;
  int turno = 0;
  int turnoRetorno = -1;
  int jaquePase = 0;
  int piezaSeleccionada = -1;
  int casillaSeleccionada = -1;
  int casillaSeleccionadaActualmente;
  int jaqueBlancas = 0;
  int jaqueNegras = 0;
  int jaqueAmarillas = 0;
  int jaqueRojas = 0;
  int enroqueBlancas =
      -1; // -1 --> no enroque. otro nro indicara la casilla con la q enrocarse
  int enroqueNegras =
      -1; // -1 --> no enroque. otro nro indicara la casilla con la q enrocarse
  int enroqueAmarillas =
      -1; // -1 --> no enroque. otro nro indicara la casilla con la q enrocarse
  int enroqueRojas =
      -1; // -1 --> no enroque. otro nro indicara la casilla con la q enrocarse
  int reyBlancoMovido = 0;
  int reyNegroMovido = 0;
  int reyAmarilloMovido = 0;
  int reyRojoMovido = 0;
  int torreBIMovida = 0;
  int torreBDMovida = 0;
  int torreNIMovida = 0;
  int torreNDMovida = 0;
  int torreAIMovida = 0;
  int torreADMovida = 0;
  int torreRIMovida = 0;
  int torreRDMovida = 0;
  int MasterBlancas = 0;
  int MasterNegras = 0;
  int MasterAmarillas = 0;
  int MasterRojas = 0;
  int blancasInmovilizadas = 0;
  int negrasInmovilizadas = 0;
  int amarillasInmovilizadas = 0;
  int rojasInmovilizadas = 0;

  int controla[4][4]; // controla[i][j] == 1: reino i puede manejar piezas de
                      // reino j
  int amenaza[4][4];  // amenaza[i][j]  == 1: reino i puede capturar piezas de
                      // reino j
  int Convenio = ASIMILACION;
  int Pacto = AISLADO;

  // Variables del juego
  pieza tablero[16][16];
  pieza blancas[16];
  pieza negras[16];
  pieza rojas[16];
  pieza amarillas[16];
  pieza coronables[4];

  int soploBlancas[16];
  int soploAmarillas[16];
  int soploNegras[16];
  int soploRojas[16];
  int reyderrotado =
      -1; // variable utilizada para soplar piezas, almacena color (no turno)

  passant *passantBlanco = new passant();
  passant *passantNegro = new passant();
  passant *passantRojo = new passant();
  passant *passantAmarillo = new passant();

  passant *middlePassantBlanco = new passant();
  passant *middlePassantNegro = new passant();
  passant *middlePassantRojo = new passant();
  passant *middlePassantAmarillo = new passant();

  passant *eatenPassantBlanco = new passant();
  passant *eatenPassantNegro = new passant();
  passant *eatenPassantRojo = new passant();
  passant *eatenPassantAmarillo = new passant();

  int dibujaPiezas = 0;
  int coronando = 0;
  int colorCoronado = -1;
  int colorCoronando = -1;
  int xCoronando, yCoronando;

  int curr_lang = LANG_ES;
  tinyxml2::XMLDocument doclang[2];


  //Variables para apertura
  int num_movimientos_amarillas;
  int num_movimientos_negras;
  int num_movimientos_rojas;

  int apertura_elegida;
  int a[6],b[6],c[6],d[6],e[6],f[6],g[7],i[7],k[7],l[7],m[7],o[7],h[8],j[8],n[8],p[8],q[8],r[8];
  int v=0,t=0,u=0;

//========================== Metodos() =======================================

#include "masterdrez-manejoxml.h"
#include "masterdrez-tablero.h"
#include "masterdrez-resetvar.h"
#include "masterdrez-movimientos.h"
#include "masterdrez-axiomas.h"

#include "masterdrez-ia4x4.h"
#include "masterdrez-ia6x6.h"

#include "masterdrez-aperturas.h"
};

extern t_masterdrez objMasterdrez;

#endif // MASTERDREZ
