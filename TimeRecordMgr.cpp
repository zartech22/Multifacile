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

#include "TimeRecordMgr.h"

TimeRecordMgr::TimeRecordMgr(Format format, Scope scope, const QString &organisation,int time, const QString group, const QString table) : QSettings(format, scope, organisation), newTime(time), Group(group), Table(table)
{
    if(Table.isEmpty())
        hardMode = true;
}
inline bool TimeRecordMgr::isKeyExist() const
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

inline int TimeRecordMgr::returnValue() const
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
