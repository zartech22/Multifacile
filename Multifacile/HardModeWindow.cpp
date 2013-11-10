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
    initButtons();
    initTimer();

    Shuffle shuffle(true);
    shuffle.getNumbers(_array, _multiple);
    setWindowFlags(Qt::FramelessWindowHint);

    this->setWindowTitle(tr("Table aléaoire"));

    initLineEdit();
    initLabels();

    startTime();

}

void HardModeWindow::initTableLabels()
{
    for(int i = 0; i < 10; ++i)
    {
        _label[i] = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(_multiple[i])+"</span> x "+QString::number(_array[i]), this);
        _label[i]->setFixedSize(100, 30);
        _label[i]->move(120, 78 + i * 40);
    }
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
