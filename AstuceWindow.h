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

class AstuceWindow : public QDialog
{
    Q_OBJECT
public:
    AstuceWindow(const int table, QWidget *parent = 0);
    ~AstuceWindow();
private:
    QLabel *label;
    QMap<int, QString> astuces;
    QPushButton *OkBouton;
    MinCloseMenu *menu;
    bool clickOnWindow;
    QPoint Diff;
    inline void astucesInit();
    void paintEvent(QPaintEvent *);
    inline void mouseMoveEvent(QMouseEvent *event);
    inline void mousePressEvent(QMouseEvent *event);
    inline void mouseReleaseEvent(QMouseEvent *);
signals:
    
public slots:
    
};

#endif // ASTUCEWINDOW_H
