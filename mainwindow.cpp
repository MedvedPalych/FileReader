#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bytearraymodel.h"
#include "imagemodel.h"

#include <QtDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setVisible(0);
    ui->dataField->setVisible(0);
    ui->setDataButton->setVisible(0);

//    QByteArray array = QByteArray("HELLO WORLD");
//    ByteArrayModel* model = new ByteArrayModel();
//    model->setArray(array);
//    ui->tableView->setModel(model);
    imodel = new ImageModel();
    model  = new ByteArrayModel();

    connect(ui->setDataButton, SIGNAL(clicked())
                       ,this, SLOT(onSetData()));
    connect(ui->actionLoad, SIGNAL(triggered(bool))
                       ,this, SLOT(onLoadFile()));
    connect(ui->actionSave, SIGNAL(triggered(bool))
                       ,this, SLOT(onSaveFile()));
    connect(ui->actionOpenRGB, SIGNAL(triggered(bool)) //ДОМАШКА 1
                       ,this, SLOT(onOpenRGB()));
    connect(ui->binBtn,     SIGNAL(clicked())
                       ,this, SLOT(onBinBtnClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSetData()
{
    QAbstractItemModel* model = ui->tableView->model();
    if (model) {
        qDebug()<<"model is set";
        ByteArrayModel* bmodel = qobject_cast< ByteArrayModel*>(model);
        if (bmodel) {
            qDebug()<<"model is ByteArray model";
            QString data = ui->dataField->text();
            bmodel->setArray(data.toUtf8());
        }
    }
}

void MainWindow::onLoadFile() {

   ui->binBtn->setEnabled(1);
   QString filePath = QFileDialog::getOpenFileName(
                        this, "Load file name", ".");
   QFile file(filePath);
   if (!file.exists())
       return;
   if (!file.open(QFile::ReadOnly))
       return;
   QByteArray data = file.readAll();
   model->setArray(data);
   ui->tableView->setModel(model);
   ui->tableView->resizeColumnsToContents();

}

void MainWindow::onOpenRGB() {
  ui->binBtn->setDisabled(1);
  QImage image;
  QString filePath = QFileDialog::getOpenFileName(this, "Load file name", ".");
  if (image.load(filePath))
      imodel->setImage(image);
  ui->tableView->setModel(imodel);
  ui->tableView->resizeColumnsToContents();
}

void MainWindow::onBinBtnClicked()
{
  if (ui->binBtn->text() == "Show Binary") {
      model->switchFormat();
      ui->tableView->setModel(model);
      ui->tableView->resizeColumnsToContents();
      ui->binBtn->setText("Show Byte");
    } else
  if (ui->binBtn->text() == "Show Byte") {
      model->switchFormat();
      ui->tableView->setModel(model);
      ui->tableView->resizeColumnsToContents();
      ui->binBtn->setText("Show Binary");
    }
}

void MainWindow::onSaveFile() {
  QAbstractItemModel* model = ui->tableView->model();
  if (!model)
    return;
  ByteArrayModel* bmodel = qobject_cast< ByteArrayModel*>(model);
  if (!bmodel)
    return;
  QByteArray data = bmodel->getArray();
  QString filePath = QFileDialog::getSaveFileName(
        this, "Save file name", ".");
  QFile file(filePath);
  if (!file.open(QFile::WriteOnly))
    return;
  file.write(data);
  file.flush();
  file.close();
}
