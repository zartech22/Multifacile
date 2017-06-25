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

#include "MinCloseMenu.h"

MinCloseMenu::MinCloseMenu(QWidget *parent) : QWidget(parent), _ParentWidget(parent), _cross("X"), _mini("_")
{
    _cross.setObjectName("Cross");
    _mini.setObjectName("mini");

    _cross.setDefault(false);
    _mini.setDefault(false);

    _layout.addWidget(&_mini);
    _layout.addWidget(&_cross);

    this->setLayout(&_layout);

    connect(&_cross, SIGNAL(clicked()), _ParentWidget, SLOT(close()));
    connect(&_mini, SIGNAL(clicked()), _ParentWidget, SLOT(showMinimized()));
}
