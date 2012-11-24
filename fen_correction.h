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

#ifndef FEN_CORRECTION_H
#define FEN_CORRECTION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTime>
#include <QMessageBox>
#include <QSettings>
#include <QApplication>
#include <QtDebug>
#include <phonon>

#include "spinBox.h"
#include "modeEnum.h"
#include "Correction.h"

class Fen_correction : public QWidget
{
    Q_OBJECT
public :
    Fen_correction(const int multiple, SpinBox *reponses[], int *order, const int time = 0, Mode mode = EASY);
    Fen_correction(SpinBox *reponses[], int *multipleOrder, int *order, const int time = 0);
    ~Fen_correction();
private :
    void setWindowLayout(int multiple);
    void setWindowLayout(int tabOrder[]);

    //void playApplause();

    int reponse[10], resultat[10], timeTab[4];
    int *tab;
    int *orderTab;
    int note;
    int timeElapsed;
    int timeSeconde;

    //Phonon::MediaObject *mediaObject;
    //Phonon::AudioOutput *audioOutput;

    Correction *correct;

    QLabel *multiplication[10];
    QLabel *correction[2][10];
    QLabel *texte;
    QLabel *total;
    QLabel *pngTotal;

    QPushButton *quit;

    QVBoxLayout *vlayout;

    QGridLayout *layout;

    QHBoxLayout *hlayout[3];
public slots:
    void openMessageBox(RecordState, const int);
};

#endif // FEN_CORRECTION_H
