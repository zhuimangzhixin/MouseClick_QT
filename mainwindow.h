#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QTextBrowser>
#include <QFile>
#include <QThread>
#include <QTimer>
#include <QMessageBox>
#include "mypushbutton.h"
#include "cparameter.h"
#include "clickmode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    QCursor cursor;                                                                             //光标

    //控件
    QPushButton * posBtn[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};                    //位置按键
    MyPushButton * startBtn = nullptr;                                                           //开始按键
    MyPushButton * stopBtn = nullptr;                                                           //开始按键
    QLineEdit * posLEdit[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};                    //位置编辑
    QLineEdit * intervalLEdit[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};               //时间间隔编辑
    QCheckBox * isInRepeatCheckBox[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};          //判断是否在循环中
    QLabel * tagLabel[4] = {nullptr, nullptr, nullptr, nullptr};                                //标签

    //判断变量
    bool isPosBtnPressed[5] = {false,false,false,false,false};                                       //判断按键是否点击
//    bool isToStop = true;

    //文件读取变量
    QFile * parameterFile;

    //参数维护变量
    CParameter test;
    CParameter parameterC[5];

    //点击模式
    ClickMode clickmode;

    void myInit();
    void myUpdate();

    //重写paintEvent事件，画背景图
    void paintEvent(QPaintEvent *);

    //重写鼠标事件，获取位置
    void mousePressEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent* );

//    void mouseDoubleClickEvent(QMouseEvent* );
//    void mouseMoveEvent(QMouseEvent*);
//    void wheelEvent(QWheelEvent* );
};

#endif // MAINWINDOW_H
