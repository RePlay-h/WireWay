#include "Network/network.hpp"

IoContextWorker::IoContextWorker(MainWindow* win, asio::io_context &io, tcp::socket &sock)
    : win_(win), io_(io), sock_(sock)
{
    QObject::connect(this, &IoContextWorker::PktHandler, win_, &MainWindow::PacketHandler);
}

void IoContextWorker::process() {

    io_.run(); // waiting for stop to be called on another thread

    GetPacket();
}


void IoContextWorker::GetPacket() {
    while(sock_.is_open()) {

            std::vector<uint8_t> buf(5);
            system::error_code ec;

            // get header of packet
            sock_.receive(asio::buffer(buf, 5), 0, ec);

            if(ec != boost::system::errc::success) {
                break;
            }

            uint32_t remaining_len = (buf[1] << 24);
            remaining_len |= (buf[2] << 16);
            remaining_len |= (buf[3] << 8);
            remaining_len |= buf[4];


            if(remaining_len != 0) {
                // Get the rest of the package

                buf.resize(remaining_len + 5);

                // get remaining part of packet
                sock_.receive(asio::buffer(buf.data() + 5, remaining_len), 0, ec);

                if(ec != boost::system::errc::success) {
                    break;
                }
            }

            emit PktHandler(buf);
        }

    QThread::currentThread()->quit();
}

inline void IoContextWorker::PktHandler(std::vector<uint8_t> &pkt) {}

void IoContextWorker::SendPacket(std::vector<uint8_t> &pkt) {

    system::error_code ec;

    sock_.send(asio::buffer(pkt, pkt.size()), 0, ec);

    if(ec != system::errc::success) {
    }
}
