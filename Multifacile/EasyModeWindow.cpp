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

#include "EasyModeWindow.h"

EasyModeWindow::EasyModeWindow(const unsigned short m_multiplicateur)
{
    initStyle();
    initButtons();
    initTimer();

    _mode = EASY;
    _multiple = m_multiplicateur;

    setWindowFlags(Qt::FramelessWindowHint);
    Shuffle shuffle(false);
    shuffle.getNumbers(_array);

    setWindowTitle(tr("Table de ")+QString::number(_multiple));

    initLineEdit();
    initLabels();
    initNextPrev();


    startTime();

}

void EasyModeWindow::initButtons()
{
    MediumModeWindow::initButtons();

    _astuces = new QPushButton(tr("Astuce"));
    _astuces->setParent(this);
    _astuces->setFixedSize(70, 40);
    _astuces->move(310, 490);
    _astuces->setObjectName("Astuce");

    connect(_astuces, SIGNAL(clicked()), this, SLOT(openAstuce()));
}

void EasyModeWindow::openAstuce() const
{
    CustomMessageBox trick (Trick, 0, _multiple);
    trick.setObjectName("AstuceFen");
    trick.exec();
}
EasyModeWindow::~EasyModeWindow()
{
    delete _astuces;
    _astuces = NULL;
}
