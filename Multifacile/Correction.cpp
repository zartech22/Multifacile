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

Correction::Correction(Mode mode, const unsigned short multiple, int *order, unsigned short int* userAnswers, const unsigned short int time) : _Multiple(multiple), _orderTab(order), _answers(userAnswers), _difficultyMode(mode), _seconds(time), _isHardMode(false) {}

Correction::Correction(unsigned short *multiple, int *order, unsigned short int *userAnswers, const unsigned short time) : _multipleTab(multiple), _orderTab(order), _answers(userAnswers), _seconds(time), _isHardMode(true){}

int Correction::getCorrection(QString texte[], bool isGood[])
{
    unsigned short int resultat[10];
    _note = 10;

    this->notation(resultat, isGood);
    this->doCorrection(texte, isGood, resultat);

    if(_seconds != 0)
        this->manageTime();

    return _note;
}
void Correction::notation(unsigned short int resultat[], bool isGood[])
{
    if(!_isHardMode)
    {
        for(int i = 0; i < 10; ++i)
        {
            resultat[i] = _Multiple*_orderTab[i];
            if(resultat[i] != _answers[i])
            {
                isGood[i] = false;
                --_note;
            }
            else
                isGood[i] = true;
        }
    }
    else
    {
        for(int i = 0; i < 10; ++i)
        {
            resultat[i] = _multipleTab[i]*_orderTab[i];
            if(resultat[i] != _answers[i])
            {
                isGood[i] = false;
                --_note;
            }
            else
                isGood[i] = true;
        }
    }
}
void Correction::doCorrection(QString texte[], bool isGood[], unsigned short int resultat[]) const
{
    for(int i = 0; i < 10; ++i)
        texte[i] = (isGood[i]) ? QString("<span style=\"color: #9FC54D;\">" + QString::number(resultat[i]) + tr(" C'est la bonne réponse !") + "</span>") : QString("<span style=\"color: red;\">" + QString::number(_answers[i]) +  "</span> <span style=\"color: #9FC54D;\"> " + tr("La bonne réponse était ") + QString::number(resultat[i]));
}

void Correction::manageTime()
{
    _manager = new DataFileMgr("Multifacile.xml");
    if(_isHardMode)
        _manager->setValue(getModeGroupName(), _seconds);
    else
        _manager->setValue(getModeGroupName(), _seconds, (_note == 10) , _Multiple);
}
void Correction::isRecordValid(RecordState record, int lastRecordTime)
{
    if(record == NORECORD)
        emit newRecord(NORECORD, lastRecordTime);
    else if(_note == 10)  // if record != NORECORD then record == RECORD
        emit newRecord(RECORD, lastRecordTime);
    else
        emit newRecord(UNVALIDRECORD, lastRecordTime);
}
QString Correction::getModeGroupName() const
{
    if(_isHardMode)
        return QString("HardMode");
    else if(_difficultyMode == EASY)
        return QString("EasyMode");
    else if(_difficultyMode == MEDIUM)
        return QString("MediumMode");
    else
        return QString();
}
QString Correction::getModeKeyName() const
{
    if(_difficultyMode == EASY || _difficultyMode == MEDIUM)
        return QString("TableDe"+QString::number(_Multiple));
    else
        return QString();
}
Correction::~Correction()
{
    delete _manager;

    _manager = NULL;
}
