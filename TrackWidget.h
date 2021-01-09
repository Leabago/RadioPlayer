#ifndef TRACKWIDGET_H
#define TRACKWIDGET_H

#include <QtWidgets>

class TrackWidget : public QWidget
{
    Q_OBJECT

    QPushButton *playButton;
    QLabel *nameLabel;
    QLabel *locationLabel;

    QString name = "-";
    QString location = "-";

public:
    TrackWidget(QWidget *parent = 0 )  : QWidget(parent)
    {

        skelet();
    }

    void setNameAndLoc(QString location, QString name)
    {
        this->name = name;
        this->location = location;

        nameLabel->setText(name);
        locationLabel->setText(location);
    }

    void skelet()
    {
        playButton = new QPushButton;
        nameLabel = new QLabel;
        locationLabel = new QLabel;

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(playButton);
        mainLayout->addWidget(nameLabel);
        mainLayout->addWidget(locationLabel);
    }


    QString getName()
    {
        return name;
    }
    QString getLocation()
    {
        return location;
    }

};

#endif // TRACKWIDGET_H
