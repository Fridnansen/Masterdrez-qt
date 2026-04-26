#ifndef GRAFICOS
#define GRAFICOS

#include <QtOpenGL>
#include <GL/glut.h>
#include "masterdrez.h"

//==================================================================

#define PAWN_HEIGHT 2.0f

#define ROOK_HEIGHT_MID 1.3f
#define ROOK_HEIGHT_TOP ROOK_HEIGHT_MID * 2.0f
#define ROOK_LOWER_WIDTH 1.0f
#define ROOK_UPPER_WIDTH 0.75f

#define KNIGHT_HEIGHT_MID 1.4f
#define KNIGHT_HEIGHT_TOP KNIGHT_HEIGHT_MID * 1.5f
#define KNIGHT_HEAD_WIDTH 0.3f
#define KNIGHT_HEAD_HEIGHT 0.5f
#define KNIGHT_LOWER_WIDTH 1.0f
#define KNIGHT_UPPER_WIDTH 0.4f
#define KNIGHT_SNOUT_LENGTH 1.3f
#define KNIGHT_SNOUT_DROP 0.3f
#define KNIGHT_EAR_HEIGHT 0.35f
#define KNIGHT_EAR_WIDTH 0.1f
#define KNIGHT_EYE_SIZE 0.7f

#define BISHOP_HEIGHT_MID 2.2f
#define BISHOP_NECK_WIDTH 0.25f
#define BISHOP_HEAD_HEIGHT 1.68f
#define BISHOP_HEAD_HEIGHT_MID BISHOP_HEIGHT_MID + (BISHOP_HEAD_HEIGHT / 2.0f)
#define BISHOP_HEIGHT_TOP BISHOP_HEIGHT_MID + BISHOP_HEAD_HEIGHT
#define BISHOP_HEAD_WIDTH 0.5f

#define QUEEN_HEIGHT_MID 3.0f
#define QUEEN_NECK_WIDTH 0.35f
#define QUEEN_HEAD_HEIGHT 2.0f
#define QUEEN_HEAD_HEIGHT_MID QUEEN_HEIGHT_MID + (QUEEN_HEAD_HEIGHT / 2.0f)
#define QUEEN_HEIGHT_TOP QUEEN_HEIGHT_MID + QUEEN_HEAD_HEIGHT - 0.5f
#define QUEEN_HEAD_WIDTH 0.65f
#define QUEEN_SPHERE_SIZE 2.0f

#define KING_HEIGHT_MID 3.5f
#define KING_NECK_WIDTH 0.40f
#define KING_HEAD_HEIGHT 2.2f
#define KING_HEAD_HEIGHT_MID KING_HEIGHT_MID + (KING_HEAD_HEIGHT / 2.0f)
#define KING_HEIGHT_TOP 0.0f
#define KING_HEAD_WIDTH 0.70f
#define KING_CROSS_SIZE KING_HEAD_WIDTH / 2.0f
#define KING_CROSS_HEIGHT 0.6f

//==================================================================

extern GLfloat colWhite[];
extern GLfloat colBlack[];
extern GLfloat colRed[];
extern GLfloat colGreen[];
extern GLfloat colBlue[];
extern GLfloat colYellow[];
extern GLfloat colCyan[];
extern GLfloat colOrange[];
extern GLfloat colGrey[];
extern GLfloat colPink[];
extern GLfloat colMarron[];
extern GLfloat colbrown[];
extern GLfloat colbrown_dark[];

extern GLfloat pos[];
extern GLfloat ref_difusa[];
extern GLfloat ref_especular[];
extern GLfloat ref_brillo[];

extern GLfloat seleccion[];
extern GLfloat movimientoCorrecto[];
extern GLfloat movimientoIncorrecto[];
extern GLfloat colortablero[];

//==================================================================

class Graficos {

private:
  GLfloat colorcasilla[4] = {0.5, 0.5, 0.8, 0}; // por omision azul

  GLUnurbsObj *miNurb;
  float ptos[6][6][3]; // una malla de puntos 3D

  // Peon
  float cPeon[6][3] = {{0, 0.5, 0.0},
                       {0.5, 0.5, 0.0},
                       {0.5, 0.0, 0.0},
                       {0.0, 0.0, 0.0},
                       {0.0, 0.0, 0.0},
                       {0.0, 0, 0.0}};
  float pPeon[6][3] = {{0.0, 3.0, 0.0},
                       {2, 3.0, 0.0},
                       {0.0, 2.5, 0.0},
                       {1, 1.2, 0.0},
                       {2, 0.6, 0.0},
                       {2.0, 0, 0.0}};

  // Torre
  float cTorre[6][3] = {{2, 0, 0.0},
                        {1, 1, 0.0},
                        {1, 1, 0.0},
                        {2, 1, 0.0},
                        {2, 1, 0.0},
                        {2, 0, 0.0}};
  float pTorre[6][3] = {{2, 5.0, 0.0},
                        {1, 4.5, 0.0},
                        {1.5, 2.5, 0.0},
                        {1.5, 2, 0.0},
                        {2.5, 1, 0.0},
                        {2.5, 0.0, 0.0}};

  float a[6][3] = {{0.0, 0.5, 0.0},
                   {0.0, 0.5, 0.0},
                   {1, 0.0, 0.0},
                   {0, 0, 0.0},
                   {0, 0, 0.0},
                   {0, 0.0, 0.0}};

  // Caballo
  GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
  GLfloat ctlpoints[4][4][3];

  float pCaballo[6][3] = {{0.0, 4.0, 0.0},
                          {1, 4.0, 0.0},
                          {0.0, 3.0, 0.0},
                          {1, 1.0, 0.0},
                          {2, 0.5, 0.0},
                          {2.0, 0, 0.0}};

  // Alfil
  float pAlfil[6][3] = {{0.0, 6.0, 0.0},
                        {2, 5, 0.0},
                        {0.5, 4.0, 0.0},
                        {1, 1.5, 0.0},
                        {2, 1, 0.0},
                        {2.0, 0, 0.0}};

  // Reina
  float cReina[6][3] = {{0, 1.5, 0.0},
                        {0.5, 1, 0.0},
                        {1.5, 1.5, 0.0},
                        {1.7, 0.7, 0.0},
                        {0.7, 0.5, 0.0},
                        {1.0, 0, 0.0}};
  float pReina[6][3] = {{1.0, 5.0, 0.0},
                        {2, 4.3, 0.0},
                        {0.5, 4.0, 0.0},
                        {1.2, 1.5, 0.0},
                        {2, 1, 0.0},
                        {2.0, 0, 0.0}};

public:
  void inicializarGraficos() {
    miNurb = gluNewNurbsRenderer(); /* crea un manejador de nurbs */
    gluNurbsProperty(miNurb, GLU_SAMPLING_TOLERANCE,
                     10.0); /* Frecuencia de muestreo */
    gluNurbsProperty(miNurb, GLU_DISPLAY_MODE,
                     GLU_FILL); /* Aproxima por poligonos */

    ctlpoints[3][0][0] = 0.0;
    ctlpoints[3][0][1] = 4.0;
    ctlpoints[3][0][2] = -2.0;
    ctlpoints[3][1][0] = 0.0;
    ctlpoints[3][1][1] = 4.0;
    ctlpoints[3][1][2] = -1.33;
    ctlpoints[3][2][0] = 0.0;
    ctlpoints[3][2][1] = 4.0;
    ctlpoints[3][2][2] = 0.66;
    ctlpoints[3][3][0] = 0.0;
    ctlpoints[3][3][1] = 4.0;
    ctlpoints[3][3][2] = 0.0;

    ctlpoints[2][0][0] = 0.0;
    ctlpoints[2][0][1] = 2.66;
    ctlpoints[2][0][2] = -2.0;
    ctlpoints[2][1][0] = 3.0;
    ctlpoints[2][1][1] = 2.66;
    ctlpoints[2][1][2] = -2.0;
    ctlpoints[2][2][0] = 3.0;
    ctlpoints[2][2][1] = 2.66;
    ctlpoints[2][2][2] = 0.0;
    ctlpoints[2][3][0] = 0.0;
    ctlpoints[2][3][1] = 2.66;
    ctlpoints[2][3][2] = 0.0;

    ctlpoints[1][0][0] = 0.0;
    ctlpoints[1][0][1] = 0.0;
    ctlpoints[1][0][2] = -2.0;
    ctlpoints[1][1][0] = 4.0;
    ctlpoints[1][1][1] = 0.0;
    ctlpoints[1][1][2] = -2.0;
    ctlpoints[1][2][0] = 4.0;
    ctlpoints[1][2][1] = 0.0;
    ctlpoints[1][2][2] = 0.0;
    ctlpoints[1][3][0] = 0.0;
    ctlpoints[1][3][1] = 0.0;
    ctlpoints[1][3][2] = 0.0;

    ctlpoints[0][0][0] = 0.0;
    ctlpoints[0][0][1] = 0.0;
    ctlpoints[0][0][2] = -2.0;
    ctlpoints[0][1][0] = 0.0;
    ctlpoints[0][1][1] = 0.0;
    ctlpoints[0][1][2] = -1.33;
    ctlpoints[0][2][0] = 0.0;
    ctlpoints[0][2][1] = 0.0;
    ctlpoints[0][2][2] = -0.66;
    ctlpoints[0][3][0] = 0.0;
    ctlpoints[0][3][1] = 0.0;
    ctlpoints[0][3][2] = 0.0;
  }
  void setColorCasilla(float r, float g, float b) {
    colorcasilla[0] = r;
    colorcasilla[1] = g;
    colorcasilla[2] = b;
  }
  void dibujarTablero();
  void dibujarMasterdrez();

  void cubo(GLfloat x, GLfloat y, GLfloat z);
  void generarMallaPorRotacion(float p[6][3], float ptos[6][6][3], int n,
                               int v);
  void dibujarSuperficie(GLUnurbsObj *miNurb, float ptos[6][6][3]);

  void dibujarPeon();
  void dibujarTorre();
  void dibujarCabezaCaballo();
  void dibujarCaballo();
  void dibujarAlfil();
  void dibujarReina();
  void dibujarRey();

  void dibujarPieza(int xact, int yact, int xfin, int yfin);
  void dibujarPiezas();
};

extern Graficos Proyeccion;

#endif // GRAFICOS
