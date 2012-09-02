#ifndef FEN_CORRECTION_H
#define FEN_CORRECTION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTime>
#include <QMessageBox>
#include <QSettings>
#include <QApplication>
#include <QtDebug>
#include <phonon>

#include "spinBox.h"
#include "modeEnum.h"
#include "Correction.h"

class Fen_correction : public QWidget
{
    Q_OBJECT
public :
    Fen_correction(const int multiple, SpinBox *reponses[], int *order, int time = 0, Mode mode = EASY);
    Fen_correction(SpinBox *reponses[], int *multipleOrder, int *order, int time = 0);
    ~Fen_correction();
private :
    void setWindowLayout(int multiple);
    void setWindowLayout(int tabOrder[]);

    //void playApplause();

    int reponse[10], resultat[10], timeTab[4];
    int *tab;
    int *orderTab;
    int note;
    int timeElapsed;
    int timeSeconde;

    //Phonon::MediaObject *mediaObject;
    //Phonon::AudioOutput *audioOutput;

    Correction *correct;

    QLabel *multiplication[10];
    QLabel *correction[2][10];
    QLabel *texte;
    QLabel *total;
    QLabel *pngTotal;

    QPushButton *quit;

    QVBoxLayout *vlayout;

    QGridLayout *layout;

    QHBoxLayout *hlayout[3];
public slots:
    void openMessageBox(RecordState, int);
};

#endif // FEN_CORRECTION_H
