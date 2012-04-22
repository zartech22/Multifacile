#ifndef FEN_SECONDAIRE_H
#define FEN_SECONDAIRE_H

#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include "fen_correction.h"

class Fen_secondaire : public QWidget
{
    Q_OBJECT
public :
    Fen_secondaire();
    Fen_secondaire(const int multiplicateur);
    ~Fen_secondaire();
private :
    int m_multiplicateur;

    QVBoxLayout *vlayout;

    QFormLayout *layout;

    QPushButton *corriger;

    QSpinBox *reponses[10];

    Fen_correction *fen;

public slots:
    void open();

};

#endif // FEN_SECONDAIRE_H
