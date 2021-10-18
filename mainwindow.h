#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool openFile(const QString& filename);
    void openUrl(const QString& url);
    void testJson(QByteArray data);
protected slots:
    void handleNetFinished(QNetworkReply* reply);
private slots:
    void on_pushButtonGetUrl_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* mNetManager=NULL;
};
#endif // MAINWINDOW_H
