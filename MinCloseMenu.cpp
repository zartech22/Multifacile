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

MinCloseMenu::MinCloseMenu(QWidget *parent) : QWidget(parent), ParentWidget(parent)
{
    cross = new QPushButton("X");
    mini = new QPushButton("_");

    cross->setObjectName("Cross");
    mini->setObjectName("mini");

    layout = new QHBoxLayout;

    layout->addWidget(mini);
    layout->addWidget(cross);

    this->setLayout(layout);

    connect(cross, SIGNAL(clicked()), parent, SLOT(close()));
    connect(mini, SIGNAL(clicked()), ParentWidget, SLOT(showMinimized()));
}
MinCloseMenu::~MinCloseMenu()
{
    delete cross, mini, layout;

    cross = nullptr;
    mini = nullptr;
    layout = nullptr;
}
