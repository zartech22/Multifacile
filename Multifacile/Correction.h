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

#ifndef CORRECTION_H
#define CORRECTION_H

#include <QLabel>
#include <QMultiMap>
#include <QString>

#include "MainWindowEnums.h"
#include "DataFileMgr.h"

enum RecordState
{
    RECORD, UNVALIDRECORD, NORECORD
};

typedef enum RecordState RecordState;

class Correction : public QObject  // Classe donnant la correction pour une classe : Le texte à affciher pour la correction, la note
{
    Q_OBJECT

public:
    Correction(Mode mode, const unsigned short int multiple, int* order, unsigned short int *userAnswers, const unsigned short int time = 0);
    Correction(unsigned short int* multiple, int* order, unsigned short *userAnswers, const unsigned short int time = 0);

    ~Correction();

    int getCorrection(QString texte[], bool isGood[]);  //renvoie la note, modifie texte en lui attribuant le texte a affciher pour la correction, initialise isGood (Vrai si reponse correcte Faux sinon)

private:
    unsigned short int _seconds;
    unsigned short int _Multiple;
    unsigned short int _note;

    int* _orderTab;
    unsigned short int* _multipleTab;
    unsigned short int* _answers;

    bool _isHardMode;

    DataFileMgr *_manager;

    Mode _difficultyMode;

    void manageTime();  //enregistre le temps et la reussite ou non de la table dans le fichier xml
    void notation(unsigned short int resultat[], bool isGood[]);  //initialise isGood et modifie la note
    void doCorrection(QString texte[], bool isGood[], unsigned short int resultat[]) const;  //modifie texte avec ou sans resultat en fonction de isGood
    QString Correction::getModeGroupName() const;  //donne la chaine de caractere correspondant au mode

};

#endif // CORRECTION_H
