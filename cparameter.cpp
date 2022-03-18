#include "cparameter.h"
#include <typeinfo>

CParameter::CParameter(){
    pos.setX(0);
    pos.setY(0);
}

CParameter::CParameter(QString inQString){
    QStringList temp = inQString.split(',');
    pos.setX(temp[0].toInt());
    pos.setY(temp[1].toInt());
    interval = temp[2].toDouble();
    isInRepeat = temp[3].toInt();
}

CParameter::CParameter(int posX = 0, int posY = 0, int _interval = 0, bool _isInRepeat = false){
    pos.setX(posX);
    pos.setY(posY);
    interval = _interval;
    isInRepeat = _isInRepeat;
}

QString CParameter::toString(){
    csvOut = QString::number(pos.x()) +","+ QString::number(pos.y()) +","+ QString::number(interval) + "," + QString::number(isInRepeat);
    return csvOut;
}


void CParameter::setPos(int x, int y){
    pos.setX(x);
    pos.setY(y);
}

void CParameter::setPosX(int x){
    pos.setX(x);
}

void CParameter::setPosY(int y){
    pos.setY(y);
}

void CParameter::setInterval(int _interval){
    interval = _interval;
}

void CParameter::setIsInRepeat(bool _isInRepeat){
    isInRepeat = _isInRepeat;
}

QPoint CParameter::getPos(){
    return pos;
}

int CParameter::getPosX(){
    return pos.x();
}

int CParameter::getPosY(){
    return pos.y();
}

double CParameter::getInterval(){
    return interval;
}

bool CParameter::getIsInRepeat(){
    return isInRepeat;
}
