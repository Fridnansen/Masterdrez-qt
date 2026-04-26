#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>

#define GLUT_DISABLE_ATEXIT_HACK
#define GLUT_BUILDING_LIB
#define GLUT_NO_LIB_PRAGMA
#define GLUT_NO_WARNING_DISABLE

#include <GL/glut.h> //3.7.6

#include "qdebugstream.h"
//==========================================================================

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_actionAcerca_de_triggered();

  void on_actionSalir_triggered();

  void on_borrarConsola_clicked();

  void on_actionBlanco_Azul_triggered();

  void on_actionBlanco_Verde_triggered();

  void on_actionBlanco_Marron_triggered();

  void on_actionBlanco_Gris_triggered();

  void on_actionPartida_Humano_M_quina_3_triggered();

  void on_actionPartida_Humano_Humano_3_triggered();

  void on_actionLibro_de_ayuda_triggered();

private:
  Ui::MainWindow *ui;
};

class t_manejador_ui {

public:
  Ui::MainWindow *pUi;
  void pasarPuntero(Ui::MainWindow *ui) { pUi = ui; }
};

extern t_manejador_ui gUi;

#endif // MAINWINDOW_H
