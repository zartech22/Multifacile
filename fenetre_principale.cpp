#include "fenetre_principale.h"
#include "CheckUpdate.h"
#include "Shuffle.h"

Fenetre_principale::Fenetre_principale()
{
    userAction = false;
    mode = EASY;

    widget = new QWidget();

    check = new CheckUpdate(this, VERSION);  //create a new CheckUpdate object with VERSION defined in header


    /******************Labels' construction***************/

    texte = new QLabel(tr("Choisis la table que tu veux travailler !"));
    espace = new QLabel("<hr />");

    /*****************************************************/

    /******************Menu's construction****************/
        //add Menu to the QMenuBar
    file = menuBar()->addMenu(tr("&Fichier"));
    tools = menuBar()->addMenu(tr("&Outils"));
    modes = menuBar()->addMenu(tr("&Mode"));

        //create QActions
    quitAction = new QAction(QIcon(":/icon/sortie.png"), tr("&Quitter"), this); //the file comes of a Qt ressource file (it's faster than charge a directory's file)
    updateAction = new QAction(QIcon(":/icon/update.png"), tr("&Vérifier les mise à jours"), this);  //idem
    chrono = new QAction(tr("Table &chronomètré"), this);
    shuffleAction = new QAction(tr("Table en &désordre"), this);
    easyMode = new QAction(tr("&Facile"), this);
    mediumMode = new QAction(tr("&Moyen"), this);
    hardMode = new QAction(tr("D&ifficile"), this);

        //set the QAction checkable and set easyMode checked
    easyMode->setCheckable(true);
    mediumMode->setCheckable(true);
    hardMode->setCheckable(true);
    easyMode->setChecked(true);
    shuffleAction->setCheckable(true);
    chrono->setCheckable(true);

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
    modes->addAction(shuffleAction);
    modes->addAction(chrono);
    /*****************************************************/

    /**************QPushbuttons contruction***************/

    mapper = new QSignalMapper(this); //construct a QSignalMapper for the QPushButtonof tables

    for(int i = 0; i < 10; i++) //contruct the QPushButtons and map the clicked signal
    {
        bouton[i] = new QPushButton(tr("Table de ")+QString::number(i+1));
        connect(bouton[i], SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(bouton[i], i+1);
    }

    quit = new QPushButton(tr("Quitter"));
    customTable = new QPushButton(tr("Table personnalisée"));
    /*****************************************************/

    /*****************Layouts construction****************/

        //construct layouts
    layout = new QGridLayout();
    glayout = new QGridLayout();
    vlayout = new QVBoxLayout();

        //add widgets to the main layout
    layout->addWidget(texte, 0, 0, 1, 2);

    layout->addWidget(bouton[0], 1, 0);
    layout->addWidget(bouton[1], 1, 1);
    layout->addWidget(bouton[2], 2, 0);
    layout->addWidget(bouton[3], 2, 1);
    layout->addWidget(bouton[4], 3, 0);
    layout->addWidget(bouton[5], 3, 1);
    layout->addWidget(bouton[6], 4, 0);
    layout->addWidget(bouton[7], 4, 1);
    layout->addWidget(bouton[8], 5, 0);
    layout->addWidget(bouton[9], 5, 1);

        //add widgets to a secondary layout
    glayout->addWidget(espace, 0, 1, 1, 2);
    glayout->addWidget(customTable, 1, 1);
    glayout->addWidget(quit, 1, 2);

        //add layouts into a QVBoxLayout
    vlayout->addLayout(layout);
    vlayout->addLayout(glayout);

        //bind the vertical layout to the widget and bind it to the MainWindow
    widget->setLayout(vlayout);
    this->setCentralWidget(widget);

    /*****************************************************/

    check->tryConnection();  //try a connection for check updates

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);  //Work only on Windows ! ; disallow user to resize the window

    /********************Connect part*********************/

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(open_window(int)));  //connect the signal mapped of QSignalMapper to the custom slot open_window(int)

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(customTable, SIGNAL(clicked()), this, SLOT(open_window()));

    connect(check, SIGNAL(checkUpdateAnswer(UpdateType)), this, SLOT(checkUpdateReceivedAnswer(UpdateType)));
    connect(check, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket()));

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(updateAction, SIGNAL(triggered()), this, SLOT(verification()));
    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setMode(QAction*)));
    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(resetLabel(QAction*)));

    /*****************************************************/
}
void Fenetre_principale::open_window()  //open a window which ask the table that the user want to work on and open a questionary window in function of the Mode mode and the number given
{
    bool ok = false;
    int nbr = QInputDialog::getInteger(this, tr("Choix de la table"), tr("Indiquer la table sur laquelle vous voulez travailler"), 0, -2147483647, 2147483647, 1, &ok); //ask the number of the table
    if(ok)  //verify that the user clic on the Ok button and open a questionary window in function of the number and the Mode
    {
        if(mode == EASY)
        {
            fen = new EasyModeWindow(nbr, shuffleAction->isChecked(), chrono->isChecked());
            fen->resize(300, 200);
            fen->show();
            fenList.append(fen);    //append the new questionnary window to the list
        }
        else if(mode == MEDIUM)
        {
            fen = new MediumModeWindow(nbr, chrono->isChecked());
            fen->resize(300, 200);
            fen->show();
            fenList.append(fen);
        }
        else if(mode == HARD)
        {
            fen = new HardModeWindow(chrono->isChecked());
            fen->resize(300, 200);
            fen->show();
            fenList.append(fen);
        }
    }
}

void Fenetre_principale::open_window(const int nbr)   //open a questionary window with the number given by the map signal of mapper. The questionary window is create in function of the Mode
{
    if(mode == EASY)
    {
        fen = new EasyModeWindow(nbr, shuffleAction->isChecked(), chrono->isChecked());
        fen->resize(300, 200);
        fen->show();
        fenList.append(fen);
    }
    else if(mode == MEDIUM)
    {
        fen = new MediumModeWindow(nbr, chrono->isChecked());
        fen->resize(300, 200);
        fen->show();
        fenList.append(fen);
    }
    else if(mode == HARD)
    {
        fen = new HardModeWindow(chrono->isChecked());
        fen->resize(300, 200);
        fen->show();
        fenList.append(fen);
    }
}
void Fenetre_principale::checkUpdateReceivedAnswer(UpdateType update)    //slot which is connected to the updateNeeded(bool) signal of check. It processes the answer given by check
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
            QProcess::startDetached("Updater.exe"); //run updater.exe (for Linux)
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
            QFile::copy(":/application/Add.exe", "Add.exe");
            ShellExecute(NULL, L"open", L"Add.exe", NULL, NULL, SW_SHOWNORMAL);
#endif
            this->close();
        }
        else if(userAnswer == QMessageBox::No)
            return;
        else
            return;
    }
}
void Fenetre_principale::setMode(QAction *action)   //slot call when user change the mode
{
    if(action == easyMode)
    {
        mode = EASY;
        if(!shuffleAction->isEnabled()) //if shuffleAction was disabled
        {
            shuffleAction->setEnabled(true);    //make it enabled and unchecked it
            shuffleAction->setChecked(false);
        }
    }
    else if(action == mediumMode)
    {
        mode = MEDIUM;
        shuffleAction->setChecked(true);
        shuffleAction->setDisabled(true);
    }
    else if(action == hardMode)
    {
        mode = HARD;
        shuffleAction->setChecked(true);
        shuffleAction->setDisabled(true);
    }
}
void Fenetre_principale::resetLabel(QAction *action)    //change the Buttons' text when changing mode
{
    if(action == easyMode || action == mediumMode)
    {
        customTable->setEnabled(true);
        for(int i = 0; i < 10; i++)
            bouton[i]->setText(tr("Table de ")+QString::number(i+1));
    }
    else if(action == hardMode)
    {
        customTable->setEnabled(false);
        for(int i = 0; i < 10; i++)
            bouton[i]->setText(tr("Table aléatoire"));
    }
}

void Fenetre_principale::erreurSocket() { QMessageBox::information(this, tr("Erreur de connexion"), tr("Impossible de vérifier les mise à jour")); }    //if there is a connection error, it opern a QMessageBox for inform the user

void Fenetre_principale::verification() //slot that is call when user click on check update action.
{
    check->tryConnection(); //try a connection
    userAction = true;  //set userAction to true because it's the user who ask update (not the program)
}
void Fenetre_principale::closeEvent(QCloseEvent *event) //reimplemented slot who close the program
{
    qApp->quit();
    event->accept();
}
Fenetre_principale::~Fenetre_principale()
{
    delete file, tools, modes;
    delete quitAction, updateAction, shuffleAction, chrono, easyMode, mediumMode, hardMode;
    delete actionGroup;
    delete quit, customTable;
    delete layout, glayout, vlayout;
    delete check;
    delete widget;
    delete mapper;

    for(int i = 0; i < fenList.size(); i++)
    {
        delete fenList[i];
        fenList[i] = 0;
    }

    file = nullptr;
    tools = nullptr;
    modes = nullptr;
    quitAction = nullptr;
    updateAction = nullptr;
    shuffleAction = nullptr;
    chrono = nullptr;
    easyMode = nullptr;
    mediumMode = nullptr;
    hardMode = nullptr;
    actionGroup = nullptr;
    quit = nullptr;
    customTable = nullptr;
    layout = nullptr;
    glayout = nullptr;
    vlayout = nullptr;
    check = nullptr;
    widget = nullptr;
    mapper = nullptr;
}
