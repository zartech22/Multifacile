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

#include "MediumModeWindow.h"

MediumModeWindow::MediumModeWindow() : AbstractModeWindow()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    initNextPrev();
}

MediumModeWindow::MediumModeWindow(const operande multiplicateur, bool actualProgressifMode) : AbstractModeWindow(), _mode(MEDIUM), _progressifMode(actualProgressifMode)
  , _multiple(multiplicateur)
{
    this->setWindowFlags(Qt::FramelessWindowHint);

    Shuffle shuffle(true);
    shuffle.getNumbers(_array);

    this->setWindowTitle(tr("Table de ")+QString::number(_multiple));

    initNextPrev();
    initLabels();
}

void MediumModeWindow::initAskLabels()
{
    for(int i = 0; i < 10; ++i)
    {
        _label[i] = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(_multiple)+"</span> x "+QString::number(_array[i]), this);
        _label[i]->setFixedSize(100, 30);
        _label[i]->move(120, 78 + i * 40);
    }
}

void MediumModeWindow::initNextPrev()
{
    for(int i = 0; i < 2; ++i)
        _nextPrev[i] = new QPushButton(this);

    _nextPrev[0]->setObjectName("Precedent");
    _nextPrev[1]->setObjectName("Suivant");

    _nextPrev[0]->setFixedSize(58, 58);
    _nextPrev[1]->setFixedSize(58, 58);

    _nextPrev[0]->move(20, 240);
    _nextPrev[1]->move(570, 240);

    connect(_nextPrev[0], SIGNAL(clicked()), this, SLOT(Previous()));
    connect(_nextPrev[1], SIGNAL(clicked()), this, SLOT(Next()));
}

void MediumModeWindow::closeEvent(QCloseEvent *event)
{
    //if(event->spontaneous())
      //  delete _chronometre;
    event->accept();
}

void MediumModeWindow::Previous()
{
    if(_progressifMode && _mode == MEDIUM)
        _multiple = DataFileMgr::previousTableWithNoErrorTrue("Multifacile.xml", "EasyMode", _multiple);
    else if(_multiple > 1)
        --_multiple;
    setNewNumber(_multiple);
}

void MediumModeWindow::Next()
{
    if(_progressifMode && _mode == MEDIUM)
        _multiple = DataFileMgr::nextTableWithNoErrorTrue("Multifacile.xml", "EasyMode", _multiple);
    else if(_multiple < 10)
       ++ _multiple;
    setNewNumber(_multiple);
}

void MediumModeWindow::setNewNumber(const operande newNumber)
{
    this->setWindowTitle(tr("Table de ")+QString::number(newNumber));

    _correct->setText("Corriger");

    for(int i = 0; i < 10; ++i)
    {
        _label[i]->setText("<span style=\"color: #9FC54D\">"+QString::number(newNumber)+"</span> x "+QString::number(_array[i]));

        _labelCorrection[i]->setVisible(false);

        _lineEdits[i]->clear();
        _lineEdits[i]->setVisible(true);

        _trueFalse[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        _trueFalse[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
    }

    /*if(_chronometre != NULL)
    {
        stopTimer();
        //delete _chronometre;
    }*/
    restartTimer();
    _lineEdits[0]->setFocus();
}

void MediumModeWindow::correct()
{
    stopTimer();
    std::array<unsigned short int, 10> rep;

    for(int i = 0; i < 10; ++i)
        rep[i] = _lineEdits[i]->text().toInt();

    Correction correction(_mode, _multiple, _array, rep, _timeElapsed);

    bool isGood[10];
    QString texte[10];

    _note = correction.getCorrection(texte, isGood);

    CustomMessageBox results(_timeElapsed, _note, this);

    _correct->setText(tr("Retenter"));
    disconnect(_correct, SIGNAL(clicked()), this, SLOT(correct()));
    connect(_correct, SIGNAL(clicked()), this, SLOT(Retry()));

    for(int i = 0; i < 10; ++i)
    {
        _lineEdits[i]->setVisible(false);

        _labelCorrection[i]->setText(texte[i]);
        _labelCorrection[i]->move(200, (80 + (i * 40)));
        _labelCorrection[i]->setVisible(true);

        if(isGood[i])
        {
            _trueFalse[0][i]->setPixmap(QPixmap(":/image/Right.png"));
            _trueFalse[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
        }
        else
        {
            _trueFalse[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
            _trueFalse[1][i]->setPixmap(QPixmap(":/image/Wrong.png"));
        }
        this->repaint();
    }

    results.exec();
}

void MediumModeWindow::Retry()
{
    _correct->setText(tr("Corriger"));
    disconnect(_correct, SIGNAL(clicked()), this, SLOT(Retry()));
    connect(_correct, SIGNAL(clicked()), this, SLOT(correct()));

    for(int i = 0; i < 10; ++i)
    {
        _labelCorrection[i]->setVisible(false);
        _lineEdits[i]->clear();
        _lineEdits[i]->setVisible(true);

        _trueFalse[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        _trueFalse[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
    }

    restartTimer();
}

void MediumModeWindow::checkTableAvailable()
{
    if(!DataFileMgr::hasNoErrorTrue("Multifacile.xml", "MediumMode", _multiple))
    {
        stopTimer();
        CustomMessageBox(CannotDoThisTable, this, _multiple).exec();
        emit wasClosed();
    }
}

MediumModeWindow::~MediumModeWindow()
{
    for(int i = 0; i < 10; ++i)
    {
        delete _label[i];
        _label[i] = nullptr;

        /*delete _reponses[i];
        _reponses[i] = nullptr;*/
    }
}
