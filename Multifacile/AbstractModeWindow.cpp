#include "AbstractModeWindow.h"

AbstractModeWindow::AbstractModeWindow() : QWidget()
{
    initStyle();
    initButtons();
    initTimer();
    initLineEdit();
    startTime();
}

void AbstractModeWindow::initStyle()
{
    QFile css(":/css/Fen2.css");
    css.open(QIODevice::ReadOnly);
    setStyleSheet(css.readAll());
    css.close();
}

void AbstractModeWindow::initButtons()
{
    _quit = new QPushButton(tr("Retour"));
    _quit->setParent(this);
    _quit->setFixedSize(70, 40);
    _quit->move(490, 490);
    _quit->setObjectName("Quitter");

    _correct = new QPushButton(tr("Corriger"));
    _correct->setParent(this);
    _correct->setFixedSize(80, 40);
    _correct->move(400, 490);
    _correct->setObjectName("Corriger");

    connect(_correct, SIGNAL(clicked()), this, SLOT(correct()));
    connect(_quit, SIGNAL(clicked()), this, SIGNAL(wasClosed()));
}

void AbstractModeWindow::initTimer()
{
    _timerLabel = new QLabel(tr("Temps : 00:00"), this);
    _timerLabel->move(235, 15);

    _timeElapsed = 0;
}

void AbstractModeWindow::initLineEdit()
{
    _mapper = new QSignalMapper(this);
    const QRegExp reg(R"(\d{0,3})");

    for(int i = 0; i < 10; ++i) // Currently fixed size
    {
        _lineEdits[i] = new QLineEdit(this);
        _lineEdits[i]->setAttribute(Qt::WA_TranslucentBackground);
        _lineEdits[i]->setFixedSize(302, 69);
        _lineEdits[i]->move(185, (60 + 40 * i));
        _lineEdits[i]->setValidator(new QRegExpValidator(reg, _lineEdits[i]));

        connect(_lineEdits[i], SIGNAL(returnPressed()), _mapper, SLOT(map()));
        _mapper->setMapping(_lineEdits[i], (i + 1));
    }

    connect(_mapper, SIGNAL(mapped(int)), this, SLOT(focusNextLine(const int)));
}

void AbstractModeWindow::showEvent(QShowEvent *event)
{
    _lineEdits[0]->setFocus();
    QWidget::showEvent(event);
}

void AbstractModeWindow::focusNextLine(const int lineNumber)
{
    if(lineNumber < 10)
    {
        _lineEdits[lineNumber]->setFocus();
        _lineEdits[lineNumber]->selectAll();
    }
    else
        correct();
}

void AbstractModeWindow::initLabels()
{
    this->initAskLabels();

    const QPixmap point(":/image/Point.png");
    const QPixmap right(":/image/OpacRight.png");
    const QPixmap wrong(":/image/OpacWrong.png");

    for(int i = 0; i < 10; ++i) // Curently fixed size
    {
        _points[i] = new QLabel(this);
        _points[i]->setPixmap(point);
        _points[i]->move(105, (90 + 40 * i));

        _labelCorrection[i] = new QLabel(this);
        _labelCorrection[i]->setVisible(false);
    }

    for(int j = 0; j < 2; ++j)
    {
        for(int i = 0; i < 10; ++i)
        {
            _trueFalse[j][i] = new QLabel(this);

            if(j == 0)
            {
                _trueFalse[j][i]->setPixmap(right);
                _trueFalse[j][i]->move(475, (70 + 40 * i));
            }
            else
            {
                _trueFalse[j][i]->setPixmap(wrong);
                _trueFalse[j][i]->move(525, (75 + 40 * i));
            }
        }
    }
}

void AbstractModeWindow::startTime()
{
    _timer = new QTimer;
    connect(_timer, SIGNAL(timeout()), this, SLOT(newSecondElapsed()));
    connect(this, SIGNAL(timeElapsedUpdated()), this, SLOT(updateTimerLabel()));

    _timer->start(1000);
}

void AbstractModeWindow::stopTimer()
{
    _timer->stop();
    delete _timer;
    _timer = nullptr;
}

void AbstractModeWindow::resetTimer()
{
    _timerLabel->setText(tr("Temps : 00:00"));
    _timeElapsed = 0;
}

void AbstractModeWindow::restartTimer()
{
    if(_timer)
       stopTimer();

    resetTimer();
    startTime();
}

void AbstractModeWindow::newSecondElapsed()
{
    ++_timeElapsed;
    emit timeElapsedUpdated();
}

void AbstractModeWindow::updateTimerLabel()
{
   unsigned short minutes = _timeElapsed / 60;
   unsigned short seconds = _timeElapsed % 60;

    _timerLabel->setText(QString("Temps : %1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
}

void AbstractModeWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);

    QPainter p(this);

    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

AbstractModeWindow::~AbstractModeWindow()
{
    if(_timer)
        delete _timer;

    delete _quit;
    delete _correct;
    delete _timerLabel;
    delete _mapper;

    for(int i = 0; i < 10; ++i)
    {
        delete _points[i];
        delete _lineEdits[i];
        delete _labelCorrection[i];
        delete _trueFalse[0][i];
        delete _trueFalse[1][i];
    }
}
