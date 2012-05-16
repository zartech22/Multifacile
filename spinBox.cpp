#include "spinBox.h"

SpinBox::SpinBox() : QSpinBox()
{
}
void SpinBox::keyPressEvent(QKeyEvent *event)
{
    QSpinBox::keyPressEvent(event);
    QKeyEvent key = *event;
    if(key.key() == Qt::Key_Enter)
    {
        emit enterKeyPressed(numero);
    }
    else
        return;
}
void SpinBox::setNumero(int num)
{
    numero = num;
}
