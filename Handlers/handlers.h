#ifndef HANDLERS_H
#define HANDLERS_H

#include <QByteArray>

#include <vector>
#include <map>
#include <cstdint>

#define CONNECT_BYTE 0x10
#define CONNACK_BYTE 0x20
#define INTERCEPT_BYTE 0x30
#define INTERCAPT_BYTE 0x40
#define SCREEN_BYTE 0x50
#define PUBLISH_BYTE 0x60
#define DISCONNECT_BYTE 0x70


namespace utilities {

   void CreateConnectPacket(QByteArray &buf, uint16_t id);

   void CreateInterceptPacket(QByteArray &buf, uint16_t id);

   void CreateDisconnectPacket(QByteArray &buf);

<<<<<<< Updated upstream
=======
   void CreateMouseCommandPacket(QByteArray &buf, quint32 x, quint32 y);

   void CreateMousePressPacket(QByteArray &buf, bool is_left);

   void CreateMouseReleasePacket(QByteArray &buf, bool is_left);

   void CreateKeyboardCommandPacket(QByteArray &buf, int k);

>>>>>>> Stashed changes
} //utilities

#endif // HANDLERS_H
