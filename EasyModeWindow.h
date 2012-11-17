#ifndef SHUFFLEQUESTIONNAIRE_H
#define SHUFFLEQUESTIONNAIRE_H

#include "MediumModeWindow.h"
#include "Shuffle.h"
#include"AstuceWindow.h"

class EasyModeWindow : public MediumModeWindow
{
    Q_OBJECT
public:
    EasyModeWindow(const int m_multiplicateur, bool shuffleNeeded, bool chrono);
    ~EasyModeWindow();
protected:
    QPushButton *astuces;
public slots:
    void openAstuce() const;
    void open();
};

#endif // SHUFFLEQUESTIONNAIRE_H
