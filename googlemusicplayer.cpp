#include "googlemusicplayer.h"

GoogleMusicPlayer::GoogleMusicPlayer(QWebEngineView *browser)
{
    this->browser = browser;
    this->status = PlayerStatus();
}

void GoogleMusicPlayer::playPause()
{
    jsClickButton("play-pause");
}

void GoogleMusicPlayer::next()
{
    jsClickButton("forward");
}

void GoogleMusicPlayer::prev()
{
    jsClickButton("rewind");
}

void GoogleMusicPlayer::trumbsUp()
{
    jsQuerySelectorClick(".player-rating-container sj-icon-button[data-rating=5]");
}

void GoogleMusicPlayer::trumbsDown()
{
    jsQuerySelectorClick(".player-rating-container sj-icon-button[data-rating=1]");
}

void GoogleMusicPlayer::shuffle()
{
    jsClickButton("shuffle");
}

void GoogleMusicPlayer::updatePlayingStatus()
{
    QString disabledCode = QString("document.querySelector('sj-icon-button[data-id=play-pause]').disabled === true");
    getPage()->runJavaScript(disabledCode, [this](const QVariant &result){
        this->status.disabled = result.toBool();
    });

    QString playingCode = QString("document.querySelector('sj-icon-button[data-id=play-pause]').className === 'playing'");
    getPage()->runJavaScript(playingCode, [this](const QVariant &result){
        this->status.playing = result.toBool();
    });
}

void GoogleMusicPlayer::updateArt()
{
    QString currentTrackArtCode = QString("document.getElementById('playingAlbumArt').src.replace(\"=s90-\", \"=s500-\")");
    getPage()->runJavaScript(currentTrackArtCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status.art = result.toString();
        } else {
            this->status.art = "";
        }
    });
}

void GoogleMusicPlayer::updateSongTitle()
{
    QString currentTrackTitleCode = QString("var elm = document.getElementById('player-song-title').firstChild;"
                                       "elm.innerText || elm.textContent;");
    getPage()->runJavaScript(currentTrackTitleCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status.title = result.toString();
        } else {
            this->status.title = "";
        }
    });
}

void GoogleMusicPlayer::updateSongArtist()
{
    QString currentTrackTitleCode = QString("var elm = document.getElementById('player-artist').firstChild;"
                                       "elm.innerText || elm.textContent;");
    getPage()->runJavaScript(currentTrackTitleCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status.artist = result.toString();
        } else {
            this->status.artist = "";
        }
    });
}

void GoogleMusicPlayer::updateSongAlbum()
{
    QString currentTrackTitleCode = QString("var elm = document.querySelector(\"#playerSongInfo .player-album\");"
                                       "elm.innerText || elm.textContent;");
    getPage()->runJavaScript(currentTrackTitleCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status.album = result.toString();
        } else {
            this->status.album = "";
        }
    });
}

void GoogleMusicPlayer::updateStatus()
{
    updatePlayingStatus();

    updateArt();

    updateSongTitle();

    updateSongArtist();

    updateSongAlbum();
}

PlayerStatus* GoogleMusicPlayer::getStatus()
{
    return &status;
}

QWebEnginePage *GoogleMusicPlayer::getPage()
{
    return browser->page();
}

void GoogleMusicPlayer::jsQuerySelectorClick(QString selector)
{
    QString code = QString("document.querySelector('%1').click();").arg(selector);
    getPage()->runJavaScript(code);
}

void GoogleMusicPlayer::jsClickButton(QString button)
{
    QString selector = QString("sj-icon-button[data-id=%1]").arg(button);
    jsQuerySelectorClick(selector);
}


int PlayerStatus::getState()
{
    if (disabled) {
        return 0;
    } else if (playing) {
        return 1;
    } else {
        return 2;
    }
}
