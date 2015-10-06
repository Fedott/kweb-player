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
    void setProgressNow(const qlonglong &value);
    void setProgressMin(const qlonglong &value);
    void setProgressMax(const qlonglong &value);

    void setCanPlay(bool value);
    void setCanPause(bool value);
    void setCanNext(bool value);
    void setCanPrev(bool value);
    void setCanOpen(bool value);
    void setCanControl(bool value);

    void setVolume(int value);

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
