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

#include "CustomMessageBox.h"

CustomMessageBox::CustomMessageBox(MessageType msgType, QWidget *parent, const operande table) : QDialog(parent, Qt::FramelessWindowHint), _clickOnWindow(false), _type(msgType)
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    _menu = new MinCloseMenu(this);
    _menu->setStyleSheet("QPushButton#Cross{background-image: url(none);}QPushButton#mini{margin-right: 5px;}QPushButton{background-color: rgba(255, 255, 255, 0);margin: 0px;padding: 0px;}QPushButton:pressed{color: rgb(255,169,50);}");
    _label = new QLabel(this);

    _okBouton = new QPushButton("Ok", this);
    _okBouton->setAttribute(Qt::WA_TranslucentBackground);
    _okBouton->setObjectName("OkBouton");
    _okBouton->setStyleSheet("QPushButton#OkBouton{background-color: rgba(255, 255, 255, 0);color: rgb(144,191,79);}");

    switch(_type)
    {
    case ConnectionError:
        displayConnectionError();
        break;
    case NewUpdate:
        displayNewUpdate();
        break;
    case NoUpdateMsg:
        displayNoUpdate();
        break;
    case Trick:
        displayTricks(table);
        break;
    case CannotMediumMode:
    case CannotHardMode:
        displayCannotAMode();
        break;
    case CannotDoThisTable:
        displayCannotDoATable(table);
        break;
    }

    connect(_okBouton, SIGNAL(clicked()), this, SLOT(close()));
}

CustomMessageBox::CustomMessageBox(const operande time, const operande note, QWidget* parent) : QDialog(parent, Qt::FramelessWindowHint), _clickOnWindow(false), _type(Results)
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    _menu = new MinCloseMenu(this);
    _menu->setStyleSheet("QPushButton#Cross{background-image: url(none);}QPushButton#mini{margin-right: 5px;}QPushButton{background-color: rgba(255, 255, 255, 0);margin: 0px;padding: 0px;}QPushButton:pressed{color: rgb(255,169,50);}");

    _label = new QLabel(this);

    _okBouton = new QPushButton("Ok", this);
    _okBouton->setAttribute(Qt::WA_TranslucentBackground);
    _okBouton->setObjectName("OkBouton");
    _okBouton->setStyleSheet("QPushButton#OkBouton{background-color: rgba(255, 255, 255, 0);color: rgb(144,191,79);}");

    displayResults(time, note);

    connect(_okBouton, SIGNAL(clicked()), this, SLOT(close()));
}

void CustomMessageBox::displayTricks(const operande &table)
{
    setFixedSize(646, 266);

    QMap<unsigned short int, QString> tricks;
    tricksInit(tricks);

    _label->setObjectName("LabelAstuce");
    _label->setFixedWidth(625);
    _label->setWordWrap(true);
    _label->move(10, 40);

    _menu->move(560, 0);
    _okBouton->move(575, 200);

    if(tricks.contains(table))
        _label->setText(tricks[table]);
    else
        _label->setText(tr("Il n'y a pas encore d'astuces pour cette table."));
}

void CustomMessageBox::tricksInit(QMap<operande, QString> &tricks)
{
    tricks[1] = tr("Pour la table de 1, le résultat sera toujours égal au nombre que multiplie 1.<br /><span style=\"color: #9FC54D\">Ex</span> : 1 x <span style=\"text-decoration: underline;\">7</span> = <span style=\"text-decoration: underline;\">7</span></strong>");
    tricks[2] = tr("Pour la table de 2, le résultat est toujours un nombre paire et les résultats vont de 2 en 2.<br /><span style=\"color: #9FC54D\">Ex</span> : <strong>2 x 1 = <span style=\"text-decoration: underline;\">2</span><br />2 x 2 = <span style=\"text-decoration: underline;\">4</span></strong>");
    tricks[5] = tr("Pour la table de 5, le résultat termine soit par 0 soit par 5. Cela dépend du nombre que multiplie 5 : si le nombre est paire, le résultat terminera par 0 sinon, si le nombre est impaire, le résultat terminera par 5. En plus, les résultats vont de 5 en 5 !<br /><span style=\"color: #9FC54D\">Ex</span> : <strong>5 x 2 = <span style=\"text-decoration: underline;\">10</span><br />5 x 3 = <span style=\"text-decoration: underline;\">15</span></strong>");
    tricks[9] = tr("Pour la table de 9, tu la connais déjà ! Tu as déjà eu à multiplier 9 par les autres chiffres dans les autres tables il te suffit de retenir en plus :<br />9 x 9 = 81<br />9 x 10 = 90");
    tricks[10] = tr("Pour la table de 10, on rajoute un 0 au chiffre que multiplie 10.<br /><span style=\"color: #9FC54D\">Ex</span> : <strong><span style=\"text-decoration: underline;\">5</span> x 10 = <span style=\"text-decoration: underline;\">50</span></strong>");
}

void CustomMessageBox::displayConnectionError()
{
    setFixedSize(434, 179);
    _label->setText(tr("Impossible de vérifier les mise à jours"));
    _label->move(45, 65);

    _menu->move(376, 0);
    _okBouton->move(386, 135);
}

void CustomMessageBox::displayResults(const operande &time, const operande &note)
{
    setFixedSize(434, 179);

    unsigned short int seconds, minutes;

    calculTime(time, minutes, seconds);

    QLabel *noteLabel = new QLabel("<span style=\"color: #9FC54D\">"+QString::number(note)+"</span>/10", this);
    QLabel *smiley = new QLabel(this);

    QPixmap smileyPixmap;
    setSmiley(note, smileyPixmap);
    smiley->setPixmap(smileyPixmap);

    noteLabel->move(217, 110);
    smiley->move(287, 115);



    _label->setText(tr("Tu as mis %1 minute(s) et %2 seconde(s) pour faire ta table.<br />Et tu as eu :").arg(minutes).arg(seconds));
    _label->setWordWrap(true);
    _label->move(85, 45);

    _menu->move(376, 0);
    _okBouton->move(386, 135);
    _okBouton->setDefault(true);
    _okBouton->setFocus();
}

void CustomMessageBox::displayNoUpdate()
{
    setFixedSize(434, 179);

    _label->setText("Il n'y a aucune mise à jour disponible pour le moment.");
    _label->setWordWrap(true);
    _label->move(45, 50);

    _menu->move(376, 0);
    _okBouton->move(386, 135);
}

void CustomMessageBox::displayNewUpdate()
{
    setFixedSize(434, 179);

    _label->setText("Une version plus récente de Multifacile est disponible, veux-tu la télécharger ?");
    _label->setWordWrap(true);
    _label->move(45, 50);

    _menu->move(376, 0);


    _okBouton->setText(tr("Oui"));
    _okBouton->move(346, 135);

    QPushButton *No = new QPushButton(tr("Non"), this);
    No->setAttribute(Qt::WA_TranslucentBackground);
    No->move(386, 140);
    No->setObjectName("NoButton");
    No->setStyleSheet("QPushButton#NoButton{background-color: rgba(255, 255, 255, 0);color: rgb(144,191,79); background-image: url(none);}");

    disconnect(_okBouton, SIGNAL(clicked()), this, SLOT(close()));

    connect(_okBouton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(No, SIGNAL(clicked()), this, SLOT(reject()));
}

void CustomMessageBox::displayCannotAMode()
{
    setFixedSize(434, 179);

    (_type == CannotMediumMode) ? _label->setText("Réussis au moins une table du mode Facile sans faire de faute pour accéder au mode Moyen.")
                                : _label->setText("Réussis toutes les tables du mode Moyen et du mode Facile sans faire de faute pour accéder au mode Difficile.");
    _label->setWordWrap(true);
    _label->move(45, 50);

    _menu->move(376, 0);
    _okBouton->move(386, 135);
}

void CustomMessageBox::displayCannotDoATable(const operande &table)
{
    setFixedSize(434, 179);

    _label->setText("Réussis d'abords à faire la table de " + QString::number(table) + " sans faute en mode Facile pour la faire en mode Moyen.");
    _label->setWordWrap(true);
    _label->move(45, 50);

    _menu->move(376, 0);

    _okBouton->move(386, 135);
}

void CustomMessageBox::calculTime(const operande &time, operande &minutes, operande &seconds)
{
    minutes = time/60;
    seconds = time % 60;
}

void CustomMessageBox::setSmiley(const operande &note, QPixmap &smiley)
{
    if(note < 3)
        smiley.load(":/smiley/mauvais.png");
    else if (note < 10)
        smiley.load(":/smiley/bien.png");
    else // note == 10
        smiley.load(":/smiley/excellent.png");
}

void CustomMessageBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRectF imgRect;
    QRectF deviceRect;
    QImage img;

    if(_type == Trick)
    {
        imgRect.setCoords(0, 0, 646, 266);
        deviceRect.setCoords(0, 0, 646, 266);
        img.load(":/image/Background_Astuce.png");
    }
    else
    {
        imgRect.setCoords(0, 0, 434, 179);
        deviceRect.setCoords(0, 0, 434, 179);
        img.load(":/image/Message_box.png");
    }

    painter.drawImage(deviceRect, img, imgRect);

    painter.end();
}

void CustomMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    if(_clickOnWindow)
        window()->move(event->globalPos() - _Diff);
}

void CustomMessageBox::mousePressEvent(QMouseEvent *event)
{
    _clickOnWindow = true;
    _Diff = event->pos();
}
