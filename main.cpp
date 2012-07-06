#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "fenetre_principale.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("qt_fr");
    app.installTranslator(&translator);


    Fenetre_principale fenetre;
    fenetre.setWindowIcon(QIcon("icon.png"));
    fenetre.show();

    return app.exec();
}
