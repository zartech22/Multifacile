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

#include "HardModeWindow.h"

HardModeWindow::HardModeWindow(bool chrono)
{
    time = chrono;
    Shuffle shuffle(true);
    shuffle.getNumbers(array, multiple);
    this->setWindowTitle(tr("Table aléatoire"));

    corriger = new QPushButton(tr("Corriger"));

    hlayoutBottom = new QHBoxLayout;

    hlayoutBottom->addWidget(corriger);

    if(time)
    {
        text = new QLabel(tr("Temps : "));
        minute = new QLabel("00");
        deuxPoint = new QLabel(":");
        seconde = new QLabel("00");

        hlayoutTop = new QHBoxLayout;
        hlayoutTop->setAlignment(Qt::AlignCenter);
        hlayoutTop->addWidget(text);
        hlayoutTop->addWidget(minute);
        hlayoutTop->addWidget(deuxPoint);
        hlayoutTop->addWidget(seconde);
    }

    for(int i = 0; i < 10; i++)
    {
        reponses[i] = new SpinBox();
        reponses[i]->setMaximum(2147483647);
        reponses[i]->setMinimum(-2147483647);
        reponses[i]->setValue(0);
        reponses[i]->setNumero(i);
        if(i == 0)
        {
            reponses[i]->setFocus();
            reponses[i]->selectAll();
        }
    }

    for(int i = 0; i < 10; i++)
        label[i] = new QLabel(QString::number(multiple[i])+" x "+QString::number(array[i]));

    layout = new QFormLayout();

    for(int i = 0; i < 10; i++)
        layout->addRow(label[i], reponses[i]);

    vlayout = new QVBoxLayout();
    if(time)
        vlayout->addLayout(hlayoutTop);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayoutBottom);


    this->setLayout(vlayout);
    if(time)
        startTime();

    connect(corriger, SIGNAL(clicked()), this, SLOT(open()));

    for(int i = 0; i < 10; i++)
        connect(reponses[i], SIGNAL(enterKeyPressed(int)), this, SLOT(newSetFocus(int)));

}
void HardModeWindow::open()
{
    if(time)
    {
        chronometre->stop();
        fen = new Fen_correction(reponses, multiple, array, secondes);
    }
    else if(!time)
        fen = new Fen_correction(reponses, multiple, array);
    fen->resize(200, 200);
    fen->show();
    this->close();
}
HardModeWindow::~HardModeWindow()
{
}
