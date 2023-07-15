#include "handlers.h"

void utilities::CreateConnectPacket(QByteArray &buf, uint16_t id)
{
    buf.resize(7);

    //type
    buf[0] = CONNECT_BYTE;

    //size
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    buf[4] = 0x02;

    //id
    buf[5] = (id >> 8);
    buf[6] = id;
}

void utilities::CreateInterceptPacket(QByteArray &buf, uint16_t id)
{
    buf.resize(7);

    //type
    buf[0] = INTERCEPT_BYTE;

    //size
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    buf[4] = 0x02;

    //id of contact
    buf[5] = (id >> 8);
    buf[6] = id;
}

void utilities::CreateDisconnectPacket(QByteArray &buf) {

    buf.resize(5);

    buf[0] = DISCONNECT_BYTE;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    buf[4] = 0x00;
}

<<<<<<< Updated upstream
void handlers::ConnackHandler(std::vector<uint8_t> &buf) {

}

bool handlers::IntercaptHandler(std::vector<uint8_t> &buf) {


    return (buf[0] & 0x0F);
}

=======
void utilities::CreateMouseCommandPacket(QByteArray &buf, quint32 x, quint32 y) {

    buf.resize(9);

    buf[0] = COMMAND_BYTE;

    // set X
    buf[1] = uint8_t(x >> 24);
    buf[2] = uint8_t(x >> 16);
    buf[3] = uint8_t(x >> 8);
    buf[4] = uint8_t(x);

    uint32_t x1 = (buf[1] << 24);
    x1 |= (buf[2] << 16);
    x1 |= (buf[3] << 8);
    x1 |= (buf[4]);

    // set Y
    buf[5] = uint8_t(y >> 24);
    buf[6] = uint8_t(y >> 16);
    buf[7] = uint8_t(y >> 8);
    buf[8] = uint8_t(y);
}

void utilities::CreateMousePressPacket(QByteArray &buf, bool is_left) {

    buf.resize(5);

    buf[0] = COMMAND_BYTE;
    buf[0] |= 0x03;

    buf[1] |= is_left;
    buf[2] = 0x00;
    buf[3] = 0x00;
    buf[4] = 0x00;

}

void utilities::CreateMouseReleasePacket(QByteArray &buf, bool is_left) {

    buf.resize(5);

    buf[0] = COMMAND_BYTE;
    buf[0] |= 0x04;

    buf[1] |= is_left;
    buf[2] = 0x00;
    buf[3] = 0x00;
    buf[4] = 0x00;
}

void utilities::CreateKeyboardCommandPacket(QByteArray &buf, int k) {

    buf.resize(9);

    buf[0] = COMMAND_BYTE;
    buf[0] |= 0x01;

    buf[1] = k >> 24;
    buf[2] = k >> 16;
    buf[3] = k >> 8;
    buf[4] = k;

    buf[5] = 0x00;
    buf[6] = 0x00;
    buf[7] = 0x00;
    buf[8] = 0x00;
}




>>>>>>> Stashed changes
