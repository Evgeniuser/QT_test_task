#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMap>
#include <math.h>
#include <iostream>
#include <QStringList>

QMap<QString,QImage> imgPair;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Layers->setEnabled(false);
    ui->menuBar->setVisible(false);

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
    _img = _img.scaled(_img.width()/pow(s,l),_img.height()/pow(s,l));
    ui->sizeL->setText(QString::number(_img.width())+"x"+QString::number(_img.height()));
    _img = _img.scaled(img.width(),img.height());
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
    QString path = QFileDialog::getOpenFileName(this,"Open File","","*.png *.jpg *.jpeg");

        if(path.isEmpty())
            return;
        else
        {
            ui->Layers->setEnabled(false);
            ui->fileName->setEnabled(false);
            QGraphicsScene *graphic = new QGraphicsScene(this);
            img.load(path);
            QString name = getName(path);
            imgPair.insert(name,img);
            sortMap(name);
            //ui->fileName->setCurrentText(name);
            ui->Layers->clear();
            graphic->addPixmap(QPixmap::fromImage(img));
            fill_ComboLayers();
            ui->Layers->setCurrentIndex(0);
            ui->Layers->setEnabled(true);
            ui->fileName->setEnabled(true);
            ui->sizeL->setText(QString::number(img.width())+"x"+QString::number(img.height()));
            ui->graphicsView->setScene(graphic);

        }
}

void MainWindow::on_Exit_triggered()
{
   MainWindow::close();
}

void MainWindow::on_fileName_currentTextChanged(const QString &arg1)
{
    if(!ui->fileName->isEnabled())
        return;

    ui->Layers->setEnabled(false);
    ui->Layers->clear();
    img = imgPair.value(arg1);

    QGraphicsScene *emp = ui->graphicsView->scene();
    emp->clear();
    emp->addPixmap(QPixmap::fromImage(img));

    ui->graphicsView->setScene(emp);
    fill_ComboLayers();
    ui->Layers->setCurrentIndex(0);
    ui->Layers->setEnabled(true);
    ui->fileName->setEnabled(true);
    ui->sizeL->setText(QString::number(img.width())+"x"+QString::number(img.height()));
}

void MainWindow::on_Layers_currentIndexChanged(int index)
{
    if(!ui->Layers->isEnabled())
        return;
    QGraphicsScene *emp = ui->graphicsView->scene();
    emp->clear();
    emp->addPixmap(QPixmap::fromImage(scaledLayer(img,2,index)));
    ui->graphicsView->setScene(emp);
}

void MainWindow::on_closeCurFile_triggered()
{
    if(!ui->fileName->isEnabled() || ui->fileName->count()==0)
        return;
    ui->fileName->setEnabled(false);
    imgPair.remove(ui->fileName->currentText());
    ui->fileName->removeItem(ui->fileName->currentIndex());
    img = imgPair.value(ui->fileName->currentText());
    QGraphicsScene *emp = ui->graphicsView->scene();
    emp->clear();
    emp->addPixmap(QPixmap::fromImage(img));
    ui->graphicsView->setScene(emp);
    ui->Layers->setEnabled(false);
    ui->Layers->clear();
    if(ui->fileName->currentIndex()==-1)
    {
        ui->sizeL->setText(QString::number(img.width())+"x"+QString::number(img.height()));
        return;
    }
    fill_ComboLayers();
    ui->Layers->setCurrentIndex(0);
    ui->Layers->setEnabled(true);
    ui->fileName->setEnabled(true);
}

void MainWindow::sortMap(QString curInd)
{
    QStringList imgName;
    QMap<QString, QImage>::const_iterator i = imgPair.constBegin();
    while (i != imgPair.constEnd()) {
        if(imgName.empty())
            imgName.insert(0,i.key());
        else
        {
            QString str_temp = i.key();
            long temp,sorce;
            int flg = 0;
            for(int j = 0; j<imgName.size();j++)
            {
                temp = cDiag(imgPair.value(imgName.value(j)));
                sorce = cDiag(imgPair.value(str_temp));
                if(temp>sorce || temp==sorce)
                {
                    imgName.insert(j,str_temp);
                    flg = 1;
                    break;
                }
            }
            if(flg == 0)
                imgName.insert(imgName.size(),str_temp);
        }
        ++i;
    }
    ui->fileName->setEnabled(false);
    ui->fileName->clear();
    ui->fileName->addItems(imgName);
    ui->fileName->setCurrentText(curInd);
    ui->fileName->setEnabled(true);
}

long MainWindow::cDiag(QImage _img)
{
    return sqrt(pow(_img.height(),2)+pow(_img.width(),2));
}

QString MainWindow::getName(QString path)
{
    QStringList list = path.split('\/');
    QString del = list.last();
    return del;
}
