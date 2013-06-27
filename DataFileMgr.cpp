#include "DataFileMgr.h"

DataFileMgr::DataFileMgr(const QString &fileName)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
#ifdef Q_OS_WIN32
    QDir multifacileDir(env.value("appdata") + "/Multifacile");

    if(!multifacileDir.exists())
    {
        QDir appdata(env.value("appdata"));
        appdata.mkdir("Multifacile");
    }

    xmlFile.setFileName(env.value("appdata") + "/Multifacile/" + fileName);
#endif
#ifdef Q_OS_LINUX
    xmlFile.setFileName(env.value("$HOME") + "/.config/Multifacile/" + fileName);
#endif
#ifdef Q_OS_MAC
    xmlFile.setFileName(env.value("$HOME") + "/.config/Multifacile/" + fileName);
#endif

    xmlFile.open(QIODevice::ReadWrite);

    if(xmlFile.readAll().isEmpty())
        createGroup(true);
}
bool DataFileMgr::setValue(const QString &group, const unsigned int &time, const unsigned int &table)
{
    xmlFile.seek(0);
    QTextStream out(&xmlFile);

    if(!doc.setContent(&xmlFile))
        return false;
    if(!exist(group))
        createGroup(false, group);

    QDomElement data = doc.documentElement();

    QDomElement groupElement = data.elementsByTagName(group).at(0).toElement();

    if(group == "HardMode")
    {

        QDomElement timeElement = doc.createElement("time");
        timeElement.appendChild(doc.createTextNode(QString::number(time)));

        if(groupElement.elementsByTagName("time").isEmpty())
            groupElement.appendChild(timeElement);
        else
            groupElement.replaceChild(timeElement, groupElement.firstChild());
     }

    else
    {
        QDomElement timeElement = doc.createElement("time");
        timeElement.setAttribute("table", table);
        timeElement.appendChild(doc.createTextNode(QString::number(time)));

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
                groupElement.replaceChild(timeElement, actualTime);
            else
                groupElement.appendChild(timeElement);
        }
    }

    xmlFile.resize(0);
        doc.save(out, 4);
        return true;
}

const QString DataFileMgr::value(const QString &group, const int &table)
{
    if(!doc.setContent(&xmlFile))
        return "Error : cannot set content";
    else if(!exist(group))
        return QString("no value");

    QDomElement data = doc.documentElement();

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
bool DataFileMgr::exist(const QString &group)
{
    xmlFile.flush();
    xmlFile.seek(0);
    doc.setContent(&xmlFile);

    QDomElement data = doc.documentElement();

    if(data.elementsByTagName(group).isEmpty())
        return false;
    else
        return true;
}
void DataFileMgr::createGroup(bool createAllGroups, const QString &group)
{
    QTextStream out(&xmlFile);

    if(createAllGroups)
    {
        doc.appendChild(doc.createProcessingInstruction("xml", "version=\"1.0\""));

        QDomElement data = doc.createElement("data");

        QDomElement EasyMode = doc.createElement("EasyMode");
        QDomElement MediumMode = doc.createElement("MediumMode");
        QDomElement HardMode = doc.createElement("HardMode");

        data.appendChild(EasyMode);
        data.appendChild(MediumMode);
        data.appendChild(HardMode);

        doc.appendChild(data);

        doc.save(out, 4);
    }

    else
    {
        QDomElement data = doc.documentElement();
        data.appendChild(doc.createElement(group));
        doc.save(out, 4);
    }
}

DataFileMgr::~DataFileMgr()
{
    xmlFile.close();
}
