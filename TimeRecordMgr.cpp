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

#include "TimeRecordMgr.h"

TimeRecordMgr::TimeRecordMgr(Scope scope, const QString &organisation, int time, const QString &group, const QString &table) : QSettings(XML, scope, organisation), newTime(time), Group(group), Table(table), hardMode(false)
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

QString TimeRecordMgr::read()
{
    this->setValue(QString("HardMode"), 5);
    return "true";
}

bool readXML(QIODevice &device, QSettings::SettingsMap &map)
{
    QMap<QString, QVariant>::iterator i = map.begin();
    QDomDocument doc;


    for(i; i != map.end(); ++i)
    {
        if(!doc.setContent(&device))
            return false;

        if(i.key() == "HardMode")
        {
            QDomElement HardMode = doc.documentElement().elementsByTagName("HardMode").at(0).toElement();
            QString time = HardMode.text();
            i.value() = time;
        }
        else
        {
            QStringList groupAndTable = i.key().split("/");

            QDomElement Mode = doc.documentElement().elementsByTagName(groupAndTable.at(0)).at(0).toElement();

            QDomNodeList timeList = Mode.elementsByTagName("time");

            for(int j = 0; j < timeList.size(); ++j)
                if(timeList.at(j).toElement().attribute("table") == groupAndTable.at(1))
                {
                    i.value() = timeList.at(j).toElement().attribute("table");
                    break;
                }
        }
    }
    return true;
}
bool writeXML(QIODevice &device, const QSettings::SettingsMap &map)
{
    /*QTextStream out(&device);
    QDomDocument doc;


    qDebug() << "Map :" <<  map;

    QMap<QString, QVariant>::iterator i = map.begin();

    for(i; i != map.end(); ++i)
    {
        if(i.key() == "HardMode")
        {
            QDomElement HardMode = doc.createElement("HardMode");
            QDomElement time = doc.createElement("time");
            time.appendChild(doc.createTextNode(i.value().toString()));

            HardMode.appendChild(time);
            doc.appendChild(HardMode);
        }
        else
        {
            QStringList groupAndTable = i.key().split("/");

            QDomElement Mode = doc.createElement(groupAndTable.at(0));
            QDomElement time = doc.createElement("time");
            time.setAttribute("table", groupAndTable.at(1));
            time.appendChild(doc.createTextNode(i.value().toString()));
            Mode.appendChild(time);

            doc.appendChild(Mode);
        }
    }

    if(i.key() == "HardMode")
    {
        QDomElement HardMode = doc.elementsByTagName("HardMode").at(0).toElement();

        if(HardMode.elementsByTagName("time").isEmpty())
        {
            QDomElement time = doc.createElement("time");
            time.appendChild(doc.createTextNode(i.value().toString()));
            HardMode.appendChild(time);
        }
        else
        {
            QDomElement time = HardMode.elementsByTagName("time").at(0).toElement();
            time.replaceChild(doc.createTextNode(i.value().toString()), time.firstChild());
        }
    }
    else
    {
        QStringList keys = i.key().split("/");

        QDomElement mode = doc.elementsByTagName(keys.at(0)).at(0).toElement();

        if(mode.elementsByTagName("time").isEmpty())
        {
            qDebug() << mode.elementsByTagName("time").isEmpty() << mode.elementsByTagName("time").size();
            QDomElement time = doc.createElement("time");
            time.setAttribute("table", keys.at(1));
            time.appendChild(doc.createTextNode(i.value().toString()));

            mode.appendChild(time);
        }
        else
        {
            for(int i = 0; i < mode.elementsByTagName("time").size(); i++)
            {
                QDomElement time = mode.elementsByTagName("time").at(i).toElement();

                if(time.attributeNode("table").value() == keys.at(1))
                {
                    time.setAttribute("table", keys.at(1).toInt());
                    break;
                }
            }
        }
    }

    doc.save(out, 4);
    return true;*/

    device.seek(0);
    qDebug() << device.readAll();
    return true;
}

