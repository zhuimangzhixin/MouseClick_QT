#ifndef CPARAMETER_H
#define CPARAMETER_H

#include <QPoint>
#include <QDebug>

class CParameter
{
public:
    CParameter();
    CParameter(QString);
    CParameter(int, int, int, bool);

    QString toString();

    void setPos(int, int);
    void setPosX(int);
    void setPosY(int);
    void setInterval(int);
    void setIsInRepeat(bool);

    QPoint getPos();
    int getPosX();
    int getPosY();
    double getInterval();
    bool getIsInRepeat();

private:

    QPoint pos;
    double interval = 1;
    bool isInRepeat = false;

    //转为csv
    QString csvOut = "123";

};

#endif // CPARAMETER_H
