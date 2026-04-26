#include "myopengl.h"
#include "graficos.h"
#include "ui_mainwindow.h"

//===============================================================================
static void qNormalizeAngle(int &angle) {
  while (angle < 0)
    angle += 360 * 16;
  while (angle > 360)
    angle -= 360 * 16;
}
//===============================================================================

MyOpengl::MyOpengl(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

  xRot = 40;
  yRot = -180;
  zRot = 0;
  Profundidad = 150;
}

MyOpengl::~MyOpengl() {}

void MyOpengl::setXRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != xRot) {
    xRot = angle;
    emit xRotationChanged(angle);
    updateGL();
  }
}

void MyOpengl::setYRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != yRot) {
    yRot = angle;
    emit yRotationChanged(angle);
    updateGL();
  }
}

void MyOpengl::setZRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != zRot) {
    zRot = angle;
    emit zRotationChanged(angle);
    updateGL();
  }
}

void MyOpengl::initializeGL() {

  glClearColor(0, .25, .25, 1);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_CULL_FACE);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_AUTO_NORMAL); /* genera automaticamente las normales   */
  glEnable(GL_NORMALIZE);
}

void MyOpengl::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glTranslatef(0, 0, -Profundidad);
  glRotatef(xRot, 1.0, 0.0, 0.0);
  glRotatef(yRot, 0.0, 1.0, 0.0);
  glRotatef(zRot, 0.0, 0.0, 1.0);
  glTranslatef(-20, 0, -20);

  Dibujar();
}

void MyOpengl::ViewTrans() {

  if (viewX == 0)
    viewX = 1;

  double ratio = (double)viewY / (double)viewX;
  glFrustum(-1, 1, (-1) * ratio, (1) * ratio, 5, 1000);

  glMatrixMode(GL_MODELVIEW);
}
void MyOpengl::setViewTrans() {
  glMatrixMode(
      GL_PROJECTION); // Especificamos la transformacion de visualizacion
  glLoadIdentity();   // Inicializa la transformacion
  ViewTrans();
}

void MyOpengl::resizeGL(int width, int height) {

  /* Actualizar tablero...
   * glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (width == 0)
    width = 1;

  double ratio = (double)height / (double)width;
  glFrustum(-1, 1, (-1) * ratio, (1) * ratio, 5, 1000);

  std::cout << "____ResizeGL____\n";
  std::cout << "x: " << width << "\n";
  std::cout << "y: " << height << "\n";
  std::cout << "ratio: " << ratio << "\n";
  std::cout << "________________\n";

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(0, 0, -Profundidad);
  glRotatef(xRot, 1.0, 0.0, 0.0);
  glRotatef(yRot, 0.0, 1.0, 0.0);
  glRotatef(zRot, 0.0, 0.0, 1.0);
  glTranslatef(-20, 0, -20);*/

  glViewport(0, 0, width, height);
  viewX = width;
  viewY = height;
  setViewTrans();
}

void MyOpengl::keyPressEvent(QKeyEvent *e) {

  switch (e->key()) {
  case Qt::Key_Up:
    setXRotation(xRot - 5);
    break;

  case Qt::Key_Down:
    setXRotation(xRot + 5);
    break;

  case Qt::Key_Left:
    setYRotation(yRot - 5);
    break;

  case Qt::Key_Right:
    setYRotation(yRot + 5);
    break;

  case Qt::Key_Plus:
    Profundidad -= 5;
    updateGL();
    break;

  case Qt::Key_Minus:
    Profundidad += 5;
    updateGL();
    break;

  case Qt::Key_Escape:
    exit(1);
  }
}

#define BUFSIZE 512
GLuint selectBuf[BUFSIZE];
int MyOpengl::startPicking(int cursorX, int cursorY) {

  GLint viewport[4];

  glSelectBuffer(BUFSIZE, selectBuf);
  glRenderMode(GL_SELECT);

  glInitNames();  // Inicializa el stack de nombres
  glPushName(-1); // Valor de fondo

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glGetIntegerv(GL_VIEWPORT, viewport);

  gluPickMatrix((GLdouble)cursorX, (GLdouble)(viewport[3] - cursorY), 3.0, 3.0,
                viewport); // Agrega la transformacion
  // para reducir la imagen a una ventana de 3 pixels arededor del
  // punto en el que seleccionar

  ViewTrans();
  objMasterdrez.dibujaPiezas = 0;
  Proyeccion.dibujarMasterdrez(); // Dibuja el modelo (no se genera imagen
                                  // estamos en Render mode)
  objMasterdrez.dibujaPiezas = 1;
  glMatrixMode(GL_PROJECTION); // Pasamos a Convenio proyeccion
  glPopMatrix();               // Deja la transformacion como estaba

  GLint hits;                     // Numero de elementos seleccionados
  hits = glRenderMode(GL_RENDER); // Obtiene informacion de seleccion

  int i;

  if (hits == 0)
    i = -1; // Nada seleccionado
  else
    i = selectBuf[3] - 1;

  // std::cout << "Valor de hits: " << hits << ", Valor de i: " << i << "\n";

  setViewTrans(); // Fija la transformacion de visualizacion

  return i;
}

void MyOpengl::mousePressEvent(QMouseEvent *event) {

  QApplication::setOverrideCursor(Qt::ClosedHandCursor);

  lastPos = event->pos();

  if (event->buttons() & Qt::LeftButton) {
    if (objMasterdrez.seleccionandoPieza) {
      objMasterdrez.piezaSeleccionada = startPicking(event->x(), event->y());
      if (objMasterdrez.piezaYTurnoValidos()) {
        objMasterdrez.casillaSeleccionadaActualmente =
            objMasterdrez.piezaSeleccionada;
        objMasterdrez.seleccionandoPieza = 0;
        objMasterdrez.seleccionandoCasilla = 1;
      } else {
        std::cout << "mousePressEvent: "
                  << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                               "ERROR_SELECCIONANDO_PIEZA")
                  << "\n";
      }
    }
  }

  updateGL();
}

void MyOpengl::mouseMoveEvent(QMouseEvent *event) {

  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    // std::cout << "2- inside mouseMoveEvent -"            << "\n";
    int casillaActual = startPicking(event->x(), event->y());
    if (objMasterdrez.casillaSeleccionadaActualmente != casillaActual) {
      objMasterdrez.casillaSeleccionadaActualmente = casillaActual;
      objMasterdrez.enroqueBlancas = -1;
      objMasterdrez.enroqueNegras = -1;
      objMasterdrez.enroqueAmarillas = -1;
      objMasterdrez.enroqueRojas = -1;
      updateGL();
    }
  } else if (event->buttons() & Qt::RightButton) {
    // std::cout << "El valor de dx: " << dx << std::endl;
    if (dx > 0)
      setYRotation(yRot + 1);
    else
      setYRotation(yRot - 1);

    if (dy > 0)
      setXRotation(xRot + 1);
    else
      setXRotation(xRot - 1);
  }
}

void MyOpengl::wheelEvent(QWheelEvent *event) {

  int delta = event->delta();
  // std::cout << "El valor de event->delta(): " << delta << std::endl;
  Profundidad += delta / 120;
  updateGL();
}

//================= mouseReleaseEvent ===============================
void MyOpengl::mouseReleaseEvent(QMouseEvent *event) {

  emit clicked();

  QApplication::restoreOverrideCursor();

  if (objMasterdrez.partidaComenzada) {
    switch (objMasterdrez.partidaHM) {
    case 0:
      // Si se esta seleccionando casilla
      if (objMasterdrez.seleccionandoCasilla) {

        // Eliminar la posibilidad de peon al paso del turno actual
        // pues ya ha pasado una ronda y no se efectuo la captura.
        switch (objMasterdrez.turno) {
        case 0:
          objMasterdrez.passantBlanco->noAsignar();
          objMasterdrez.middlePassantBlanco->noAsignar();
          break;
        case 1:
          objMasterdrez.passantAmarillo->noAsignar();
          objMasterdrez.middlePassantAmarillo->noAsignar();
          break;
        case 2:
          objMasterdrez.passantNegro->noAsignar();
          objMasterdrez.middlePassantNegro->noAsignar();
          break;
        case 3:
          objMasterdrez.passantRojo->noAsignar();
          objMasterdrez.middlePassantRojo->noAsignar();
          break;
        }

        objMasterdrez.casillaSeleccionada =
            startPicking(event->x(), event->y());
        // Si la casilla seleccionada y el turno son validos
        if (objMasterdrez.casillaYTurnoValidos(
                objMasterdrez.piezaSeleccionada,
                objMasterdrez.casillaSeleccionada, objMasterdrez.blancas,
                objMasterdrez.negras, objMasterdrez.amarillas,
                objMasterdrez.rojas, objMasterdrez.tablero, objMasterdrez.turno,
                true)) {
          objMasterdrez.eatenPassantBlanco->noAsignar();
          objMasterdrez.eatenPassantAmarillo->noAsignar();
          objMasterdrez.eatenPassantNegro->noAsignar();
          objMasterdrez.eatenPassantRojo->noAsignar();

          int xact = objMasterdrez.piezaSeleccionada / 16;
          int yact = objMasterdrez.piezaSeleccionada % 16;
          int xfin = objMasterdrez.casillaSeleccionada / 16;
          int yfin = objMasterdrez.casillaSeleccionada % 16;
          t_masterdrez::pieza *p1 = NULL;

          // Verificar si se produce situacion de enroque
          // para ajustar las variables correspondientes.
          if (objMasterdrez.tablero[xact][yact].tipo == REY) {
            switch (objMasterdrez.tablero[xact][yact].color) {
            case BLANCO:
              if ((yfin - yact == 0) && (abs(xfin - xact) == 2) &&
                  (!objMasterdrez.reyBlancoMovido) && (xact == 8) &&
                  (yact == 0)) {
                if ((xfin == 6) && (!objMasterdrez.torreBDMovida) &&
                    (objMasterdrez.tablero[4][0].tipo == TORRE) &&
                    (objMasterdrez.tablero[4][0].color == BLANCO) &&
                    (objMasterdrez.tablero[7][0].tipo <= 0) &&
                    (objMasterdrez.tablero[6][0].tipo <= 0) &&
                    (objMasterdrez.tablero[5][0].tipo <= 0))
                  objMasterdrez.enroqueBlancas = TORRED;
                else if ((xfin == 10) && (!objMasterdrez.torreBIMovida) &&
                         (objMasterdrez.tablero[11][0].tipo == TORRE) &&
                         (objMasterdrez.tablero[11][0].color == BLANCO) &&
                         (objMasterdrez.tablero[9][0].tipo <= 0) &&
                         (objMasterdrez.tablero[10][0].tipo <= 0))
                  objMasterdrez.enroqueBlancas = TORREI;
              }
              break;

            case AMARILLO:
              if ((xfin - xact == 0) && (abs(yfin - yact) == 2) &&
                  (!objMasterdrez.reyAmarilloMovido) && (xact == 0) &&
                  (yact == 8)) {
                if ((yfin == 10) && (!objMasterdrez.torreADMovida) &&
                    (objMasterdrez.tablero[0][11].tipo == TORRE) &&
                    (objMasterdrez.tablero[0][11].color == AMARILLO) &&
                    (objMasterdrez.tablero[0][9].tipo <= 0) &&
                    (objMasterdrez.tablero[0][10].tipo <= 0))
                  objMasterdrez.enroqueAmarillas = TORRED;
                else if ((yfin == 6) && (!objMasterdrez.torreAIMovida) &&
                         (objMasterdrez.tablero[0][4].tipo == TORRE) &&
                         (objMasterdrez.tablero[0][4].color == AMARILLO) &&
                         (objMasterdrez.tablero[0][5].tipo <= 0) &&
                         (objMasterdrez.tablero[0][6].tipo <= 0) &&
                         (objMasterdrez.tablero[0][7].tipo <= 0))
                  objMasterdrez.enroqueAmarillas = TORREI;
              }
              break;

            case NEGRO:
              if ((yfin - yact == 0) && (abs(xfin - xact) == 2) &&
                  (!objMasterdrez.reyNegroMovido) && (xact == 7) &&
                  (yact == 15)) {
                if ((xfin == 9) && (!objMasterdrez.torreNDMovida) &&
                    (objMasterdrez.tablero[11][15].tipo == TORRE) &&
                    (objMasterdrez.tablero[11][15].color == NEGRO) &&
                    (objMasterdrez.tablero[8][15].tipo <= 0) &&
                    (objMasterdrez.tablero[9][15].tipo <= 0) &&
                    (objMasterdrez.tablero[10][15].tipo <= 0))
                  objMasterdrez.enroqueNegras = TORRED;
                else if ((xfin == 5) && (!objMasterdrez.torreNIMovida) &&
                         (objMasterdrez.tablero[4][15].tipo == TORRE) &&
                         (objMasterdrez.tablero[4][15].color == NEGRO) &&
                         (objMasterdrez.tablero[6][15].tipo <= 0) &&
                         (objMasterdrez.tablero[5][15].tipo <= 0))
                  objMasterdrez.enroqueNegras = TORREI;
              }
              break;

            case ROJO:
              if ((xfin - xact == 0) && (abs(yfin - yact) == 2) &&
                  (!objMasterdrez.reyRojoMovido) && (xact == 15) &&
                  (yact == 7)) {
                if ((yfin == 5) && (!objMasterdrez.torreRDMovida) &&
                    (objMasterdrez.tablero[15][4].tipo == TORRE) &&
                    (objMasterdrez.tablero[15][4].color == ROJO) &&
                    (objMasterdrez.tablero[15][6].tipo <= 0) &&
                    (objMasterdrez.tablero[15][5].tipo <= 0))
                  objMasterdrez.enroqueRojas = TORRED;
                else if ((yfin == 9) && (!objMasterdrez.torreRIMovida) &&
                         (objMasterdrez.tablero[15][11].tipo == TORRE) &&
                         (objMasterdrez.tablero[15][11].color == ROJO) &&
                         (objMasterdrez.tablero[15][8].tipo <= 0) &&
                         (objMasterdrez.tablero[15][9].tipo <= 0) &&
                         (objMasterdrez.tablero[15][10].tipo <= 0))
                  objMasterdrez.enroqueRojas = TORREI;
              }
              break;
            }

          }

          // Verificar si se produce situacion de peon al paso
          // para ajustar las variables correspondientes.
          else if (objMasterdrez.tablero[xact][yact].tipo == PEON) {
            /*************************************************
            Si el peón se encuentra en la posición 0 y se
            mueve a alguna de las posiciones 1, 2, 3 o 4,
            se verifica si en las posiciones marcadas con
            [x] el peón hubiese quedado en una posición
            alcanzable por otro peón.

            [ ][ ][1][ ][ ]
            [ ][ ][x][ ][ ]
            [2][x][0][x][4]
            [ ][ ][x][ ][ ]
            [ ][ ][3][ ][ ]
            ************************************************/
            int x2 = -1;
            int z2 = -1;

            if ((yfin == yact) && (xfin - xact == -2)) //[1]
            {
              x2 = xfin + 1;
              z2 = yfin;
            }
            if ((xfin == xact) && (yfin - yact == -2)) //[2]
            {
              x2 = xfin;
              z2 = yfin + 1;
            }
            if ((yfin == yact) && (xfin - xact == 2)) //[3]
            {
              x2 = xfin - 1;
              z2 = yfin;
            }
            if ((xfin == xact) && (yfin - yact == 2)) //[4]
            {
              x2 = xfin;
              z2 = yfin - 1;
            }

            // Si hizo movimiento de peon al paso
            if (x2 != -1 && z2 != -1)
              if (objMasterdrez.capturablePorPeon(x2, z2, objMasterdrez.tablero,
                                                  objMasterdrez.turno)) {
                switch (objMasterdrez.turno) {
                case 0:
                  objMasterdrez.passantBlanco->Asignar(xfin, yfin);
                  objMasterdrez.middlePassantBlanco->Asignar(x2, z2);
                  break;

                case 1:
                  objMasterdrez.passantAmarillo->Asignar(xfin, yfin);
                  objMasterdrez.middlePassantAmarillo->Asignar(x2, z2);
                  break;

                case 2:
                  objMasterdrez.passantNegro->Asignar(xfin, yfin);
                  objMasterdrez.middlePassantNegro->Asignar(x2, z2);
                  break;

                case 3:
                  objMasterdrez.passantRojo->Asignar(xfin, yfin);
                  objMasterdrez.middlePassantRojo->Asignar(x2, z2);
                  break;
                }
              }
          }

          // Buscar pieza a mover
          for (int i = 0; i < 16; i++) {
            if ((objMasterdrez.blancas[i].tipo > 0) &&
                (objMasterdrez.blancas[i].x == xact) &&
                (objMasterdrez.blancas[i].y == yact))
              p1 = &(objMasterdrez.blancas[i]);
            if ((objMasterdrez.negras[i].tipo > 0) &&
                (objMasterdrez.negras[i].x == xact) &&
                (objMasterdrez.negras[i].y == yact))
              p1 = &(objMasterdrez.negras[i]);
            if ((objMasterdrez.amarillas[i].tipo > 0) &&
                (objMasterdrez.amarillas[i].x == xact) &&
                (objMasterdrez.amarillas[i].y == yact))
              p1 = &(objMasterdrez.amarillas[i]);
            if ((objMasterdrez.rojas[i].tipo > 0) &&
                (objMasterdrez.rojas[i].x == xact) &&
                (objMasterdrez.rojas[i].y == yact))
              p1 = &(objMasterdrez.rojas[i]);
          }
          if (objMasterdrez.coronando == 1) {
            for (int i = 0; i < 16; i++)
              if ((objMasterdrez.coronables[i].tipo > 0) &&
                  (objMasterdrez.coronables[i].x == xact) &&
                  (objMasterdrez.coronables[i].y == yact))
                p1 = &(objMasterdrez.coronables[i]);
          }

          int xpas, ypas, colorpas;
          if (objMasterdrez.CapturaAlPaso(xact, yact, xfin, yfin,
                                          objMasterdrez.tablero, p1, xpas, ypas,
                                          colorpas)) {
            if (colorpas == BLANCO) {
              objMasterdrez.eatenPassantBlanco->Asignar(xpas, ypas);
            }
            if (colorpas == AMARILLO) {
              objMasterdrez.eatenPassantAmarillo->Asignar(xpas, ypas);
            }
            if (colorpas == NEGRO) {
              objMasterdrez.eatenPassantNegro->Asignar(xpas, ypas);
            }
            if (colorpas == ROJO) {
              objMasterdrez.eatenPassantRojo->Asignar(xpas, ypas);
            }
          }

          int promoting = objMasterdrez.promotingPawn(xfin, yfin, p1);
          if (promoting > 0) {
            objMasterdrez.coronando = 1;
            objMasterdrez.colorCoronado = promoting;
            objMasterdrez.colorCoronando = p1->color;
            objMasterdrez.xCoronando = xfin;
            objMasterdrez.yCoronando = yfin;
            objMasterdrez.coronables[0].color = p1->color;
            objMasterdrez.coronables[1].color = p1->color;
            objMasterdrez.coronables[2].color = p1->color;
            objMasterdrez.coronables[3].color = p1->color;
            if (promoting == BLANCO) {
              objMasterdrez.coronables[0].x = 12;
              objMasterdrez.coronables[1].x = 13;
              objMasterdrez.coronables[2].x = 14;
              objMasterdrez.coronables[3].x = 15;
              objMasterdrez.coronables[0].y = 0;
              objMasterdrez.coronables[1].y = 0;
              objMasterdrez.coronables[2].y = 0;
              objMasterdrez.coronables[3].y = 0;
            } else if (promoting == AMARILLO) {
              objMasterdrez.coronables[0].x = 0;
              objMasterdrez.coronables[1].x = 0;
              objMasterdrez.coronables[2].x = 0;
              objMasterdrez.coronables[3].x = 0;
              objMasterdrez.coronables[0].y = 0;
              objMasterdrez.coronables[1].y = 1;
              objMasterdrez.coronables[2].y = 2;
              objMasterdrez.coronables[3].y = 3;
            } else if (promoting == NEGRO) {
              objMasterdrez.coronables[0].x = 0;
              objMasterdrez.coronables[1].x = 1;
              objMasterdrez.coronables[2].x = 2;
              objMasterdrez.coronables[3].x = 3;
              objMasterdrez.coronables[0].y = 15;
              objMasterdrez.coronables[1].y = 15;
              objMasterdrez.coronables[2].y = 15;
              objMasterdrez.coronables[3].y = 15;
            } else if (promoting == ROJO) {
              objMasterdrez.coronables[0].x = 15;
              objMasterdrez.coronables[1].x = 15;
              objMasterdrez.coronables[2].x = 15;
              objMasterdrez.coronables[3].x = 15;
              objMasterdrez.coronables[0].y = 12;
              objMasterdrez.coronables[1].y = 13;
              objMasterdrez.coronables[2].y = 14;
              objMasterdrez.coronables[3].y = 15;
            }
          }

          // antes de ejecutar el movimiento:
          // Verificar si tiene algun reino en jaque
          int reinoEnMaster = -1;
          if (objMasterdrez.tieneMasterBlancas(
                  objMasterdrez.blancas, objMasterdrez.negras,
                  objMasterdrez.amarillas, objMasterdrez.rojas,
                  objMasterdrez.tablero, objMasterdrez.turno)) {
            reinoEnMaster = 0;
          }
          if (objMasterdrez.tieneMasterNegras(
                  objMasterdrez.blancas, objMasterdrez.negras,
                  objMasterdrez.amarillas, objMasterdrez.rojas,
                  objMasterdrez.tablero, objMasterdrez.turno)) {
            reinoEnMaster = 1;
          }
          if (objMasterdrez.tieneMasterAmarillas(
                  objMasterdrez.blancas, objMasterdrez.negras,
                  objMasterdrez.amarillas, objMasterdrez.rojas,
                  objMasterdrez.tablero, objMasterdrez.turno)) {
            reinoEnMaster = 2;
          }
          if (objMasterdrez.tieneMasterRojas(
                  objMasterdrez.blancas, objMasterdrez.negras,
                  objMasterdrez.amarillas, objMasterdrez.rojas,
                  objMasterdrez.tablero, objMasterdrez.turno)) {
            reinoEnMaster = 3;
          }

          // Se ejecuta el movimiento...
          objMasterdrez.movimiento(objMasterdrez.blancas, objMasterdrez.negras,
                                   objMasterdrez.rojas, objMasterdrez.amarillas,
                                   objMasterdrez.tablero);
          updateGL();

          objMasterdrez.seleccionandoPieza = 1;
          objMasterdrez.seleccionandoCasilla = 0;

          // Verificar si hay condicion de partida ganada
          if (objMasterdrez.partida_ganada(objMasterdrez.Pacto) == 1) {
            std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                   "VICTORIA") << "\n";
            gUi.pUi->statusBar->showMessage(
                objMasterdrez.get_message(objMasterdrez.curr_lang, "VICTORIA"));

            objMasterdrez.resetVariablesEstado();
            return;
          } else if (objMasterdrez.tablas(
                         objMasterdrez.blancas, objMasterdrez.negras,
                         objMasterdrez.amarillas, objMasterdrez.rojas,
                         objMasterdrez.controla, objMasterdrez.Pacto) == 1) {
            std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                   "TABLAS") << "\n";
            gUi.pUi->statusBar->showMessage(
                objMasterdrez.get_message(objMasterdrez.curr_lang, "TABLAS"));

            objMasterdrez.resetVariablesEstado();
            return;
          }

          // Verificar si hubo posibilidad de Master y no se hizo: soplar piezas
          if (reinoEnMaster > -1 && objMasterdrez.reyderrotado < 1) {
            if (objMasterdrez.turno == 0) {
              for (int i = 0; i < 16; i++)
                if (objMasterdrez.soploBlancas[i] == 1) {
                  objMasterdrez.blancas[i].tipo = -1;
                  objMasterdrez.blancas[i].x = -1;
                  objMasterdrez.blancas[i].y = -1;
                  objMasterdrez.tablero[i][i].tipo = -1;
                  objMasterdrez.tablero[i][i].color = -1;
                }
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "SOPLO_BLANCAS") << "\n";
              gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                  objMasterdrez.curr_lang, "SOPLO_BLANCAS"));
            } else if (objMasterdrez.turno == 1) {
              for (int i = 0; i < 16; i++)
                if (objMasterdrez.soploAmarillas[i] == 1) {
                  objMasterdrez.amarillas[i].tipo = -1;
                  objMasterdrez.amarillas[i].x = -1;
                  objMasterdrez.amarillas[i].y = -1;
                  objMasterdrez.tablero[i][i].tipo = -1;
                  objMasterdrez.tablero[i][i].color = -1;
                }
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "SOPLO_AMARILLAS") << "\n";
              gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                  objMasterdrez.curr_lang, "SOPLO_AMARILLAS"));
            } else if (objMasterdrez.turno == 2) {
              for (int i = 0; i < 16; i++)
                if (objMasterdrez.soploNegras[i] == 1) {
                  objMasterdrez.negras[i].tipo = -1;
                  objMasterdrez.negras[i].x = -1;
                  objMasterdrez.negras[i].y = -1;
                  objMasterdrez.tablero[i][i].tipo = -1;
                  objMasterdrez.tablero[i][i].color = -1;
                }
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "SOPLO_NEGRAS") << "\n";
              gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                  objMasterdrez.curr_lang, "SOPLO_NEGRAS"));
            } else if (objMasterdrez.turno == 3) {
              for (int i = 0; i < 16; i++)
                if (objMasterdrez.soploRojas[i] == 1) {
                  objMasterdrez.rojas[i].tipo = -1;
                  objMasterdrez.rojas[i].x = -1;
                  objMasterdrez.rojas[i].y = -1;
                  objMasterdrez.tablero[i][i].tipo = -1;
                  objMasterdrez.tablero[i][i].color = -1;
                }
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "SOPLO_ROJAS") << "\n";
              gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                  objMasterdrez.curr_lang, "SOPLO_ROJAS"));
            }

          } else {
            objMasterdrez.resetSoplos();
          }

          // Cambiar de turno solo si no estoy coronando
          if (objMasterdrez.coronando != 1) {
            objMasterdrez.turno =
                objMasterdrez.calcular_turno(objMasterdrez.turno);
            if (objMasterdrez.turno + 1 == BLANCO) {
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "TURNO_BLANCAS") << "\n";
              gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                  objMasterdrez.curr_lang, "TURNO_BLANCAS"));
            } else if (objMasterdrez.turno + 1 == AMARILLO) {
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "TURNO_AMARILLAS") << "\n";
              gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                  objMasterdrez.curr_lang, "TURNO_AMARILLAS"));
            } else if (objMasterdrez.turno + 1 == NEGRO) {
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "TURNO_NEGRAS") << "\n";
              gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                  objMasterdrez.curr_lang, "TURNO_NEGRAS"));
            } else if (objMasterdrez.turno + 1 == ROJO) {
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "TURNO_ROJAS") << "\n";
              gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                  objMasterdrez.curr_lang, "TURNO_ROJAS"));
            }
          }
        } else {
          std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                 "ERROR_SELECCIONANDO_CASILLA")
                    << "\n";
          objMasterdrez.seleccionandoPieza = 1;
          objMasterdrez.seleccionandoCasilla = 0;
        }
      } /*else if (!objMasterdrez.seleccionandoCasilla) {
        // Si el siguiente turno ya no esta activo -> pase
        if (!objMasterdrez.activo(objMasterdrez.turno))
          objMasterdrez.turno =
              objMasterdrez.calcular_turno(objMasterdrez.turno);
      }*/
      if (objMasterdrez.turno == 1 &&
          objMasterdrez.partida_ganada(objMasterdrez.Pacto) != 1) {
        gUi.pUi->Reloj_Blancas->timer->stop();
        gUi.pUi->Reloj_Amarillas->timer->start();
      } else if (objMasterdrez.turno == 2 &&
                 objMasterdrez.partida_ganada(objMasterdrez.Pacto) != 1) {
        gUi.pUi->Reloj_Amarillas->timer->stop();
        gUi.pUi->Reloj_Negras->timer->start();
      } else if (objMasterdrez.turno == 3 &&
                 objMasterdrez.partida_ganada(objMasterdrez.Pacto) != 1) {
        gUi.pUi->Reloj_Negras->timer->stop();
        gUi.pUi->Reloj_Rojas->timer->start();
      } else if (objMasterdrez.turno == 0 &&
                 objMasterdrez.partida_ganada(objMasterdrez.Pacto) != 1) {
        gUi.pUi->Reloj_Rojas->timer->stop();
        gUi.pUi->Reloj_Blancas->timer->start();
      }
      break;

    //===================== HUMANO - MAQUINA(3) ================================
    case 1:
      if (objMasterdrez.turno == 0 &&
          objMasterdrez.partida_ganada(objMasterdrez.Pacto) != 1) {
        if (objMasterdrez.seleccionandoCasilla) {

          // Eliminar la posibilidad de peon al paso del turno actual
          // pues ya ha pasado una ronda y no se efectuo la captura.
          switch (objMasterdrez.turno) {
          case 0:
            objMasterdrez.passantBlanco->noAsignar();
            objMasterdrez.middlePassantBlanco->noAsignar();
            break;
          case 1:
            objMasterdrez.passantAmarillo->noAsignar();
            objMasterdrez.middlePassantAmarillo->noAsignar();
            break;
          case 2:
            objMasterdrez.passantNegro->noAsignar();
            objMasterdrez.middlePassantNegro->noAsignar();
            break;
          case 3:
            objMasterdrez.passantRojo->noAsignar();
            objMasterdrez.middlePassantRojo->noAsignar();
            break;
          }

          objMasterdrez.casillaSeleccionada =
              startPicking(event->x(), event->y());
          // Si la casilla seleccionada y el turno son validos
          if (objMasterdrez.casillaYTurnoValidos(
                  objMasterdrez.piezaSeleccionada,
                  objMasterdrez.casillaSeleccionada, objMasterdrez.blancas,
                  objMasterdrez.negras, objMasterdrez.amarillas,
                  objMasterdrez.rojas, objMasterdrez.tablero,
                  objMasterdrez.turno, true)) {
            objMasterdrez.eatenPassantBlanco->noAsignar();
            objMasterdrez.eatenPassantAmarillo->noAsignar();
            objMasterdrez.eatenPassantNegro->noAsignar();
            objMasterdrez.eatenPassantRojo->noAsignar();

            int xact = objMasterdrez.piezaSeleccionada / 16;
            int yact = objMasterdrez.piezaSeleccionada % 16;
            int xfin = objMasterdrez.casillaSeleccionada / 16;
            int yfin = objMasterdrez.casillaSeleccionada % 16;
            t_masterdrez::pieza *p1 = NULL;

            // Verificar si se produce situacion de enroque
            // para ajustar las variables correspondientes.
            if (objMasterdrez.tablero[xact][yact].tipo == REY) {
              switch (objMasterdrez.tablero[xact][yact].color) {
              case BLANCO:
                if ((yfin - yact == 0) && (abs(xfin - xact) == 2) &&
                    (!objMasterdrez.reyBlancoMovido) && (xact == 8) &&
                    (yact == 0)) {
                  if ((xfin == 6) && (!objMasterdrez.torreBDMovida) &&
                      (objMasterdrez.tablero[4][0].tipo == TORRE) &&
                      (objMasterdrez.tablero[4][0].color == BLANCO) &&
                      (objMasterdrez.tablero[7][0].tipo <= 0) &&
                      (objMasterdrez.tablero[6][0].tipo <= 0) &&
                      (objMasterdrez.tablero[5][0].tipo <= 0))
                    objMasterdrez.enroqueBlancas = TORRED;
                  else if ((xfin == 10) && (!objMasterdrez.torreBIMovida) &&
                           (objMasterdrez.tablero[11][0].tipo == TORRE) &&
                           (objMasterdrez.tablero[11][0].color == BLANCO) &&
                           (objMasterdrez.tablero[9][0].tipo <= 0) &&
                           (objMasterdrez.tablero[10][0].tipo <= 0))
                    objMasterdrez.enroqueBlancas = TORREI;
                }
                break;

              case AMARILLO:
                if ((xfin - xact == 0) && (abs(yfin - yact) == 2) &&
                    (!objMasterdrez.reyAmarilloMovido) && (xact == 0) &&
                    (yact == 8)) {
                  if ((yfin == 10) && (!objMasterdrez.torreADMovida) &&
                      (objMasterdrez.tablero[0][11].tipo == TORRE) &&
                      (objMasterdrez.tablero[0][11].color == AMARILLO) &&
                      (objMasterdrez.tablero[0][9].tipo <= 0) &&
                      (objMasterdrez.tablero[0][10].tipo <= 0))
                    objMasterdrez.enroqueAmarillas = TORRED;
                  else if ((yfin == 6) && (!objMasterdrez.torreAIMovida) &&
                           (objMasterdrez.tablero[0][4].tipo == TORRE) &&
                           (objMasterdrez.tablero[0][4].color == AMARILLO) &&
                           (objMasterdrez.tablero[0][5].tipo <= 0) &&
                           (objMasterdrez.tablero[0][6].tipo <= 0) &&
                           (objMasterdrez.tablero[0][7].tipo <= 0))
                    objMasterdrez.enroqueAmarillas = TORREI;
                }
                break;

              case NEGRO:
                if ((yfin - yact == 0) && (abs(xfin - xact) == 2) &&
                    (!objMasterdrez.reyNegroMovido) && (xact == 7) &&
                    (yact == 15)) {
                  if ((xfin == 9) && (!objMasterdrez.torreNDMovida) &&
                      (objMasterdrez.tablero[11][15].tipo == TORRE) &&
                      (objMasterdrez.tablero[11][15].color == NEGRO) &&
                      (objMasterdrez.tablero[8][15].tipo <= 0) &&
                      (objMasterdrez.tablero[9][15].tipo <= 0) &&
                      (objMasterdrez.tablero[10][15].tipo <= 0))
                    objMasterdrez.enroqueNegras = TORRED;
                  else if ((xfin == 5) && (!objMasterdrez.torreNIMovida) &&
                           (objMasterdrez.tablero[4][15].tipo == TORRE) &&
                           (objMasterdrez.tablero[4][15].color == NEGRO) &&
                           (objMasterdrez.tablero[6][15].tipo <= 0) &&
                           (objMasterdrez.tablero[5][15].tipo <= 0))
                    objMasterdrez.enroqueNegras = TORREI;
                }
                break;

              case ROJO:
                if ((xfin - xact == 0) && (abs(yfin - yact) == 2) &&
                    (!objMasterdrez.reyRojoMovido) && (xact == 15) &&
                    (yact == 7)) {
                  if ((yfin == 5) && (!objMasterdrez.torreRDMovida) &&
                      (objMasterdrez.tablero[15][4].tipo == TORRE) &&
                      (objMasterdrez.tablero[15][4].color == ROJO) &&
                      (objMasterdrez.tablero[15][6].tipo <= 0) &&
                      (objMasterdrez.tablero[15][5].tipo <= 0))
                    objMasterdrez.enroqueRojas = TORRED;
                  else if ((yfin == 9) && (!objMasterdrez.torreRIMovida) &&
                           (objMasterdrez.tablero[15][11].tipo == TORRE) &&
                           (objMasterdrez.tablero[15][11].color == ROJO) &&
                           (objMasterdrez.tablero[15][8].tipo <= 0) &&
                           (objMasterdrez.tablero[15][9].tipo <= 0) &&
                           (objMasterdrez.tablero[15][10].tipo <= 0))
                    objMasterdrez.enroqueRojas = TORREI;
                }
                break;
              }

            }

            // Verificar si se produce situacion de peon al paso
            // para ajustar las variables correspondientes.
            else if (objMasterdrez.tablero[xact][yact].tipo == PEON) {
              /*************************************************
              Si el peón se encuentra en la posición 0 y se
              mueve a alguna de las posiciones 1, 2, 3 o 4,
              se verifica si en las posiciones marcadas con
              [x] el peón hubiese quedado en una posición
              alcanzable por otro peón.

              [ ][ ][1][ ][ ]
              [ ][ ][x][ ][ ]
              [2][x][0][x][4]
              [ ][ ][x][ ][ ]
              [ ][ ][3][ ][ ]
              ************************************************/
              int x2 = -1;
              int z2 = -1;

              if ((yfin == yact) && (xfin - xact == -2)) //[1]
              {
                x2 = xfin + 1;
                z2 = yfin;
              }
              if ((xfin == xact) && (yfin - yact == -2)) //[2]
              {
                x2 = xfin;
                z2 = yfin + 1;
              }
              if ((yfin == yact) && (xfin - xact == 2)) //[3]
              {
                x2 = xfin - 1;
                z2 = yfin;
              }
              if ((xfin == xact) && (yfin - yact == 2)) //[4]
              {
                x2 = xfin;
                z2 = yfin - 1;
              }

              // Si hizo movimiento de peon al paso
              if (x2 != -1 && z2 != -1)
                if (objMasterdrez.capturablePorPeon(
                        x2, z2, objMasterdrez.tablero, objMasterdrez.turno)) {
                  switch (objMasterdrez.turno) {
                  case 0:
                    objMasterdrez.passantBlanco->Asignar(xfin, yfin);
                    objMasterdrez.middlePassantBlanco->Asignar(x2, z2);
                    break;

                  case 1:
                    objMasterdrez.passantAmarillo->Asignar(xfin, yfin);
                    objMasterdrez.middlePassantAmarillo->Asignar(x2, z2);
                    break;

                  case 2:
                    objMasterdrez.passantNegro->Asignar(xfin, yfin);
                    objMasterdrez.middlePassantNegro->Asignar(x2, z2);
                    break;

                  case 3:
                    objMasterdrez.passantRojo->Asignar(xfin, yfin);
                    objMasterdrez.middlePassantRojo->Asignar(x2, z2);
                    break;
                  }
                }
            }

            // Buscar pieza a mover
            for (int i = 0; i < 16; i++) {
              if ((objMasterdrez.blancas[i].tipo > 0) &&
                  (objMasterdrez.blancas[i].x == xact) &&
                  (objMasterdrez.blancas[i].y == yact))
                p1 = &(objMasterdrez.blancas[i]);
              if ((objMasterdrez.negras[i].tipo > 0) &&
                  (objMasterdrez.negras[i].x == xact) &&
                  (objMasterdrez.negras[i].y == yact))
                p1 = &(objMasterdrez.negras[i]);
              if ((objMasterdrez.amarillas[i].tipo > 0) &&
                  (objMasterdrez.amarillas[i].x == xact) &&
                  (objMasterdrez.amarillas[i].y == yact))
                p1 = &(objMasterdrez.amarillas[i]);
              if ((objMasterdrez.rojas[i].tipo > 0) &&
                  (objMasterdrez.rojas[i].x == xact) &&
                  (objMasterdrez.rojas[i].y == yact))
                p1 = &(objMasterdrez.rojas[i]);
            }
            if (objMasterdrez.coronando == 1) {
              for (int i = 0; i < 16; i++)
                if ((objMasterdrez.coronables[i].tipo > 0) &&
                    (objMasterdrez.coronables[i].x == xact) &&
                    (objMasterdrez.coronables[i].y == yact))
                  p1 = &(objMasterdrez.coronables[i]);
            }

            int xpas, ypas, colorpas;
            if (objMasterdrez.CapturaAlPaso(xact, yact, xfin, yfin,
                                            objMasterdrez.tablero, p1, xpas,
                                            ypas, colorpas)) {
              if (colorpas == BLANCO) {
                objMasterdrez.eatenPassantBlanco->Asignar(xpas, ypas);
              }
              if (colorpas == AMARILLO) {
                objMasterdrez.eatenPassantAmarillo->Asignar(xpas, ypas);
              }
              if (colorpas == NEGRO) {
                objMasterdrez.eatenPassantNegro->Asignar(xpas, ypas);
              }
              if (colorpas == ROJO) {
                objMasterdrez.eatenPassantRojo->Asignar(xpas, ypas);
              }
            }

            int promoting = objMasterdrez.promotingPawn(xfin, yfin, p1);
            if (promoting > 0) {
              objMasterdrez.coronando = 1;
              objMasterdrez.colorCoronado = promoting;
              objMasterdrez.colorCoronando = p1->color;
              objMasterdrez.xCoronando = xfin;
              objMasterdrez.yCoronando = yfin;
              objMasterdrez.coronables[0].color = p1->color;
              objMasterdrez.coronables[1].color = p1->color;
              objMasterdrez.coronables[2].color = p1->color;
              objMasterdrez.coronables[3].color = p1->color;
              if (promoting == BLANCO) {
                objMasterdrez.coronables[0].x = 12;
                objMasterdrez.coronables[1].x = 13;
                objMasterdrez.coronables[2].x = 14;
                objMasterdrez.coronables[3].x = 15;
                objMasterdrez.coronables[0].y = 0;
                objMasterdrez.coronables[1].y = 0;
                objMasterdrez.coronables[2].y = 0;
                objMasterdrez.coronables[3].y = 0;
              } else if (promoting == AMARILLO) {
                objMasterdrez.coronables[0].x = 0;
                objMasterdrez.coronables[1].x = 0;
                objMasterdrez.coronables[2].x = 0;
                objMasterdrez.coronables[3].x = 0;
                objMasterdrez.coronables[0].y = 0;
                objMasterdrez.coronables[1].y = 1;
                objMasterdrez.coronables[2].y = 2;
                objMasterdrez.coronables[3].y = 3;
              } else if (promoting == NEGRO) {
                objMasterdrez.coronables[0].x = 0;
                objMasterdrez.coronables[1].x = 1;
                objMasterdrez.coronables[2].x = 2;
                objMasterdrez.coronables[3].x = 3;
                objMasterdrez.coronables[0].y = 15;
                objMasterdrez.coronables[1].y = 15;
                objMasterdrez.coronables[2].y = 15;
                objMasterdrez.coronables[3].y = 15;
              } else if (promoting == ROJO) {
                objMasterdrez.coronables[0].x = 15;
                objMasterdrez.coronables[1].x = 15;
                objMasterdrez.coronables[2].x = 15;
                objMasterdrez.coronables[3].x = 15;
                objMasterdrez.coronables[0].y = 12;
                objMasterdrez.coronables[1].y = 13;
                objMasterdrez.coronables[2].y = 14;
                objMasterdrez.coronables[3].y = 15;
              }
            }

            // antes de ejecutar el movimiento:
            // Verificar si tiene algun reino en jaque
            int reinoEnMaster = -1;
            if (objMasterdrez.tieneMasterBlancas(
                    objMasterdrez.blancas, objMasterdrez.negras,
                    objMasterdrez.amarillas, objMasterdrez.rojas,
                    objMasterdrez.tablero, objMasterdrez.turno)) {
              reinoEnMaster = 0;
            }
            if (objMasterdrez.tieneMasterNegras(
                    objMasterdrez.blancas, objMasterdrez.negras,
                    objMasterdrez.amarillas, objMasterdrez.rojas,
                    objMasterdrez.tablero, objMasterdrez.turno)) {
              reinoEnMaster = 1;
            }
            if (objMasterdrez.tieneMasterAmarillas(
                    objMasterdrez.blancas, objMasterdrez.negras,
                    objMasterdrez.amarillas, objMasterdrez.rojas,
                    objMasterdrez.tablero, objMasterdrez.turno)) {
              reinoEnMaster = 2;
            }
            if (objMasterdrez.tieneMasterRojas(
                    objMasterdrez.blancas, objMasterdrez.negras,
                    objMasterdrez.amarillas, objMasterdrez.rojas,
                    objMasterdrez.tablero, objMasterdrez.turno)) {
              reinoEnMaster = 3;
            }

            // Se ejecuta el movimiento...
            objMasterdrez.movimiento(objMasterdrez.blancas,
                                     objMasterdrez.negras, objMasterdrez.rojas,
                                     objMasterdrez.amarillas,
                                     objMasterdrez.tablero);
            updateGL();

            objMasterdrez.seleccionandoPieza = 1;
            objMasterdrez.seleccionandoCasilla = 0;

            // Verificar si hay condicion de partida ganada
            if (objMasterdrez.partida_ganada(objMasterdrez.Pacto) == 1) {
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "VICTORIA") << "\n";
              gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                  objMasterdrez.curr_lang, "VICTORIA"));
              objMasterdrez.resetVariablesEstado();
              return;
            } else if (objMasterdrez.tablas(
                           objMasterdrez.blancas, objMasterdrez.negras,
                           objMasterdrez.amarillas, objMasterdrez.rojas,
                           objMasterdrez.controla, objMasterdrez.Pacto) == 1) {
              std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                     "TABLAS") << "\n";
              gUi.pUi->statusBar->showMessage(
                  objMasterdrez.get_message(objMasterdrez.curr_lang, "TABLAS"));
              objMasterdrez.resetVariablesEstado();
              return;
            }

            // Verificar si hubo posibilidad de Master y no se hizo: soplar
            // piezas
            if (reinoEnMaster > -1 && objMasterdrez.reyderrotado < 1) {
              if (objMasterdrez.turno == 0) {
                for (int i = 0; i < 16; i++)
                  if (objMasterdrez.soploBlancas[i] == 1) {
                    objMasterdrez.blancas[i].tipo = -1;
                    objMasterdrez.blancas[i].x = -1;
                    objMasterdrez.blancas[i].y = -1;
                    objMasterdrez.tablero[i][i].tipo = -1;
                    objMasterdrez.tablero[i][i].color = -1;
                  }
                std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                       "SOPLO_BLANCAS") << "\n";
                gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                    objMasterdrez.curr_lang, "SOPLO_BLANCAS"));
              } else if (objMasterdrez.turno == 1) {
                for (int i = 0; i < 16; i++)
                  if (objMasterdrez.soploAmarillas[i] == 1) {
                    objMasterdrez.amarillas[i].tipo = -1;
                    objMasterdrez.amarillas[i].x = -1;
                    objMasterdrez.amarillas[i].y = -1;
                    objMasterdrez.tablero[i][i].tipo = -1;
                    objMasterdrez.tablero[i][i].color = -1;
                  }
                std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                       "SOPLO_AMARILLAS")
                          << "\n";
                gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                    objMasterdrez.curr_lang, "SOPLO_AMARILLAS"));
              } else if (objMasterdrez.turno == 2) {
                for (int i = 0; i < 16; i++)
                  if (objMasterdrez.soploNegras[i] == 1) {
                    objMasterdrez.negras[i].tipo = -1;
                    objMasterdrez.negras[i].x = -1;
                    objMasterdrez.negras[i].y = -1;
                    objMasterdrez.tablero[i][i].tipo = -1;
                    objMasterdrez.tablero[i][i].color = -1;
                  }
                std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                       "SOPLO_NEGRAS") << "\n";
                gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                    objMasterdrez.curr_lang, "SOPLO_NEGRAS"));
              } else if (objMasterdrez.turno == 3) {
                for (int i = 0; i < 16; i++)
                  if (objMasterdrez.soploRojas[i] == 1) {
                    objMasterdrez.rojas[i].tipo = -1;
                    objMasterdrez.rojas[i].x = -1;
                    objMasterdrez.rojas[i].y = -1;
                    objMasterdrez.tablero[i][i].tipo = -1;
                    objMasterdrez.tablero[i][i].color = -1;
                  }
                std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                       "SOPLO_ROJAS") << "\n";
                gUi.pUi->statusBar->showMessage(objMasterdrez.get_message(
                    objMasterdrez.curr_lang, "SOPLO_ROJAS"));
              }

            } else {
              objMasterdrez.resetSoplos();
            }

            // Cambiar de turno solo si no estoy coronando
            /*if (objMasterdrez.coronando != 1) {
              objMasterdrez.turno =
                  objMasterdrez.calcular_turno(objMasterdrez.turno);
              if (objMasterdrez.turno + 1 == BLANCO) {
                std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                       "TURNO_BLANCAS") << "\n";
              } else if (objMasterdrez.turno + 1 == AMARILLO) {
                std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                       "TURNO_AMARILLAS")
                          << "\n";
              } else if (objMasterdrez.turno + 1 == NEGRO) {
                std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                       "TURNO_NEGRAS") << "\n";
              } else if (objMasterdrez.turno + 1 == ROJO) {
                std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                                       "TURNO_ROJAS") << "\n";
              }
            }*/
            objMasterdrez.turno = (objMasterdrez.turno + 1) % 4;
          } else {
            std::cout << objMasterdrez.get_message(
                             objMasterdrez.curr_lang,
                             "ERROR_SELECCIONANDO_CASILLA") << "\n";
            objMasterdrez.seleccionandoPieza = 1;
            objMasterdrez.seleccionandoCasilla = 0;
          }
        }
      }

      //===================== COMIENZO I.A. ============================
      int V[4], p1, c1, p2, c2, p3, c3, p4, c4, valorMaximo = 0;

      //=================== TURNO AMARILLAS =============================
      if (objMasterdrez.turno == 1 &&
          objMasterdrez.partida_ganada(objMasterdrez.Pacto) != 1) {

        updateGL();
        gUi.pUi->Reloj_Blancas->timer->stop();
        gUi.pUi->Reloj_Amarillas->timer->start();

        if (objMasterdrez.num_movimientos_amarillas < 7) {

          if (objMasterdrez.apertura_elegida == peones_centrales)
            objMasterdrez.apertura_peonescentrales_amarillas(
                ++objMasterdrez.num_movimientos_amarillas);
          /*else if (objMasterdrez.apertura_elegida == fianchetto_simple)
            objMasterdrez.apertura_fianchetto_simple_amarillas(
                ++objMasterdrez.num_movimientos_amarillas);*/
          else if (objMasterdrez.apertura_elegida == fianchetto_doble)
            objMasterdrez.apertura_Fianchetto_x2_Amarillas(
                ++objMasterdrez.num_movimientos_amarillas);
          else if (objMasterdrez.apertura_elegida == peones)
            objMasterdrez.apertura_peones_amarillas(
               ++objMasterdrez.num_movimientos_amarillas);
        } else {
          V[0] = objMasterdrez.movimientoMaquinaBlancas(
              &p1, &c1, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          V[1] = objMasterdrez.movimientoMaquinaAmarillas(
              &p2, &c2, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          V[2] = objMasterdrez.movimientoMaquinaNegras(
              &p3, &c3, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          V[3] = objMasterdrez.movimientoMaquinaRojas(
              &p4, &c4, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          for (int i = 0; i < 4; i++) {
            if (V[i] > valorMaximo) {
              valorMaximo = V[i];
            }
          }

          std::cout << "=== Turno Amarillas: mv1: " << V[0] << " mv2: " << V[1]
                    << " mv3: " << V[2] << " mv4: " << V[3]
                    << " valorMaximo: " << valorMaximo << " ==\n";

          // obteniendo la mejor casilla y la mejor pieza
          if (valorMaximo == V[0]) {
            objMasterdrez.casillaSeleccionada = c1;
            objMasterdrez.piezaSeleccionada = p1;
          } else if (valorMaximo == V[1]) {
            objMasterdrez.casillaSeleccionada = c2;
            objMasterdrez.piezaSeleccionada = p2;
          } else if (valorMaximo == V[2]) {
            objMasterdrez.casillaSeleccionada = c3;
            objMasterdrez.piezaSeleccionada = p3;
          } else {
            objMasterdrez.casillaSeleccionada = c4;
            objMasterdrez.piezaSeleccionada = p4;
          }

          // Se ejecuta el movimiento...
          objMasterdrez.movimiento(objMasterdrez.blancas, objMasterdrez.negras,
                                   objMasterdrez.rojas, objMasterdrez.amarillas,
                                   objMasterdrez.tablero);
        }
        objMasterdrez.turno = (objMasterdrez.turno + 1) % 4;
      }

      //=================== TURNO NEGRAS =============================
      if (objMasterdrez.turno == 2 &&
          objMasterdrez.partida_ganada(objMasterdrez.Pacto) != 1) {

        updateGL();

        gUi.pUi->Reloj_Amarillas->timer->stop();
        gUi.pUi->Reloj_Negras->timer->start();

        if (objMasterdrez.num_movimientos_negras < 7) {

          if (objMasterdrez.apertura_elegida == peones_centrales)
            objMasterdrez.apertura_Fianchetto_x2_Negras(
                ++objMasterdrez.num_movimientos_negras);
          else if (objMasterdrez.apertura_elegida == fianchetto_simple)
            objMasterdrez.apertura_peonescentrales_negras(
                ++objMasterdrez.num_movimientos_negras);
          else if (objMasterdrez.apertura_elegida == fianchetto_doble)
            objMasterdrez.apertura_fianchetto_simple_negras(
                ++objMasterdrez.num_movimientos_negras);
          else if (objMasterdrez.apertura_elegida == peones)
            objMasterdrez.apertura_peones_negras(
               ++objMasterdrez.num_movimientos_negras);

        } else {
          valorMaximo = 0;
          V[0] = objMasterdrez.movimientoMaquinaBlancas(
              &p1, &c1, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          V[1] = objMasterdrez.movimientoMaquinaAmarillas(
              &p2, &c2, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          V[2] = objMasterdrez.movimientoMaquinaNegras(
              &p3, &c3, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          V[3] = objMasterdrez.movimientoMaquinaRojas(
              &p4, &c4, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          for (int i = 0; i < 4; i++) {
            if (V[i] > valorMaximo) {
              valorMaximo = V[i];
            }
          }

          std::cout << "=== Turno Negras: mv1: " << V[0] << " mv2: " << V[1]
                    << " mv3: " << V[2] << " mv4: " << V[3]
                    << " valorMaximo: " << valorMaximo << " ==\n";

          // obteniendo la mejor casilla y la mejor pieza
          if (valorMaximo == V[0]) {
            objMasterdrez.casillaSeleccionada = c1;
            objMasterdrez.piezaSeleccionada = p1;
          } else if (valorMaximo == V[1]) {
            objMasterdrez.casillaSeleccionada = c2;
            objMasterdrez.piezaSeleccionada = p2;
          } else if (valorMaximo == V[2]) {
            objMasterdrez.casillaSeleccionada = c3;
            objMasterdrez.piezaSeleccionada = p3;
          } else {
            objMasterdrez.casillaSeleccionada = c4;
            objMasterdrez.piezaSeleccionada = p4;
          }

          // Se ejecuta el movimiento...
          objMasterdrez.movimiento(objMasterdrez.blancas, objMasterdrez.negras,
                                   objMasterdrez.rojas, objMasterdrez.amarillas,
                                   objMasterdrez.tablero);
        }
        objMasterdrez.turno = (objMasterdrez.turno + 1) % 4;
      }

      //=================== TURNO ROJAS =============================
      if (objMasterdrez.turno == 3 &&
          objMasterdrez.partida_ganada(objMasterdrez.Pacto) != 1) {

        updateGL();

        gUi.pUi->Reloj_Negras->timer->stop();
        gUi.pUi->Reloj_Rojas->timer->start();

        if (objMasterdrez.num_movimientos_rojas < 7) {

          if (objMasterdrez.apertura_elegida == fianchetto_simple)
            objMasterdrez.apertura_fianchetto_simple_rojas(
                ++objMasterdrez.num_movimientos_rojas);
          else if (objMasterdrez.apertura_elegida == fianchetto_doble)
            objMasterdrez.apertura_Fianchetto_x2_Rojas(
                ++objMasterdrez.num_movimientos_rojas);
          else if (objMasterdrez.apertura_elegida == peones_centrales)
            objMasterdrez.apertura_peonescentrales_rojas(
                ++objMasterdrez.num_movimientos_rojas);
          else if (objMasterdrez.apertura_elegida == peones)
            objMasterdrez.apertura_peones_rojas(
               ++objMasterdrez.num_movimientos_rojas);

        } else {
          valorMaximo = 0;
          V[0] = objMasterdrez.movimientoMaquinaBlancas(
              &p1, &c1, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          V[1] = objMasterdrez.movimientoMaquinaAmarillas(
              &p2, &c2, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          V[2] = objMasterdrez.movimientoMaquinaNegras(
              &p3, &c3, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          V[3] = objMasterdrez.movimientoMaquinaRojas(
              &p4, &c4, objMasterdrez.blancas, objMasterdrez.amarillas,
              objMasterdrez.negras, objMasterdrez.rojas, objMasterdrez.tablero,
              objMasterdrez.turno, 1);

          for (int i = 0; i < 4; i++) {
            if (V[i] > valorMaximo) {
              valorMaximo = V[i];
            }
          }

          std::cout << "=== Turno Rojas: mv1: " << V[0] << " mv2: " << V[1]
                    << " mv3: " << V[2] << " mv4: " << V[3]
                    << " valorMaximo: " << valorMaximo << " ==\n";

          // obteniendo la mejor casilla y la mejor pieza
          if (valorMaximo == V[0]) {
            objMasterdrez.casillaSeleccionada = c1;
            objMasterdrez.piezaSeleccionada = p1;
          } else if (valorMaximo == V[1]) {
            objMasterdrez.casillaSeleccionada = c2;
            objMasterdrez.piezaSeleccionada = p2;
          } else if (valorMaximo == V[2]) {
            objMasterdrez.casillaSeleccionada = c3;
            objMasterdrez.piezaSeleccionada = p3;
          } else {
            objMasterdrez.casillaSeleccionada = c4;
            objMasterdrez.piezaSeleccionada = p4;
          }

          // Se ejecuta el movimiento...
          objMasterdrez.movimiento(objMasterdrez.blancas, objMasterdrez.negras,
                                   objMasterdrez.rojas, objMasterdrez.amarillas,
                                   objMasterdrez.tablero);

          updateGL();
        }
        objMasterdrez.turno = (objMasterdrez.turno + 1) % 4;

        gUi.pUi->Reloj_Rojas->timer->stop();
        gUi.pUi->Reloj_Blancas->timer->start();
      }
      break;
      //===================== FIN I.A.=============================
    }
  }

  updateGL();
}
//=================================================================

void MyOpengl::Dibujar() { Proyeccion.dibujarMasterdrez(); }
