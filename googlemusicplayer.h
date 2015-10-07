#ifndef GOOGLEMUSICPLAYER_H
#define GOOGLEMUSICPLAYER_H

#include "playerstatus.h"

#include <QWebEngineView>

class GoogleMusicPlayer : public QObject
{
    Q_OBJECT

public:
    GoogleMusicPlayer(QWebEngineView *browser);

    void playPause();
    void next();
    void prev();
    void trumbsUp();
    void trumbsDown();
    void shuffle();
    PlayerStatus* getStatus();
    void setVolume(double volume);
protected:
    QWebEngineView *browser;
    QWebEnginePage* getPage();
    QString playerControlCode;

    void jsQuerySelectorClick(QString selector);
    void jsClickButton(QString button);

    PlayerStatus *status;
    void updatePlayingStatus();
    void updateArt();
    void updateSongTitle();
    void updateSongArtist();
    void updateSongAlbum();
    void updateSongProgress();
    void updateCanControls();
    QString getJsQuerySelectorAction(QString selector, QString actionCode);
    QString getJsButtonSelector(QString button);
    void updateVolume();
signals:

public slots:
    void updateStatus();
    void finishLoading(bool);
};


#endif // GOOGLEMUSICPLAYER_H
