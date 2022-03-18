#include "clickmode.h"

ClickMode::ClickMode()
{

}

void ClickMode::lClick(int x, int y){
    mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x * 65535 / 1920, y * 65535 /1080, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void ClickMode::run(){
    if(!isToStop){
        lClick(parameterC[nthPointToClick].getPosX(),parameterC[nthPointToClick].getPosY());
        ++nthPointToClick;
        nthPointToClick %= maxN;
        mytimer->start(parameterC[nthPointToClick].getInterval() * 1000);
    }
}


ClickMode::~ClickMode()
{
//    delete mytimer;
}
