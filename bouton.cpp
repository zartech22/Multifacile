#include "bouton.h"

Bouton::Bouton()
{

}
Bouton::Bouton(const QString &text, int nombre) : QPushButton(text), m_multiplicateur(nombre)
{
}
void Bouton::clique()
{
    emit cliquer(m_multiplicateur);
}
