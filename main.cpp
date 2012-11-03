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
#include "fenetre_principale.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("qt_fr");
    app.installTranslator(&translator);

    QFile file(":/css/Multifacile.css");

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    app.setStyleSheet(file.readAll());

    file.close();

    for(int i = 0; i < argc; i++)
    {
        QString arg(argv[i]);

        if(arg == "-updated")
        {
            int answer = QMessageBox::information(nullptr, "Mise à jour achevé", "Multifacile vient d'être mis à jour. Voulez-vous voir les changements ?", QMessageBox::No | QMessageBox::Yes);

            if(answer == QMessageBox::Yes)
            {
                QWidget *change = new QWidget;

                QFile fichier("change.txt");
                fichier.open(QIODevice::ReadOnly | QIODevice::Text);

                QTextEdit *textEdit = new QTextEdit(fichier.readAll(), change);

                fichier.close();

                change->show();
            }
        }
    }

    Fenetre_principale fenetre;
    fenetre.setWindowIcon(QIcon(":/icon/icone.png"));
    fenetre.show();

    return app.exec();
}
