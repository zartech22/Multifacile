#ifndef HARDMODEWINDOW_H
#define HARDMODEWINDOW_H

#include "MediumModeWindow.h"

class HardModeWindow : public MediumModeWindow
{
public:
    HardModeWindow();
    ~HardModeWindow();
private:
    int multiple[10];
    void open();
};

#endif // HARDMODEWINDOW_H
