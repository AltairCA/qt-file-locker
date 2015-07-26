#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <QMainWindow>
#include<QMediaPlayer>
namespace Ui {
class Encrypt;
}

class Encrypt : public QMainWindow
{
    Q_OBJECT

public:
    explicit Encrypt(QWidget *parent = 0);
    ~Encrypt();

    QMediaPlayer *player;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
public slots:
    //void Play();
    void stateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);

private:
    Ui::Encrypt *ui;
    void encrypts(QString saltspath,QString FIlepath,QString pass);
    void decrypts(QString saltspath,QString FIlepath,QString pass);


   // void timer();
};

#endif // ENCRYPT_H
