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

EasyModeWindow::EasyModeWindow(const operande m_multiplicateur) : MediumModeWindow()
{
    _mode = EASY;
    _multiple = m_multiplicateur;

    Shuffle shuffle(false);
    shuffle.getNumbers(_array);

    setWindowTitle(tr("Table de ")+QString::number(_multiple));

    initTipButton();
    initLabels();
}

void EasyModeWindow::initTipButton()
{
    _tip = new QPushButton(tr("Astuce"));
    _tip->setParent(this);
    _tip->setFixedSize(70, 40);
    _tip->move(310, 490);
    _tip->setObjectName("Astuce");

    connect(_tip, SIGNAL(clicked()), this, SLOT(openTip()));
}

void EasyModeWindow::openTip() const
{
    CustomMessageBox trick(Trick, 0, _multiple);
    trick.setObjectName("AstuceFen");
    trick.exec();
}
