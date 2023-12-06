#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "structtest.h"
#include "jsonexample.h"
#include "jsontostructengine.h"

#include <QJsonDocument>
#include <QByteArray>
#include <QJsonObject>
#include <QDebug>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>  // C++ lexer for syntax highlighting
#include <Qsci/qscilexerjson.h>  // C++ lexer for syntax highlighting

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_edit1(new QsciScintilla(this))
    , m_edit2(new QsciScintilla(this))
{
    ui->setupUi(this);

    ui->container1Lay->addWidget(m_edit1);
    m_edit1->setLexer(new QsciLexerJSON());
    m_edit1->setFolding(QsciScintilla::BoxedTreeFoldStyle);

    ui->container2Lay->addWidget(m_edit2);
    m_edit2->setLexer(new QsciLexerCPP());
    m_edit2->setFolding(QsciScintilla::BoxedTreeFoldStyle);

    m_edit1->setText(jsonExample::complexJson());

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
    auto jsonStr = m_edit1->text();
    auto jsonObj = (QJsonDocument().fromJson(jsonStr.toLatin1())).object();

    auto res = engine.installJsonToStruct(jsonObj,"MainStruct");
    m_edit2->setText(res);
    qDebug()<<engine.count();
}

void MainWindow::onBtn2Clicked()
{
    auto jsonStr = m_edit1->text();
    auto jsonObj = (QJsonDocument().fromJson(jsonStr.toLatin1())).object();

    MainStruct i;
    i = jsonObj;


    qDebug() << i.rename_meta.testTheList2List.at(1).at(0).key;

    qDebug() << i.notesList.count();
}

