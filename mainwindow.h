#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QsciScintilla;

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
    void onBtn1Clicked();
    void onBtn2Clicked();

private:
    Ui::MainWindow *ui;
    QsciScintilla* m_edit1;
    QsciScintilla* m_edit2;
};
#endif // MAINWINDOW_H
