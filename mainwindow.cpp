#include "mainwindow.h"
#include "mprisplayerobject.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QDBusConnection>
#include <QTimer>
#include <QTime>

#include <kglobalaccel.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    browser = new QWebEngineView(this);
    setCentralWidget(browser);

    player = new GoogleMusicPlayer(browser);


    setupActions();
    setupDbus();

    initWebPlayer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupActions()
{
    connect(ui->actionPlayPause, SIGNAL(triggered(bool)), SLOT(playPausePlayer()));
    connect(ui->actionNext, SIGNAL(triggered(bool)), SLOT(nextPlayer()));
    connect(ui->actionPrev, SIGNAL(triggered(bool)), SLOT(prevPlayer()));
    connect(ui->actionStatus, SIGNAL(triggered(bool)), SLOT(status()));
}

void MainWindow::setupDbus()
{

    bool success = QDBusConnection::sessionBus().registerService(QLatin1String("org.mpris.MediaPlayer2.KWebPlayer"));

    if (success) {
        DBusAbstractAdaptor *adaptor = new MprisPlayerObject(player, this);
        adaptor->setDBusPath("/org/mpris/MediaPlayer2");
        adaptor = new MprisObject(this);
        adaptor->setDBusPath("/org/mpris/MediaPlayer2");
        QDBusConnection::sessionBus().registerObject("/org/mpris/MediaPlayer2", this, QDBusConnection::ExportAdaptors);
    }
}

void MainWindow::initWebPlayer()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(playerStatusUpdate()));
    timer->start(500);
}

void MainWindow::playerStatusUpdate()
{
    player->updateStatus();
}

void MainWindow::playPausePlayer()
{
    player->playPause();
}

void MainWindow::nextPlayer()
{
    player->next();
}

void MainWindow::prevPlayer()
{
    player->prev();
}

void MainWindow::shufflePlayer()
{
    player->shuffle();
}

void MainWindow::thumbsUpPlayer()
{
    player->trumbsUp();
}

void MainWindow::thumbsDownPlayer()
{
    player->trumbsDown();
}

void MainWindow::status()
{
    PlayerStatus *status = player->getStatus();
    qDebug() << status->disabled << status->playing << status->getState() << status->artist << status->album << status->title << status->art;
}
