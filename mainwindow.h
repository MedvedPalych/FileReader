#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class ImageModel;
class ByteArrayModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onSetData();
    void onLoadFile();
    void onSaveFile();
    void onOpenRGB();
    void onBinBtnClicked();
private:
    Ui::MainWindow *ui;
    ImageModel *imodel;
    ByteArrayModel *model;
};
#endif // MAINWINDOW_H
