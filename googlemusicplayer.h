#ifndef GOOGLEMUSICPLAYER_H
#define GOOGLEMUSICPLAYER_H

#include <QWebEngineView>



class GoogleMusicPlayer
{
public:
    GoogleMusicPlayer(QWebEngineView *browser);

    void playPause();
    void next();
    void prev();
    void trumbsUp();
    void trumbsDown();
    void shuffle();
    int getStatus();
protected:
    QWebEngineView *browser;
    QWebEnginePage* getPage();
    void jsQuerySelectorClick(QString selector);
    void jsClickButton(QString button);

signals:

public slots:
};

#endif // GOOGLEMUSICPLAYER_H
