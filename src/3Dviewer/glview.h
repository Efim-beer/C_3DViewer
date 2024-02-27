#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>

#ifdef __cplusplus
extern "C" {
#endif
#include "s21_3d.h"
#ifdef __cplusplus
}
#endif

class GLview : public QOpenGLWidget {
public:
  GLview(QWidget *parent = nullptr);
  QString str = {};
  int count_v = 0, count_f = 0, v_in_f = 0;

  float red = 1, green = 0.9, blue = 0.3;
  float p_red = 1, p_green = 0, p_blue = 0;
  float l_red = 1, l_green = 0, l_blue = 0;
  float m = 0.5;
  int m_x = 0, m_y = 0, m_z = 0;
  float x_m = 0, y_m = 0, z_m = 0, d_z_m = 0;
  bool prodj_centr = false;
  float line_w = 1, point_w = 1;
  bool line_pp = false;
  int line_s = 0xffff, point_s = 1;

  void screenshot(QString filename);

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
};

#endif // GLVIEW_H
