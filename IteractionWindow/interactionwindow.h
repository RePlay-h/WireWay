#ifndef INTERACTIONWINDOW_H
#define INTERACTIONWINDOW_H

#include <QWidget>
#include <QThread>
#include <QMouseEvent>
#include <QList>
#include <QMap>
#include <QKeyEvent>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include <memory>

#include "./Handlers/handlers.h"

#define SIZE_OF_MAIN_SCREEN 5'760'000

class IoContextWorker;

namespace Ui {
class InteractionWindow;
}

class InteractionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InteractionWindow(QWidget *parent = nullptr);

    void Start(std::string address);

    ~InteractionWindow();

    void SendCommand();

    void ReadyReadSlot();

    void ScreenHandler();

protected:

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::InteractionWindow *ui;

    QUdpSocket *sock_;

    std::string address_;

    quint8 pkt_type_;

    quint32 pkt_size_;

    std::vector<uint8_t> remain_part_; // screen buf

    QByteArray cmd_pkt_;

    QMap<quint8, QByteArray> screen_parts_;
};

#endif // INTERACTIONWINDOW_H
