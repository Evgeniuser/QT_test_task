#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Layers->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage MainWindow::scaledLayer(QImage _img,float s, int l)
{
    if(l == 0)
    {
     ui->sizeL->setText(QString::number(_img.width())+"x"+QString::number(_img.height()));
     return _img;
    }
    _img = _img.scaled(_img.width()/(s*l),_img.height()/(s*l));
    ui->sizeL->setText(QString::number(_img.width())+"x"+QString::number(_img.height()));
    _img = _img.scaled(_img.width()*(s*l),_img.height()*(s*l));
    return _img;
}

int MainWindow::countLayers(QImage _img, float s)
{
    int nLayers = 0;
    long img_size;
    if(_img.height()>=_img.width())
        img_size = _img.width();
    else
        img_size = _img.height();
    while(img_size>0)
    {
        img_size/=s;
        nLayers++;
    }
    return nLayers;
}

void MainWindow::fill_ComboLayers()
{

    int cLayers = MainWindow::countLayers(img,2);
    ui->Layers->addItem("Оригинал");
    for(size_t i = 0; i < cLayers;i++)
    {
        ui->Layers->addItem("Слой "+ QString::number(i));
    }
}

void MainWindow::on_OpenFile_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,"Open File","","*.png *.jpg *.jpeg *.gif *.bmp");

        if(path.isEmpty())
            return;
        else
        {
            ui->Layers->setEnabled(false);
            QGraphicsScene *graphic = new QGraphicsScene(this);
            img.load(path);
            ui->fileName->addItem(path);
            ui->Layers->clear();
            graphic->addPixmap(QPixmap::fromImage(img));
            fill_ComboLayers();
            ui->Layers->setCurrentIndex(0);
            ui->Layers->setEnabled(true);
            ui->sizeL->setText(QString::number(img.width())+"x"+QString::number(img.height()));



            ui->graphicsView->setScene(graphic);

        }
}

void MainWindow::on_Exit_triggered()
{
   MainWindow::close();
}

void MainWindow::on_Layers_currentIndexChanged(int index)
{
    if(!ui->Layers->isEnabled())
        return;
    QGraphicsScene *emp = ui->graphicsView->scene();
    emp->addPixmap(QPixmap::fromImage(scaledLayer(img,2,index)));
    ui->graphicsView->setScene(emp);
}
