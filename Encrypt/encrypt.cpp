#include "encrypt.h"
#include "ui_encrypt.h"
#include "botanwrapper.h"


#include<QDebug>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<cstring>
#include<memory>
#include<QMessageBox>
#include<QFileDialog>
#include<QInputDialog>

#include<QTimer>
using namespace std;
using namespace Botan;

Encrypt::Encrypt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Encrypt)
{
    QFile::copy(":/new/prefix1/a.mp3", QDir::tempPath()+"/a.mp3");

    player = new QMediaPlayer;

    //player->setMedia(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    //
    player->setMedia(QUrl::fromLocalFile(QDir::tempPath()+"/a.mp3"));
    player->setVolume(50);
    this->setFixedWidth(383);
    this->setFixedHeight(161);
    this->setFixedSize(this->size());

   // timer();
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),SLOT(stateChanged(QMediaPlayer::State)));
    connect(player,SIGNAL(positionChanged(qint64)),SLOT(positionChanged(qint64)));
    player->play();

    ui->setupUi(this);
}

Encrypt::~Encrypt()
{
    delete ui;
}
/*
void Encrypt::timer(){

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Play()));
    timer->start(1000);

}
*/

void Encrypt::positionChanged(qint64 position){
    ui->progressBar_2->setValue((float(position)/float(player->duration()))*100);
    //qDebug()<<(float(position)/float(player->duration()));

}

void Encrypt::stateChanged(QMediaPlayer::State state){

    try{


            if(state==player->StoppedState){
                player->play();

            }




    }catch(Exception ex){


    }

}

void Encrypt::decrypts(QString saltspath,QString FIlepath,QString pass){
    QString cDecrypted = FIlepath;
    cDecrypted.remove(cDecrypted.length()-4,4);
    ui->progressBar->setValue(60);
    BotanWrapper cWrapper2;
    cWrapper2.setPassword(pass);
    cWrapper2.setSalt(saltspath);


    if(cWrapper2.DecryptFile(FIlepath,cDecrypted)){
        ui->progressBar->setValue(100);
        QMessageBox::information(this,tr("Done"),"File Decryption Complete");
    }else{
        ui->progressBar->setValue(0);
        QFile::remove(cDecrypted);
        QMessageBox::information(this,tr("Abort"),"File Decryption incomplete");

    }


}

void Encrypt::encrypts(QString saltspath,QString FIlepath,QString pass){
    BotanWrapper cWrapper1;

    QString cEncrypted = FIlepath+".enc";

    ui->progressBar->setValue(60);
    cWrapper1.setPassword(pass);
    cWrapper1.setSalt(saltspath);




    if(cWrapper1.EncryptFile(FIlepath,cEncrypted)){
        ui->progressBar->setValue(100);
        QMessageBox::information(this,tr("Done"),"File Encryption Complete");
    }else{
        ui->progressBar->setValue(0);
        QMessageBox::information(this,tr("Abort"),"File Encryption incomplete");
    }



}

void Encrypt::on_pushButton_clicked()
{
        ui->progressBar->setValue(10);
        QString filename=QFileDialog::getOpenFileName(
                    this,
                    tr("Select the File"),
                    QApplication::applicationDirPath(),
                    "All Files (*.*)"
                    );
        ui->progressBar->setValue(20);
        if(filename.isEmpty()){
            ui->progressBar->setValue(0);
            QMessageBox::information(this,tr("Abort"),"File Encryption Abort");
        }else{
        QString certpath = QFileDialog::getOpenFileName(
                    this,
                    tr("Select the Certificate"),
                    QApplication::applicationDirPath(),
                    "Certficate Files (*.cer);;Certificate Files (*.crt)"
                    );
            ui->progressBar->setValue(25);
            if(certpath.isEmpty()){
                ui->progressBar->setValue(0);
                QMessageBox::information(this,tr("Abort"),"File Encryption Abort");
            }else{

                bool ok;
                QString password = QInputDialog::getText(this, tr("Enter the password"),
                                                          tr("Password:"), QLineEdit::Password,
                                                          "", &ok);
                bool ok1;
                QString password1;
                if(ok && !password.isEmpty()){

                    password1 = QInputDialog::getText(this, tr("Enter the password Again"),
                                                          tr("Password:"), QLineEdit::Password,
                                                          "", &ok1);
                }
                if ((ok && !password.isEmpty())&&(ok1&&!password1.isEmpty())&&(password==password1)){


                    ui->progressBar->setValue(40);
                    encrypts(certpath,filename,password);
                }else{
                    ui->progressBar->setValue(0);
                    QMessageBox::information(this,tr("Abort"),"File Encryption Abort");
                }


            }
        }

}

void Encrypt::on_pushButton_2_clicked()
{
    ui->progressBar->setValue(0);
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Select the File"),
                QApplication::applicationDirPath(),
                "Encrypted Files (*.enc)"
                );
    if(filename.isEmpty()){
        ui->progressBar->setValue(0);
        QMessageBox::information(this,tr("Abort"),"File Decryption Abort");
    }else{
        ui->progressBar->setValue(20);
        QString certpath = QFileDialog::getOpenFileName(
                    this,
                    tr("Select the Certificate"),
                    QApplication::applicationDirPath(),
                    "Certficate Files (*.cer);;Certificate Files (*.crt)"
                );

        if(certpath.isEmpty()){
            ui->progressBar->setValue(0);
            QMessageBox::information(this,tr("Abort"),"File Decryption Abort");
        }else{
            ui->progressBar->setValue(30);
            bool ok;
            QString password = QInputDialog::getText(this, tr("Enter the password"),
                                                      tr("Password:"), QLineEdit::Password,
                                                      "", &ok);
            if (ok && !password.isEmpty()){
                ui->progressBar->setValue(40);
                decrypts(certpath,filename,password);
            }else{
                ui->progressBar->setValue(0);
                QMessageBox::information(this,tr("Abort"),"File Decryption Abort");
            }


        }
    }




}
