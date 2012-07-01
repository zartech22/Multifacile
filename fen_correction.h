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
#include <QtDebug>

#include <QFile>
#include <QTextStream>

#include "spinBox.h"
#include "modeEnum.h"

typedef enum RecordState RecordState;

class Fen_correction : public QWidget
{
public :
    Fen_correction(const int multiple, SpinBox *reponses[], int *order, int time = 0, Mode mode = EASY);
    Fen_correction(SpinBox *reponses[], int *multipleOrder, int *order, int time = 0);
    ~Fen_correction();
private :

    void notation(const int m_multiple);
    void notation(int *m_multiple);

    void setWindowLayout(int multiple);
    void setWindowLayout(int tabOrder[]);

    void returnTime(const int sec, RecordState state);

    int reponse[10], resultat[10], timeTab[4];
    int *tab;
    int *orderTab;
    int note;
    int timeElapsed;
    int timeSeconde;

    QLabel *multiplication[10];
    QLabel *correction[2][10];
    QLabel *texte;
    QLabel *total;
    QLabel *pngTotal;

    QPushButton *quit;

    QVBoxLayout *vlayout;

    QGridLayout *layout;

    QHBoxLayout *hlayout[3];
};

enum RecordState
{
    RECORD, NORECORD
};

#endif // FEN_CORRECTION_H
