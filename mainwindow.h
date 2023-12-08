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
private:
    Ui::MainWindow *ui;
    ByteArrayModel *model;
    ImageModel *imodel;
// SLOTS
    void onLoadFile();
    void onSaveFile();
    void onOpenRGB();
    void onBinBtnClicked();
};
#endif // MAINWINDOW_H
