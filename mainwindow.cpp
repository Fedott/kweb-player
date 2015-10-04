#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>

#include <kglobalaccel.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QUrl startPageUrl = QUrl("https://play.google.com/music/listen");

    browser = new QWebEngineView(this);
    browser->load(startPageUrl);
    setCentralWidget(browser);

    player = new GoogleMusicPlayer(browser);

    connect(browser, SIGNAL(loadFinished(bool)), SLOT(initWebPlayer()));

    connect(ui->actionPlayPause, SIGNAL(triggered(bool)), SLOT(playPausePlayer()));
    connect(ui->actionNext, SIGNAL(triggered(bool)), SLOT(nextPlayer()));
    connect(ui->actionPrev, SIGNAL(triggered(bool)), SLOT(prevPlayer()));

    setupActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupActions()
{
    KGlobalAccel *accel = new KGlobalAccel();
    KGlobalAccel::getGlobalShortcutsByKey()
}

void MainWindow::initWebPlayer()
{

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
