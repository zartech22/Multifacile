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
#include <QDesktopServices>
#include <memory>

#include <QDebug>
#include "Include.h"

class DataFileMgr  // Classe gérant l'acces aux donnees contenues dans le fichier xml
{
public:
    DataFileMgr(const QString &fileName);
    ~DataFileMgr() { _xmlFile.close(); }

    bool setValue(const QString &group, const operande &time, const bool &noError = false, const operande &table = 0); //ecrit une valeur dans le fcihier de type table
    bool setValue(const QString &group, const QString &key, const QString &value); //ecrit une valeur dans le fcihier de n'importe quel type
    const QString value(const QString &group, const operande &table = 0);  //lit une valeur de type table
    const QString value(const QString &group, const QString &key);  //lit une valeur de n'importe quel type

    static QMap<int, bool>* getNoErrorList(const QString &fileName, const QString &mode);  //retourne la liste de toutes les tables d'un mode presente dans le fichier contenant le numero de la table et si elle a ete reussite ou pas
    static bool hasNoErrorTrue(const QString &fileName, const QString &mode, const operande &table);  // retourne vrai si la table a ete reussite sinon retourne faux (pareil si la table n'est pas presente dans le fichier)
    static bool isAllTableWithNoErrorTrue(const QString &fileName, const QString &mode);  //retourne vrai si toutes les tables d'un mode ont ete reussite sinon retourne faux
    static bool isAllTableWithNoErrorFalse(const QString &fileName, const QString &mode); //contraire de la fonction precedente
    static int nextTableWithNoErrorTrue(const QString &fileName, const QString &mode, const operande table);  //retourne la prochaine table reussite
    static int previousTableWithNoErrorTrue(const QString &fileName, const QString &mode, const operande table);  //retourne la precedente table reussite

private:
    QFile _xmlFile;
    QDomDocument _doc;

    bool exist(const QString &group);  //retourne vrai si le nom de groupe existe
    void createGroup(bool createAllGroups, const QString &group = QString());  //creer un groupe ou tout les groupes a la fois
};

#endif // DATAFILEMGR_H
