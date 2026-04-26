#ifndef MYOPENGL_H
#define MYOPENGL_H

#include "mainwindow.h"

class MyOpengl : public QGLWidget {
  Q_OBJECT
public:
  explicit MyOpengl(QWidget *parent = 0);
  ~MyOpengl();

signals:
  // signaling rotation from mouse movement
  void xRotationChanged(int angle);
  void yRotationChanged(int angle);
  void zRotationChanged(int angle);
  void clicked();

public slots:
  // slots for xyz-rotation slider
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);

protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);
  void keyPressEvent(QKeyEvent *e);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

private:
  void Dibujar();

  float xRot;
  float yRot;
  float zRot;
  float Profundidad;

  void ViewTrans();
  void setViewTrans();
  int startPicking(int cursorX, int cursorY);

  float viewX;
  float viewY;

  QPoint lastPos;
};

#endif // MYOPENGL_H
