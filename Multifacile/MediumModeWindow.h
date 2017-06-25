/*Copyright (C) <2013> <Plestan> <Kévin>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#ifndef FEN_SECONDAIRE_H
#define FEN_SECONDAIRE_H

#include <QApplication>
#include <QCloseEvent>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QPoint>
#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include <QStyleOption>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "MinCloseMenu.h"
#include "Shuffle.h"
#include "Correction.h"
#include "CustomMessageBox.h"
#include "AbstractModeWindow.h"

class MediumModeWindow : public AbstractModeWindow  // Classe representant la fenetre des tables de mode moyen.
{
    Q_OBJECT
public :

    MediumModeWindow();
    MediumModeWindow(const operande multiplicateur, bool actualProgressifMode);
    ~MediumModeWindow();

    virtual operande getMultiple() { return _multiple; }  //retourne la table en cours
    void progressifModeHasChanged(const bool actualProgressifMode) { _progressifMode = actualProgressifMode; checkTableAvailable();}  //si changement de mode de progression, on verifie si la table est disponible
protected :

    operande _multiple;
    operande _note;
    std::array<unsigned short int, 10> _array;

    bool _progressifMode;

    Mode _mode;

    QPushButton *_nextPrev[2];

    virtual void initAskLabels() override;  //initialise le texte des multiplications
    void initNextPrev();  //initialise les boutons suivant et precedent
    void closeEvent(QCloseEvent *event);  //reimplementation
    void setNewNumber(const operande newNumber);  //change de table
    virtual void checkTableAvailable();

public slots:

    virtual void correct() override;  //Fait la correction
    void Next();  //fait passer à la table suivante
    void Previous();  //fait passer à la table precedente
    virtual void Retry();  //remet tout à zero pour un nouvel essai
};

#endif // FEN_SECONDAIRE_H
