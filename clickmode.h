#ifndef CLICKMODE_H
#define CLICKMODE_H

#include <windows.h>
#include <QTimer>
#include "cparameter.h"

class ClickMode
{
public:
    ClickMode();
    ~ClickMode();

    int nthPointToClick = 0;
    int maxN = 1;
    QTimer * mytimer;

    CParameter parameterC[5];

    bool isToStop = false;

    void lClick(int, int);
    void run();

};

#endif // CLICKMODE_H
