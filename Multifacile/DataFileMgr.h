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

#ifndef DATAFILEMGR_H
#define DATAFILEMGR_H

#include <QFile>
#include <QDomDocument>
#include <QString>
#include <QProcessEnvironment>
#include <QTextStream>
#include <QDir>

#include <QDebug>

class DataFileMgr
{
public:
    DataFileMgr(const QString &fileName);
    ~DataFileMgr() { _xmlFile.close(); }

    bool setValue(const QString &group, const unsigned short int &time, const bool &noError = false, const unsigned short int &table = 0);
    bool setValue(const QString &group, const QString &key, const QString &value);
    const QString value(const QString &group, const unsigned short int &table = 0);
    const QString value(const QString &group, const QString &key);

    static QMap<int, bool>* getNoErrorList(const QString &fileName, const QString &mode);
    static bool hasNoErrorTrue(const QString &fileName, const QString &mode, const unsigned short int &table);
    static bool isAllTableWithNoErrorTrue(const QString &fileName, const QString &mode);
    static bool isAllTableWithNoErrorFalse(const QString &fileName, const QString &mode);

private:
    QFile _xmlFile;
    QDomDocument _doc;

    bool exist(const QString &group);
    void createGroup(bool createAllGroups, const QString &group = QString());
};

#endif // DATAFILEMGR_H
