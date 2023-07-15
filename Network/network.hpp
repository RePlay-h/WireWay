#ifndef WireWay_NETWORK_H
#define WireWay_NETWORK_H

#include <QObject>
#include <QMessageBox>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>

#include <chrono>
#include <future>

#include "MainWindow/mainwindow.h"

/*
 * this file contains a class that deals with receiving packets
*/

class MainWindow;

namespace Ui {
class IoContextWorker;
}

using namespace boost;
using asio::ip::tcp;

class IoContextWorker : public QObject {

    Q_OBJECT

public:
    IoContextWorker(MainWindow* win, asio::io_context &io, tcp::socket &sock);

    void GetPacket();

signals:

    void PktHandler(std::vector<uint8_t> &pkt);

public slots:

    void process();

    void SendPacket(std::vector<uint8_t> &pkt);


private:
    MainWindow *win_;

    asio::io_context &io_;

    tcp::socket &sock_;
};



#endif
