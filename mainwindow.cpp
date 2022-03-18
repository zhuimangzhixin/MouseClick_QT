#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>

/*  标题：鼠标辅助工具
 *  作者：程卫平
 *  时间：2022.03.18
 *  Qt 5.9.0 (i386-little_endian-ilp32 shared (dynamic) release build; by MSVC 2015) on "windows"
 *  OS: Windows 10 (10.0) [winnt version 10.0.19044]
 *  Architecture: x86_64; features: SSE2 SSE3 SSSE3 SSE4.1 SSE4.2 AVX AVX2
 *  Environment:
 *  Features: QT_NO_EXCEPTIONS
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置主窗口
    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/mouse.jpg"));
    setWindowTitle("鼠标辅助工具");

    ui->menuBar->hide();
//    ui->mainToolBar->hide();

    //初始化鼠标光标
    cursor.setShape(Qt::OpenHandCursor);
    setCursor(cursor);

    //初始化图标位置
    for(int i = 0; i < 5; ++i){
        posBtn[i] = new MyPushButton(":/res/pos.png");
        posBtn[i]->setParent(this);
        posBtn[i]->move(QPoint(25, 50 + i*70));

        posLEdit[i] = new QLineEdit(this);
        posLEdit[i]->move(QPoint(75, 60 + i*70));

        intervalLEdit[i] = new QLineEdit(this);
        intervalLEdit[i]->move(QPoint(200, 60 + i*70));
        intervalLEdit[i]->resize(50, 30);

        isInRepeatCheckBox[i] = new QCheckBox(this);
        isInRepeatCheckBox[i]->move(QPoint(260, 60 + i*70));
    }
    startBtn = new MyPushButton(":/res/Start.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 1.2, this->height() * 0.7);

    stopBtn = new MyPushButton(":/res/Stop.png");
    stopBtn->setParent(this);
    stopBtn->move(this->width() * 0.5 + startBtn->width() * 0.2, this->height() * 0.7);

    tagLabel[0] = new QLabel("坐标选取",this);
    tagLabel[0]->move(QPoint(posBtn[0]->x() + (posBtn[0]->width())/2 - 15 * 2, 20));

    tagLabel[1] = new QLabel("坐标",this);
    tagLabel[1]->move(QPoint(posLEdit[0]->x() + (posLEdit[0]->width())/2 - 15, 20));

    tagLabel[2] = new QLabel("时间间隔",this);
    tagLabel[2]->move(QPoint(intervalLEdit[0]->x() + (intervalLEdit[0]->width())/2 - 15*2, 20));

    clickmode.mytimer = new QTimer(this);

    //初始化变量
    parameterFile = new QFile("./parameterFile.txt");
    if(!parameterFile->open(QIODevice::ReadOnly|QIODevice::Text)){//读取文件并同步
        parameterFile->open(QIODevice::WriteOnly|QIODevice::Text);
        for(int i=0; i<5; ++i){
            parameterFile->write(clickmode.parameterC[i].toString().toUtf8());
            parameterFile->write("\n");
        }
        parameterFile->write(clickmode.parameterC[4].toString().toUtf8());
        parameterFile->close();
        parameterFile->open(QIODevice::ReadOnly|QIODevice::Text);
    }
    myInit();
    parameterFile->close();

    //按键操作
    for(int i=0; i<5; ++i){ //位置按键
        connect(posBtn[i], posBtn[i]->pressed, [=](){//判断按键i是否点击
            cursor.setShape(Qt::ClosedHandCursor);
            setCursor(cursor);
            isPosBtnPressed[i] = true;
        });
        connect(posBtn[i],posBtn[i]->clicked,[=](){//判断按键i点击之后是否在内部释放
            qDebug() << "按键1释放的x = "<< cursor.pos().rx() << "; y = " << cursor.pos().ry();
            isPosBtnPressed[i] = false;
            posLEdit[i]->setText(QString::number(cursor.pos().rx()) + ", " + QString::number(cursor.pos().ry()));
        });
    }
    connect(startBtn,&MyPushButton::clicked,[=](){
        //弹跳效果

        startBtn->zoom1();
        startBtn->zoom2();

//        isToStop = false;
        int n = -1;
        for(int i=0; i<5; ++i){
            if(clickmode.parameterC[i].getIsInRepeat() == true)
                n = i+1;
        }
        clickmode.maxN = n;
        clickmode.isToStop = false;
        clickmode.run();
    });
    connect(stopBtn,&MyPushButton::clicked,[=](){
        //弹跳效果
        stopBtn->zoom1();
        stopBtn->zoom2();
        clickmode.isToStop = true;
        clickmode.nthPointToClick = 0;
    });

    //控件更改操作
    for(int i=0; i<5; ++i){ //位置按键
        connect(posLEdit[i], posLEdit[i]->editingFinished, [=](){//判断按键i是否点击
            myUpdate();
        });
        connect(intervalLEdit[i], intervalLEdit[i]->editingFinished, [=](){//判断按键i是否点击
            myUpdate();
        });
        connect(isInRepeatCheckBox[i], isInRepeatCheckBox[i]->stateChanged, [=](){//判断按键i是否点击
            myUpdate();
        });
    } 
    connect(clickmode.mytimer, &QTimer::timeout,[=](){ //时间到了操作
        clickmode.run();
    });
    connect(ui->actioninstruct,&QAction::triggered,[=](){
        QMessageBox::information(this, "软件说明", "    坐标：设置点击位置，可以手动输入或拖动坐标图标实现。\n    时间间隔：可以设置前后两次点击时间间隔，单位为秒。\n    选择框：点击位置是否加入循环，如果不选择，则点击位置及其时间间隔将不加入循环。\n    Start：开始点击循环，点击时立即点第一下，然后空第二个时间间隔，再带点击第二下，再空第三个时间间隔，以此类推。");
    });
    connect(ui->actionexit,&QAction::triggered,[=](){
        int temp = QMessageBox::question(this, "退出", "确定退出程序？");
        if(temp == QMessageBox::Yes){
            exit(0);
        }
    });
}

void MainWindow::myInit(){//初始化函数
    for(int i=0; i<5; ++i){
        //初始化类
        clickmode.parameterC[i] = CParameter(QString::fromUtf8(parameterFile->readLine()));
        //初始化各个控件
        posLEdit[i]->setText(QString::number(clickmode.parameterC[i].getPosX()) + ", " + QString::number(clickmode.parameterC[i].getPosY()) );
        intervalLEdit[i]->setText(QString::number(clickmode.parameterC[i].getInterval()));
        isInRepeatCheckBox[i]->setChecked(clickmode.parameterC[i].getIsInRepeat());
    }
}

void MainWindow::myUpdate(){//更新函数
    QString inQString;//输入字符串
//    qDebug() << "更新";
    for(int i=0; i<5; ++i){//将控件同步到类中
        if(intervalLEdit[i]->text().toInt() < 0.05){
            QMessageBox::warning(this, "输入错误", "时间间隔不得小于0.05");
            return;
        }
        inQString = posLEdit[i]->text() + "," + intervalLEdit[i]->text() + "," + QString::number(int(isInRepeatCheckBox[i]->checkState()));
        inQString.replace("，",",");
        clickmode.parameterC[i] = CParameter(inQString);
    }
    parameterFile->open(QIODevice::WriteOnly|QIODevice::Text);
    for(int i=0; i<4; ++i){//同步到文件中
        parameterFile->write(clickmode.parameterC[i].toString().toUtf8());
        parameterFile->write("\n");
    }
    parameterFile->write(clickmode.parameterC[4].toString().toUtf8());
    parameterFile->close();
}

void MainWindow::paintEvent(QPaintEvent * ){
    //设置画家
    QPainter painter(this);
    QPixmap pix;

    //设置背景图片
    pix.load(":/res/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void MainWindow::mousePressEvent(QMouseEvent* event){ //鼠标按下事件重写
    if(event->button() == Qt::LeftButton){
        cursor.setShape(Qt::ClosedHandCursor);
        setCursor(cursor);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event){ //鼠标释放事件重写
    if(event->button() == Qt::LeftButton){
        cursor.setShape(Qt::OpenHandCursor);
        setCursor(cursor);
    }
    for(int i=0; i<5; ++i){
        if(event->button() == Qt::LeftButton && isPosBtnPressed[i] == true){//按键1松口位置
            isPosBtnPressed[i] = false;
            posLEdit[i]->setText(QString::number(event->globalPos().rx()) + ", " + QString::number(event->globalPos().ry()));
        }
    }
    myUpdate();
}

MainWindow::~MainWindow()
{
    delete ui;
}
