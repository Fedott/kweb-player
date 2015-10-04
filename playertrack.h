#ifndef PLAYERTRACK_H
#define PLAYERTRACK_H

#include <QString>



class PlayerTrack
{
public:
    PlayerTrack();
    QString getArtist() const;
    void setArtist(const QString &value);

    QString getAlbum() const;
    void setAlbum(const QString &value);

    QString getTitle() const;
    void setTitle(const QString &value);

protected:
    QString artist;
    QString album;
    QString title;

signals:

public slots:
};

#endif // PLAYERTRACK_H
