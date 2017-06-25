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

MainWindow::MainWindow() :  _mode(EASY), _actualWindow(FirstWidget),  _mgr("Multifacile.xml"), _ClickOnWindow(false) //, _probWidget(NULL)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("Multifacile");
    resize(650, 650);

    _isProgressifMode = (_mgr.value("settings", "progressifMode") == "true");

    initStyle();

    doMenuBar();

    createCentralWidget();

    _check = new CheckUpdate(this);  //create a new CheckUpdate object with VERSION defined in header

    _minCloseMenu = new MinCloseMenu(this);

    menuBar()->setCornerWidget(_minCloseMenu);

    this->setCentralWidget(_widget);


    connect(_check, SIGNAL(checkUpdateAnswer(UpdateType)), this, SLOT(checkUpdateReceivedAnswer(UpdateType)));
    connect(_check, SIGNAL(error()), this, SLOT(socketError()));

    connect(_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(_updateAction, SIGNAL(triggered()), this, SLOT(verification()));
    connect(_actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setMode(QAction*)));
    connect(_progressifModeActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(changeProgressifMode(QAction*)));
}

//void MainWindow::switchToProblems()
//{
//    _probWidget = new ProblemWidget();

//    disconnect(_widget, SIGNAL(goToProblems()), this, SLOT(switchToProblems()));

//    this->setCentralWidget(_probWidget);

//    connect(_probWidget, SIGNAL(goToTables()), this, SLOT(switchToTables()));
//}

//void MainWindow::switchToTables()
//{
//    disconnect(_probWidget, SIGNAL(goToTables()), this, SLOT(switchToTables()));
//    resetCentralWidget();
//    connect(_widget, SIGNAL(goToProblems()), this, SLOT(switchToProblems()));
//}

void MainWindow::checkSucceedTables()
{
    _widget->checkSucceedTables(_mode);
    verifyModesPermissions();
}

void MainWindow::verifyModesPermissions(bool hasProgressifModeChanged)
{
     _isProgressifMode = (_mgr.value("settings", "progressifMode") == "true");

     if(_actualWindow == FirstWidget)
         _widget->updateButtonsLabels(_mode, _isProgressifMode);

    if( !(DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "EasyMode") && DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "MediumMode")) && _isProgressifMode )
    {
        _hardModeActionText->setStyleSheet("color: grey; padding-left: 12px;");
        if(_mode == HARD && !DataFileMgr::isAllTableWithNoErrorFalse("Multifacile.xml", "EasyMode") && hasProgressifModeChanged)
        {
            unavailableMode(HARD);
            _mediumMode->trigger();
        }
        else if(_mode == HARD && hasProgressifModeChanged)
        {
            unavailableMode(HARD);
            _easyMode->trigger();
        }
    }
    else
        _hardModeActionText->setStyleSheet("color: white; padding-left: 12px;");

    if(DataFileMgr::isAllTableWithNoErrorFalse("Multifacile.xml", "EasyMode") && _isProgressifMode)
    {
        _mediumModeActionText->setStyleSheet("color: grey; padding-left: 12px;");

        if(_mode == MEDIUM && hasProgressifModeChanged)
        {
            unavailableMode(MEDIUM);
            _easyMode->trigger();
        }
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

    if(_actualWindow == SecondWidget)
        _fen->progressifModeHasChanged(_isProgressifMode);
}

void MainWindow::checkUpdateReceivedAnswer(UpdateType update)    //slot which is connected to the updateNeeded(UpdateType) signal of check. It processes the answer given by check
{

    if(update == NoUpdate) //if not update needed
    {
        if(_check->isUserAction())  //and if it's the user who clicked on "check for updates"
            CustomMessageBox(NoUpdateMsg, this).exec();
    }
    else if(update == NormalUpdate) //else if update needed
    {
        _check->disconnectFromHost();
        const bool userAnswer = CustomMessageBox(NewUpdate, this).exec();

        if(userAnswer)  //if the user want to update
        {
            _check->runMultifacileUpdate();
            this->close();  //close this window
        }
    }
    else if(update == UpdaterUpdate)
    {
        _check->disconnectFromHost();
        const bool userAnswer = CustomMessageBox(NewUpdate, this).exec();

        if(userAnswer)
        {
            _check->runUpdaterUpdate();
            this->close();
        }
    }
}

void MainWindow::createCentralWidget()
{
    _actualWindow = FirstWidget;

    _widget = new MainWidget(_mode);

    connect(_widget, SIGNAL(clicked(int)),  this, SLOT(openWindow(int)));
//    connect(_widget, SIGNAL(goToProblems()), this, SLOT(switchToProblems()));

    checkSucceedTables();
}

void MainWindow::deleteAddIfExist()
{
#ifdef Q_OS_LINUX
    if(QFile::exists("Add"))
        QFile::remove("Add");
#endif
#ifdef Q_OS_WIN32
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if(QFile::exists(env.value("appdata") + "/Add.exe"))
        QFile::remove(env.value("appdata") + "/Add.exe");
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

void MainWindow::openWindow(const int nbr)   //open a questionary window with the number given by the map signal of mapper. The questionary window is create in function of the Mode
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
            _fen = new MediumModeWindow(nbr, _isProgressifMode);
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

void MainWindow::updateButtonsLabels()    //change the Buttons's text when changing mode
{
    if( _actualWindow == FirstWidget)
    {
       _widget->updateButtonsLabels(_mode);
        checkSucceedTables();
    }
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

        if( !(DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "EasyMode") && DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "MediumMode")) && _isProgressifMode)
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
    delete _minCloseMenu;


    _file = nullptr;
    _tools = nullptr;
    _modes = nullptr;
    _quitAction = nullptr;
    _updateAction = nullptr;
    _easyMode = nullptr;
    _mediumMode = nullptr;
    _hardMode = nullptr;
    _actionGroup = nullptr;
    _minCloseMenu = nullptr;
    _check = nullptr;
    _widget = nullptr;
    _fen = nullptr;
}
