#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "googlemusicplayer.h"
#include "trayicon.h"

#include <QMainWindow>
#include <QWebEngineView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void playerStatusUpdate();
    void showNotify();
protected:
    QWebEngineView *browser;
    GoogleMusicPlayer *player;
    TrayIcon *trayIcon;
    void setupActions();
    void setupDbus();
protected slots:
    void playPausePlayer();
    void initWebPlayer();
    void nextPlayer();
    void prevPlayer();
    void shufflePlayer();
    void thumbsUpPlayer();
    void thumbsDownPlayer();
    void status();
    void quit();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
