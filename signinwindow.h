#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>

#include "./MainWindow/mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SignInWindow; }
QT_END_NAMESPACE

class SignInWindow : public QMainWindow
{
    Q_OBJECT

public:
    SignInWindow(QWidget *parent = nullptr);
    ~SignInWindow();

protected:

    void keyPressEvent(QKeyEvent *e) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::SignInWindow *ui;

    std::unique_ptr<MainWindow> main_window;

    quint16 port_ = 8888;
    QString address_ = "127.0.0.1";

};
#endif // SIGNINWINDOW_H
