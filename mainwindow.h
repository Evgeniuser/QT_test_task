#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OpenFile_triggered();

    void on_Exit_triggered();

   void on_Layers_currentIndexChanged(int index);

   void on_fileName_currentTextChanged(const QString &arg1);

   void on_closeCurFile_triggered();

private:
    Ui::MainWindow *ui;
    QImage img;

    void MainWindow::fill_ComboLayers();
    QImage scaledLayer(QImage _img, float s, int l);
    int MainWindow::countLayers(QImage _img, float s);
};

#endif // MAINWINDOW_H
