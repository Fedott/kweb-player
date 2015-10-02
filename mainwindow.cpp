#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QUrl startPageUrl = QUrl("https://play.google.com/music/listen");

    browser = new QWebEngineView(this);
    browser->load(startPageUrl);
    setCentralWidget(browser);

    connect(browser, SIGNAL(loadFinished(bool)), SLOT(initWebPlayer()));

    connect(ui->actionPlay_Pause, SIGNAL(triggered(bool)), SLOT(playPausePlayer()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWebPlayer()
{

}

void MainWindow::playPausePlayer()
{
    QString code = QString("document.querySelector('sj-icon-button[data-id=play-pause]').click()");
    browser->page()->runJavaScript(code);
}
