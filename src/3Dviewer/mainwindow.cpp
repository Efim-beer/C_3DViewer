#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  ui->widget->setUpdatesEnabled(false);
  readSettings();
  ui->scroll_line->setValue(ui->widget->line_w);
  ui->scroll_point->setValue(ui->widget->point_w);
  if (ui->widget->prodj_centr)
    ui->center->setChecked(true);
  else
    ui->parallel->setChecked(true);
  if (ui->widget->line_pp)
    ui->line_punktir->setChecked(true);
  if (ui->widget->point_s == 0)
    ui->radio_point->setChecked(true);
  else if (ui->widget->point_s == 1)
    ui->radio_cicle->setChecked(true);
  else
    ui->radio_square->setChecked(true);
}

MainWindow::~MainWindow() {
  writeSettings();
  delete ui;
}

void MainWindow::on_build_clicked() {
  ui->widget->setUpdatesEnabled(true);
  ui->widget->update();
  QString num_text = QString::number(ui->widget->count_v);
  ui->label_v->setText(num_text);
  num_text = QString::number(ui->widget->count_f);
  ui->label_f->setText(num_text);
}

void MainWindow::on_phon_color_clicked() {
  QColor ph_color = QColorDialog::getColor(Qt::white, this, "Выбор цвета");
  if (ph_color.isValid()) {
    ui->widget->red = ph_color.redF();
    ui->widget->green = ph_color.greenF();
    ui->widget->blue = ph_color.blueF();
  }
  ui->widget->update();
}

void MainWindow::on_open_file_clicked() {
  ui->widget->str = QFileDialog::getOpenFileName(this, tr("Open File"), "/",
                                                 tr("Object file (*.obj)"));
  ui->lab_name_file->setText(ui->widget->str);
  ui->widget->setUpdatesEnabled(true);
  ui->widget->update();
}

void MainWindow::on_point_color_clicked() {
  QColor ph_color = QColorDialog::getColor(Qt::white, this, "Выбор цвета");
  if (ph_color.isValid()) {
    ui->widget->p_red = ph_color.redF();
    ui->widget->p_green = ph_color.greenF();
    ui->widget->p_blue = ph_color.blueF();
  }
  ui->widget->update();
}

void MainWindow::on_line_color_clicked() {
  QColor ph_color = QColorDialog::getColor(Qt::white, this, "Выбор цвета");
  if (ph_color.isValid()) {
    ui->widget->l_red = ph_color.redF();
    ui->widget->l_green = ph_color.greenF();
    ui->widget->l_blue = ph_color.blueF();
  }
  ui->widget->update();
}

void MainWindow::on_scroll_sliderMoved(int position) {
  ui->widget->m = (float)position / 100;
  QString label = QString::number(ui->widget->m);
  ui->label_scroll->setText("Масштаб 1 * " + label);
  ui->widget->update();
}

void MainWindow::on_scroll_x_sliderMoved(int position) {
  ui->widget->m_x = position;
  QString label = QString::number(position);
  ui->label_scroll_x->setText("по оси Х: " + label);
  ui->widget->update();
}

void MainWindow::on_scroll_y_sliderMoved(int position) {
  ui->widget->m_y = position;
  QString label = QString::number(position);
  ui->label_scroll_y->setText("по оси Y: " + label);
  ui->widget->update();
}

void MainWindow::on_scroll_z_sliderMoved(int position) {
  ui->widget->m_z = position;
  QString label = QString::number(position);
  ui->label_scroll_z->setText("по оси Z: " + label);
  ui->widget->update();
}

void MainWindow::on_scroll_x_m_sliderMoved(int position) {
  ui->widget->x_m = (float)position / 100;
  QString label = QString::number(ui->widget->x_m);
  ui->label_scroll_x_2->setText("по оси Х: " + label);
  ui->widget->update();
}

void MainWindow::on_scroll_y_m_sliderMoved(int position) {
  ui->widget->y_m = (float)position / 100;
  QString label = QString::number(ui->widget->y_m);
  ui->label_scroll_y_2->setText("по оси Y: " + label);
  ui->widget->update();
}

void MainWindow::on_scroll_z_m_sliderMoved(int position) {
  ui->widget->z_m = (float)position / 100;
  QString label = QString::number(ui->widget->z_m);
  ui->label_scroll_z_2->setText("по оси Z: " + label);
  ui->widget->update();
}

void MainWindow::on_center_clicked(bool checked) {
  ui->widget->prodj_centr = checked;
  ui->widget->update();
}

void MainWindow::on_parallel_clicked(bool checked) {
  ui->widget->prodj_centr = !checked;
  ui->widget->update();
}

void MainWindow::on_scroll_line_sliderMoved(int position) {
  ui->widget->line_w = (float)position / 10;
  QString label = QString::number(ui->widget->line_w);
  ui->label_line_w->setText("Толщина: " + label);
  ui->widget->update();
}

void MainWindow::on_line_punktir_clicked(bool checked) {
  ui->widget->line_pp = checked;
  ui->widget->update();
}

void MainWindow::on_scroll_point_sliderMoved(int position) {
  ui->widget->point_w = (float)position / 10;
  QString label = QString::number(ui->widget->point_w);
  ui->label_point_w->setText("Толщина: " + label);
  ui->widget->update();
}

void MainWindow::on_radio_point_clicked() {
  ui->widget->point_s = 0;
  ui->widget->update();
}

void MainWindow::on_radio_cicle_clicked() {
  ui->widget->point_s = 1;
  ui->widget->update();
}

void MainWindow::on_radio_square_clicked() {
  ui->widget->point_s = 2;
  ui->widget->update();
}

void MainWindow::writeSettings() {
  QSettings settings("E2", "3dViewer", this);

  settings.setValue("proj", ui->widget->prodj_centr);
  settings.setValue("line_pp", ui->widget->line_pp);
  settings.setValue("line_s", ui->widget->line_s);
  settings.setValue("line_w", ui->widget->line_w);
  settings.setValue("point_s", ui->widget->point_s);
  settings.setValue("point_w", ui->widget->point_w);
  settings.setValue("background_red", ui->widget->red);
  settings.setValue("background_green", ui->widget->green);
  settings.setValue("background_blue", ui->widget->blue);
  settings.setValue("line_red", ui->widget->l_red);
  settings.setValue("line_green", ui->widget->l_green);
  settings.setValue("line_blue", ui->widget->l_blue);
  settings.setValue("point_red", ui->widget->p_red);
  settings.setValue("point_green", ui->widget->p_green);
  settings.setValue("point_blue", ui->widget->p_blue);
}

void MainWindow::readSettings() {
  QSettings settings("E2", "3dViewer", this);

  ui->widget->prodj_centr = settings.value("proj").toBool();
  ui->widget->line_pp = settings.value("line_pp").toBool();
  ui->widget->line_s = settings.value("line_s").toUInt();
  ui->widget->line_w = settings.value("line_w").toInt();
  ui->widget->point_s = settings.value("point_s").toInt();
  ui->widget->point_w = settings.value("point_w").toInt();
  ui->widget->red = settings.value("background_red").toFloat();
  ui->widget->green = settings.value("background_green").toFloat();
  ui->widget->blue = settings.value("background_blue").toFloat();
  ui->widget->l_red = settings.value("line_red").toFloat();
  ui->widget->l_green = settings.value("line_green").toFloat();
  ui->widget->l_blue = settings.value("line_blue").toFloat();
  ui->widget->p_red = settings.value("point_red").toFloat();
  ui->widget->p_green = settings.value("point_green").toFloat();
  ui->widget->p_blue = settings.value("point_blue").toFloat();
}

void MainWindow::on_screenshot_clicked() {
  if (!flag) {
    QString filename = QFileDialog ::getSaveFileName(
        this, tr("Сохранить файл"), "../untitled.bmp",
        tr("Images (*.bmp *.jpeg)"));
    //    qDebug() << filename;
    ui->widget->screenshot(filename);
  }
}

void MainWindow::on_to_gif_clicked() {
  if (!flag) {
    gifFileName = QFileDialog::getSaveFileName(
        this, "GIF file", "../untitled.gif", "Image file (*.gif)");
    ui->to_gif->setText("RECORD");
    flag = 1;
  } else if (flag == 1) {
    ui->to_gif->setText("STOP");
    gif = new QGifImage;
    img = new QImage;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(recordingGif()));
    connect(timer, SIGNAL(timeout()), this, SLOT(GLview::paintGL()));
    timer->start(100);
    flag = 2;
  } else {
    flag = 0;
    ui->to_gif->setText("Record to Gif");
    timer->stop();
    gif->save(gifFileName);
  }
}

void MainWindow::recordingGif() {
  *img = ui->widget->grabFramebuffer().scaled(480, 640, Qt::KeepAspectRatio);
  gif->addFrame(*img, 0);
}
