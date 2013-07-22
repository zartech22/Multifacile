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

#ifndef CORRECTION_H
#define CORRECTION_H

#include <QLabel>
#include <QMultiMap>
#include <QString>

#include "MainWindowEnums.h"
#include "DataFileMgr.h"

enum RecordState
{
    RECORD, UNVALIDRECORD, NORECORD
};

typedef enum RecordState RecordState;

class Correction : public QObject
{
    Q_OBJECT

public:
    Correction(Mode mode, const int multiple, int* order, int *userAnswers, const int time = 0);
    Correction(int* multiple, int* order, int* userAnswers, const int time = 0);

    ~Correction();

    int getCorrection(QString texte[], bool isGood[]);

private:
    unsigned int seconds;
    int Multiple;
    int note;

    int* orderTab;
    int* multipleTab;
    int* answers;

    bool isHardMode;

    DataFileMgr *manager;

    Mode difficultyMode;

    void manageTime();
    void notation(int resultat[], bool isGood[]);
    void doCorrection(QString texte[], bool isGood[], int resultat[]) const;

    QString getModeGroupName() const;
    QString getModeKeyName() const;
signals:
    void newRecord(RecordState, int);
public slots:
    void isRecordValid(RecordState, int);
};

#endif // CORRECTION_H
