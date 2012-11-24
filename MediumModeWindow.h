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

#ifndef FEN_SECONDAIRE_H
#define FEN_SECONDAIRE_H

#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QTimer>
#include <QLCDNumber>

#include "fen_correction.h"
#include "spinBox.h"
#include "Shuffle.h"


class MediumModeWindow : public QWidget
{
    Q_OBJECT
public :
    MediumModeWindow();
    MediumModeWindow(const int multiplicateur, bool chrono);
    virtual ~MediumModeWindow();
protected :
    int m_multiple;

    int array[10], secondes;

    QLabel *label[10], *text, *minute, *seconde, *deuxPoint;

    QVBoxLayout *vlayout;

    QHBoxLayout *hlayoutBottom, *hlayoutTop;

    QFormLayout *layout;

    QPushButton *corriger;

    SpinBox *reponses[10];

    Fen_correction *fen;

    QTimer *chronometre;

    void startTime();
    void closeEvent(QCloseEvent *event);

    bool time;

signals:
    void addSeconde(int);
public slots:
    virtual void open();
    void newSetFocus(const int number);
    void newSecond();
    void updateLabel(const int temps) const;

};

#endif // FEN_SECONDAIRE_H
