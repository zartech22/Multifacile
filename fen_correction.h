#ifndef FEN_CORRECTION_H
#define FEN_CORRECTION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "spinBox.h"


class Fen_correction : public QWidget
{
public :
    Fen_correction(const int multiple, SpinBox *reponses[], int *order);
    Fen_correction(SpinBox *reponses[], int *multipleOrder, int *order);
    ~Fen_correction();
private :

    void notation(const int m_multiple);
    void notation(int *m_multiple);

    void setWindowLayout(int multiple);
    void setWindowLayout(int tabOrder[]);

    int reponse[10], resultat[10];
    int *tab;
    int *orderTab;
    int note;
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

#endif // FEN_CORRECTION_H
