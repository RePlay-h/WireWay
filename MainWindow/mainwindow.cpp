#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(quint16 id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    id_(std::move(id)),
    pkt_size_(0),
    pkt_type_(0)
{

    sock_ = new QTcpSocket(this);
    ui->setupUi(this);

    setWindowTitle("WireWay");

    setWindowIcon(QIcon(":/icon/icon.png"));

    QObject::connect(sock_, &QTcpSocket::readyRead, this, &MainWindow::ReadyReadSlot);
}


void MainWindow::Start() {

    sock_->connectToHost(S_ADDRESS, 8888);

    show();
}

void MainWindow::ErrorHandler(QAbstractSocket::SocketError socketError) {

    QMessageBox::critical(this, "Oooops...", "Error occurred while communicating with the server!");

    DestroyTcpConnection();

}

void MainWindow::DestroyTcpConnection() {

    QObject::disconnect(sock_, &QTcpSocket::readyRead, this, &MainWindow::ReadyReadSlot);
    QObject::disconnect(sock_, &QTcpSocket::disconnected, sock_, &QTcpSocket::deleteLater);

    if(sock_->isOpen()) {
        SendDisconnectPacket();
    }

}

bool MainWindow::SendConnectPacket()
{
    QByteArray pkt;

    // create CONNECT packet
    utilities::CreateConnectPacket(pkt, id_);


    // send CONNECT packet
    if(sock_->write(pkt) == -1) {
        QMessageBox::critical(this, "Oooops...", "An error occurred while communicating with the server");
        return false;
    }

    return true;
}

void MainWindow::ReadyReadSlot() {

    QDataStream in(sock_);
    in.setVersion(QDataStream::Qt_6_3);

    for(;;) {


        if(pkt_size_ == 0) {

            if(sock_->bytesAvailable() < 5) {
                break;
            }

            // set packet type and packet size
            in >> pkt_type_;
            in >> pkt_size_;

        }

        if(sock_->bytesAvailable() < pkt_size_) {
            break;
        }

        // set the rest of the packet
        while(sock_->bytesAvailable()) {
            quint8 byte;
            in >> byte;

            remain_part_.push_back(byte);
        }

        break;
    }

    PacketHandler();
}

void MainWindow::CreateContact(uint16_t id) {

    // create item and Widget
    QListWidgetItem *item = new QListWidgetItem();
    Contact *wid = new Contact(std::move(id), ui->Contacts);

    item->setSizeHint(QSize(1000, 300));

    ui->Contacts->addItem(item);

    ui->Contacts->setItemWidget(item, wid);

    ui->Contacts->show();
}

void MainWindow::DeleteContact(uint16_t id) {

    // iterate over all contacts to find the right one
    for(size_t i = 0; i < ui->Contacts->count(); ++i) {

        QListWidgetItem *item = ui->Contacts->item(i);

        QWidget* wid = ui->Contacts->itemWidget(item);
        Contact* con = dynamic_cast<Contact*>(wid);

        if(con->GetId() == id) {

            // delete contact
            delete item;
            delete con;
            break;
        }
    }
    ui->Contacts->show();

}

void MainWindow::PacketHandler() {

    switch (pkt_type_ & 0xF0) {

    case CONNACK_BYTE: {

        if(pkt_type_ & 0x0F) {
            QMessageBox::critical(this, "Oooops...", "Failed to connect to the server");
            DestroyTcpConnection();
            return;
        }

        for(quint32 i = 0; i < pkt_size_; i += 2) {

            uint16_t id = ((remain_part_[i] << 8) | remain_part_[i+1]);

            CreateContact(id);

        }
        break;
    }

    case INTERCAPT_BYTE:

        // if the eighth bit of the first byte is 1,
        // then server did not find the previously specified id
<<<<<<< Updated upstream
        if(!(buf[0] & 0x0F)) {
            // Create Working Window
=======
        if(!(pkt_type_ & 0x0F)) {

            window_ = std::make_unique<InteractionWindow>();

            window_->Start(std::string(remain_part_.begin(), remain_part_.end()));

            DestroyTcpConnection();

            window_->show();

            hide();

>>>>>>> Stashed changes
        }
        break;
    case SCREEN_BYTE:
        SetScreen();

        break;
    case PUBLISH_BYTE:

        uint16_t id = ((remain_part_[0] << 8) | remain_part_[1]);

        if(!(pkt_type_ & 0x0F)) {

            CreateContact(id);
        }
        else {
            DeleteContact(id);
        }
        break;

    }

    pkt_type_ = 0;
    pkt_size_ = 0;
    remain_part_.clear();
}

void MainWindow::SetScreen() {

    uint16_t id = ((remain_part_[0] << 8) | remain_part_[1]);

    // Looking for the right contact
    for(size_t i = 0; i < ui->Contacts->count(); ++i) {
        QListWidgetItem *item = ui->Contacts->item(i);

        QWidget* wid = ui->Contacts->itemWidget(item);
        Contact* con = dynamic_cast<Contact*>(wid);

        if(con->GetId() == id) {
            bool is_show = con->SetImg(pkt_size_, remain_part_);
            if(is_show) {
                con->show();
                ui->Contacts->show();
            }
            break;
        }
    }
}

void MainWindow::SendDisconnectPacket() {

    QByteArray pkt;

    utilities::CreateDisconnectPacket(pkt);

    sock_->write(pkt);
    sock_->flush();

}

MainWindow::~MainWindow()
{
<<<<<<< Updated upstream
    SendDisconnectPacket();

    sock_.close();

    thr_.wait();
=======

    DestroyTcpConnection();
>>>>>>> Stashed changes

    delete ui;
}

void MainWindow::on_Connect_clicked()
{
    QByteArray pkt;
    uint16_t id;


    if(current_screen_item_ != nullptr) {
        QWidget* wid = ui->Contacts->itemWidget(current_screen_item_);
        Contact* con = dynamic_cast<Contact*>(wid);

        id = con->GetId();
    }
    else {
        QMessageBox::warning(this, "Oooops...", "Choose a contact");
        return;
    }

    utilities::CreateInterceptPacket(pkt, id);

    // send INTERCEPT
    if(sock_->write(pkt) == -1) {
        QMessageBox::critical(this, "Oooops...", "Server not responding");
        return;
    }

}

void MainWindow::SetPixmap(QPixmap &pix) {
    ui->Screen->setPixmap(pix);
    ui->Screen->show();
}

void MainWindow::on_Contacts_itemDoubleClicked(QListWidgetItem *item) {

   QWidget* wid = ui->Contacts->itemWidget(current_screen_item_);
   Contact* con = dynamic_cast<Contact*>(wid);

   // reset the connection to the previous contact list object
   if(current_screen_item_ != nullptr) {
        QObject::disconnect(con, SIGNAL(ChangedPixmap(QPixmap&)), this, SLOT(SetPixmap(QPixmap&)));
   }

   current_screen_item_ = item;
   wid = ui->Contacts->itemWidget(current_screen_item_);
   con = dynamic_cast<Contact*>(wid);

   ui->Screen->setPixmap(con->GetScreen()->pixmap());
   QObject::connect(con, SIGNAL(ChangedPixmap(QPixmap&)), this, SLOT(SetPixmap(QPixmap&)));
}


