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

#include "MainWindow.h"
#include "CheckUpdate.h"
#include "Shuffle.h"
#include "DataFileMgr.h"

MainWindow::MainWindow() :  _mode(EASY), _actualWindow(MainWidget), _mapper(NULL), _mgr("Multifacile.xml")
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("Multifacile");
    resize(650, 650);

    if(_mgr.value("settings", "progressifMode") == "no value")
        qDebug() << "_mgr.setValue" << _mgr.setValue("settings", "progressifMode", "true");
    _isProgressifMode = (_mgr.value("settings", "progressifMode") == "true");

    initStyle();

    doMenuBar();

    createCentralWidget();

    _check = new CheckUpdate(this);  //create a new CheckUpdate object with VERSION defined in header

    _minCloseMenu = new MinCloseMenu(this);

    menuBar()->setCornerWidget(_minCloseMenu);

    this->setCentralWidget(_widget);



    connect(_mapper, SIGNAL(mapped(int)), this, SLOT(open_window(int)));  //connect the signal mapped of QSignalMapper to the custom slot open_window(int)

    connect(_check, SIGNAL(checkUpdateAnswer(UpdateType)), this, SLOT(checkUpdateReceivedAnswer(UpdateType)));
    connect(_check, SIGNAL(error()), this, SLOT(socketError()));

    connect(_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(_updateAction, SIGNAL(triggered()), this, SLOT(verification()));
    connect(_actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setMode(QAction*)));
    connect(_progressifModeActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(changeProgressifMode(QAction*)));
}

void MainWindow::checkSucceedTables()
{
    if(_mode != HARD)
    {
        QMap<int, bool> *list = DataFileMgr::getNoErrorList("Multifacile.xml", (_mode == EASY) ? "EasyMode" : "MediumMode");

        for(QMap<int, bool>::Iterator it = list->begin(); it != list->end(); ++it)
            if(it.value())
                _bouton[ (it.key() - 1)]->setStyleSheet("background-image: url(\":/image/Bouton_succes.png\");");

        delete list;

    }

    verifyModesPermissions();
}

void MainWindow::verifyModesPermissions(bool hasProgressifModeChanged)
{
     _isProgressifMode = (_mgr.value("settings", "progressifMode") == "true");

    if(_mode == MEDIUM && _isProgressifMode)
    {
        for(int i = 0; i < 10; ++i)
            if(!DataFileMgr::hasNoErrorTrue("Multifacile.xml", "EasyMode", (i + 1)))
                _bouton[i]->setStyleSheet("background-image: url(\":/image/Bouton_inacessible.png\"); color: grey;");
    }
    else if(_mode == MEDIUM && !_isProgressifMode)
        for(int i = 0; i < 10; ++i)
            if(!DataFileMgr::hasNoErrorTrue("Multifacile.xml", "EasyMode", (i + 1)))
                _bouton[i]->setStyleSheet("");


    if( (!DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "EasyMode") || !DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "MediumMode")) && _isProgressifMode )
    {
        _hardModeActionText->setStyleSheet("color: grey; padding-left: 12px;");
        if(_mode == HARD && !DataFileMgr::isAllTableWithNoErrorFalse("Multifacile.xml", "EasyMode") && hasProgressifModeChanged)
            _mediumMode->trigger();
        else if(_mode == HARD && hasProgressifModeChanged)
            _easyMode->trigger();
    }
    else
        _hardModeActionText->setStyleSheet("color: white; padding-left: 12px;");

    if(DataFileMgr::isAllTableWithNoErrorFalse("Multifacile.xml", "EasyMode") && _isProgressifMode)
    {
        _mediumModeActionText->setStyleSheet("color: grey; padding-left: 12px;");
        if(_mode == MEDIUM && hasProgressifModeChanged)
            _easyMode->trigger();
    }
    else
        _mediumModeActionText->setStyleSheet("color: white; padding-left: 12px;");
}

void MainWindow::changeProgressifMode(QAction *action)
{
    if(action == _progressifMode)
        _mgr.setValue("settings", "progressifMode", "true");
    else
        _mgr.setValue("settings", "progressifMode", "false");

    verifyModesPermissions(true);
}

void MainWindow::checkUpdateReceivedAnswer(UpdateType update)    //slot which is connected to the updateNeeded(UpdateType) signal of check. It processes the answer given by check
{

    if(update == NoUpdate) //if not update needed
    {
        if(_check->isUserAction())  //and if it's the user who clicked on "check for updates"
            CustomMessageBox(NoUpdateMsg, this).exec();
        return;
    }
    else if(update == NormalUpdate) //else if update needed
    {
        _check->disconnectFromHost();
        CustomMessageBox updateMsgBox(NewUpdate, this);
        bool userAnswer = updateMsgBox.exec();

        if(userAnswer)  //if the user want to update
        {
            _check->runMultifacileUpdate();
            this->close();  //close this window
        }
        else
            return;
    }
    else if(update == UpdaterUpdate)
    {
        _check->disconnectFromHost();
        CustomMessageBox updateMsgBox(NewUpdate, this);
        bool userAnswer = updateMsgBox.exec();

        if(userAnswer)
        {
            _check->runUpdaterUpdate();
            this->close();
        }
        else
            return;
    }
}

void MainWindow::createCentralWidget()
{
    _widget = new QWidget();

    _texte = new QLabel(tr("Choisis la table de multiplication que tu souhaites travailler !"));
    _texte->setAttribute(Qt::WA_TranslucentBackground);

    _point = new QLabel;
    _point->setPixmap(QPixmap(":/image/Point.png"));

    if(_mapper == NULL)
        _mapper = new QSignalMapper(this);

    for(int i = 0; i < 10; ++i)
    {
        if(_mode == EASY || _mode == MEDIUM)
            _bouton[i] = new QPushButton(tr("La table de ")+QString::number(i+1), _widget);
        else // _mode == HARD
            _bouton[i] = new QPushButton(tr("La table aléatoire"), _widget);

        _bouton[i]->setFixedSize(256, 94);

        connect(_bouton[i], SIGNAL(clicked()), _mapper, SLOT(map()));
        _mapper->setMapping(_bouton[i], i+1);
    }

    checkSucceedTables();

    _quit = new QPushButton(tr("Quitter"));
    _quit->setFixedSize(70, 40);
    _quit->setObjectName("QuitButton");

    _texte->setParent(_widget);
    _texte->move(68, 25);

    _point->setParent(_widget);
    _point->move(50, 38);

    _quit->setParent(_widget);
    _quit->move(490, 480);

    for(int i = 0, j = 0; i < 10; ++i)
    {
        if(i % 2 == 0)
            _bouton[i]->move(80, (75 + 80 * j));
        else
        {
            _bouton[i]->move(320, (75 + 80 * j));
            ++j;
        }
    }


    connect(_quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    _actualWindow = MainWidget;
}
void MainWindow::deleteAddIfExist()
{
#ifdef Q_OS_LINUX
    if(QFile::exists("Add"))
        QFile::remove("Add");
#endif
#ifdef Q_OS_WIN32
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if(QFile::exists(env.value("appdata")+"/Add.exe"))
        QFile::remove(env.value("appdata")+"/Add.exe");
#endif
}

void MainWindow::doActions()
{
    _quitAction = new QAction(QIcon(":/icon/sortie.png"), tr("&Quitter"), this); //the file comes of a Qt ressource file (it's faster than charge a directory's file)

    _updateAction = new QAction(QIcon(":/icon/update.png"), tr("&Vérifier les mise à jours"), this);  //idem

    _easyMode = new QWidgetAction(this);
    _easyModeActionText = new QLabel("Facile");
    _easyMode->setDefaultWidget(_easyModeActionText);
    _easyModeActionText->setStyleSheet("color: white; padding-left: 12px; text-decoration: underline; font-style: italic;");

    _mediumMode = new QWidgetAction(this);
    _mediumModeActionText = new QLabel("Moyen");
    _mediumMode->setDefaultWidget(_mediumModeActionText);

    _hardMode = new QWidgetAction(this);
    _hardModeActionText = new QLabel("Difficile");
    _hardMode->setDefaultWidget(_hardModeActionText);

    _progressifMode = new QAction(tr("Progression pas à pas"), this);

    _freeMode = new QAction(tr("Progression libre"), this);
}

void MainWindow::doActionGroup()
{
    _actionGroup = new QActionGroup(this);
    _actionGroup->addAction(_easyMode);
    _actionGroup->addAction(_mediumMode);
    _actionGroup->addAction(_hardMode);
    _actionGroup->setExclusive(true);

    _progressifModeActionGroup = new QActionGroup(this);
    _progressifModeActionGroup->addAction(_progressifMode);
    _progressifModeActionGroup->addAction(_freeMode);
    _progressifModeActionGroup->setExclusive(true);
}

void MainWindow::doMenuBar()
{
    _file = menuBar()->addMenu(tr("      &Fichier |"));
    _file->setObjectName("FileMenu");
    _tools = menuBar()->addMenu(tr("&Outils"));
    _modes = new Menu(tr("| &Mode"));
    menuBar()->addMenu(_modes);
    _modes->setStyleSheet("QMenu { border: 1.5px solid rgb(255, 169, 50); border-radius: 4px; background-color: rgb(54, 103, 59); }");

    doActions();

    _easyMode->setCheckable(true);
    _easyMode->setToolTip("Table dans l'ordre avec astuces");
    _mediumMode->setCheckable(true);
    _mediumMode->setToolTip("Table en désordre sans astuces");
    _hardMode->setCheckable(true);
    _hardMode->setToolTip("Table mystère...");
    _progressifMode->setCheckable(true);
    _progressifMode->setChecked(_isProgressifMode);
    _progressifMode->setToolTip("Tu est obligé de faire \nles tables par modes \n(du plus facile au plus difficile)");
    _freeMode->setCheckable(true);
    _freeMode->setChecked(!_isProgressifMode);
    _freeMode->setToolTip("Tu fait la table que tu veux \ndans le mode que tu veux");
    _easyMode->setChecked(true);

    doActionGroup();

    _file->addAction(_quitAction);
    _tools->addAction(_updateAction);
    _modes->addActions(_actionGroup->actions());
    _modes->addSeparator();
    _modes->addActions(_progressifModeActionGroup->actions());

#ifndef Q_OS_WIN32
    menuBar()->setNativeMenuBar(false);
#endif

    menuBar()->setAttribute(Qt::WA_TranslucentBackground);
}

void MainWindow::socketError()
{
    if(_check->isUserAction())
        CustomMessageBox(ConnectionError, this).exec(); //if there is a connection error, it open a QMessageBox for inform the user
}

void MainWindow::initStyle()
{
    QFile css(":/css/Multifacile.css");
    css.open(QIODevice::ReadOnly);
    this->setStyleSheet(css.readAll());
    css.close();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    qApp->quit();
    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(_ClickOnWindow)
        window()->move(event->globalPos() - _Diff);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    _ClickOnWindow = true;
    _Diff = event->pos();
}

void MainWindow::open_window(const int nbr)   //open a questionary window with the number given by the map signal of mapper. The questionary window is create in function of the Mode
{
    switch(_mode)
    {
    case EASY:
        _fen = new EasyModeWindow(nbr);
        _fen->setFixedSize(650, 560);
        _fen->setObjectName("Fen");
        this->setCentralWidget(_fen);
        connect(_fen, SIGNAL(wasClosed()), this, SLOT(resetCentralWidget()));
        break;
    case MEDIUM:
        if(DataFileMgr::hasNoErrorTrue("Multifacile.xml", "EasyMode", nbr) || !_isProgressifMode)
        {
            _fen = new MediumModeWindow(nbr);
            _fen->setFixedSize(650, 560);
            _fen->setObjectName("Fen");
            this->setCentralWidget(_fen);
            connect(_fen, SIGNAL(wasClosed()), this, SLOT(resetCentralWidget()));
        }
        else
        {
            unavailableTable(nbr);
            return;
        }
        break;
    case HARD:
        _fen = new HardModeWindow();
        _fen->setFixedSize(650, 560);
        _fen->setObjectName("Fen");
        this->setCentralWidget(_fen);
        connect(_fen, SIGNAL(wasClosed()), this, SLOT(resetCentralWidget()));
        break;
    }
    _actualWindow = SecondWidget;
}

void MainWindow::resetCentralWidget()
{
    createCentralWidget();
    this->setCentralWidget(_widget);
}

void MainWindow::updateButtonsLabels()    //change the Buttons's text when changing mode
{
    if((_mode == EASY || _mode == MEDIUM) && _actualWindow == MainWidget)
    {
        for(int i = 0; i < 10; ++i)
        {
            _bouton[i]->setText(tr("La table de ") + QString::number(i+1));
            _bouton[i]->setStyleSheet("");
        }

        checkSucceedTables();
    }
    else if(_mode == HARD && _actualWindow == MainWidget)
    {
        for(int i = 0; i < 10; ++i)
        {
            _bouton[i]->setText(tr("La table aléatoire"));
            _bouton[i]->setStyleSheet("");
        }
    }
    else
        return;
}

void MainWindow::setMode(QAction *action)   //slot call when user change the mode
{
    if(action == _easyMode)
    {
        if(_mode == MEDIUM)
            _mediumModeActionText->setStyleSheet("color: white; padding-left: 12px;");
        else
             _hardModeActionText->setStyleSheet("color: white; padding-left: 12px;");

        _mode = EASY;

        if(_actualWindow == SecondWidget)
                setNewSecondWindow();
        else
            updateButtonsLabels();

        _easyModeActionText->setStyleSheet("color: white; padding-left: 12px; text-decoration: underline; font-style: italic;");
    }
    else if(action == _mediumMode)
    {
        if(_mode == EASY)
            _easyModeActionText->setStyleSheet("color: white; padding-left: 12px;");
        else
            _hardModeActionText->setStyleSheet("color: white; padding-left: 12px;");

        if(DataFileMgr::isAllTableWithNoErrorFalse("Multifacile.xml", "EasyMode") && _isProgressifMode)
        {
            unavailableMode(MEDIUM);
            _easyMode->setChecked(true);
            return;
        }
        else if(_actualWindow == SecondWidget)
        {
            _mode = MEDIUM;
            _mediumMode->setChecked(true);
            setNewSecondWindow();
        }
        else
        {
            _mode = MEDIUM;
            updateButtonsLabels();
        }

        _mediumModeActionText->setStyleSheet("color: white; padding-left: 12px; text-decoration: underline; font-style: italic;");

    }
    else
    {
        if(_mode == EASY)
            _easyModeActionText->setStyleSheet("color: white; padding-left: 12px;");
        else
            _mediumModeActionText->setStyleSheet("color: white; padding-left: 12px;");

        if( (!DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "EasyMode") || !DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "MediumMode")) && _isProgressifMode)
        {
            unavailableMode(HARD);
            if(_mode == MEDIUM)
                _mediumMode->trigger();
            else
                _easyMode->trigger();
            return;
        }
        else if(_actualWindow == SecondWidget)
        {
            _mode = HARD;
            setNewSecondWindow();
        }
        else
        {
            _mode = HARD;
            updateButtonsLabels();
        }

        _hardModeActionText->setStyleSheet("color: white; padding-left: 12px; text-decoration: underline; font-style: italic;");
    }
}

void MainWindow::unavailableMode(Mode mode)
{
    MessageType type = (mode == MEDIUM) ? CannotMediumMode : CannotHardMode;
    CustomMessageBox(type, this).exec();
}

MainWindow::~MainWindow()
{
    delete _file, _tools, _modes;
    delete _quitAction, _updateAction, _easyMode, _mediumMode, _hardMode;
    delete _actionGroup;
    delete _check;
    delete _mapper;
    delete _minCloseMenu;

    for(int i = 0; i < 10; ++i)
        _bouton[i] = NULL;

    _file = NULL;
    _tools = NULL;
    _modes = NULL;
    _quitAction = NULL;
    _updateAction = NULL;
    _easyMode = NULL;
    _mediumMode = NULL;
    _hardMode = NULL;
    _actionGroup = NULL;
    _quit = NULL;
    _minCloseMenu = NULL;
    _check = NULL;
    _widget = NULL;
    _mapper = NULL;
    _fen = NULL;
}
