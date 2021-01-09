#ifndef TRACK_H
#define TRACK_H

#include <QString>

class Track
{
private:
    QString name;
    QString location;

public:
    Track(QString location, QString name )
    {       
        this->location = location;
        this->name = name;
    }
    Track( )
    {
        this->location = "location";
        this->name = "name";
    }



    QString getName()
    {
        return name;
    }
    QString getLocation()
    {
        return location;
    }
    QString getNameAndLoc()
    {
        return name + " - " + location;
    }
    void setName(QString name)
    {
        this->name = name;
    }
    void setLocation(QString location)
    {
        this->location = location;
    }

};

#endif // TRACK_H
