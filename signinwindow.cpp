#include "signinwindow.h"
#include "./ui_signinwindow.h"

SignInWindow::SignInWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignInWindow)
{
    ui->setupUi(this);

    setWindowTitle("WireWay");

    setWindowIcon(QIcon(":/icon/icon.png"));
}

SignInWindow::~SignInWindow()
{
    delete ui;
}

void SignInWindow::keyPressEvent(QKeyEvent *e) {

    if(e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
        on_pushButton_clicked();
    }
}

void SignInWindow::on_pushButton_clicked()
{

    if(ui->Login->text().isEmpty()) {
        QMessageBox::warning(this, "Ooooops...", "login or password not entered!");
        return;
    }

    quint16 id = ui->Login->text().toInt();

    main_window = std::make_unique<MainWindow>(id);

    main_window->Start();

    // Send Connect packet
    // The function returns 0 if the packet
    // or part of it was not sended or the server closed the connection
    if(!main_window->SendConnectPacket()) {
        QMessageBox::warning(this, "Ooooops...", "An error occurred while connecting to the server");
        return;
    }
    hide();
}

