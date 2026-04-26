#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graficos.h"
#include "lcdnumber.h"

t_manejador_ui gUi;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  /*****************************
      * Idiomas
      *****************************/
  tinyxml2::XMLError loadOkay =
      objMasterdrez.doclang[0].LoadFile("lang_es.xml");
  if (loadOkay != tinyxml2::XML_SUCCESS) {
    QMessageBox messageBox;
    messageBox.critical(0, "Masterdrez 3D",
                        "Error: Reading lang_es.xml file !");
    exit(-1);
  }

  loadOkay = objMasterdrez.doclang[1].LoadFile("lang_en.xml");
  if (loadOkay != tinyxml2::XML_SUCCESS) {
    QMessageBox messageBox;
    messageBox.critical(0, "Masterdrez 3D",
                        "Error: Reading lang_en.xml file !");
    exit(-1);
  }

  ui->setupUi(this);

  ui->Reloj_Blancas->setSegmentStyle(QLCDNumber::Flat);
  ui->Reloj_Amarillas->setSegmentStyle(QLCDNumber::Flat);
  ui->Reloj_Negras->setSegmentStyle(QLCDNumber::Flat);
  ui->Reloj_Rojas->setSegmentStyle(QLCDNumber::Flat);

  new QDebugStream(std::cout, ui->Mensajes_Juego);

  std::cout << "ULA y FUNDACION MASTERDREZ\n";
  std::cout
      << "Masterdrez 3D / Version 3.5.2.1 / Pre - Alfa / En desarrollo\n\n";
  std::cout << "Mensajes de Juego:\n";

  Proyeccion.inicializarGraficos();

  gUi.pasarPuntero(ui);

  ui->statusBar->showMessage("Listo");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionAcerca_de_triggered() {
  QMessageBox about_box(this);
  about_box.setText(
      "Masterdrez 3D Versión: 3.5.2.1\n\nCREDITOS:\n\nCerrada, Luis\n"
      "Díaz, Francisco\nEspinoza, Leidy\nGutiérrez, Jesús");
  about_box.adjustSize();
  about_box.exec();
}

void MainWindow::on_actionSalir_triggered() { close(); }

void MainWindow::on_borrarConsola_clicked() { ui->Mensajes_Juego->clear(); }

// Menu de selección de color
void MainWindow::on_actionBlanco_Azul_triggered() {

  Proyeccion.setColorCasilla(0.5, 0.5, 0.8);
}

void MainWindow::on_actionBlanco_Verde_triggered() {

  Proyeccion.setColorCasilla(0.0, 0.8, 0.0);
}

void MainWindow::on_actionBlanco_Marron_triggered() {

  Proyeccion.setColorCasilla(0.6, 0.3, 0.1);
}

void MainWindow::on_actionBlanco_Gris_triggered() {
  Proyeccion.setColorCasilla(0.5f, 0.5f, 0.5f); // 0.75 como valor anterior
}

void MainWindow::on_actionPartida_Humano_M_quina_3_triggered() {
  std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                         "PARTIDA_COMENZADA") << "\n";
  ui->statusBar->showMessage(
      objMasterdrez.get_message(objMasterdrez.curr_lang, "PARTIDA_COMENZADA"));

  objMasterdrez.inicializarTablero();
  objMasterdrez.resetVariablesEstado();
  objMasterdrez.partidaHM = 1;
  objMasterdrez.piezasColocadas = 1;
  objMasterdrez.partidaComenzada = 1;
  objMasterdrez.seleccionandoPieza = 1;
  objMasterdrez.dibujaPiezas = 1;

  ui->Reloj_Blancas->Init(20, 0);
  ui->Reloj_Amarillas->Init(20, 0);
  ui->Reloj_Negras->Init(20, 0);
  ui->Reloj_Rojas->Init(20, 0);

  ui->Reloj_Blancas->timer->setInterval(1000);
  ui->Reloj_Amarillas->timer->setInterval(1000);
  ui->Reloj_Negras->timer->setInterval(1000);
  ui->Reloj_Rojas->timer->setInterval(1000);

  ui->Reloj_Blancas->timer->start();
}

void MainWindow::on_actionPartida_Humano_Humano_3_triggered() {
  std::cout << objMasterdrez.get_message(objMasterdrez.curr_lang,
                                         "PARTIDA_COMENZADA") << "\n";
  ui->statusBar->showMessage(
      objMasterdrez.get_message(objMasterdrez.curr_lang, "PARTIDA_COMENZADA"));

  objMasterdrez.inicializarTablero();
  objMasterdrez.resetVariablesEstado();
  objMasterdrez.piezasColocadas = 1;
  objMasterdrez.partidaComenzada = 1;
  objMasterdrez.seleccionandoPieza = 1;
  objMasterdrez.dibujaPiezas = 1;
  objMasterdrez.apertura_elegida = objMasterdrez.elegir_apertura();

  // QString valor_apertura =  "Valor de apertura: " +
  // QString::number(objMasterdrez.apertura_elegida);
  // ui->statusBar->showMessage(valor_apertura);

  ui->Reloj_Blancas->Init(20, 0);
  ui->Reloj_Amarillas->Init(20, 0);
  ui->Reloj_Negras->Init(20, 0);
  ui->Reloj_Rojas->Init(20, 0);

  ui->Reloj_Blancas->timer->setInterval(1000);
  ui->Reloj_Amarillas->timer->setInterval(1000);
  ui->Reloj_Negras->timer->setInterval(1000);
  ui->Reloj_Rojas->timer->setInterval(1000);

  ui->Reloj_Blancas->timer->start();
}

void MainWindow::on_actionLibro_de_ayuda_triggered() {
  QString adobeReade =
      "C:/Program Files/Adobe/Acrobat Reader DC/Reader/AcroRd32.exe";

  QString fileName = "C:/Users/First Vision/Documents/Qt "
                     "Project/Masterdrez-qt/pdf/Reglas del Masterdrez EDICION "
                     "AJEDREZ.pdf";

  QStringList arguments;
  arguments << fileName;

  QProcess *myProcess = new QProcess();
  if (!myProcess)
    return;

  myProcess->start(adobeReade, arguments, QIODevice::ReadOnly);
  if (myProcess->waitForStarted())
    ui->statusBar->showMessage("Archivo de reglas cargado");
  else
    ui->statusBar->showMessage("Adobe Reader DC no está instalado");
}
