#include "dialogadd.h"

bool checkUrl(const QUrl &url) {
    if (!url.isValid()) {
        qDebug("Invalid URL: %s", qUtf8Printable(url.toString()));
        return false;
    }

    qDebug("norm " );
    return true;
}


DialogAdd::DialogAdd(const bool &proverkaContains , const QString &nameInput, const QString &locInput, QWidget* par) : QDialog(par, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    this->proverkaContains = proverkaContains;

    QObject::connect(updaterTitle, SIGNAL(timeout()), this, SLOT(updateTitleSlot())); // таймер для проверки ссылки


    player = new QMediaPlayer;  // для проверки ссылки

    list = new PlayList;  // для проверки ссылки на существование в имеющемся списке

    name = new QLineEdit;   // поле ввода имени
    location = new QLineEdit;  // поле ввода ссылки

    name->setText(nameInput);
    location->setText(locInput);

    nameLab = new QLabel("&Название радио");
    locationLab = new QLabel("&Адрес радио");

    errorMessage = new QLabel;  // поле вывода ошибок

    nameLab->setBuddy(name);  // для навигации с помощью клавиатуры
    locationLab->setBuddy(location); // для навигации с помощью клавиатуры

    okButton = new  QPushButton("&Проверить");  // кнопка проверки и добавления
    cancelButton = new QPushButton("&Отмена");  // кнопка отмены

    connect(okButton, SIGNAL(clicked()), SLOT(checkInputSlot()));    // проверка перед добавлением
    connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));     // закрытие
    connect(location, SIGNAL(textEdited(QString)), SLOT(setEnableFalse()));  // при изменении поля для ввода ссылки меняется кнопка

    // скелет формы
    layout = new QGridLayout(this);
    layout->addWidget(nameLab, 0, 0);
    layout->addWidget(locationLab, 1, 0);
    layout->addWidget(name, 0, 1);
    layout->addWidget(location, 1, 1);
    layout->addWidget(errorMessage, 2, 0, 1, 2);
    errorMessage->setAlignment(Qt::AlignCenter);
    layout->addWidget(okButton, 3,0);
    layout->addWidget(cancelButton, 3, 1);


    //обработка ошибок
    connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            [=](QMediaPlayer::Error error){  qDebug("test error"); });

}


void DialogAdd::setEnableFalse() // изменение состояния при изменении поля ввода ссылки
{
    correctInput = false;
    correctUrl = false;
    okButton->setText("проверить");
    okButton->setEnabled(true);
}


void DialogAdd::updateTitleSlot() // проверка ссылки на работоспособность
{
    qDebug() << player->mediaStatus();

    if (player->mediaStatus() == QMediaPlayer::LoadingMedia | player->mediaStatus() == QMediaPlayer::StalledMedia)
    {
        errorMessage->setText("проверка сылки");
        correctUrl = false;
    } else if (player->mediaStatus()  ==  QMediaPlayer::BufferedMedia)
    {
        errorMessage->setText("сылка работает");
        correctUrl = true;
        updaterTitle->stop();

        okButton->setEnabled(true);
        okButton->setText("Добавить");

    } else
    {
        errorMessage->setText("сылка не работает");
        correctUrl = false;
        updaterTitle->stop();
    }
}


QString DialogAdd::getName() const
{
    return  name->text();
}

// ----------------------------------------------------------------------
QString DialogAdd::getLocation() const
{
    return  location->text();
}

void DialogAdd::checkInputSlot()
{

    //    qDebug() <<  "correctUrl " << correctUrl ;
    //     qDebug() <<  "correctInput  " << correctInput ;

    QString name = getName();
    QString loc = getLocation();

    bool contains = list->getMapTracks()->contains(loc);

    if (!(correctUrl & correctInput)) {
        if ( name.size() == 0 | loc.size() == 0)
        {
            if ( name.size() == 0  &  loc.size() == 0 )
                errorMessage->setText("Введите название и ссылку");
            else if ( name.size() == 0 )
                errorMessage->setText("Введите название");
            else if ( loc.size() == 0)
                errorMessage->setText("Введите адрес");

            correctInput = false;
            okButton->setEnabled(false);

        } else  if (proverkaContains & contains)
        {
            errorMessage->setText("такая ссылка уже есть");
            correctInput = false;
            okButton->setEnabled(false);
        } else {
            correctInput = true;

            player->setMedia(QUrl(loc));
            player->play();
            player->pause();
            updaterTitle->start(1000);

            okButton->setEnabled(false);
        }
    } else
    {
        okButton->setEnabled(true);
        accept();
    }
}




