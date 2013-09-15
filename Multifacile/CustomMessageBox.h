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

enum MessageType
{
    Trick, Results, ConnectionError, NoUpdateMsg, NewUpdate, CannotMediumMode, CannotHardMode, CannotDoThisTable
};

typedef enum MessageType MessageType;

class CustomMessageBox : public QDialog
{
    Q_OBJECT
public:
    CustomMessageBox(MessageType msgType, QWidget *parent = 0, const unsigned short int table = 0);
    CustomMessageBox(const unsigned short int time, const unsigned short int note, QWidget *parent = 0);
    ~CustomMessageBox();
private:
    QLabel *label;
    QPushButton *OkBouton;
    MinCloseMenu *menu;
    bool clickOnWindow;
    QPoint Diff;
    MessageType type;

    inline void tricksInit(QMap<unsigned short int, QString> &tricks);
    void displayTricks(const unsigned short int &table);
    void displayResults(const unsigned short int &time, const unsigned short int &note);
    void displayConnectionError();
    void displayNoUpdate();
    void displayNewUpdate();
    void displayCannotAMode();
    void displayCannotDoATable(const int &table);
    void calculTime(const unsigned short int &time, unsigned short int &minutes, unsigned short int &seconds);
    void setSmiley(const unsigned short int &note, QPixmap &smiley);

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *) { clickOnWindow = false; }

};

#endif // ASTUCEWINDOW_H
