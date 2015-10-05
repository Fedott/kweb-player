#ifndef GOOGLEMUSICPLAYER_H
#define GOOGLEMUSICPLAYER_H

#include <QWebEngineView>


class PlayerStatus {
public:
    int getState();
    int state;
    bool disabled;
    bool playing;
    QString title;
    QString artist;
    QString album;
    QString art;
};

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
    PlayerStatus* getStatus();

protected:
    QWebEngineView *browser;
    QWebEnginePage* getPage();
    void jsQuerySelectorClick(QString selector);
    void jsClickButton(QString button);

    PlayerStatus status;
    void updatePlayingStatus();
    void updateArt();
    void updateSongTitle();
    void updateSongArtist();
    void updateSongAlbum();
signals:

public slots:
    void updateStatus();
};


#endif // GOOGLEMUSICPLAYER_H
