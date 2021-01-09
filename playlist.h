#ifndef PLAYLIST_H
#define PLAYLIST_H


#include <QVector>
#include <QMap>
#include "Track.h"

class PlayList
{
    QVector <Track> tracksVec;

    QString fileName = "PlayList.abk";
    QMap<QString, QString> tracksMap;

public:
    PlayList();

    void read();
    bool addTrackInMap(const QString location, const QString name);
      void addTrackInVec(const QString location, const QString name);
    void removeTrackInMap(const QString key);
     void removeTrackInVec(int index);
    void save();
    void printMap();
    void printVec();
    void copyInVec();
    Track getTrackFromVec(int index);
    int getSize(){return tracksVec.size() ;}

    QString getNameAndLoc( QVector<Track> :: iterator it );

     QMap<QString, QString>* getMapTracks();
      QVector <Track>* getVecTracks();

};

#endif // PLAYLIST_H
