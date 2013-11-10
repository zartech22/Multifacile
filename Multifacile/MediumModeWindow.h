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

class MediumModeWindow : public QWidget  // Classe representant la fenetre des tables de mode moyen.
{
    Q_OBJECT
public :

    MediumModeWindow() {}
    MediumModeWindow(const int multiplicateur, bool actualProgressifMode);
    ~MediumModeWindow();

    virtual const unsigned short int getMultiple() { return _multiple; }  //retourne la table en cours
    void progressifModeHasChanged(const bool actualProgressifMode) { _progressifMode = actualProgressifMode; checkTableAvailable();}  //si changement de mode de progression, on verifie si la table est disponible
protected :

    unsigned short int _multiple;
    unsigned short int _note;
    int _array[10];
    unsigned short int _secondes;

    bool _progressifMode;

    Mode _mode;

    QSignalMapper *_mapper;

    QLabel *_label[10];
    QLabel *_text;
    QLabel *_minute;
    QLabel *_seconde;
    QLabel *_deuxPoint;
    QLabel *_labelPoint[10];
    QLabel *_trueFalseLabel[2][10];
    QLabel *_labelCorrection[10];

    QPushButton *_corriger;
    QPushButton *_quitter;
    QPushButton *_nextPrev[2];

    QLineEdit *_reponses[10];

    QTimer *_chronometre;

    void initStyle();  //initialise le style
    virtual void initButtons();  //initialise les boutons
    void initTimer();  //initialise l'affichage du temps
    void initLineEdit();  //initailise les lineEdit
    void initLabels();  //Initialise le texte
    virtual void initTableLabels();  //initialise le texte des multiplications
    void initNextPrev();  //initialise les boutons suivant et precedent
    void closeEvent(QCloseEvent *event);  //reimplementation
    void paintEvent(QPaintEvent *);  //reimplementation pour prise en charge du css
    void setNewNumber(const unsigned short int newNumber);  //change de table
    void startTime();  //lance le timer
    virtual void checkTableAvailable();

signals:

    void addSeconde(int);  //emis lorsqu'on doit ajouter une seconde
    void wasClosed();  //emis losrqu'on quitte la fenetre de table

public slots:

    virtual void correct();  //Fait la correction
    void newSecond();  //ajoute une seconde
    void newSetFocus(const int number);  //fait passer le focus d'un lineEdit a un autre
    void Next();  //fait passer à la table suivante
    void Previous();  //fait passer à la table precedente
    virtual void Retry();  //remet tout à zero pour un nouvel essai
    void showEvent(QShowEvent *);  //reimplementation pour donner le focus a la premiere lineEdit au debut
    void updateLabel(const int temps) const;  //met a jour le texte donnant le temps

};

#endif // FEN_SECONDAIRE_H
