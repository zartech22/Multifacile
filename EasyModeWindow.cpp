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

#include "EasyModeWindow.h"

EasyModeWindow::EasyModeWindow(const int m_multiplicateur, bool chrono) : time(chrono)
{
    ApplyStyle();

    m_multiple = m_multiplicateur;

    setWindowFlags(Qt::FramelessWindowHint);
    Shuffle shuffle(false);
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

    astuces = new QPushButton(tr("Astuce"));
    astuces->setParent(this);
    astuces->setFixedSize(70, 40);
    astuces->move(310, 490);
    astuces->setObjectName("Astuce");

    if(time)
    {
        text = new QLabel(tr("Temps : "), this);
        minute = new QLabel("00", this);
        deuxPoint = new QLabel(":", this);
        seconde = new QLabel("00", this);

        text->move(235, 15);
        minute->move(330, 15);
        deuxPoint->move(355, 15);
        seconde->move(380, 15);
    }


    for(int i = 0; i < 10; i++)
    {
        reponses[i] = new SpinBox(this);
        reponses[i]->setAttribute(Qt::WA_TranslucentBackground);
        reponses[i]->setNumero(i);
        reponses[i]->setFixedSize(302, 69);
        reponses[i]->move(185, (60 + 40 * i));

        labelCorrection[i] = new QLabel(this);
        labelCorrection[i]->setVisible(false);
    }

    reponses[0]->setFocus();

    register int temp_multiple = m_multiple;

    for(int i = 0; i < 10; i++)
    {
        label[i] = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(temp_multiple)+"</span> x "+QString::number(array[i]), this);
        label[i]->setFixedSize(100, 30);
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

    for(int i = 0; i < 10; i++)
    {
        labelPoint[i] = new QLabel(this);
        labelPoint[i]->setPixmap(QPixmap(":/image/Point.png"));
        labelPoint[i]->move(105, (90 + 40 * i));
    }

    nextPrev[0] = new QPushButton(this);
    nextPrev[0]->setObjectName("Precedent");
    nextPrev[0]->setFixedSize(58, 58);
    nextPrev[0]->move(20, 240);

    nextPrev[1] = new QPushButton(this);
    nextPrev[1]->setObjectName("Suivant");
    nextPrev[1]->setFixedSize(58, 58);
    nextPrev[1]->move(570, 240);

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

    if(time)
        startTime();

    connect(quitter, SIGNAL(clicked()), this, SIGNAL(wasClosed()));
    connect(corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(astuces, SIGNAL(clicked()), this, SLOT(openAstuce()));

    connect(nextPrev[0], SIGNAL(clicked()), this, SLOT(Previous()));
    connect(nextPrev[1], SIGNAL(clicked()), this, SLOT(Next()));

    for(int i = 0; i < 10; i++)
        connect(reponses[i], SIGNAL(enterKeyPressed(int)), this, SLOT(newSetFocus(int)));
}
void EasyModeWindow::openAstuce() const
{
    AstuceWindow *astuce = new AstuceWindow(m_multiple);
    astuce->setObjectName("AstuceFen");
    astuce->show();
}
EasyModeWindow::~EasyModeWindow()
{
    delete astuces;
    astuces = nullptr;
}
