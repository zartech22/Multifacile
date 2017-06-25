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

#ifndef ASTUCEWINDOW_H
#define ASTUCEWINDOW_H

#include <QDialog>
#include <QMap>
#include <QStyleOption>
#include <QPainter>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

#include "MinCloseMenu.h"
#include "Include.h"

enum MessageType
{
    Trick, Results, ConnectionError, NoUpdateMsg, NewUpdate, CannotMediumMode, CannotHardMode, CannotDoThisTable
};

typedef enum MessageType MessageType;

/* Message Box personnalisé utilisé pour toutes interaction avec l'utilisateur
     -Astuce
     -Resultats
     -Erreur de connection
     -Pas de mise a jour disponible
     -Nouvelle mise a jour
     -Mode moyen inacessible
     -Mode difficile inacessible
     -Table inacessible
 */

class CustomMessageBox : public QDialog
{
    Q_OBJECT
public:
    CustomMessageBox(MessageType msgType, QWidget *parent = 0, const operande table = 0);
    CustomMessageBox(const operande time, const operande note, QWidget *parent = 0);
private:
    QLabel *_label;
    QPushButton *_okBouton;
    MinCloseMenu *_menu;
    bool _clickOnWindow;
    QPoint _Diff;
    MessageType _type;

    inline void tricksInit(QMap<operande, QString> &tricks);  //initialise les astuces
    void displayTricks(const operande &table);  //affcihe l'astuce
    void displayResults(const operande &time, const operande &note);  //affiche les resultats
    void displayConnectionError();  //Affiche l'erreur de connection
    void displayNoUpdate();  //Affiche qu'il n'y a pas de mise a jours
    void displayNewUpdate();  //Affcihe qu'il y a une nouvelle mise a jour
    void displayCannotAMode();  //Affiche qu'on ne peut pas acceder a un mode
    void displayCannotDoATable(const operande &table);  //Affiche qu'on ne peut pas acceder a uune table
    void calculTime(const operande &time, operande &minutes, operande &seconds); //Donne le nombre de minutes et de secondes en fonction de time qui est en secondes
    void setSmiley(const operande &note, QPixmap &smiley);  //Attribut un smiley a smiley en fonction de note

    void paintEvent(QPaintEvent *);  //reimplementation pour afficher l'image de fond approprie
    void mouseMoveEvent(QMouseEvent *event);  // (Les trois fonctions)  Gestion du deplacement de la fenetre
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *) { _clickOnWindow = false; }

};

#endif // ASTUCEWINDOW_H
