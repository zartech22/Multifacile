#ifndef DATAFILEMGR_H
#define DATAFILEMGR_H

#include <QFile>
#include <QDomDocument>
#include <QString>
#include <QProcessEnvironment>
#include <QTextStream>
#include <QDir>

class DataFileMgr
{
public:
    DataFileMgr(const QString &fileName);
    ~DataFileMgr();

    bool setValue(const QString &group, const unsigned int &time, const bool &noError = false, const unsigned int &table = 0);
    const QString value(const QString &group, const int &table = 0);

    static QMap<int, bool>* getNoErrorList(const QString &fileName, const QString &mode);

private:
    QFile xmlFile;
    QDomDocument doc;

    bool exist(const QString &group);
    void createGroup(bool createAllGroups, const QString &group = QString());
};

#endif // DATAFILEMGR_H
