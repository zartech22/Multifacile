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

#include "Correction.h"

Correction::Correction(Mode mode, const unsigned short multiple, int *order, unsigned short int* userAnswers, const unsigned short int time) : Multiple(multiple), orderTab(order), answers(userAnswers), difficultyMode(mode), seconds(time), isHardMode(false) {}

Correction::Correction(unsigned short *multiple, int *order, unsigned short int *userAnswers, const unsigned short time) : multipleTab(multiple), orderTab(order), answers(userAnswers), seconds(time), isHardMode(true){}

int Correction::getCorrection(QString texte[], bool isGood[])
{
    unsigned short int resultat[10];
    note = 10;

    this->notation(resultat, isGood);
    this->doCorrection(texte, isGood, resultat);

    if(seconds != 0)
        this->manageTime();

    return note;
}
void Correction::notation(unsigned short int resultat[], bool isGood[])
{
    if(!isHardMode)
    {
        for(int i = 0; i < 10; ++i)
        {
            resultat[i] = Multiple*orderTab[i];
            if(resultat[i] != answers[i])
            {
                isGood[i] = false;
                --note;
            }
            else
                isGood[i] = true;
        }
    }
    else
    {
        for(int i = 0; i < 10; ++i)
        {
            resultat[i] = multipleTab[i]*orderTab[i];
            if(resultat[i] != answers[i])
            {
                isGood[i] = false;
                --note;
            }
            else
                isGood[i] = true;
        }
    }
}
void Correction::doCorrection(QString texte[], bool isGood[], unsigned short int resultat[]) const
{
    for(int i = 0; i < 10; ++i)
        texte[i] = (isGood[i]) ? QString("<span style=\"color: #9FC54D;\">" + QString::number(resultat[i]) + tr(" C'est la bonne réponse !") + "</span>") : QString("<span style=\"color: red;\">" + QString::number(answers[i]) +  "</span> <span style=\"color: #9FC54D;\"> " + tr("La bonne réponse était ") + QString::number(resultat[i]));
}

void Correction::manageTime()
{
    manager = new DataFileMgr("Multifacile.xml");
    if(isHardMode)
        manager->setValue(getModeGroupName(), seconds);
    else
        manager->setValue(getModeGroupName(), seconds, (note == 10) ? true : false, Multiple);
}
void Correction::isRecordValid(RecordState record, int lastRecordTime)
{
    if(record == RECORD && note == 10)
        emit newRecord(RECORD, lastRecordTime);
    else if(record == RECORD && note != 10)
        emit newRecord(UNVALIDRECORD, lastRecordTime);
    else
        emit newRecord(NORECORD, lastRecordTime);
}
QString Correction::getModeGroupName() const
{
    if(isHardMode)
        return QString("HardMode");
    else if(difficultyMode == EASY)
        return QString("EasyMode");
    else if(difficultyMode == MEDIUM)
        return QString("MediumMode");
    else
        return QString();
}
QString Correction::getModeKeyName() const
{
    if(difficultyMode == EASY || difficultyMode == MEDIUM)
        return QString("TableDe"+QString::number(Multiple));
    else
        return QString();
}
Correction::~Correction()
{
    delete manager;

    manager = NULL;
}
