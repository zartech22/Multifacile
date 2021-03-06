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

#ifndef SHUFFLEQUESTIONNAIRE_H
#define SHUFFLEQUESTIONNAIRE_H

#include "MediumModeWindow.h"
#include "Shuffle.h"
#include "CustomMessageBox.h"

class EasyModeWindow : public MediumModeWindow  // Classe representant la fenetre de table en mode facile. Herite de MediumModeWindow
{
    Q_OBJECT
public:
    EasyModeWindow(const operande m_multiplicateur);
protected:
    QPushButton *_tip;

    void checkTableAvailable() {} //reimplementation
    void initTipButton();
public slots:
    void openTip() const;  //ouvre la fenetre astuce
};

#endif // SHUFFLEQUESTIONNAIRE_H
