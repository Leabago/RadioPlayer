
#include <QApplication>

#include <QtWidgets>

#include "player.h"

#include <QMediaPlayer>


#include <iostream>
using namespace std;

    int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);

        Player pl;
        pl.show();


          qDebug() << " qwe[i];";

//        QVector<int> *qwe = new QVector<int> ;
//        qwe->push_back(1);
//         qwe->push_back(4);
//          qwe->push_back(5);

//          qwe->operator[](0) = 0;

// QVector<int>::iterator iter = qwe->begin()+1;
//  *iter = 228 ;


//          for (int i = 0; i < qwe->size(); ++i)
//          {
//              qDebug() <<  "| " << *qwe;
//          }

//  qDebug() << " end";


         return app.exec();
    }
