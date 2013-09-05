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

MainWindow::MainWindow() : userAction(false), _mode(EASY), actualWindow(MainWidget), mapper(NULL)
{
    setWindowFlags(Qt::FramelessWindowHint);  //Work only on Windows ! ; disallow user to resize the window
    resize(650, 650);

    initStyle();

    doMenuBar();

    createCentralWidget();

    check = new CheckUpdate(this, VERSION);  //create a new CheckUpdate object with VERSION defined in header

    minCloseMenu = new MinCloseMenu(this);

    menuBar()->setCornerWidget(minCloseMenu);

    this->setCentralWidget(widget);



    connect(mapper, SIGNAL(mapped(int)), this, SLOT(open_window(int)));  //connect the signal mapped of QSignalMapper to the custom slot open_window(int)

    connect(check, SIGNAL(checkUpdateAnswer(UpdateType)), this, SLOT(checkUpdateReceivedAnswer(UpdateType)));
    connect(check, SIGNAL(error()), this, SLOT(socketError()));

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(updateAction, SIGNAL(triggered()), this, SLOT(verification()));
    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setMode(QAction*)));
}

void MainWindow::checkUpdateReceivedAnswer(UpdateType update)    //slot which is connected to the updateNeeded(UpdateType) signal of check. It processes the answer given by check
{
    if(update == NoUpdate) //if not update needed
    {
        if(userAction)  //and if it's the user who clicked on "check for updates"
        {
            CustomMessageBox(NoUpdateMsg, this).exec();
            userAction = false;
        }

        //check->disconnectFromHost();
        return;
    }
    else if(update == NormalUpdate) //else if update needed
    {
        if(userAction)
            userAction = false;

        check->disconnectFromHost();
        CustomMessageBox updateMsgBox(NewUpdate, this);
        bool userAnswer = updateMsgBox.exec();

        if(userAnswer)  //if the user want to update
        {
            START_UPDATER();
            this->close();  //close this window
        }
        else
            return;
    }
    else if(update == UpdaterUpdate)
    {
        if(userAction)
            userAction = false;

        check->disconnectFromHost();
        CustomMessageBox updateMsgBox(NewUpdate, this);
        bool userAnswer = updateMsgBox.exec();

        if(userAnswer)
        {
            START_ADD();
            this->close();
        }
        else
            return;
    }
}

void MainWindow::createCentralWidget()
{
    widget = new QWidget();

    texte = new QLabel(tr("Choisis la table de multiplication que tu souhaites travailler !"));
    texte->setAttribute(Qt::WA_TranslucentBackground);

    point = new QLabel;
    point->setPixmap(QPixmap(":/image/Point.png"));

    if(mapper == NULL)
        mapper = new QSignalMapper(this);

    for(int i = 0; i < 10; ++i)
    {
        if(_mode == EASY || _mode == MEDIUM)
            bouton[i] = new QPushButton(tr("La table de ")+QString::number(i+1), widget);
        else if(_mode == HARD)
            bouton[i] = new QPushButton(tr("La table aléatoire"), widget);

        bouton[i]->setFixedSize(256, 94);

        connect(bouton[i], SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(bouton[i], i+1);
    }

    quit = new QPushButton(tr("Quitter"));
    quit->setFixedSize(70, 40);
    quit->setObjectName("QuitButton");

    texte->setParent(widget);
    texte->move(68, 25);

    point->setParent(widget);
    point->move(50, 38);

    quit->setParent(widget);
    quit->move(490, 480);

    for(int i = 0, j = 0; i < 10; ++i)
    {
        if(i % 2 == 0)
            bouton[i]->move(80, (75 + 80 * j));
        else
        {
            bouton[i]->move(320, (75 + 80 * j));
            ++j;
        }
    }

    if(_mode == EASY || _mode == MEDIUM)
    {
        QMap<int, bool> *list = DataFileMgr::getNoErrorList("Multifacile.xml", (_mode == EASY) ? "EasyMode" : "MediumMode");

        for(QMap<int, bool>::Iterator it = list->begin(); it != list->end(); ++it)
            if(it.value())
                bouton[ (it.key() - 1)]->setStyleSheet("background-image: url(\":/image/Bouton_succes.png\");");

        delete list;

        if(_mode == MEDIUM)
            for(int i = 0; i < 10; ++i)
                if(!DataFileMgr::hasNoErrorTrue("Multifacile.xml", "EasyMode", (i + 1)))
                    bouton[i]->setStyleSheet("background-image: url(\":/image/Bouton_inacessible.png\"); color: grey;");
    }

    if(!DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "EasyMode") || !DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "MediumMode"))
        hardModeActionText->setStyleSheet("color: grey; padding-left: 12px;");
    else
        hardModeActionText->setStyleSheet("color: white; padding-left: 12px;");

    if(DataFileMgr::isAllTableWithNoErrorFalse("Multifacile.xml", "EasyMode"))
        mediumModeActionText->setStyleSheet("color: grey; padding-left: 12px;");
    else
        mediumModeActionText->setStyleSheet("color: white; padding-left: 12px;");

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    actualWindow = MainWidget;
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
    quitAction = new QAction(QIcon(":/icon/sortie.png"), tr("&Quitter"), this); //the file comes of a Qt ressource file (it's faster than charge a directory's file)
    updateAction = new QAction(QIcon(":/icon/update.png"), tr("&Vérifier les mise à jours"), this);  //idem
    easyMode = new QAction(tr("&Facile"), this);
    mediumMode = new QWidgetAction(this);
    mediumModeActionText = new QLabel("Moyen");
    mediumMode->setDefaultWidget(mediumModeActionText);
    hardMode = new QWidgetAction(this);
    hardModeActionText = new QLabel("Difficile");
    hardMode->setDefaultWidget(hardModeActionText);

    if(!DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "EasyMode") || !DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "MediumMode"))
        hardModeActionText->setStyleSheet("color: grey; padding-left: 12px;");
    else
        hardModeActionText->setStyleSheet("color: white; padding-left: 12px;");

    if(DataFileMgr::isAllTableWithNoErrorFalse("Multifacile.xml", "EasyMode"))
        mediumModeActionText->setStyleSheet("color: grey; padding-left: 12px;");
    else
        mediumModeActionText->setStyleSheet("color: white; padding-left: 12px;");
}

void MainWindow::doActionGroup()
{
    actionGroup = new QActionGroup(this);
    actionGroup->addAction(easyMode);
    actionGroup->addAction(mediumMode);
    actionGroup->addAction(hardMode);
    actionGroup->setExclusive(true);
}

void MainWindow::doMenuBar()
{
    file = menuBar()->addMenu(tr("      &Fichier |"));
    file->setObjectName("FileMenu");
    tools = menuBar()->addMenu(tr("&Outils"));
    modes = new Menu(tr("| &Mode"));
    menuBar()->addMenu(modes);
    modes->setStyleSheet("QMenu { border: 1.5px solid rgb(255, 169, 50); border-radius: 4px; background-color: rgb(54, 103, 59); }");

    doActions();

    easyMode->setCheckable(true);
    easyMode->setToolTip("Table dans l'ordre avec astuces");
    mediumMode->setCheckable(true);
    mediumMode->setToolTip("Table en désordre sans astuces");
    hardMode->setCheckable(true);
    hardMode->setToolTip("Table mystère...");
    easyMode->setChecked(true);

    doActionGroup();

    file->addAction(quitAction);
    tools->addAction(updateAction);
    modes->addActions(actionGroup->actions());

#ifndef Q_OS_WIN32
    menuBar()->setNativeMenuBar(false);
#endif

    menuBar()->setAttribute(Qt::WA_TranslucentBackground);
}

void MainWindow::socketError()
{
    if(userAction)
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
    if(ClickOnWindow)
        window()->move(event->globalPos() - Diff);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    ClickOnWindow = true;
    Diff = event->pos();
}

void MainWindow::open_window(const int nbr)   //open a questionary window with the number given by the map signal of mapper. The questionary window is create in function of the Mode
{
    switch(_mode)
    {
    case EASY:
        fen = new EasyModeWindow(nbr);
        fen->setFixedSize(650, 560);
        fen->setObjectName("Fen");
        this->setCentralWidget(fen);
        connect(fen, SIGNAL(wasClosed()), this, SLOT(resetCentralWidget()));
        break;
    case MEDIUM:
        if(DataFileMgr::hasNoErrorTrue("Multifacile.xml", "EasyMode", nbr))
        {
            fen = new MediumModeWindow(nbr);
            fen->setFixedSize(650, 560);
            fen->setObjectName("Fen");
            this->setCentralWidget(fen);
            connect(fen, SIGNAL(wasClosed()), this, SLOT(resetCentralWidget()));
        }
        else
        {
            unavailableTable(nbr);
            return;
        }
        break;
    case HARD:
        fen = new HardModeWindow();
        fen->setFixedSize(650, 560);
        fen->setObjectName("Fen");
        this->setCentralWidget(fen);
        connect(fen, SIGNAL(wasClosed()), this, SLOT(resetCentralWidget()));
        break;
    }
    actualWindow = SecondWidget;
}

void MainWindow::resetCentralWidget()
{
    createCentralWidget();
    this->setCentralWidget(widget);
}

void MainWindow::updateButtonsLabels()    //change the Buttons's text when changing mode
{
    if((_mode == EASY || _mode == MEDIUM) && actualWindow == MainWidget)
    {
        for(int i = 0; i < 10; ++i)
        {
            bouton[i]->setText(tr("La table de ") + QString::number(i+1));
            bouton[i]->setStyleSheet("");
        }

        QMap<int, bool> *list = DataFileMgr::getNoErrorList("Multifacile.xml", (_mode == EASY) ? "EasyMode" : "MediumMode");

        for(QMap<int, bool>::Iterator it = list->begin(); it != list->end(); ++it)
            if(it.value())
                bouton[ (it.key() - 1)]->setStyleSheet("background-image: url(\":/image/Bouton_succes.png\");");

        delete list;

        if(_mode == MEDIUM)
            for(int i = 0; i < 10; ++i)
                if(!DataFileMgr::hasNoErrorTrue("Multifacile.xml", "EasyMode", (i + 1)))
                    bouton[i]->setStyleSheet("background-image: url(\":/image/Bouton_inacessible.png\"); color: grey;");

    }
    else if(_mode == HARD && actualWindow == MainWidget)
    {
        for(int i = 0; i < 10; ++i)
        {
            bouton[i]->setText(tr("La table aléatoire"));
            bouton[i]->setStyleSheet("");
        }
    }
    else
        return;
}

void MainWindow::setMode(QAction *action)   //slot call when user change the mode
{
    if(action == easyMode)
    {
        _mode = EASY;
        if(actualWindow == SecondWidget)
                setNewSecondWindow();
        else
            updateButtonsLabels();
    }
    else if(action == mediumMode)
    {

        if(DataFileMgr::isAllTableWithNoErrorFalse("Multifacile.xml", "EasyMode"))
        {
            unavailableMode(MEDIUM);
            easyMode->setChecked(true);
        }
        else if(actualWindow == SecondWidget)
        {
            _mode = MEDIUM;
            mediumMode->setChecked(true);
            setNewSecondWindow();
        }
        else
        {
            _mode = MEDIUM;
            updateButtonsLabels();
        }
    }
    else if(action == hardMode)
    {
        if(!DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "EasyMode") || !DataFileMgr::isAllTableWithNoErrorTrue("Multifacile.xml", "MediumMode"))
        {
            unavailableMode(HARD);
            if(_mode == MEDIUM)
                mediumMode->setChecked(true);
            else
                easyMode->setChecked(true);
        }
        else if(actualWindow == SecondWidget)
        {
            _mode = HARD;
            setNewSecondWindow();
        }
        else
        {
            _mode = HARD;
            updateButtonsLabels();
        }
    }
}

void MainWindow::unavailableMode(Mode mode)
{
    MessageType type = (mode == MEDIUM) ? CannotMediumMode : CannotHardMode;
    CustomMessageBox(type, this).exec();
}

void MainWindow::verification()
{
    check->tryConnection(); //try a connection
    userAction = true;  //set userAction to true because it's the user who ask update (not the program)
}

MainWindow::~MainWindow()
{
    delete file, tools, modes;
    delete quitAction, updateAction, easyMode, mediumMode, hardMode;
    delete actionGroup;
    delete check;
    delete mapper;
    delete minCloseMenu;

    for(int i = 0; i < 10; ++i)
        bouton[i] = NULL;

    file = NULL;
    tools = NULL;
    modes = NULL;
    quitAction = NULL;
    updateAction = NULL;
    easyMode = NULL;
    mediumMode = NULL;
    hardMode = NULL;
    actionGroup = NULL;
    quit = NULL;
    minCloseMenu = NULL;
    check = NULL;
    widget = NULL;
    mapper = NULL;
    fen = NULL;
}
