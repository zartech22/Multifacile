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

HardModeWindow::HardModeWindow() : AbstractModeWindow()
{
    Shuffle shuffle(true);
    shuffle.getNumbers(_array, _multiple);

    initLabels();

    this->setWindowTitle(tr("Table aléaoire"));
}

void HardModeWindow::initAskLabels()
{
    for(int i = 0; i < 10; ++i)
    {
        _label[i] = new QLabel("<span style=\"color: #9FC54D\">" + QString::number(_multiple[i]) + "</span> x " + QString::number(_array[i]), this);
        _label[i]->setFixedSize(100, 30);
        _label[i]->move(120, 78 + i * 40);
    }
}

void HardModeWindow::correct()
{
    std::array<unsigned short int, 10> rep;

    for(int i = 0; i < 10; ++i)
        rep[i] = _lineEdits[i]->text().toInt();

    Correction correction(_multiple, _array, rep, _timeElapsed);

    bool isGood[10];
    QString texte[10];

    _note = correction.getCorrection(texte, isGood);

    _correct->setText(tr("Retenter"));
    disconnect(_correct, SIGNAL(clicked()), this, SLOT(correct()));
    connect(_correct, SIGNAL(clicked()), this, SLOT(Retry()));

    stopTimer();

    CustomMessageBox results(_timeElapsed, _note, this);

    _timeElapsed = 0;

    const QPixmap right(":/image/Right.png");
    const QPixmap rightOpac(":/image/OpacRight.png");

    const QPixmap wrong(":/image/Wrong.png");
    const QPixmap wrongOpac(":/image/OpacWrong.png");

    for(int i = 0; i < 10; ++i)
    {
        _lineEdits[i]->setVisible(false);

        _labelCorrection[i]->setText(texte[i]);
        _labelCorrection[i]->move(200, (80 + (i * 40)));
        _labelCorrection[i]->setVisible(true);

        if(isGood[i])
        {
            _trueFalse[0][i]->setPixmap(right);
            _trueFalse[1][i]->setPixmap(wrongOpac);
        }
        else
        {
            _trueFalse[0][i]->setPixmap(rightOpac);
            _trueFalse[1][i]->setPixmap(wrong);
        }

        this->repaint();
    }

    results.exec();
}

void HardModeWindow::Retry()
{
    _correct->setText(tr("Corriger"));
    disconnect(_correct, SIGNAL(clicked()), this, SLOT(Retry()));
    connect(_correct, SIGNAL(clicked()), this, SLOT(correct()));

    Shuffle shuffle(true);
    shuffle.getNumbers(_array, _multiple);

    const QPixmap rigthOpac(":/image/OpacRight.png");
    const QPixmap wrongOpac(":/image/OpacWrong.png");

    for(int i = 0; i < 10; ++i)
    {
        _labelCorrection[i]->setVisible(false);

        _label[i]->setText("<span style=\"color: #9FC54D\">"+QString::number(_multiple[i])+"</span> x "+QString::number(_array[i]));
        _trueFalse[0][i]->setPixmap(rigthOpac);
        _trueFalse[1][i]->setPixmap(wrongOpac);
        _lineEdits[i]->clear();
        _lineEdits[i]->setVisible(true);
    }

    _lineEdits[0]->setFocus();

    restartTimer();
}
