#ifndef CORRECTION_H
#define CORRECTION_H

#include "spinBox.h"
#include "modeEnum.h"
#include "TimeRecordMgr.h"
#include "QLabel"

class Correction : public QObject
{
    Q_OBJECT

public:
    Correction(Mode mode, int multiple, int* order, int *userAnswers, int time = 0);
    Correction(int* multiple, int* order, int* userAnswers, int time = 0);

    ~Correction();

    int getCorrection(QLabel *correction[][10]);

    void saveTime();
private:
    int seconds;
    int Multiple;
    int note;

    int* orderTab;
    int* multipleTab;
    int* answers;

    bool isHardMode;

    TimeRecordMgr *manager;

    Mode difficultyMode;

    void manageTime();
    void notation(int resultat[], bool isCorrect[]);
    void doCorrection(QLabel *correction[][10], int resultat[], bool isCorrect[]);

    QString getModeGroupName();
    QString getModeKeyName();
signals:
    void newRecord(RecordState, int);
public slots:
    void isRecordValid(RecordState, int);
};

#endif // CORRECTION_H
