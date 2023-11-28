#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bytearraymodel.h"

#include <QtDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->label->setVisible(0);
//    ui->dataField->setVisible(0);
//    ui->setDataButton->setVisible(0);

    QByteArray array = QByteArray("1234567890");

    ByteArrayModel* model = new ByteArrayModel();
    model->setArray(array);

    ui->tableView->setModel(model);

    connect(ui->setDataButton, SIGNAL(clicked())
                ,this, SLOT(onSetDataRequest()));
    connect(ui->actionLoad, SIGNAL(triggered(bool))
                ,this, SLOT(onLoadFileRequest()));
    connect(ui->actionSave, SIGNAL(triggered(bool))
                ,this, SLOT(onSaveFileRequest()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSetDataRequest()
{
    QAbstractItemModel* model = ui->tableView->model();
    if (model) {
        qDebug()<<"model is set";
        ByteArrayModel* bmodel = qobject_cast< ByteArrayModel*>(model);
        if (bmodel) {
            qDebug()<<"model is ByteArray model";
            QString data = ui->dataField->text();
            bmodel->setArray(data.toUtf8());
// ПРИМЕЧАНИЕ!!! Здесь сталкиваемся с тем, что при смене модели отрисовка НЕ обновляется
// данные обновляются только при выполнении действия, обновляющего вид. Пример того, что можно сделать:
           // ui->tableView->setModel(0);     // сбрасываем
           // ui->tableView->setModel(bmodel);// и загружаем (но так НЕКРАСИВО)

        }
    }
}

void MainWindow::onLoadFileRequest() {
   QAbstractItemModel* model = ui->tableView->model();
   if (!model)
       return;
   ByteArrayModel* bmodel = qobject_cast< ByteArrayModel*>(model);
   if (!bmodel)
       return;
   QString filePath = QFileDialog::getOpenFileName(
                        this, "Load file name", ".");
   QFile file(filePath);
   if (!file.exists())
       return;
   if (!file.open(QFile::ReadOnly))
       return;
   QByteArray data = file.readAll();
   bmodel->setArray(data);
}

void MainWindow::onSaveFileRequest() {
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

