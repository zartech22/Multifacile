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

#ifndef FEN_SECONDAIRE_H
#define FEN_SECONDAIRE_H

#include <QApplication>
#include <QCloseEvent>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QPoint>
#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include <QStyleOption>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "MinCloseMenu.h"
#include "Shuffle.h"
#include "Correction.h"
#include "CustomMessageBox.h"

class MediumModeWindow : public QWidget
{
    Q_OBJECT
public :

    MediumModeWindow() {}
    MediumModeWindow(const int multiplicateur);
    ~MediumModeWindow();

    virtual const unsigned short int getMultiple() { return m_multiple; }
protected :

    unsigned short int m_multiple;
    unsigned short int note;
    int array[10];
    unsigned short int secondes;

    bool ClickOnWindow;

    Mode mode;

    QSignalMapper *mapper;

    QLabel *label[10], *text, *minute, *seconde, *deuxPoint, *labelPoint[10], *trueFalseLabel[2][10], *labelCorrection[10];

    QPushButton *corriger, *quitter, *nextPrev[2];

    QLineEdit *reponses[10];

    QTimer *chronometre;

    QPoint Diff;

    void initStyle();
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *);
    void setNewNumber(const unsigned short int newNumber);
    void startTime();

signals:

    void addSeconde(int);
    void wasClosed();

public slots:

    virtual void correct();
    void newSecond();
    void newSetFocus(const int number);
    void Next();
    void Previous();
    virtual void Retry();
    void showEvent(QShowEvent *);
    void updateLabel(const int temps) const;

};

#endif // FEN_SECONDAIRE_H
