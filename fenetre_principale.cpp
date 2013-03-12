/*Copyright (C) <2012> <Plestan> <Kévin>

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

#include "fenetre_principale.h"
#include "CheckUpdate.h"
#include "Shuffle.h"

Fenetre_principale::Fenetre_principale() : userAction(false), mode(EASY), actualWindow(MainWindow)
{
    QFile css(":/css/Multifacile.css");
    css.open(QIODevice::ReadOnly);
    this->setStyleSheet(css.readAll());
    css.close();

    mapper = new QSignalMapper(this); //construct a QSignalMapper for the QPushButtonof tables

    createCentralWidget();

    check = new CheckUpdate(this, VERSION);  //create a new CheckUpdate object with VERSION defined in header

    resize(650, 650);

    /******************Menu's construction****************/
        //add Menu to the QMenuBar

    file = menuBar()->addMenu(tr("      &Fichier |"));
    file->setObjectName("FileMenu");
    tools = menuBar()->addMenu(tr("&Outils"));
    modes = menuBar()->addMenu(tr("| &Mode"));
    modes->setObjectName("ModeMenu");

    menuBar()->setAttribute(Qt::WA_TranslucentBackground);

        //create QActions
    quitAction = new QAction(QIcon(":/icon/sortie.png"), tr("&Quitter"), this); //the file comes of a Qt ressource file (it's faster than charge a directory's file)
    updateAction = new QAction(QIcon(":/icon/update.png"), tr("&Vérifier les mise à jours"), this);  //idem
    chrono = new QAction(tr("Table &chronomètré"), this);
    easyMode = new QAction(tr("&Facile"), this);
    mediumMode = new QAction(tr("&Moyen"), this);
    hardMode = new QAction(tr("D&ifficile"), this);

        //set the QAction checkable and set easyMode checked
    easyMode->setCheckable(true);
    easyMode->setToolTip("Table de multiplication normale avec astuces");
    mediumMode->setCheckable(true);
    mediumMode->setToolTip("Table en désordre sans astuces");
    hardMode->setCheckable(true);
    hardMode->setToolTip("Une table mélangé avec n'importe quelle table");
    easyMode->setChecked(true);
    chrono->setCheckable(true);
    chrono->setObjectName("Chrono");

        //create a QActionGroup, add to it QActions and set it exclusive
    actionGroup = new QActionGroup(this);
    actionGroup->addAction(easyMode);
    actionGroup->addAction(mediumMode);
    actionGroup->addAction(hardMode);
    actionGroup->setExclusive(true);

        //bind QActions with their QMenu
    file->addAction(quitAction);
    tools->addAction(updateAction);
    modes->addActions(actionGroup->actions());
    modes->addSeparator();
    modes->addAction(chrono);
    /*****************************************************/


    minCloseMenu = new MinCloseMenu(this);

    menuBar()->setCornerWidget(minCloseMenu);

    this->setCentralWidget(widget);

    /*****************************************************/


    setWindowFlags(Qt::FramelessWindowHint);  //Work only on Windows ! ; disallow user to resize the window

    /********************Connect part*********************/

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(open_window(int)));  //connect the signal mapped of QSignalMapper to the custom slot open_window(int)

    connect(check, SIGNAL(checkUpdateAnswer(UpdateType)), this, SLOT(checkUpdateReceivedAnswer(UpdateType)));
    connect(check, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket()));

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(updateAction, SIGNAL(triggered()), this, SLOT(verification()));
    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setMode(QAction*)));
    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(resetLabel(QAction*)));


    /*****************************************************/

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

inline void Fenetre_principale::closeEvent(QCloseEvent *event) //reimplemented slot who close the program
{
    qApp->quit();
    event->accept();
}

void Fenetre_principale::checkUpdateReceivedAnswer(UpdateType update)    //slot which is connected to the updateNeeded(UpdateType) signal of check. It processes the answer given by check
{
    if(update == NoUpdate) //if not update needed
    {
        if(userAction)  //and if it's the user who clicked on "check for updates"
        {
            QMessageBox::information(this, tr("Vérification de mise à jour"), tr("Il n'y a pour le moment aucune mise à jour disponible."));
            userAction = false;
        }
        check->disconnectFromHost();
        return;
    }
    else if(update == NormalUpdate) //else if update needed
    {
        if(userAction)
            userAction = false;
        check->disconnectFromHost();
        int userAnswer = QMessageBox::question(this, tr("Mise à jour disponible"), tr("Une version plus récente de Multifacile est disponible, veux-tu la télécharger ?"), QMessageBox::Yes | QMessageBox::No);
        if(userAnswer == QMessageBox::Yes)  //if the user want to update
        {
#ifdef Q_OS_WIN32
            ShellExecute(NULL, L"open", L"Updater.exe", NULL, NULL, SW_SHOWNORMAL); //run updater.exe (for Windows)
#endif
#ifdef Q_OS_LINUX
            QProcess::startDetached("Updater"); //run updater.exe (for Linux)
#endif
            this->close();  //close this window
        }
        else if(userAnswer == QMessageBox::No)  //if user don't want to update
            return;
        else
            return;
    }
    else if(update == UpdaterUpdate)
    {
        if(userAction)
            userAction = false;
        check->disconnectFromHost();
        int userAnswer = QMessageBox::question(this, tr("Mise à jour disponible"), tr("Une version plus récente de Multifacile est disponible, veux-tu la télécharger ?"), QMessageBox::Yes | QMessageBox::No);
        if(userAnswer == QMessageBox::Yes)
        {
#ifdef Q_OS_LINUX
            QFile::copy(":/application/Add", "Add");
            QProcess::startDetached("Add");
#endif
#ifdef Q_OS_WIN32
            QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
            QString str(env.value("appdata")+"/Add.exe");
            QFile::copy(":/application/Add.exe", str);
            ShellExecute(NULL, L"open", str.toStdWString().c_str(), NULL, NULL, SW_SHOWNORMAL);
#endif
            this->close();
        }
        else if(userAnswer == QMessageBox::No)
            return;
        else
            return;
    }
}

void Fenetre_principale::createCentralWidget()
{
    widget = new QWidget();

    texte = new QLabel(tr("Choisis la table de multiplication que tu souhaites travailler !"));
    texte->setAttribute(Qt::WA_TranslucentBackground);

    point = new QLabel;
    point->setPixmap(QPixmap(":/image/Point.png"));


    for(int i = 0; i < 10; i++)
    {
        if(mode == EASY || mode == MEDIUM)
            bouton[i] = new QPushButton(tr("La table de ")+QString::number(i+1), widget);
        else if(mode == HARD)
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

    for(int i = 0, j = 0; i < 10; i++)
    {
        if(i % 2 == 0)
            bouton[i]->move(80, (80 + 75 * j));
        else
        {
            bouton[i]->move(320, (80 + 75 * j));
            j++;
        }
    }

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    actualWindow = MainWindow;
}

void Fenetre_principale::erreurSocket()
{
    if(userAction)
        QMessageBox::information(this, tr("Erreur de connexion"), tr("Impossible de vérifier les mise à jours")); //if there is a connection error, it open a QMessageBox for inform the user
}

inline void Fenetre_principale::mouseMoveEvent(QMouseEvent *event)
{
    if(ClickOnWindow)
    {
        QPoint p = event->globalPos();

        window()->move(p - Diff);
    }
}

inline void Fenetre_principale::mousePressEvent(QMouseEvent *event)
{
    ClickOnWindow = true;
    Diff = event->pos();
}

inline void Fenetre_principale::mouseReleaseEvent(QMouseEvent *) { ClickOnWindow = false; }

void Fenetre_principale::open_window(const int nbr)   //open a questionary window with the number given by the map signal of mapper. The questionary window is create in function of the Mode
{
    if(mode == EASY)
    {
        fen = new EasyModeWindow(nbr, chrono->isChecked());
        fen->setFixedSize(650, 560);
        fen->setObjectName("Fen");
        this->setCentralWidget(fen);
        connect(fen, SIGNAL(wasClosed()), this, SLOT(resetCentralWidget()));
    }
    else if(mode == MEDIUM)
    {
        fen = new MediumModeWindow(nbr, chrono->isChecked());
        fen->setFixedSize(650, 560);
        fen->setObjectName("Fen");
        this->setCentralWidget(fen);
        connect(fen, SIGNAL(wasClosed()), this, SLOT(resetCentralWidget()));
    }
    else if(mode == HARD)
    {
        fen = new HardModeWindow(chrono->isChecked());
        fen->setFixedSize(650, 560);
        fen->setObjectName("Fen");
        this->setCentralWidget(fen);
        connect(fen, SIGNAL(wasClosed()), this, SLOT(resetCentralWidget()));
    }
    actualWindow = SecondWindow;
}

void Fenetre_principale::resetCentralWidget()
{
    createCentralWidget();
    this->setCentralWidget(widget);
}

void Fenetre_principale::resetLabel(QAction *action)    //change the Buttons's text when changing mode
{
    if((action == easyMode || action == mediumMode) && actualWindow == MainWindow)
    {
        for(int i = 0; i < 10; i++)
            bouton[i]->setText(tr("La table de ")+QString::number(i+1));
    }
    else if(action == hardMode && actualWindow == MainWindow)
    {
        for(int i = 0; i < 10; i++)
            bouton[i]->setText(tr("La table aléatoire"));
    }
    else
        return;
}

void Fenetre_principale::setMode(QAction *action)   //slot call when user change the mode
{
    if(action == easyMode)
    {
        mode = EASY;
        if(actualWindow == SecondWindow)
                setNewSecondWindow();
    }
    else if(action == mediumMode)
    {
        mode = MEDIUM;

        if(actualWindow == SecondWindow)
            setNewSecondWindow();
    }
    else if(action == hardMode)
    {
        mode = HARD;

        if(actualWindow == SecondWindow)
            setNewSecondWindow();
    }
}

inline void Fenetre_principale::setNewSecondWindow() { open_window(fen->getMultiple()); }

void Fenetre_principale::verification() //slot that is call when user click on check update action.
{
    check->tryConnection(); //try a connection
    userAction = true;  //set userAction to true because it's the user who ask update (not the program)
}

Fenetre_principale::~Fenetre_principale()
{
    delete file, tools, modes;
    delete quitAction, updateAction, chrono, easyMode, mediumMode, hardMode;
    delete actionGroup;
    delete check;
    delete mapper;
    delete minCloseMenu;

    for(int i = 0; i < 10; i++)
        bouton[i] = nullptr;

    file = nullptr;
    tools = nullptr;
    modes = nullptr;
    quitAction = nullptr;
    updateAction = nullptr;
    chrono = nullptr;
    easyMode = nullptr;
    mediumMode = nullptr;
    hardMode = nullptr;
    actionGroup = nullptr;
    quit = nullptr;
    minCloseMenu = nullptr;
    check = nullptr;
    widget = nullptr;
    mapper = nullptr;
    fen = nullptr;
}
