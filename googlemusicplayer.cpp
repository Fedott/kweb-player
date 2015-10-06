#include "googlemusicplayer.h"

GoogleMusicPlayer::GoogleMusicPlayer(QWebEngineView *browser)
    : QObject(browser)
{
    this->browser = browser;
    this->status = new PlayerStatus(this->browser);

    this->browser->load(QUrl("https://play.google.com/music/listen"));
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

void GoogleMusicPlayer::setVolume(double volume)
{
    int normalizeVolume = (int) (volume * 100);
    QString action = QString("value = %1").arg(normalizeVolume);
    QString code = getJsQuerySelectorAction("#material-vslider", action);

    getPage()->runJavaScript(code);
}

void GoogleMusicPlayer::updatePlayingStatus()
{
    QString disabledCode = QString("document.querySelector('sj-icon-button[data-id=play-pause]').disabled === true");
    getPage()->runJavaScript(disabledCode, [this](const QVariant &result){
        this->status->setDisabled(result.toBool());
    });

    QString playingCode = QString("document.querySelector('sj-icon-button[data-id=play-pause]').className === 'playing'");
    getPage()->runJavaScript(playingCode, [this](const QVariant &result){
        this->status->setPlaying(result.toBool());
    });
}

void GoogleMusicPlayer::updateArt()
{
    QString currentTrackArtCode = QString("document.getElementById('playingAlbumArt').src.replace(\"=s90-\", \"=s500-\")");
    getPage()->runJavaScript(currentTrackArtCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status->setArt(result.toString());
        } else {
            this->status->setArt("");
        }
    });
}

void GoogleMusicPlayer::updateSongTitle()
{
    QString currentTrackTitleCode = QString("var elm = document.getElementById('player-song-title').firstChild;"
                                       "elm.innerText || elm.textContent;");
    getPage()->runJavaScript(currentTrackTitleCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status->setTitle(result.toString());
        } else {
            this->status->setTitle("");
        }
    });
}

void GoogleMusicPlayer::updateSongArtist()
{
    QString currentTrackTitleCode = QString("var elm = document.getElementById('player-artist').firstChild;"
                                       "elm.innerText || elm.textContent;");
    getPage()->runJavaScript(currentTrackTitleCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status->setArtist(result.toString());
        } else {
            this->status->setArtist("");
        }
    });
}

void GoogleMusicPlayer::updateSongAlbum()
{
    QString currentTrackTitleCode = QString("var elm = document.querySelector(\"#playerSongInfo .player-album\");"
                                       "elm.innerText || elm.textContent;");
    getPage()->runJavaScript(currentTrackTitleCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status->setAlbum(result.toString());
        } else {
            this->status->setAlbum("");
        }
    });
}

void GoogleMusicPlayer::updateSongProgress()
{
    QString songProgressNowCode = QString("document.querySelector('#material-player-progress').getAttribute('aria-valuenow');");
    QString songProgressMinCode = QString("document.querySelector('#material-player-progress').getAttribute('aria-valuemin');");
    QString songProgressMaxCode = QString("document.querySelector('#material-player-progress').getAttribute('aria-valuemax');");

    getPage()->runJavaScript(songProgressMinCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status->setProgressMin(result.toLongLong());
        } else {
            this->status->setProgressMin(0);
        }
    });

    getPage()->runJavaScript(songProgressMaxCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status->setProgressMax(result.toLongLong());
        } else {
            this->status->setProgressMax(0);
        }
    });

    getPage()->runJavaScript(songProgressNowCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->status->setProgressNow(result.toLongLong());
        } else {
            this->status->setProgressNow(0);
        }
    });
}

void GoogleMusicPlayer::updateCanControls()
{
    QString canNextCode = getJsQuerySelectorAction(getJsButtonSelector("forward"), "disabled === false");
    QString canPrevCode = getJsQuerySelectorAction(getJsButtonSelector("rewind"), "disabled === false");

    getPage()->runJavaScript(canNextCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->getStatus()->setCanNext(result.toBool());
        } else {
            this->getStatus()->setCanNext(false);
        }
    });

    getPage()->runJavaScript(canPrevCode, [this](const QVariant &result){
        if (result.isValid()) {
            this->getStatus()->setCanPrev(result.toBool());
        } else {
            this->getStatus()->setCanPrev(false);
        }
    });
}

void GoogleMusicPlayer::updateVolume()
{
    QString code = getJsQuerySelectorAction("#material-vslider", ".value");
    getPage()->runJavaScript(code, [this](const QVariant &result){
        if (result.isValid()) {
            this->getStatus()->setVolume(result.toInt());
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
    updateSongProgress();
    updateCanControls();
    updateVolume();
}

PlayerStatus* GoogleMusicPlayer::getStatus()
{
    return status;
}

QWebEnginePage *GoogleMusicPlayer::getPage()
{
    return browser->page();
}

QString GoogleMusicPlayer::getJsQuerySelectorAction(QString selector, QString actionCode)
{
    QString code = QString("document.querySelector('%1').%2;").arg(selector, actionCode);
    return code;
}

void GoogleMusicPlayer::jsQuerySelectorClick(QString selector)
{
    QString code = getJsQuerySelectorAction(selector, "click()");
    getPage()->runJavaScript(code);
}

QString GoogleMusicPlayer::getJsButtonSelector(QString button)
{
    return QString("sj-icon-button[data-id=%1]").arg(button);
}

void GoogleMusicPlayer::jsClickButton(QString button)
{
    QString selector = getJsButtonSelector(button);
    jsQuerySelectorClick(selector);
}
