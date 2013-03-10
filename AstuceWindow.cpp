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

#include "AstuceWindow.h"

AstuceWindow::AstuceWindow(const int table) : QWidget()
{
    setFixedSize(441, 182);
    QFile css(":/css/Fen2.css");
    css.open(QIODevice::ReadOnly);
    this->setStyleSheet(css.readAll());
    css.close();

    astucesInit();
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    label = new QLabel(this);
    label->setObjectName("LabelAstuce");

    OkBouton = new QPushButton("Ok", this);
    OkBouton->setAttribute(Qt::WA_TranslucentBackground);
    OkBouton->setObjectName("OkBouton");
    OkBouton->move(385, 125);

    label->setText("Les astuces nes sont pas encore disponibles !<br /> Reviens bientôt !");

    /*if(astuces.contains(table))
        label->setText(astuces[table]);
    else
        label->setText(tr("Il n'y a pas encore d'astuces pour cette table."));*/

    connect(OkBouton, SIGNAL(clicked()), this, SLOT(close()));
}
inline void AstuceWindow::astucesInit()
{
    astuces[1] = tr("Pour la table de 1, le résultat sera toujours <br />égal au nombre que multiplie 1.<br /><br /><span style=\"color: #9FC54D\">Ex</span> : 1 x <span style=\"text-decoration: underline;\">7</span> = <span style=\"text-decoration: underline;\">7</span></strong>");
    astuces[2] = tr("Pour la table de 2, le résultat est toujours un nombre paire et les résultats vont de 2 en 2.<br /><span style=\"color: #9FC54D\">Ex</span> :<br /><strong>2 x 1 = <span style=\"text-decoration: underline;\">2</span><br />2 x 2 = <span style=\"text-decoration: underline;\">4</span></strong>");
    astuces[5] = tr("Pour la table de 5, le résultat termine soit par 0 <br />soit par 5. Cela dépend du nombre que <br />multiplie 5 : si le nombre est paire, le résultat terminera par 0 sinon, si le nombre est impaire, le résultat terminera par 5. En plus, les résultats vont de 5 en 5 !<br /><span style=\"color: #9FC54D\">Ex</span> :<br /><strong>5 x 2 = <span style=\"text-decoration: underline;\">10</span><br />5 x 3 = <span style=\"text-decoration: underline;\">15</span></strong>");
    astuces[10] = tr("Pour la table de 10, on rajoute un 0 au chiffre que multiplie 10.<br /><span style=\"color: #9FC54D\">Ex</span> :<br /><strong><span style=\"text-decoration: underline;\">5</span> x 10 = <span style=\"text-decoration: underline;\">50</span></strong>");
}
void AstuceWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
AstuceWindow::~AstuceWindow()
{
    delete label;
    label = nullptr;
}
