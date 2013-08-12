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

MediumModeWindow::MediumModeWindow(const int multiplicateur) : secondes(0), mode(MEDIUM)
{
    initStyle();
    this->setWindowFlags(Qt::FramelessWindowHint);

    m_multiple = multiplicateur;

    Shuffle shuffle(true);
    shuffle.getNumbers(array);

    this->setWindowTitle(tr("Table de ")+QString::number(m_multiple));

    quitter = new QPushButton(tr("Retour"));
    quitter->setParent(this);
    quitter->setFixedSize(70, 40);
    quitter->move(490, 490);
    quitter->setObjectName("Quitter");

    corriger = new QPushButton(tr("Corriger"));
    corriger->setParent(this);
    corriger->setFixedSize(80, 40);
    corriger->move(400, 490);
    corriger->setObjectName("Corriger");

    mapper = new QSignalMapper(this);

    for(int i = 0; i < 10; ++i)
    {
        reponses[i] = new QLineEdit(this);
        reponses[i]->setMaxLength(3);
        reponses[i]->setAttribute(Qt::WA_TranslucentBackground);
        reponses[i]->setFixedSize(302, 69);
        reponses[i]->move(185, (60 + 40 * i));

        connect(reponses[i], SIGNAL(returnPressed()), mapper, SLOT(map()));
        mapper->setMapping(reponses[i], (i + 1));

        label[i] = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(m_multiple)+"</span> x "+QString::number(array[i]), this);
        label[i]->setFixedSize(100, 30);

        labelPoint[i] = new QLabel(this);
        labelPoint[i]->setPixmap(QPixmap(":/image/Point.png"));
        labelPoint[i]->move(105, (90 + 40 * i));

        labelCorrection[i] = new QLabel(this);
        labelCorrection[i]->setVisible(false);
    }

    for(int j = 0; j < 2; ++j)
        for(int i = 0; i < 10; ++i)
        {
            trueFalseLabel[j][i] = new QLabel(this);
            if(j == 0)
            {
                trueFalseLabel[j][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
                trueFalseLabel[j][i]->move(475, (70 + 40 * i));
            }
            if(j == 1)
            {
                trueFalseLabel[j][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
                trueFalseLabel[j][i]->move(525, (75 + 40 * i));
            }
        }


    for(int i = 0; i < 2; ++i)
        nextPrev[i] = new QPushButton(this);

    nextPrev[0]->setObjectName("Precedent");
    nextPrev[1]->setObjectName("Suivant");

    nextPrev[0]->setFixedSize(58, 58);
    nextPrev[1]->setFixedSize(58, 58);

    for(int i = 0; i < 10; ++i)
        label[i]->move(120, 78 + i * 40);

    nextPrev[0]->move(20, 240);
    nextPrev[1]->move(570, 240);

    text = new QLabel(tr("Temps :"),this);
    minute = new QLabel("00", this);
    deuxPoint = new QLabel(":", this);
    seconde = new QLabel("00", this);

    text->move(235, 15);
    minute->move(330, 15);
    deuxPoint->move(355, 15);
    seconde->move(380, 15);

    startTime();

    connect(corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(quitter, SIGNAL(clicked()), this, SIGNAL(wasClosed()));


    connect(nextPrev[0], SIGNAL(clicked()), this, SLOT(Previous()));
    connect(nextPrev[1], SIGNAL(clicked()), this, SLOT(Next()));

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(newSetFocus(int)));
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
        reponses[number]->setFocus();
        reponses[number]->selectAll();
    }
    else
        correct();
}

void MediumModeWindow::startTime()
{
    chronometre = new QTimer;
    chronometre->start(1000);
    connect(chronometre, SIGNAL(timeout()), this, SLOT(newSecond()));
    connect(this, SIGNAL(addSeconde(int)), this, SLOT(updateLabel(int)));
}

void MediumModeWindow::closeEvent(QCloseEvent *event)
{
    if(event->spontaneous())
        delete chronometre;
    event->accept();
}

void MediumModeWindow::newSecond()
{
    ++secondes;
    emit addSeconde(secondes);
}

void MediumModeWindow::updateLabel(const int temps) const
{
    if((temps/60) != 0)
    {
        minute->setText("0"+QString::number(temps/60));
        if((temps%60) < 10)
            seconde->setText("0"+QString::number(temps%60));
        else
            seconde->setText(QString::number(temps%60));
    }
    else
    {
        if(temps < 10)
            seconde->setText("0"+QString::number(temps));
        else
            seconde->setText(QString::number(temps));
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
    if(m_multiple > 1)
        --m_multiple;
    setNewNumber(m_multiple);
}

void MediumModeWindow::Next()
{
    if(m_multiple < 10)
       ++ m_multiple;
    setNewNumber(m_multiple);
}

void MediumModeWindow::setNewNumber(register int newNumber)
{
    this->setWindowTitle(tr("Table de ")+QString::number(newNumber));

    corriger->setText("Corriger");

    for(int i = 0; i < 10; ++i)
        label[i]->setText("<span style=\"color: #9FC54D\">"+QString::number(newNumber)+"</span> x "+QString::number(array[i]));

    for(int i = 0; i < 10; ++i)
    {
        labelCorrection[i]->setVisible(false);

        reponses[i]->clear();
        reponses[i]->setVisible(true);

        trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
    }
    if(chronometre != NULL)
    {
        chronometre->stop();
        delete chronometre;
    }
    secondes = 0;
    minute->setText("00");
    seconde->setText("00");
    startTime();
    reponses[0]->setFocus();
}

void MediumModeWindow::correct()
{
    chronometre->stop();
    delete chronometre;
    chronometre = NULL;

    int rep[10];
    for(int i = 0; i < 10; ++i)
        rep[i] = reponses[i]->text().toInt();

    Correction test(mode, m_multiple, array, rep, secondes);

    bool isGood[10];
    QString texte[10];

    note = test.getCorrection(texte, isGood);

    CustomMessageBox results(secondes, note, this);

    secondes = 0;

    corriger->setText(tr("Retenter"));
    disconnect(corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(corriger, SIGNAL(clicked()), this, SLOT(Retry()));

    for(int i = 0; i < 10; ++i)
    {
        reponses[i]->setVisible(false);

        labelCorrection[i]->setText(texte[i]);
        labelCorrection[i]->move(200, (80 + (i * 40)));
        labelCorrection[i]->setVisible(true);

        if(isGood[i])
        {
            trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/Right.png"));
            trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
        }
        else
        {
            trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
            trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/Wrong.png"));
        }
        this->repaint();
    }

    results.exec();
}

void MediumModeWindow::Retry()
{
    corriger->setText(tr("Corriger"));
    disconnect(corriger, SIGNAL(clicked()), this, SLOT(Retry()));
    connect(corriger, SIGNAL(clicked()), this, SLOT(correct()));

    for(int i = 0; i < 10; ++i)
    {
        labelCorrection[i]->setVisible(false);
        reponses[i]->clear();
        reponses[i]->setVisible(true);

        trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
    }

    minute->setText("00");
    seconde->setText("00");
    startTime();
}

void MediumModeWindow::showEvent(QShowEvent *event)
{
    reponses[0]->setFocus();
    QWidget::showEvent(event);
}

MediumModeWindow::~MediumModeWindow()
{
    delete corriger;
    corriger = NULL;

    delete quitter;
    quitter = NULL;

    for(int i = 0; i < 10; ++i)
    {
        delete label[i];
        label[i] = NULL;

        delete labelPoint[i];
        labelPoint[i] = NULL;

        /*delete reponses[i];
        reponses[i] = nullptr;*/
    }

    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            delete trueFalseLabel[i][j];
            trueFalseLabel[i][j] = NULL;
        }

        /*delete nextPrev[i];
        nextPrev[i] = nullptr;*/
    }

    delete text;
    delete minute;
    delete seconde;
    delete deuxPoint;
    if(chronometre != NULL)
        delete chronometre;


    chronometre = NULL;
    text = NULL;
    minute = NULL;
    seconde = NULL;
    deuxPoint = NULL;
}
