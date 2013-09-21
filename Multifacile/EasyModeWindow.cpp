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

#include "EasyModeWindow.h"

EasyModeWindow::EasyModeWindow(const unsigned short m_multiplicateur)
{
    initStyle();

    _mode = EASY;
    _multiple = m_multiplicateur;
    _secondes = 0;

    setWindowFlags(Qt::FramelessWindowHint);
    Shuffle shuffle(false);
    shuffle.getNumbers(_array);

    setWindowTitle(tr("Table de ")+QString::number(_multiple));

    _quitter = new QPushButton(tr("Retour"));
    _quitter->setParent(this);
    _quitter->setFixedSize(70, 40);
    _quitter->move(490, 490);
    _quitter->setObjectName("Quitter");

    _corriger = new QPushButton(tr("Corriger"));
    _corriger->setParent(this);
    _corriger->setFixedSize(80, 40);
    _corriger->move(400, 490);
    _corriger->setObjectName("Corriger");

    _astuces = new QPushButton(tr("Astuce"));
    _astuces->setParent(this);
    _astuces->setFixedSize(70, 40);
    _astuces->move(310, 490);
    _astuces->setObjectName("Astuce");

    _text = new QLabel(tr("Temps : "), this);
    _minute = new QLabel("00", this);
    _deuxPoint = new QLabel(":", this);
    _seconde = new QLabel("00", this);

    _text->move(235, 15);
    _minute->move(330, 15);
    _deuxPoint->move(355, 15);
    _seconde->move(380, 15);

    _mapper = new QSignalMapper(this);

    for(int i = 0; i < 10; ++i)
    {
        _reponses[i] = new QLineEdit(this);
        _reponses[i]->setAttribute(Qt::WA_TranslucentBackground);
        _reponses[i]->setFixedSize(302, 69);
        _reponses[i]->move(185, (60 + 40 * i));
        _reponses[i]->setValidator(new QRegExpValidator(QRegExp("\\d{0,3}"), _reponses[i]));

        connect(_reponses[i], SIGNAL(returnPressed()), _mapper, SLOT(map()));
        _mapper->setMapping(_reponses[i], (i + 1));

        _labelCorrection[i] = new QLabel(this);
        _labelCorrection[i]->setVisible(false);

        _label[i] = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(_multiple)+"</span> x "+QString::number(_array[i]), this);
        _label[i]->setFixedSize(100, 30);
        _label[i]->move(120, 78 + (i * 40));

        _labelPoint[i] = new QLabel(this);
        _labelPoint[i]->setPixmap(QPixmap(":/image/Point.png"));
        _labelPoint[i]->move(105, (90 + 40 * i));
    }

    for(int j = 0; j < 2; ++j)
        for(int i = 0; i < 10; ++i)
        {
            _trueFalseLabel[j][i] = new QLabel(this);
            if(j == 0)
            {
                _trueFalseLabel[j][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
                _trueFalseLabel[j][i]->move(475, (70 + 40 * i));
            }
            if(j == 1)
            {
                _trueFalseLabel[j][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
                _trueFalseLabel[j][i]->move(525, (75 + 40 * i));
            }
        }

    _nextPrev[0] = new QPushButton(this);
    _nextPrev[0]->setObjectName("Precedent");
    _nextPrev[0]->setFixedSize(58, 58);
    _nextPrev[0]->move(20, 240);

    _nextPrev[1] = new QPushButton(this);
    _nextPrev[1]->setObjectName("Suivant");
    _nextPrev[1]->setFixedSize(58, 58);
    _nextPrev[1]->move(570, 240);

    startTime();

    connect(_quitter, SIGNAL(clicked()), this, SIGNAL(wasClosed()));
    connect(_corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(_astuces, SIGNAL(clicked()), this, SLOT(openAstuce()));

    connect(_nextPrev[0], SIGNAL(clicked()), this, SLOT(Previous()));
    connect(_nextPrev[1], SIGNAL(clicked()), this, SLOT(Next()));

    connect(_mapper, SIGNAL(mapped(int)), this, SLOT(newSetFocus(int)));
}
void EasyModeWindow::openAstuce() const
{
    CustomMessageBox trick (Trick, 0, _multiple);
    trick.setObjectName("AstuceFen");
    trick.exec();
}
EasyModeWindow::~EasyModeWindow()
{
    delete _astuces;
    _astuces = NULL;
}
