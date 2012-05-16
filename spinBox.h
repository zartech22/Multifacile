#ifndef SPINBOX_H
#define SPINBOX_H

#include <QSpinBox>
#include <QKeyEvent>
#include <QString>

class SpinBox : public QSpinBox
{
    Q_OBJECT
public:
    SpinBox();
    void keyPressEvent(QKeyEvent *event);
    void setNumero(int num);
private:
    int numero;
signals:
    void enterKeyPressed(int);
};

#endif // SPINBOX_H
