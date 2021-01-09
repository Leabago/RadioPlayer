#ifndef PLAYER_H
#define PLAYER_H
#include <QtWidgets>

#include <QWidget>
#include <dialogadd.h>
#include "playlist.h"

#include <QMediaPlayer>
#include <scrolltext.h>

class Player : public QWidget
{
    Q_OBJECT
public:
    Player(QWidget *parent = nullptr);
    ~Player();

    void setSkeleton(); // задает форму главного окна
    void updateList();  // обновляет лист с радио
void setCurrentTrackLabel(); // устанавливает текущиее радио по индексу
    void setStop(); // останавливает при удалении

    PlayList* playList = new PlayList;
    QPushButton *add ;
    QPushButton *remove ;
     QPushButton *edit ;
    QListWidget *playListWidget;
    QPushButton* playButton  ;
    QDial* soundValueSpin ;
    ScrollText* nameLabel ;
    ScrollText* locLabel  ;
    ScrollText* trackNameLabel ;
    QMediaPlayer *player;
    QTimer *updaterTitle = new QTimer(this);
    QPushButton* copyNameButton ;
    QPushButton* copyLocButton ;
    QPushButton* copyTrackNameButton ;

    int currentTrack = -1;

     QVBoxLayout *upBoxAddRemove ; // размещение конопок добавить, удалить
       QHBoxLayout *upBox ;  // размещение лист виджет +  размещение конопок добавить, удалить
        QGridLayout* viewNameAndLoc ; // размещение названия, адрес, название трека, кнопки копировать
          QHBoxLayout *instrumentsPlay ; // нижняя панель инструментов
           QVBoxLayout *mainLayout ; // объединение панели инструментов и лист виджет

public slots:
    void addNewTrackSlot();
    void removeOneTrackSlot();
    void saveMapSlot();
    void playRadioSlot();
    void editRadioSlot();
    void setVolumeSlot();

    void updateTitleSlot();

    void copyNameSlot();
    void copyLocSlot();
    void copyTrackNameSlot();

};

#endif // PLAYER_H
