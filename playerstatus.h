#ifndef PLAYERSTATUS_H
#define PLAYERSTATUS_H

#include <QObject>

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
    PlayerStatus *setProgressNow(const qlonglong &value);
    void setProgressMin(const qlonglong &value);
    void setProgressMax(const qlonglong &value);

    PlayerStatus *setCanPlay(bool value);
    PlayerStatus *setCanPause(bool value);
    PlayerStatus *setCanNext(bool value);
    PlayerStatus *setCanPrev(bool value);
    PlayerStatus *setCanOpen(bool value);
    PlayerStatus *setCanControl(bool value);

    PlayerStatus *setVolume(int value);

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
    double volume = 1.0;

    PlayerStatus *setMetadata(
            QString songTitle,
            QString songArtist,
            QString songAlbum,
            QString songArt,
            qlonglong songProgressMax,
            qlonglong songProgressMin);
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
    void volumeChanged();
};

#endif // PLAYERSTATUS_H
