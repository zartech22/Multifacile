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

    virtual const unsigned short int getMultiple() { return _multiple; }
protected :

    unsigned short int _multiple;
    unsigned short int _note;
    int _array[10];
    unsigned short int _secondes;

    Mode _mode;

    QSignalMapper *_mapper;

    QLabel *_label[10];
    QLabel *_text;
    QLabel *_minute;
    QLabel *_seconde;
    QLabel *_deuxPoint;
    QLabel *_labelPoint[10];
    QLabel *_trueFalseLabel[2][10];
    QLabel *_labelCorrection[10];

    QPushButton *_corriger;
    QPushButton *_quitter;
    QPushButton *_nextPrev[2];

    QLineEdit *_reponses[10];

    QTimer *_chronometre;

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
