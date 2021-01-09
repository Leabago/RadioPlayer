#include "player.h"
#include <QMediaMetaData>


Player::Player(QWidget *parent) : QWidget(parent)
{
    setSkeleton();
    player = new QMediaPlayer;
    player->setVolume(50);

    QObject::connect(add, SIGNAL(clicked()), this, SLOT(addNewTrackSlot()));
    QObject::connect(remove, SIGNAL(clicked()), this, SLOT(removeOneTrackSlot()));
    QObject::connect(playButton, SIGNAL(clicked()), this, SLOT(playRadioSlot()));

    QObject::connect(soundValueSpin, SIGNAL( sliderReleased()), this, SLOT(setVolumeSlot()));

    QObject::connect(playListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(playRadioSlot()));

    QObject::connect(updaterTitle, SIGNAL(timeout()), this, SLOT(updateTitleSlot()));

    QObject::connect(copyNameButton, SIGNAL(clicked()), this, SLOT(copyNameSlot()));
    QObject::connect(copyLocButton, SIGNAL(clicked()), this, SLOT(copyLocSlot()));
    QObject::connect(copyTrackNameButton, SIGNAL(clicked()), this, SLOT(copyTrackNameSlot()));

    QObject::connect(edit, SIGNAL(clicked()), this, SLOT(editRadioSlot()));

    updaterTitle->start(5000);

    updateList();
    if ( playListWidget->count()  != 0)
    {
        playListWidget->setCurrentRow(0);
        currentTrack = 0;
        QString name =  playList->getTrackFromVec(currentTrack).getName();
        QString location =  playList->getTrackFromVec(currentTrack).getLocation();
        nameLabel->setText(name);
        locLabel->setText(location);

    }
    player->pause();
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));



}

void Player::setVolumeSlot( )
{
    player->setVolume(soundValueSpin->value());


    QString albumTitle2  = player->metaData(QMediaMetaData::Title).toString() ;
    qDebug() <<  albumTitle2 ;
}

void Player::updateTitleSlot()
{
    QString trackTitle  = player->metaData(QMediaMetaData::Title).toString() ;
    trackNameLabel->setText(trackTitle);

}

void Player::copyNameSlot()
{
    QApplication::clipboard()->setText(nameLabel->text() );

}
void Player::copyLocSlot()
{
    QApplication::clipboard()->setText(locLabel->text() );
}
void Player::copyTrackNameSlot()
{
    QApplication::clipboard()->setText(trackNameLabel->text() );
}

void Player::editRadioSlot()
{
    qDebug() << "curr " << currentTrack;

    QListWidgetItem *curIttem = playListWidget->currentItem();

    Track track = playList->getTrackFromVec(currentTrack);
    QString name = track.getName();
    QString loc = track.getLocation();
    QString locOld = loc;

    DialogAdd* addDialog = new DialogAdd(false , name, loc);

    if (addDialog->exec() == QDialog::Accepted) {
        name = addDialog->getName();
        loc = addDialog->getLocation();

        QMap<QString, QString> *playListMap = playList->getMapTracks();
        playListMap->remove(locOld);
        playListMap->insert(loc, name);

        QVector<Track> *playListTrack = playList->getVecTracks();
        Track forIdit(loc, name);

        QVector<Track>::iterator iter = playListTrack->begin()+currentTrack;
        *iter = forIdit ;

        curIttem->setText(name + " - " + loc);
        updateList();
        playList->save();

        setCurrentTrackLabel();

        if (loc != locOld)
        {
            player->stop();
            player->setMedia(QUrl(loc));
            player->play();
        }

        delete addDialog;
    }

    qDebug() << "curr " << currentTrack;
}

void Player::setSkeleton()
{
    int xSize = 100;
    int ySize = 100;

    // бокс с кнопками добавить удалить
    add = new QPushButton;
    remove  = new QPushButton;
    edit = new QPushButton;

    upBoxAddRemove = new QVBoxLayout;
    upBoxAddRemove->addWidget(add);
    upBoxAddRemove->addWidget(remove);
    upBoxAddRemove->addWidget(edit);
    upBoxAddRemove->addStretch();


    // верх, playListWidget + add_delete
    playListWidget  = new QListWidget;
    upBox = new QHBoxLayout;
    upBox->addWidget(playListWidget);
    upBox->addLayout(upBoxAddRemove);


    // интсрументы на нижней части
    playButton = new  QPushButton;
    soundValueSpin = new QDial;
    nameLabel = new ScrollText;
    locLabel = new ScrollText;
    trackNameLabel = new ScrollText;

    soundValueSpin->setRange(0, 100);
    soundValueSpin->setValue(50);

    // бокс с именем и локацией
    viewNameAndLoc = new QGridLayout;

    copyNameButton = new QPushButton;
    copyLocButton = new QPushButton("ссылка");
    copyTrackNameButton = new QPushButton("трек");

    viewNameAndLoc->addWidget(nameLabel, 0, 0);
    viewNameAndLoc->addWidget(locLabel, 1, 0);
    viewNameAndLoc->addWidget(trackNameLabel, 2, 0);

    viewNameAndLoc->addWidget(copyNameButton, 0, 1);
    viewNameAndLoc->addWidget(copyLocButton, 1, 1);
    viewNameAndLoc->addWidget(copyTrackNameButton, 2, 1);

    // нижний бокс с инструментами
    instrumentsPlay = new QHBoxLayout;
    instrumentsPlay->addWidget(playButton);
    instrumentsPlay->addWidget(soundValueSpin);
    instrumentsPlay->addLayout(viewNameAndLoc);
    instrumentsPlay->addStretch();

    // главный бокс
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(upBox);
    mainLayout->addLayout(instrumentsPlay);

    QSize buttonSize(xSize, ySize);
    playButton->setFixedSize(buttonSize);
    soundValueSpin->setFixedSize(buttonSize);
    add->setFixedSize(buttonSize);
    remove->setFixedSize(buttonSize);
    edit->setFixedSize(buttonSize);
    playListWidget->setMinimumSize(buttonSize*2);

    nameLabel->setFixedWidth(xSize*3);
    nameLabel->setToolTip (nameLabel->text());
    locLabel->setFixedWidth(xSize*3);
    locLabel ->setToolTip (locLabel->text());
    trackNameLabel->setFixedWidth(xSize*3);
    trackNameLabel->setToolTip (trackNameLabel->text());

    copyNameButton->setFixedWidth(xSize);
    copyLocButton->setFixedWidth(xSize);
    copyTrackNameButton->setFixedWidth(xSize);

    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    QIcon iconadd;
    iconadd.addFile("IconAdd.png");
    QIcon iconRemove;
    iconRemove.addFile("IconRemove.png");
    QIcon iconEdit;
    iconEdit.addFile("IconEdit.png");
    QIcon iconCopy;
    iconCopy.addFile("IconCopy.png");

    QSize IconSize(50,50);
    add->setIcon(iconadd);
    add->setIconSize(IconSize);

    remove->setIcon(iconRemove);
    remove->setIconSize(IconSize);

    edit->setIcon(iconEdit);
    edit->setIconSize(IconSize);

    playButton->setIconSize(IconSize);
    copyNameButton->setIcon(iconCopy);
    copyLocButton->setIcon(iconCopy);
    copyTrackNameButton->setIcon(iconCopy);




    copyNameButton->setStyleSheet("text-align:left;");
    copyNameButton->setText(" - радио");

    copyLocButton->setStyleSheet("text-align:left;");
    copyLocButton->setText(" - ссылка");

    copyTrackNameButton->setStyleSheet("text-align:left;");
    copyTrackNameButton->setText(" - трек");


}

void Player::setCurrentTrackLabel()
{
    playListWidget->setCurrentRow(currentTrack);
    QString name =  playList->getTrackFromVec(currentTrack).getName();
    QString location =  playList->getTrackFromVec(currentTrack).getLocation();
    nameLabel->setText(name);
    locLabel->setText(location);

}

void Player::setStop()
{
    player->stop();

    if (currentTrack  == 0 & playListWidget->count() > 0)
    {
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        QString name =  playList->getTrackFromVec(currentTrack).getName();
        QString location =  playList->getTrackFromVec(currentTrack).getLocation();
        nameLabel->setText(name);
        locLabel->setText(location);
        playListWidget->setCurrentRow(currentTrack);
    } else  if (currentTrack  == 0 & playListWidget->count() == 0)
    {
        currentTrack--;
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        nameLabel->setText(" ");
        locLabel->setText(" ");
    } else
    {
        currentTrack--;
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        QString name =  playList->getTrackFromVec(currentTrack).getName();
        QString location =  playList->getTrackFromVec(currentTrack).getLocation();
        nameLabel->setText(name);
        locLabel->setText(location);
        playListWidget->setCurrentRow(currentTrack);
    }
}

void Player::saveMapSlot()
{
    playList->save();
}
void Player::removeOneTrackSlot()
{
    QListWidgetItem *curIttem = playListWidget->currentItem();
    int index = playListWidget->currentRow();

    if (index >=0 & index < playList->getSize())
    {

        Track track = playList->getTrackFromVec(index);
        playList->removeTrackInMap(track.getLocation());
        playList->removeTrackInVec(index);
        playList->save();
        updateList();


        if (index == currentTrack)
            setStop();
    }
}


void Player::addNewTrackSlot() // добавление нового радио
{
    DialogAdd* addDialog = new DialogAdd(true , "", "");
    if (addDialog->exec() == QDialog::Accepted) {

        QString loc = addDialog->getLocation();
        QString name = addDialog->getName();

        QMap<QString, QString> *playListMap = playList->getMapTracks();
        bool contains =  playListMap->contains(loc) ;

        if (!contains)
        {
            playList->addTrackInMap(loc, name);
            playList->addTrackInVec(loc, name);
            updateList();
            playList->save();

            playListWidget->setCurrentRow(currentTrack);
        }
    }
    delete addDialog;
}

void Player::playRadioSlot()
{
    int index = playListWidget->currentRow();

    if (playListWidget->count() != 0 & index >= 0 & index < playList->getSize() )
    {
        if (player->state() == QMediaPlayer::PlayingState & currentTrack == index)
        {

            player->pause();
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        } else  if (player->state() == QMediaPlayer::PausedState & currentTrack == index)
        {

            player->play();
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        } else
        {

            currentTrack = index;
            Track track = playList->getTrackFromVec(index);

            QString location =   track.getLocation() ;
            QString name =  track.getName();

            player->setMedia(QUrl(location));
            player->play();
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));

            locLabel->setText(location);
            nameLabel->setText(name);

        }


    }
}


void Player::updateList() // обновляет сисок виджетов
{
    playListWidget->clear();

    QVector<Track>  *listTracks = playList->getVecTracks(); // ссылка на коллекцию

    QVector<Track> :: iterator it = listTracks->begin()  ;
    for (; it  != listTracks->end() ; ++it)
    {
        QString nameAndLoc = it->getNameAndLoc();
        playListWidget->addItem(nameAndLoc);
    }
    listTracks = nullptr;
}


Player::~Player(){ playList->save();
                   delete  playList ;
                   delete add ;
                   delete remove ;
                   delete playListWidget;
                   delete playButton  ;
                   delete soundValueSpin ;
                   delete nameLabel ;
                   delete locLabel  ;
                   delete trackNameLabel ;
                   delete player;
                   delete updaterTitle ;
                   delete copyNameButton ;
                   delete copyLocButton ;
                   delete copyTrackNameButton ;
                   delete edit;
                 };



