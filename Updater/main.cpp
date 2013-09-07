#include <QApplication>
#include <QTranslator>
#include "Updater.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load(":/translation/qt_fr");

    app.installTranslator(&translator);

    Updater up;

    up.show();

    return app.exec();
}
