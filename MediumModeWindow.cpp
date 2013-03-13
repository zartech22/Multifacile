/*Copyright (C) <2012> <Plestan> <Kévin>

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

MediumModeWindow::MediumModeWindow() : QWidget()
{
}

MediumModeWindow::MediumModeWindow(const int multiplicateur, bool chrono) : time(chrono), secondes(0)
{
    ApplyStyle();
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


    register int multiple_temp = m_multiple;

    for(int i = 0; i < 10; i++)
    {
        reponses[i] = new SpinBox(this);
        reponses[i]->setAttribute(Qt::WA_TranslucentBackground);
        reponses[i]->setNumero(i);
        reponses[i]->setFixedSize(302, 69);
        reponses[i]->move(185, (60 + 40 * i));

        label[i] = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(multiple_temp)+"</span> x "+QString::number(array[i]), this);
        label[i]->setFixedSize(100, 30);

        labelPoint[i] = new QLabel(this);
        labelPoint[i]->setPixmap(QPixmap(":/image/Point.png"));
        labelPoint[i]->move(105, (90 + 40 * i));

        labelCorrection[i] = new QLabel(this);
        labelCorrection[i]->setVisible(false);
    }

    for(int j = 0; j < 2; j++)
        for(int i = 0; i < 10; i++)
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


    for(int i = 0; i < 2; i++)
        nextPrev[i] = new QPushButton(this);

    nextPrev[0]->setObjectName("Precedent");
    nextPrev[1]->setObjectName("Suivant");

    nextPrev[0]->setFixedSize(58, 58);
    nextPrev[1]->setFixedSize(58, 58);

    label[0]->move(120, 78);
    label[1]->move(120, 118);
    label[2]->move(120, 158);
    label[3]->move(120, 198);
    label[4]->move(120, 238);
    label[5]->move(120, 278);
    label[6]->move(120, 318);
    label[7]->move(120, 358);
    label[8]->move(120, 398);
    label[9]->move(120, 438);

    nextPrev[0]->move(20, 240);
    nextPrev[1]->move(570, 240);

    if(time)
    {
        text = new QLabel(tr("Temps :"),this);
        minute = new QLabel("00", this);
        deuxPoint = new QLabel(":", this);
        seconde = new QLabel("00", this);

        secondes = 0;

        text->move(235, 15);
        minute->move(330, 15);
        deuxPoint->move(355, 15);
        seconde->move(380, 15);

        startTime();
    }

    connect(corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(quitter, SIGNAL(clicked()), this, SIGNAL(wasClosed()));


    connect(nextPrev[0], SIGNAL(clicked()), this, SLOT(Previous()));
    connect(nextPrev[1], SIGNAL(clicked()), this, SLOT(Next()));

    for(int i = 0; i < 10; i++)
        connect(reponses[i], SIGNAL(enterKeyPressed(int)), this, SLOT(newSetFocus(int)));

    reponses[0]->setFocus();
}

inline void MediumModeWindow::ApplyStyle()
{
    QFile css(":/css/Fen2.css");
    css.open(QIODevice::ReadOnly);
    setStyleSheet(css.readAll());
    css.close();
}

void MediumModeWindow::newSetFocus(const int number)
{
    if(number < 9)
    {
        int num = number+1;
        reponses[num]->setFocus();
        reponses[num]->selectAll();
    }
    else
        correct();
}
inline void MediumModeWindow::startTime()
{
    chronometre = new QTimer;
    chronometre->start(1000);
    connect(chronometre, SIGNAL(timeout()), this, SLOT(newSecond()));
    connect(this, SIGNAL(addSeconde(int)), this, SLOT(updateLabel(int)));
}
inline void MediumModeWindow::closeEvent(QCloseEvent *event)
{
    if(time && event->spontaneous())
        delete chronometre;
    event->accept();
}
void MediumModeWindow::newSecond()
{
    secondes++;
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
inline void MediumModeWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MediumModeWindow::Previous()
{
    if(m_multiple > 1)
        m_multiple--;
    setNewNumber(m_multiple);
}
void MediumModeWindow::Next()
{
    if(m_multiple < 10)
        m_multiple += 1;
    setNewNumber(m_multiple);
}
inline void MediumModeWindow::setNewNumber(register int newNumber)
{
    this->setWindowTitle(tr("Table de ")+QString::number(newNumber));

    corriger->setText("Corriger");

    for(int i = 0; i < 10; i++)
        label[i]->setText("<span style=\"color: #9FC54D\">"+QString::number(newNumber)+"</span> x "+QString::number(array[i]));

    for(int i = 0; i < 10; i++)
    {
        labelCorrection[i]->setVisible(false);

        reponses[i]->clear();
        reponses[i]->setVisible(true);

        trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
    }
    reponses[0]->setFocus();
}
void MediumModeWindow::correct()
{
    if(time)
    {
        chronometre->stop();
        delete chronometre;
        int time[2];
        time[1] = secondes / 60;
        time[0] = secondes % 60;
        secondes = 0;
        QMessageBox::information(this, "Ton temps", "Tu as mis "+QString::number(time[1])+" minute(s) et "+QString::number(time[0])+" secondes !");
    }

    note = 10;

    corriger->setText("Retenter");
    disconnect(corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(corriger, SIGNAL(clicked()), this, SLOT(Retry()));

    for(int i = 0; i < 10; i++)
    {
        int number = reponses[i]->text().toInt();
        reponses[i]->setVisible(false);

        if((m_multiple * array[i]) == number)
        {
            trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/Right.png"));
            trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));

            labelCorrection[i]->setText("<span style=\"color: #9FC54D;\">" + QString::number(number) + " C'est la bonne réponse !</span>");
            labelCorrection[i]->move(200, (80 + 40 * i));
            labelCorrection[i]->setVisible(true);
        }
        else
        {

            trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
            trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/Wrong.png"));

            int Answer = m_multiple * array[i];

            labelCorrection[i]->setText("<span style=\"color: red;\">" + QString::number(number) + "</span> <span style=\"color: #9FC54D;\">La bonne réponse était " + QString::number(Answer) + "</span>");
            labelCorrection[i]->move(200, (80 + 40 * i));
            labelCorrection[i]->setVisible(true);

            if(note != 0)
                note--;
        }

        this->repaint();

    }
}
void MediumModeWindow::Retry()
{
    corriger->setText("Corriger");
    disconnect(corriger, SIGNAL(clicked()), this, SLOT(Retry()));
    connect(corriger, SIGNAL(clicked()), this, SLOT(correct()));

    for(int i = 0; i < 10; i++)
    {
        labelCorrection[i]->setVisible(false);
        reponses[i]->clear();
        reponses[i]->setVisible(true);

        trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
    }

    if(time)
    {
        minute->setText("00");
        seconde->setText("00");
        startTime();
    }
}

const int MediumModeWindow::getMultiple() { return m_multiple; }

MediumModeWindow::~MediumModeWindow()
{
    time = false;
    delete corriger;
    corriger = nullptr;

    delete quitter;
    quitter = nullptr;

    for(int i = 0; i < 10; i++)
    {
        delete label[i];
        label[i] = nullptr;

        delete labelPoint[i];
        labelPoint[i] = nullptr;

        /*delete reponses[i];
        reponses[i] = nullptr;*/
    }

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            delete trueFalseLabel[i][j];
            trueFalseLabel[i][j] = nullptr;
        }

        /*delete nextPrev[i];
        nextPrev[i] = nullptr;*/
    }

    if(time)
    {
        delete text;
        delete minute;
        delete seconde;
        delete deuxPoint;
        delete chronometre;


        chronometre = nullptr;
        text = nullptr;
        minute = nullptr;
        seconde = nullptr;
        deuxPoint = nullptr;
    }
}
