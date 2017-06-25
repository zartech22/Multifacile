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
#include <array>
#include <memory>

#include "Include.h"
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
    Correction(Mode mode, operande multiple, std::array<operande, 10> &order, std::array<operande, 10> &userAnswers, const operande time = 0);
    Correction(std::array<operande, 10> &multiples, std::array<operande, 10> &order, std::array<operande, 10> &userAnswers, const operande time = 0);

    int getCorrection(QString texte[], bool isGood[]);  //renvoie la note, modifie texte en lui attribuant le texte a affciher pour la correction, initialise isGood (Vrai si reponse correcte Faux sinon)

private:
    static const QString _goodAnswer;
    static const QString _badAnswer;

    struct Multiple
    {
        bool isHard;

        union
        {
            operande multiple;
            std::array<operande, 10> multiples;
        };
    };

    struct Multiple _multiple;

    operande _seconds;
    //operande *_multiple;
    operande _note;

    std::array<unsigned short int, 10> _orderTab;
    //operande* _multipleTab;
    std::array<operande, 10> _answers;

    //bool _isHardMode;

    std::unique_ptr<DataFileMgr> _manager;

    Mode _difficultyMode;

    void manageTime();  //enregistre le temps et la reussite ou non de la table dans le fichier xml
    void notation(operande resultat[], bool isGood[]);  //initialise isGood et modifie la note
    void doCorrection(QString texte[], bool isGood[], operande resultat[]) const;  //modifie texte avec ou sans resultat en fonction de isGood
    void calculateResult(operande res[]);
    QString getModeGroupName() const;  //donne la chaine de caractere correspondant au mode

};

#endif // CORRECTION_H
