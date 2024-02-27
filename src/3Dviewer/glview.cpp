#include "glview.h"

GLview::GLview(QWidget *parent) : QOpenGLWidget(parent) {}

void GLview::screenshot(QString filename) {
  this->grabFramebuffer().save(filename, NULL, 100);
  paintGL();
}

void GLview::initializeGL() {
  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(0, 0, width(), height());
  glClearColor(red, green, blue, 1.0f);

  glEnable(GL_DEPTH_TEST);
}

void GLview::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLview::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(red, green, blue, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (prodj_centr) {
    glFrustum(-1, 1, -1, 1, 3, 50);
    d_z_m = z_m - 5;
  } else {
    glOrtho(-1, 1, -1, 1, -10, 10);
    d_z_m = z_m;
  }
  glTranslatef(x_m, y_m, d_z_m);
  QByteArray buf = str.toLocal8Bit();
  const char *f_name = buf.data();
  obj data;
  int facet = 0;

  size_obj(f_name, &count_v, &count_f, &v_in_f);
  struct_malloc(&data);
  scan_obj(&data, f_name);

  glVertexPointer(3, GL_FLOAT, 0, data.vertexes);
  glScalef(m, m, m);
  glRotatef(m_x, 1.0, 0, 0);
  glRotatef(m_y, 0, 1.0, 0);
  glRotatef(m_z, 0, 0, 1.0);

  if (point_s) {
    if (point_s == 1)
      glEnable(GL_POINT_SMOOTH);
    else
      glDisable(GL_POINT_SMOOTH);

    glColor3d(p_red, p_green, p_blue);
    glPointSize(point_w);

    glBegin(GL_POINTS);
    for (int j = 1; j < count_v + 1; j++) {
      glVertex3d(data.vertexes[j][0], data.vertexes[j][1], data.vertexes[j][2]);
    }
    glEnd();
  }

  if (line_pp)
    line_s = 0x00F0;
  else
    line_s = 0xffff;

  glDisable(GL_POINT_SMOOTH);
  glColor3f(l_red, l_green, l_blue);
  glLineWidth(line_w);
  glLineStipple(3, line_s);
  //    0x00F0 0xffff
  glEnable(GL_LINE_STIPPLE);
  for (int j = 0; j < count_f; j++) {
    glBegin(GL_LINES);
    //отрисовывает линии, из которых состоит грань
    for (int i = 0; i < v_in_f - 1; i++) {
      facet = data.facets[j][i];
      glVertex3f(data.vertexes[facet][0], data.vertexes[facet][1],
                 data.vertexes[facet][2]);
      facet = data.facets[j][i + 1];
      glVertex3f(data.vertexes[facet][0], data.vertexes[facet][1],
                 data.vertexes[facet][2]);
    }
    //отрисовывает последнюю линию
    facet = data.facets[j][v_in_f - 1];
    glVertex3f(data.vertexes[facet][0], data.vertexes[facet][1],
               data.vertexes[facet][2]);
    facet = data.facets[j][0];
    glVertex3f(data.vertexes[facet][0], data.vertexes[facet][1],
               data.vertexes[facet][2]);
    glEnd();
  }
  glDisable(GL_LINE_STIPPLE);

  struct_free(&data);
}
