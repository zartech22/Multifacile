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
    shuffle.getNumbers(array, multiple);
    setWindowFlags(Qt::FramelessWindowHint);

    this->setWindowTitle(tr("Table aléaoire"));


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

    text = new QLabel(tr("Temps : "), this);
    minute = new QLabel("00", this);
    deuxPoint = new QLabel(":", this);
    seconde = new QLabel("00", this);

    secondes = 0;

    text->move(235, 15);
    minute->move(330, 15);
    deuxPoint->move(355, 15);
    seconde->move(380, 15);

    mapper = new QSignalMapper(this);


    for(int i = 0; i < 10; ++i)
    {
        reponses[i] = new QLineEdit(this);
        reponses[i]->setAttribute(Qt::WA_TranslucentBackground);
        reponses[i]->setFixedSize(302, 69);
        reponses[i]->move(185, (60 + 40 * i));
        reponses[i]->setValidator(new QRegExpValidator(QRegExp("\\d{0,3}"), reponses[i]));

        connect(reponses[i], SIGNAL(returnPressed()), mapper, SLOT(map()));
        mapper->setMapping(reponses[i], (i + 1));
    }

    for(int i = 0; i < 10; ++i)
    {
        label[i] = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(multiple[i])+"</span> x "+QString::number(array[i]), this);
        label[i]->setFixedSize(100, 30);
    }

    for(int i = 0; i < 10; ++i)
    {
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

    for(int i = 0; i < 10; ++i)
    {
        labelPoint[i] = new QLabel(this);
        labelPoint[i]->setPixmap(QPixmap(":/image/Point.png"));
        labelPoint[i]->move(105, (90 + 40 * i));
    }

    for(int i = 0; i < 10; ++i)
        label[i]->move(120, (78 + 40 * i));

    startTime();

    connect(quitter, SIGNAL(clicked()), this, SIGNAL(wasClosed()));
    connect(corriger, SIGNAL(clicked()), this, SLOT(correct()));

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(newSetFocus(int)));
}
void HardModeWindow::correct()
{
    int rep[10];
    for(int i = 0; i < 10; ++i)
        rep[i] = reponses[i]->text().toInt();

    Correction correction(multiple, array, rep, secondes);

    bool isGood[10];
    QString texte[10];

    note = correction.getCorrection(texte, isGood);

    corriger->setText(tr("Retenter"));
    disconnect(corriger, SIGNAL(clicked()), this, SLOT(correct()));
    connect(corriger, SIGNAL(clicked()), this, SLOT(Retry()));

    chronometre->stop();
    delete chronometre;
    chronometre = NULL;

    CustomMessageBox results(secondes, note, this);

    secondes = 0;

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
void HardModeWindow::Retry()
{
    corriger->setText(tr("Corriger"));
    disconnect(corriger, SIGNAL(clicked()), this, SLOT(Retry()));
    connect(corriger, SIGNAL(clicked()), this, SLOT(correct()));

    Shuffle shuffle(true);
    shuffle.getNumbers(array, multiple);


    for(int i = 0; i < 10; ++i)
    {
        label[i]->setText("<span style=\"color: #9FC54D\">"+QString::number(multiple[i])+"</span> x "+QString::number(array[i]));
        trueFalseLabel[0][i]->setPixmap(QPixmap(":/image/OpacRight.png"));
        trueFalseLabel[1][i]->setPixmap(QPixmap(":/image/OpacWrong.png"));
        reponses[i]->clear();
        reponses[i]->setVisible(true);
        delete labelCorrection[i];
    }

    reponses[0]->setFocus();

    minute->setText("00");
    seconde->setText("00");
    startTime();
}
