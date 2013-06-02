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

#include "AstuceWindow.h"

AstuceWindow::AstuceWindow(const int table, QWidget *parent) : QDialog(parent, Qt::FramelessWindowHint), clickOnWindow(false)
{
    setFixedSize(646, 266);

    astucesInit();
    this->setAttribute(Qt::WA_TranslucentBackground);

    menu = new MinCloseMenu(this);
    menu->move(560, 0);
    menu->setStyleSheet("QPushButton#Cross{background-image: url(none);}QPushButton#mini{margin-right: 5px;}QPushButton{background-color: rgba(255, 255, 255, 0);margin: 0px;padding: 0px;}QPushButton:pressed{color: rgb(255,169,50);}");
    label = new QLabel(this);
    label->setObjectName("LabelAstuce");
    label->setFixedWidth(625);
    label->setWordWrap(true);
    label->move(10, 40);

    OkBouton = new QPushButton("Ok", this);
    OkBouton->setAttribute(Qt::WA_TranslucentBackground);
    OkBouton->setObjectName("OkBouton");
    OkBouton->move(575, 200);
    OkBouton->setStyleSheet("QPushButton#OkBouton{background-color: rgba(255, 255, 255, 0);color: rgb(144,191,79);}");

    if(astuces.contains(table))
        label->setText(astuces[table]);
    else
        label->setText(tr("Il n'y a pas encore d'astuces pour cette table."));

    connect(OkBouton, SIGNAL(clicked()), this, SLOT(close()));
}
inline void AstuceWindow::astucesInit()
{
    astuces[1] = tr("Pour la table de 1, le résultat sera toujours égal au nombre que multiplie 1.<br /><span style=\"color: #9FC54D\">Ex</span> : 1 x <span style=\"text-decoration: underline;\">7</span> = <span style=\"text-decoration: underline;\">7</span></strong>");
    astuces[2] = tr("Pour la table de 2, le résultat est toujours un nombre paire et les résultats vont de 2 en 2.<br /><span style=\"color: #9FC54D\">Ex</span> : <strong>2 x 1 = <span style=\"text-decoration: underline;\">2</span><br />2 x 2 = <span style=\"text-decoration: underline;\">4</span></strong>");
    astuces[5] = tr("Pour la table de 5, le résultat termine soit par 0 soit par 5. Cela dépend du nombre que multiplie 5 : si le nombre est paire, le résultat terminera par 0 sinon, si le nombre est impaire, le résultat terminera par 5. En plus, les résultats vont de 5 en 5 !<br /><span style=\"color: #9FC54D\">Ex</span> : <strong>5 x 2 = <span style=\"text-decoration: underline;\">10</span><br />5 x 3 = <span style=\"text-decoration: underline;\">15</span></strong>");
    astuces[9] = tr("Pour la table de 9, tu la connais déjà ! Tu as déjà eu à multiplier 9 par les autres chiffres dans les autres tables il te suffit de retenir en plus :<br />9 x 9 = 81<br />9 x 10 = 90");
    astuces[10] = tr("Pour la table de 10, on rajoute un 0 au chiffre que multiplie 10.<br /><span style=\"color: #9FC54D\">Ex</span> : <strong><span style=\"text-decoration: underline;\">5</span> x 10 = <span style=\"text-decoration: underline;\">50</span></strong>");
}
void AstuceWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRectF imgRect(0, 0, 646, 266);
    QRectF deviceRect(0, 0, 646, 266);
    QImage img(":/image/Background_Astuce.png");

    painter.drawImage(deviceRect, img, imgRect);

    painter.end();
}
inline void AstuceWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(clickOnWindow)
        window()->move(event->globalPos() - Diff);
}
inline void AstuceWindow::mousePressEvent(QMouseEvent *event)
{
    clickOnWindow = true;
    Diff = event->pos();
}
inline void AstuceWindow::mouseReleaseEvent(QMouseEvent *) { clickOnWindow = false; }
AstuceWindow::~AstuceWindow()
{
    delete label;
    label = nullptr;
}
