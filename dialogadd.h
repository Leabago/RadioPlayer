#ifndef DIALOGADD_H
#define DIALOGADD_H
#include <QDialog>
#include <QWidget>
#include <QtWidgets>
#include "playlist.h"

#include <QMediaPlayer>

class DialogAdd : public QDialog
{
    Q_OBJECT
private:
    QLineEdit* name;
    QLineEdit* location;

    QLabel* errorMessage;
    PlayList *list;

    QMediaPlayer *player;

    QLabel* nameLab;
    QLabel* locationLab ;

    QGridLayout* layout ;

    QPushButton* okButton;
    QPushButton* cancelButton ;




public:
    DialogAdd(const bool &proverkaContains , const QString &nameInput, const QString &locInput, QWidget* par = 0);
     DialogAdd(QString name);
    ~DialogAdd(){
        delete name;
        delete location;
        delete errorMessage;
        delete list;
        delete player;
        delete nameLab;
        delete locationLab;
        delete layout;
        delete okButton;
        delete cancelButton;
    }

   bool proverkaContains;
    bool correctInput = false;
    bool correctUrl = false;


    QString getName() const;
    QString getLocation() const;

     QTimer *updaterTitle = new QTimer(this);

public slots:
    void checkInputSlot();

    void updateTitleSlot();

    void setEnableFalse();


};

#endif // DIALOGADD_H
