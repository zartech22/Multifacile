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

#include "DataFileMgr.h"

DataFileMgr::DataFileMgr(const QString &fileName)
{
#ifdef Q_OS_WIN32
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QDir multifacileDir(env.value("appdata") + "/Multifacile");

    if(!multifacileDir.exists())
    {
        QDir appdata(env.value("appdata"));
        appdata.mkdir("Multifacile");
    }

    _xmlFile.setFileName(env.value("appdata") + "/Multifacile/" + fileName);
#endif
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    if(!QDir(QDir::homePath() + "/.config/Multifacile/").exists())
        QDir(QDir::homePath() + "/.config").mkdir("Multifacile");

    _xmlFile.setFileName(QDir::homePath() + "/.config/Multifacile/" + fileName);
#endif

    _xmlFile.open(QIODevice::ReadWrite);

    if(_xmlFile.readAll().isEmpty())
        createGroup(true);
}
bool DataFileMgr::setValue(const QString &group, const unsigned short &time, const bool &noError, const unsigned short &table)
{
    _xmlFile.seek(0);
    QTextStream out(&_xmlFile);

    if(!_doc.setContent(&_xmlFile))
        return false;
    if(!exist(group))
        createGroup(false, group);

    QDomElement data = _doc.documentElement();

    QDomElement groupElement = data.elementsByTagName(group).at(0).toElement();

    if(group == "HardMode")
    {

        QDomElement timeElement = _doc.createElement("time");
        timeElement.appendChild(_doc.createTextNode(QString::number(time)));

        if(groupElement.elementsByTagName("time").isEmpty())
            groupElement.appendChild(timeElement);
        else
            groupElement.replaceChild(timeElement, groupElement.firstChild());
     }

    else
    {
        QDomElement timeElement = _doc.createElement("time");
        timeElement.setAttribute("table", table);
        timeElement.appendChild(_doc.createTextNode(QString::number(time)));

        if(noError)
            timeElement.setAttribute("noError", "true");
        else
            timeElement.setAttribute("noError", "false");


        if(groupElement.elementsByTagName("time").isEmpty())
            groupElement.appendChild(timeElement);

        else
        {
            QDomElement actualTime;

            bool alreadyExist = false;

            for(int i = 0; i < groupElement.elementsByTagName("time").size(); ++i)
            {
                actualTime = groupElement.elementsByTagName("time").at(i).toElement();

                if(actualTime.attribute("table") != QString::number(table))
                    continue;
                alreadyExist = true;
                break;
            }
            if(alreadyExist)
            {
                if(actualTime.attribute("noError", "false") == "true" && !noError)
                    timeElement.setAttribute("noError", "true");

                groupElement.replaceChild(timeElement, actualTime);
            }
            else
                groupElement.appendChild(timeElement);
        }
    }

    _xmlFile.resize(0);
    _doc.save(out, 4);
    return true;
}

bool DataFileMgr::setValue(const QString &group, const QString &key, const QString &value)
{
    //qDebug() << "dans le setValue";
    _xmlFile.seek(0);
    QTextStream out(&_xmlFile);

    if(!_doc.setContent(&_xmlFile))
        return false;
    if(!exist(group))
        createGroup(false, group);

    QDomElement data = _doc.documentElement();

    QDomElement groupElement = data.elementsByTagName(group).at(0).toElement();

    QDomElement keyElement = _doc.createElement(key);
    keyElement.appendChild(_doc.createTextNode(value));

    if(groupElement.elementsByTagName(key).isEmpty())
        groupElement.appendChild(keyElement);
    else
    {
        QDomElement previousValue = groupElement.elementsByTagName(key).at(0).toElement();
        groupElement.replaceChild(keyElement, previousValue);
    }

    _xmlFile.resize(0);
    _doc.save(out, 4);

    return true;
}

const QString DataFileMgr::value(const QString &group, const unsigned short &table)
{
    if(!_doc.setContent(&_xmlFile))
        return "Error : cannot set content";
    else if(!exist(group))
        return QString("no value");

    QDomElement data = _doc.documentElement();

    QDomElement groupElement = data.elementsByTagName(group).at(0).toElement();

    if(group == "HardMode")
        return groupElement.elementsByTagName("time").at(0).toElement().text();
    else
    {
        QDomElement time;

        for(int i = 0; i < groupElement.elementsByTagName("time").size(); ++i)
        {
            time = groupElement.elementsByTagName("time").at(i).toElement();

            if(time.attribute("table") == QString::number(table))
                break;
        }
        return time.text();
    }

}

const QString DataFileMgr::value(const QString &group, const QString &key)
{
    _xmlFile.seek(0);
    if(!_doc.setContent(&_xmlFile))
        return "Error : cannot set content";
    else if(!exist(group))
        return QString("no value");

    QDomElement data = _doc.documentElement();
    QDomElement groupElement = data.elementsByTagName(group).at(0).toElement();

    QDomElement keyElement = groupElement.elementsByTagName(key).at(0).toElement();

    return keyElement.text();
}

bool DataFileMgr::exist(const QString &group)
{
    _xmlFile.flush();
    _xmlFile.seek(0);
    _doc.setContent(&_xmlFile);

    QDomElement data = _doc.documentElement();

    //qDebug() << "Valeur de isEmpty " << data.elementsByTagName(group).isEmpty();

    if(data.elementsByTagName(group).isEmpty())
        return false;
    else
        return true;
}
void DataFileMgr::createGroup(bool createAllGroups, const QString &group)
{
    _xmlFile.seek(0);
    QTextStream out(&_xmlFile);

    if(createAllGroups)
    {
        //qDebug() << "Dans createGroup : if";
        _doc.appendChild(_doc.createProcessingInstruction("xml", "version=\"1.0\""));

        QDomElement data = _doc.createElement("data");

        QDomElement EasyMode = _doc.createElement("EasyMode");
        QDomElement MediumMode = _doc.createElement("MediumMode");
        QDomElement HardMode = _doc.createElement("HardMode");

        data.appendChild(EasyMode);
        data.appendChild(MediumMode);
        data.appendChild(HardMode);

        _doc.appendChild(data);

        _doc.save(out, 4);
    }

    else
    {
        //qDebug() << "Dans createGroup : else";
        QDomElement data = _doc.documentElement();
        data.appendChild(_doc.createElement(group));
        _doc.save(out, 4);
    }
}

QMap<int, bool>* DataFileMgr::getNoErrorList(const QString &fileName, const QString &mode)
{
    QFile file;

#ifdef Q_OS_WIN
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    file.setFileName(env.value("appdata") + "/Multifacile/" + fileName);
#endif
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    file.setFileName(QDir::homePath() + "/.config/Multifacile/" + fileName);
#endif

    if(!file.open(QIODevice::ReadOnly))
        return new QMap<int, bool>;
    else if (file.size() == 0)
        return new QMap<int, bool>;

    QDomDocument doc;

    if(!doc.setContent(&file))
        return new QMap<int, bool>;

    QDomNodeList childs = doc.elementsByTagName(mode).at(0).childNodes();

    QMap<int, bool> *noErrorList = new QMap<int, bool>;

    for(int i = 0; i < childs.size(); ++i)
    {
        if(childs.at(i).toElement().attribute("noError", "false") == "true")
            noErrorList->insert(childs.at(i).toElement().attribute("table").toInt(), true);
        else
            noErrorList->insert(childs.at(i).toElement().attribute("table").toInt(), false);
    }
    return noErrorList;
}

bool DataFileMgr::hasNoErrorTrue(const QString &fileName, const QString &mode, const unsigned short int &table)
{
    QFile file;

#ifdef Q_OS_WIN
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    file.setFileName(env.value("appdata") + "/Multifacile/" + fileName);
#endif
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    file.setFileName(QDir::homePath() + "/.config/Multifacile/" + fileName);
#endif

    if(!file.open(QIODevice::ReadOnly))
        return false;
    else if(file.size() == 0)
        return false;

    QDomDocument doc;

    if(!doc.setContent(&file))
        return false;

    QDomNodeList childs = doc.elementsByTagName(mode).at(0).toElement().childNodes();

    for(int i = 0; i < childs.size(); ++i)
        if(childs.at(i).toElement().attribute("table").toInt() == table)
            return (childs.at(i).toElement().attribute("noError", "false") == "true");
    return false;
}

bool DataFileMgr::isAllTableWithNoErrorTrue(const QString &fileName, const QString &mode)
{
    bool allWithNoError = true;

    for(int i = 0; i < 10; ++i)
        if(!hasNoErrorTrue(fileName, mode, (i + 1)))
            allWithNoError = false;

    return allWithNoError;
}

bool DataFileMgr::isAllTableWithNoErrorFalse(const QString &fileName, const QString &mode)
{
    bool AllWithError = true;

    for(int i = 0; i < 10; ++i)
        if(hasNoErrorTrue(fileName, mode, (i + 1)))
            AllWithError = false;

    return AllWithError;
}
