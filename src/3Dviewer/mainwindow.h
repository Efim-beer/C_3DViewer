#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glview.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QSettings>
#include <QTimer>
#include <QWidget>
#include <qgifimage.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "s21_3d.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_build_clicked();

  void on_phon_color_clicked();

  void on_open_file_clicked();

  void on_point_color_clicked();

  void on_line_color_clicked();

  void on_scroll_sliderMoved(int position);

  void on_scroll_x_sliderMoved(int position);

  void on_scroll_y_sliderMoved(int position);

  void on_scroll_z_sliderMoved(int position);

  void on_scroll_x_m_sliderMoved(int position);

  void on_scroll_y_m_sliderMoved(int position);

  void on_scroll_z_m_sliderMoved(int position);

  void on_center_clicked(bool checked);

  void on_parallel_clicked(bool checked);

  void on_scroll_line_sliderMoved(int position);

  void on_line_punktir_clicked(bool checked);

  void on_scroll_point_sliderMoved(int position);

  void on_radio_point_clicked();

  void on_radio_cicle_clicked();

  void on_radio_square_clicked();

  void writeSettings();

  void readSettings();

  void on_screenshot_clicked();

  void on_to_gif_clicked();

  void recordingGif();

private:
  Ui::MainWindow *ui;
  QSettings *settings = NULL;

  int flag = 0;
  QTimer *timer;
  QGifImage *gif;
  QImage *img;
  QString gifFileName;
};
#endif // MAINWINDOW_H
