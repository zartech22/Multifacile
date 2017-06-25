#ifndef ABSTRACTMODEWINDOW_H
#define ABSTRACTMODEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include <QValidator>
#include <QSignalMapper>
#include <QFile>
#include <QStyleOption>
#include <QPainter>

#include <array>

#include <QDebug>

#include "Include.h"

class AbstractModeWindow : public QWidget
{
    Q_OBJECT
public:
    AbstractModeWindow();
    virtual ~AbstractModeWindow();

    virtual operande getMultiple() = 0;
    virtual void progressifModeHasChanged(const bool) = 0;

private:
    QPushButton *_quit;

    QTimer *_timer;

    QLabel *_timerLabel;
    std::array<QLabel*, 10> _points;

    QSignalMapper *_mapper;

    void initStyle();
    void initButtons();
    void initTimer();
    void initLineEdit();

    void startTime();
    void resetTimer();
    void showEvent(QShowEvent *event) override;

protected:
    QPushButton *_correct;
    QLabel *_trueFalse[2][10];
    std::array<QLabel*, 10> _labelCorrection;
    std::array<QLabel*, 10> _label;
    std::array<QLineEdit*, 10> _lineEdits;

    std::array<operande, 10> _array;
    int _note;
    unsigned short int _timeElapsed;

    void paintEvent(QPaintEvent *) override;
    void stopTimer();
    void restartTimer();

    virtual void initLabels() final;

    virtual void initAskLabels() = 0;
signals:
    void timeElapsedUpdated();
    void wasClosed();

public slots:
    void focusNextLine(int);
    void newSecondElapsed();
    void updateTimerLabel();

    virtual void correct() = 0;

};

#endif // ABSTRACTMODEWINDOW_H
