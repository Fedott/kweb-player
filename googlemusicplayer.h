#ifndef GOOGLEMUSICPLAYER_H
#define GOOGLEMUSICPLAYER_H

#include <QWebEngineView>


class PlayerStatus : public QObject
{
    Q_OBJECT

public:
    PlayerStatus(QObject *parent);
    ~PlayerStatus();
    QString getState();
    void setDisabled(bool value);
    void setPlaying(bool value);
    void setTitle(const QString &value);
    void setArtist(const QString &value);
    void setAlbum(const QString &value);
    void setArt(const QString &value);
    void setProgressNow(const qlonglong &value);
    void setProgressMin(const qlonglong &value);
    void setProgressMax(const qlonglong &value);

    void setCanPlay(bool value);
    void setCanPause(bool value);
    void setCanNext(bool value);
    void setCanPrev(bool value);
    void setCanOpen(bool value);
    void setCanControl(bool value);


    int state;
    bool disabled;
    bool playing;
    QString title;
    QString artist;
    QString album;
    QString art;
    qlonglong progressNow;
    qlonglong progressMin;
    qlonglong progressMax;
    bool canPlay = false;
    bool canPause = false;
    bool canNext = false;
    bool canPrev = false;
    bool canOpen = true;
    bool canControl = true;

protected slots:
    void changeCanPlayPause();

signals:
    void metadataChanged();
    void playbackStatusChanged();
    void positionChanged();
    void canOpenChanged();
    void canPlayChanged();
    void canPauseChanged();
    void canNextChanged();
    void canPrevChanged();
    void canControlChanged();
};

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

protected:
    QWebEngineView *browser;
    QWebEnginePage* getPage();
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
signals:

public slots:
    void updateStatus();
};


#endif // GOOGLEMUSICPLAYER_H
