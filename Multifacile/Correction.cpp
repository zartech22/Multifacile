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

const QString Correction::_goodAnswer("<span style=\"color: #9FC54D;\">%1 C'est la bonne réponse !</span>");
const QString Correction::_badAnswer("<span style=\"color: red;\">%1</span><span style=\"color: #9FC54D;\"> La bonne réponse était %2</span>");

Correction::Correction(Mode mode, operande multiple, std::array<operande, 10> &order, std::array<operande, 10> &userAnswers, const operande time) :
    _difficultyMode(mode), _seconds(time), _note(10), _multiple({false, multiple})
{
    std::copy(order.begin(), order.end(), _orderTab.begin());
    std::copy(userAnswers.begin(), userAnswers.end(), _answers.begin());
}

Correction::Correction(std::array<operande, 10> &multiples, std::array<operande, 10> &order, std::array<operande, 10> &userAnswers, const operande time) :
    _difficultyMode(HARD), _seconds(time), _note(10)
{
    _multiple.isHard = true;

    std::copy(multiples.begin(), multiples.end(), _multiple.multiples.begin());
    std::copy(order.begin(), order.end(), _orderTab.begin());
    std::copy(userAnswers.begin(), userAnswers.end(), _answers.begin());
}

int Correction::getCorrection(QString texte[], bool isGood[])
{
    operande resultat[10];

    notation(resultat, isGood);
    doCorrection(texte, isGood, resultat);

    if(_seconds != 0)
        manageTime();

    return _note;
}

void Correction::notation(operande resultat[], bool isGood[])
{
    calculateResult(resultat);

    for(int i = 0; i < 10; i++)
        if(!(isGood[i] = (resultat[i] == _answers[i]) ))
            --_note;
}

void Correction::calculateResult(operande res[])
{
    if(!_multiple.isHard)
        for(int i = 0; i < 10; i++)
            res[i] = _multiple.multiple * _orderTab[i];
    else
        for(int i = 0; i < 10; i++)
            res[i] = _multiple.multiples[i] * _orderTab[i];
}

void Correction::doCorrection(QString texte[], bool isGood[], operande resultat[]) const
{
    for(int i = 0; i < 10; ++i)
    {
        texte[i] = (isGood[i]) ? Correction::_goodAnswer.arg(resultat[i])
                               : Correction::_badAnswer.arg(_answers[i]).arg(resultat[i]);
    }
}

void Correction::manageTime()
{
    _manager = std::make_unique<DataFileMgr>("Multifacile.xml");

    if(_multiple.isHard)
        _manager->setValue(getModeGroupName(), _seconds);
    else
        _manager->setValue(getModeGroupName(), _seconds, (_note == 10) , _multiple.multiple);
}

QString Correction::getModeGroupName() const
{
    if(_multiple.isHard)
        return QString("HardMode");
    else if(_difficultyMode == EASY)
        return QString("EasyMode");
    else if(_difficultyMode == MEDIUM)
        return QString("MediumMode");
    else
        return QString();
}
