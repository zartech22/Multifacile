/*Copyright (C) <2013> <Plestan> <K�vin>

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

#include "Menu.h"


bool Menu::event(QEvent *e)
{

    if(e->type() == QEvent::ToolTip)
    {
        QHelpEvent *he = dynamic_cast<QHelpEvent*>(e);
        QAction *act = actionAt(he->pos());

        if(act)
            QToolTip::showText(he->globalPos(), act->toolTip());
    }
    else
        QToolTip::hideText();

    return QMenu::event(e);
}