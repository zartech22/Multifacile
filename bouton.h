#ifndef BOUTON_H
#define BOUTON_H

#include <QPushButton>

class Bouton : public QPushButton
{
    Q_OBJECT
public :
    Bouton();
    Bouton(const QString &text, int nombre);
public slots :
    void clique();
signals :
    void cliquer(int);
private :
    int m_multiplicateur;
};

#endif // BOUTON_H
