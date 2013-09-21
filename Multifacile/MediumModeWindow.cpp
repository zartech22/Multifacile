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

MediumModeWindow::MediumModeWindow(const int multiplicateur) : _secondes(0), _mode(MEDIUM)
{
    initStyle();
    this->setWindowFlags(Qt::FramelessWindowHint);

    _multiple = multiplicateur;

    Shuffle shuffle(true);
    shuffle.getNumbers(_array);

    this->setWindowTitle(tr("Table de ")+QString::number(_multiple));

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

        _label[i] = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(_multiple)+"</span> x "+QString::number(_array[i]), this);
        _label[i]->setFixedSize(100, 30);
        _label[i]->move(120, 78 + i * 40);

        _labelPoint[i] = new QLabel(this);
        _labelPoint[i]->setPixmap(QPixmap(":/image/Point.png"));
        _labelPoint[i]->move(105, (90 + 40 * i));

        _labelCorrection[i] = new QLabel(this);
        _labelCorrection[i]->setVisible(false);
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


    for(int i = 0; i < 2; ++i)
        _nextPrev[i] = new QPushButton(this);

    _nextPrev[0]->setObjectName("Precedent");
    _nextPrev[1]->setObjectName("Suivant");

    _nextPrev[0]->setFixedSize(58, 58);
    _nextPrev[1]->setFixedSize(58, 58);

    _nextPrev[0]->move(20, 240);
    _nextPrev[1]->move(570, 240);

    _text = new QLabel(tr("Temps :"),this);
    _minute = new QLabel("00", this);
    _deuxPoint = new QLabel(":", this);
    _seconde = new QLabel("00", this);

    _text->move(235, 15);
    _minute->move(330, 15);
    _deuxPoint->move(355, 15);
    _seconde->move(380, 15);

    startTime();

    connect(_corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(_quitter, SIGNAL(clicked()), this, SIGNAL(wasClosed()));


    connect(_nextPrev[0], SIGNAL(clicked()), this, SLOT(Previous()));
    connect(_nextPrev[1], SIGNAL(clicked()), this, SLOT(Next()));

    connect(_mapper, SIGNAL(mapped(int)), this, SLOT(newSetFocus(int)));
}

void MediumModeWindow::initStyle()
{
    QFile css(":/css/Fen2.css");
    css.open(QIODevice::ReadOnly);
    setStyleSheet(css.readAll());
    css.close();
}

void MediumModeWindow::newSetFocus(const int number)
{
    if(number < 10)
    {
        _reponses[number]->setFocus();
        _reponses[number]->selectAll();
    }
    else
        correct();
}

void MediumModeWindow::startTime()
{
    _chronometre = new QTimer;
    _chronometre->start(1000);
    connect(_chronometre, SIGNAL(timeout()), this, SLOT(newSecond()));
    connect(this, SIGNAL(addSeconde(int)), this, SLOT(updateLabel(int)));
}

void MediumModeWindow::closeEvent(QCloseEvent *event)
{
    if(event->spontaneous())
        delete _chronometre;
    event->accept();
}

void MediumModeWindow::newSecond()
{
    ++_secondes;
    emit addSeconde(_secondes);
}

void MediumModeWindow::updateLabel(const int temps) const
{
    if((temps/60) != 0)
    {
        _minute->setText("0"+QString::number(temps/60));
        if((temps%60) < 10)
            _seconde->setText("0"+QString::number(temps%60));
        else
            _seconde->setText(QString::number(temps%60));
    }
    else
    {
        if(temps < 10)
            _seconde->setText("0"+QString::number(temps));
        else
            _seconde->setText(QString::number(temps));
    }
}

void MediumModeWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MediumModeWindow::Previous()
{
    if(_multiple > 1)
        --_multiple;
    setNewNumber(_multiple);
}

void MediumModeWindow::Next()
{
    if(_multiple < 10)
       ++ _multiple;
    setNewNumber(_multiple);
}

void MediumModeWindow::setNewNumber(const unsigned short int newNumber)
{
    this->setWindowTitle(tr("Table de ")+QString::number(newNumber));

    _corriger->setText("Corriger");

    for(int i = 0; i < 10; ++i)
    {
        _label[i]->setText("<span style=\"color: #9FC54D\">"+QString::number(newNumber)+"</span> x "+QString::number(_array[i]));

        _labelCorrection[i]->setVisible(false);

        _reponses[i]->clear();
        _reponses[i]->setVisible(true);

        _trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        _trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
    }

    if(_chronometre != NULL)
    {
        _chronometre->stop();
        delete _chronometre;
    }

    _secondes = 0;
    _minute->setText("00");
    _seconde->setText("00");
    startTime();
    _reponses[0]->setFocus();
}

void MediumModeWindow::correct()
{
    _chronometre->stop();
    delete _chronometre;
    _chronometre = NULL;

    unsigned short int rep[10];
    for(int i = 0; i < 10; ++i)
        rep[i] = _reponses[i]->text().toInt();

    Correction test(_mode, _multiple, _array, rep, _secondes);

    bool isGood[10];
    QString texte[10];

    _note = test.getCorrection(texte, isGood);

    CustomMessageBox results(_secondes, _note, this);

    _secondes = 0;

    _corriger->setText(tr("Retenter"));
    disconnect(_corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(_corriger, SIGNAL(clicked()), this, SLOT(Retry()));

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

void MediumModeWindow::Retry()
{
    _corriger->setText(tr("Corriger"));
    disconnect(_corriger, SIGNAL(clicked()), this, SLOT(Retry()));
    connect(_corriger, SIGNAL(clicked()), this, SLOT(correct()));

    for(int i = 0; i < 10; ++i)
    {
        _labelCorrection[i]->setVisible(false);
        _reponses[i]->clear();
        _reponses[i]->setVisible(true);

        _trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        _trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
    }

    _reponses[0]->setFocus();

    _minute->setText("00");
    _seconde->setText("00");
    startTime();
}

void MediumModeWindow::showEvent(QShowEvent *event)
{
    _reponses[0]->setFocus();
    QWidget::showEvent(event);
}

MediumModeWindow::~MediumModeWindow()
{
    delete _corriger;
    _corriger = NULL;

    delete _quitter;
    _quitter = NULL;

    for(int i = 0; i < 10; ++i)
    {
        delete _label[i];
        _label[i] = NULL;

        delete _labelPoint[i];
        _labelPoint[i] = NULL;

        /*delete _reponses[i];
        _reponses[i] = nullptr;*/
    }

    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            delete _trueFalseLabel[i][j];
            _trueFalseLabel[i][j] = NULL;
        }

        /*delete _nextPrev[i];
        _nextPrev[i] = nullptr;*/
    }

    delete _text;
    delete _minute;
    delete _seconde;
    delete _deuxPoint;
    if(_chronometre != NULL)
        delete _chronometre;


    _chronometre = NULL;
    _text = NULL;
    _minute = NULL;
    _seconde = NULL;
    _deuxPoint = NULL;
}
