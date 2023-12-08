#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bytearraymodel.h"
#include "imagemodel.h"
//#include "progressbardelegate.h"
#include "hexdelegate.h"
#include "chardelegate.h"
#include "bindelegate.h"
#include "imagedelegate.h"

#include <QtDebug>
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QDataWidgetMapper>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow),
     model(nullptr), imodel(nullptr)
{
    ui->setupUi(this);

    connect(ui->actionLoad,    &QAction::triggered,  this, &MainWindow::onLoadFile);
    connect(ui->actionSave,    &QAction::triggered,  this, &MainWindow::onSaveFile);
    connect(ui->actionOpenRGB, &QAction::triggered,  this, &MainWindow::onOpenRGB);
    connect(ui->binBtn,        &QPushButton::clicked,this, &MainWindow::onBinBtnClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::onSetData()
{
    QAbstractItemModel* model = ui->hexView->model();
    if (model) {
        qDebug()<<"model is set";
        ByteArrayModel* bmodel = qobject_cast< ByteArrayModel*>(model);
        if (bmodel) {
            qDebug()<<"model is ByteArray model";
            bmodel->setArray(data.toUtf8());
        }
    }
}*/

void MainWindow::onLoadFile() {

   QString filePath = QFileDialog::getOpenFileName(
                        this, "Load file name", ".");
   QFile file(filePath);
   if (!file.exists())
       return;
   if (!file.open(QFile::ReadOnly))
       return;
   QByteArray data = file.readAll();

   ui->binBtn->setEnabled(1); // можем смотреть двоичку НЕ imodel

   model  = new ByteArrayModel();
   model->setArray(data);

   QItemSelectionModel* selModel;
   selModel = new QItemSelectionModel(model);

   ui->hexView->setModel(model);
   ui->hexView->setItemDelegate(new HexDelegate(ui->hexView));
   ui->hexView->setSelectionModel(selModel);
   //ui->hexView->resizeColumnsToContents();

   ui->charView->setModel(model);
   ui->charView->setItemDelegate(new CharDelegate(ui->charView));
   ui->charView->setSelectionModel(selModel);
   //ui->charView->resizeColumnsToContents();
   //делегаты перехватывают операции по отображению, игноря эти
   QDataWidgetMapper* dmapper = new QDataWidgetMapper(this);
   dmapper->setModel(model);
   dmapper->addMapping(ui->D0, model->columnCount(QModelIndex())-1);
   connect(selModel, &QItemSelectionModel::currentRowChanged,
            dmapper, &QDataWidgetMapper::setCurrentModelIndex);
   imodel = nullptr;

}

void MainWindow::onOpenRGB() {

  imodel = new ImageModel();

  ui->binBtn->setDisabled(1); // у imodel двоичку смотреть не будем
  QImage image;
  QString filePath = QFileDialog::getOpenFileName(this, "Load file name",
                               QDir::currentPath(),"Images (*.bmp; *.jpg)");
  if (image.load(filePath))
      imodel->setImage(image);
  ui->hexView->setModel(imodel);
  model = nullptr;
  ui->hexView->setItemDelegate(new imagedelegate(ui->hexView));
  //ui->hexView->resizeColumnsToContents();
  // использование делегатов перекрывает стандартные механизмы отображения
}

void MainWindow::onBinBtnClicked()
{
  if (ui->binBtn->text() == "Show Binary") {
      model->switchFormat();
      ui->hexView->setItemDelegate(new BinDelegate(ui->hexView));
            ui->binBtn->setText("Show Byte");
    } else
  if (ui->binBtn->text() == "Show Byte") {
      model->switchFormat();
      ui->hexView->setItemDelegate(new HexDelegate(ui->hexView));
      ui->binBtn->setText("Show Binary");
    }
}

void MainWindow::onSaveFile() {

    QString filePath = QFileDialog::getSaveFileName(
                this, "Save file name", ".");
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly))
        return;

    if (this->model == nullptr) {  // если задана модель картинки
        imodel->getModelImage().save(file.fileName());
    } else
    if (this->imodel == nullptr) { // если задана модель байтмассива
        QByteArray data = this->model->getArray();
        file.write(data);
    }
    file.flush();
    file.close();

}
