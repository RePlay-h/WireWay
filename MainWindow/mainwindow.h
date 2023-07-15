#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define S_ADDRESS "127.0.0.1"

#include <QWidget>
#include <QMessageBox>
#include <QListWidget>
#include <QTcpSocket>

#include <memory>
#include <vector>
#include <algorithm>

#include "./Handlers/handlers.h"
#include "./Contact/contact.h"
<<<<<<< Updated upstream
#include "./Network/network.hpp"
=======
#include "./IteractionWindow/interactionwindow.h"
>>>>>>> Stashed changes

/*
 * This file contains a class that manages the application window.
 * The class also sends CONNECT, INTERCEPT, DISCONNECT packets and receives a CONNACK packet
*/

<<<<<<< Updated upstream
class IoContextWorker;

using namespace std::chrono_literals;

using namespace boost;
using asio::ip::tcp;
=======
class InteractionWindow;

>>>>>>> Stashed changes

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(uint16_t id, QWidget *parent = nullptr);

    bool SendConnectPacket();

    void SendDisconnectPacket();

    void Start(); // this function is called to pop up the application window and stop the io_context event handler

    void SetScreen(); // sets a picture for one of the contact screens

    void CreateContact(uint16_t id);

    void DeleteContact(uint16_t id);

    void DestroyTcpConnection();

    ~MainWindow();



private slots:

    void ReadyReadSlot();

    void on_Connect_clicked();

    void on_Contacts_itemDoubleClicked(QListWidgetItem *item);

    void ErrorHandler(QAbstractSocket::SocketError socketError);

public slots:

    void SetPixmap(QPixmap &pix); // set image to home screen

    void PacketHandler();

signals:

    void SendPacket();

private:
    Ui::MainWindow *ui;

    QTcpSocket *sock_;

    quint16 id_;

    quint8 pkt_type_;

    quint32 pkt_size_;

    std::vector<uint8_t> remain_part_;

    // the variable contains a pointer to the contact list object,
    // the image of which is broadcast on the main screen
    QListWidgetItem *current_screen_item_ = nullptr;

<<<<<<< Updated upstream
    QThread thr_;

    std::unique_ptr<IoContextWorker> worker_;
=======
    std::unique_ptr<InteractionWindow> window_; // pointer to interaction screen with contact
>>>>>>> Stashed changes
};


#endif // MAINWINDOW_H
