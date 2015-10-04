#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "googlemusicplayer.h"

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

protected:
    QWebEngineView *browser;
    GoogleMusicPlayer *player;
protected slots:
    void playPausePlayer();
    void initWebPlayer();
    void nextPlayer();
    void prevPlayer();
    void shufflePlayer();
    void thumbsUpPlayer();
    void thumbsDownPlayer();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
