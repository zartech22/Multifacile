#ifndef SHUFFLEQUESTIONNAIRE_H
#define SHUFFLEQUESTIONNAIRE_H

#include "MediumModeWindow.h"
#include "Shuffle.h"

class EasyModeWindow : public MediumModeWindow
{
    Q_OBJECT
public:
    EasyModeWindow(const int m_multiplicateur, bool shuffleNeeded);
    ~EasyModeWindow();
protected:
    QPushButton *melanger;
public slots:
    void Melange();
};

#endif // SHUFFLEQUESTIONNAIRE_H
