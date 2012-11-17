#ifndef TIMERECORDMGR_H
#define TIMERECORDMGR_H

#include <QSettings>

typedef enum RecordState RecordState;

enum RecordState
{
    RECORD, UNVALIDRECORD, NORECORD
};



class TimeRecordMgr : public QSettings
{
    Q_OBJECT
public:
    TimeRecordMgr(Format format, Scope scope, const QString &organisation, const int time, const QString group, const QString table = QString());

    void CompareTime();
    void SaveRecordInFile();

    static void returnTime(int tab[]);

private:
    int newTime;

    bool hardMode;

    QString Group;
    QString Table;

    int returnValue() const;

    bool isKeyExist() const;
    
signals:
    void isNewRecord(RecordState, int);
        
};

#endif // TIMERECORDMGR_H
