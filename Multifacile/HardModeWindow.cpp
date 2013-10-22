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

#include "HardModeWindow.h"

HardModeWindow::HardModeWindow()
{
    initStyle();
    Shuffle shuffle(true);
    shuffle.getNumbers(_array, _multiple);
    setWindowFlags(Qt::FramelessWindowHint);

    this->setWindowTitle(tr("Table aléaoire"));


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

    _text = new QLabel(tr("Temps : "), this);
    _minute = new QLabel("00", this);
    _deuxPoint = new QLabel(":", this);
    _seconde = new QLabel("00", this);

    _secondes = 0;

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

        _label[i] = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(_multiple[i])+"</span> x "+QString::number(_array[i]), this);
        _label[i]->setFixedSize(100, 30);
        _label[i]->move(120, (78 + 40 * i));

        _labelCorrection[i] = new QLabel(this);
        _labelCorrection[i]->setVisible(false);

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

    startTime();

    connect(_quitter, SIGNAL(clicked()), this, SIGNAL(wasClosed()));
    connect(_corriger, SIGNAL(clicked()), this, SLOT(correct()));

    connect(_mapper, SIGNAL(mapped(int)), this, SLOT(newSetFocus(int)));
}
void HardModeWindow::correct()
{
    unsigned short int rep[10];
    for(int i = 0; i < 10; ++i)
        rep[i] = _reponses[i]->text().toInt();

    Correction correction(_multiple, _array, rep, _secondes);

    bool isGood[10];
    QString texte[10];

    _note = correction.getCorrection(texte, isGood);

    _corriger->setText(tr("Retenter"));
    disconnect(_corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(_corriger, SIGNAL(clicked()), this, SLOT(Retry()));

    _chronometre->stop();
    delete _chronometre;
    _chronometre = NULL;

    CustomMessageBox results(_secondes, _note, this);

    _secondes = 0;

    for(int i = 0; i < 10; ++i)
    {
        _reponses[i]->setVisible(false);

        _labelCorrection[i]->setText(texte[i]);
        _labelCorrection[i]->move(200, (80 + (i * 40)));
        _labelCorrection[i]->setVisible(true);

        if(isGood[i])
        {
            _trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/Right.png"));
            _trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
        }

        else
        {
            _trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
            _trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/Wrong.png"));
        }

        this->repaint();
    }

    results.exec();
}
void HardModeWindow::Retry()
{
    _corriger->setText(tr("Corriger"));
    disconnect(_corriger, SIGNAL(clicked()), this, SLOT(Retry()));
    connect(_corriger, SIGNAL(clicked()), this, SLOT(correct()));

    Shuffle shuffle(true);
    shuffle.getNumbers(_array, _multiple);


    for(int i = 0; i < 10; ++i)
    {
        _labelCorrection[i]->setVisible(false);

        _label[i]->setText("<span style=\"color: #9FC54D\">"+QString::number(_multiple[i])+"</span> x "+QString::number(_array[i]));
        _trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        _trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
        _reponses[i]->clear();
        _reponses[i]->setVisible(true);
    }

    _reponses[0]->setFocus();

    _minute->setText("00");
    _seconde->setText("00");
    startTime();
}
