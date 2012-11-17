#include "TimeRecordMgr.h"

TimeRecordMgr::TimeRecordMgr(Format format, Scope scope, const QString &organisation,int time, const QString group, const QString table) : QSettings(format, scope, organisation)
{
    newTime = time;
    Group = group;
    Table = table;

    if(Table.isEmpty())
        hardMode = true;
}
bool TimeRecordMgr::isKeyExist() const
{
    if(hardMode)
        return this->contains(Group);
    else
        return this->contains(Group+"/"+Table);
}
void TimeRecordMgr::CompareTime()
{
    bool exist = this->isKeyExist();
    if(exist)
    {
        if(newTime < this->returnValue())
            emit isNewRecord(RECORD, returnValue());
        else
            emit isNewRecord(NORECORD, returnValue());
    }
    else
    {
        emit isNewRecord(NORECORD, 0);
        this->SaveRecordInFile();
    }
}
void TimeRecordMgr::SaveRecordInFile()
{
    if(hardMode)
        this->setValue(Group, newTime);
    else
        this->setValue(Group+"/"+Table, newTime);
}

int TimeRecordMgr::returnValue() const
{
    if(hardMode)
        return this->value(Group).toInt();
    else
        return this->value(Group+"/"+Table).toInt();
}
void TimeRecordMgr::returnTime(int tab[])
{
    tab[1] = tab[0]/60;
    tab[3] = tab[2]/60;

    if(tab[1] != 0)
        tab[0] %= 60;
    if(tab[3] != 0)
        tab[2] %= 60;
}
