#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mNetManager = new QNetworkAccessManager(this);
    connect(mNetManager, &QNetworkAccessManager::finished,
            this, &MainWindow::handleNetFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::openFile(const QString &filename)
{
    QFile f(filename);
    if (f.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while (!f.atEnd())
        {
            QByteArray line = f.readLine();
            qDebug("%s", qPrintable(line));
        }
    }
    else
    {
        qDebug("File open error");
    }

}

void MainWindow::openUrl(const QString &url)
{
    mNetManager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::testJson(QByteArray data)
{

    //URL: http://date.jsontest.com/
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();


    QString date = obj["date"].toString();
    qDebug() << "date: ";
    qDebug() << date;

    QString milliseconds_since_epoch = obj["milliseconds_since_epoch"].toString();
    qDebug() << "milliseconds_since_epoch: ";
    qDebug() << milliseconds_since_epoch;

    QString time = obj["time"].toString();
    qDebug() << "time: ";
    qDebug() << time;

    ui->label_2->setText(date);
    ui->label_3->setText(time);


}

void MainWindow::handleNetFinished(QNetworkReply *reply)
{
    if (reply->error()==QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        testJson(data);
        qDebug() << data;
    }
    else
        qDebug("Network error");
}

void MainWindow::on_pushButtonGetUrl_clicked()
{
    openUrl(ui->lineEditUrl->text());

}

