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

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QProcess>
#include <QWidget>
#include <QTextEdit>
#include <QtDebug>
#include <QFontDatabase>

#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load(":/translation/qt_fr");
    app.installTranslator(&translator);

    QFontDatabase::addApplicationFont(":/police/DK Crayon Crumble.ttf");

    QFile file(":/css/Application.css");

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    app.setStyleSheet(file.readAll());

    file.close();

    MainWindow window;
    window.setWindowIcon(QIcon(":/icon/icone.png"));
    window.show();

    return app.exec();
}
