#include "playlist.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QDataStream>

PlayList::PlayList()
{
   read();
}

void PlayList::read()  // зсчитываем с файла все в вектор треков
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly) )
    {
        qDebug() << "нет файла " + fileName;

        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "error open " + fileName +  " WriteOnly";
        }
        qDebug() << "файл " + fileName + " создан";
        file.close();

        return;
    }

    QDataStream in(&file);
    in >> tracksMap;

     QMap<QString, QString> :: iterator it = tracksMap.begin()  ;
     for (; it  != tracksMap.end() ; ++it)
     {
        tracksVec.push_back( Track(it.key(), it.value()));
     }

    qDebug() << "sucess  read";
}

 void PlayList::copyInVec()
 {
//     QMap<QString, QString> :: iterator it = tracksMap.begin()  ;
//          for (; it  != tracksMap.end() ; ++it)
//          {
//             tracksVec.push_back( Track(it.key(), it.value()));
//          }
 }


void PlayList::save()  // сохраняет map в файл
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "error open for WriteOnly "  + fileName;
        return;
    }

    QDataStream out(&file);
     out << tracksMap;

    qDebug() << "close  save";
    file.close();
}


bool PlayList::addTrackInMap(const QString location, const QString name)  // добавить в map
{
       tracksMap.insert(location, name);
}

void PlayList::addTrackInVec(const QString location, const QString name)  // добавить в map
{
    tracksVec.push_back(Track(location, name));
}


void PlayList::removeTrackInMap(const QString key)
{
    tracksMap.remove(key);
}

void PlayList::removeTrackInVec(int index)
{
   tracksVec.remove(index);
}


void PlayList::printMap()  // вывести на экран map
{
    QMap<QString, QString> :: iterator it = tracksMap.begin()  ;
    for (; it  != tracksMap.end() ; ++it)
    {
        qDebug() << "|| " << it.key()  + " " +  it.value() ;
    }
}


void PlayList::printVec()  // вывести на экран вектор
{
   QVector<Track> :: iterator it = tracksVec.begin()  ;
    for (; it  != tracksVec.end() ; ++it)
    {
        qDebug() << "|| " <<  it->getLocation() + " " + it->getName() ;
    }
}


QMap<QString, QString>* PlayList::getMapTracks()
{
    return  &tracksMap;
}

 QVector <Track>* PlayList::getVecTracks()
 {
     return &tracksVec;
 }

 QString PlayList::getNameAndLoc(  QVector<Track> :: iterator it )
 {
     return (it->getName() + " - " + it->getLocation() );
 }

 Track PlayList::getTrackFromVec(int index)
 {
     return tracksVec.at(index);
 }



