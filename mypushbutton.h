#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);
    //构造函数，参数一，正常显示图片的路径，参数二，按下后显示的图片的路径
    MyPushButton(QString normalImg, QString pressImg=""){
        this->normalImgPath = normalImg;
        this->pressImgPath = pressImg;

        QPixmap pix;
        bool ret = pix.load(normalImg);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //成员属性 保存用户传入的默认显示路径 以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效
    void zoom1();
    void zoom2();

    //重写按钮按下和释放实践
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
