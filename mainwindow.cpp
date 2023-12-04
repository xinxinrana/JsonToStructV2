#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "jsonexample.h"
#include "jsontostructengine.h"

#include <QJsonDocument>
#include <QByteArray>
#include <QJsonObject>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->edit1->setText(jsonExample::complexJson());

    connect(ui->btn1,&QPushButton::clicked,this,&MainWindow::onBtn1Clicked);
    connect(ui->btn2,&QPushButton::clicked,this,&MainWindow::onBtn2Clicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtn1Clicked()
{
    JsonToStructEngine engine;
    auto jsonStr = ui->edit1->toPlainText();
    auto jsonObj = (QJsonDocument().fromJson(jsonStr.toLatin1())).object();

    engine.installJsonToStruct(jsonObj);
    qDebug()<<engine.count();
}

void MainWindow::onBtn2Clicked()
{
//    QStringList strs;
//    strs    << "AZZA"
//            << "AZZZ"
//            << "AZAZ"
//            << "AZAY"
//            << "ZZZZ"
//               << "ZZ93."
//                  << "中文符号——."
//            ;


//    for(auto str : strs){
//        qDebug()<< str <<"  <<  "<<Tools::getNextOrder(false,str);
//        qDebug()<< str <<"  <<  "<<Tools::getNextOrder(true);
//    }
}

