#include "interactionwindow.h"
#include "ui_interactionwindow.h"

InteractionWindow::InteractionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InteractionWindow),
    sock_(new QUdpSocket(this)),
    pkt_size_(0)
{

    remain_part_.resize(SIZE_OF_MAIN_SCREEN);

    cmd_pkt_.resize(13);

    QObject::connect(sock_, &QUdpSocket::readyRead, this, &InteractionWindow::ReadyReadSlot);

    ui->setupUi(this);

    setWindowTitle("WireWay");

    setWindowIcon(QIcon(":/icon/icon.png"));
}

void InteractionWindow::Start(std::string address) {

    this->setMouseTracking(true);
    ui->Window->setMouseTracking(true);

    address_ = std::move(address);

    sock_->bind(QHostAddress::AnyIPv4, 1225);

}

inline void InteractionWindow::SendCommand() {

    sock_->writeDatagram(cmd_pkt_, QHostAddress(QString::fromStdString(address_)) , 1225);
    sock_->flush();

}

void InteractionWindow::ReadyReadSlot() {

    QHostAddress address;
    quint16 port;

    while (sock_->hasPendingDatagrams()) {

            QNetworkDatagram datagram = sock_->receiveDatagram();

            QByteArray part = datagram.data();
            qsizetype size_ = part.size();


            quint8 id = part[0];
            quint8 n = part[1];


            if(screen_parts_.size() != 0) {

                QByteArray &pt = screen_parts_.first();

                if(id != pt[0]) {
                    screen_parts_.clear();
                }

            }

            screen_parts_[n] = std::move(part);

            if(size_ < 57600 && screen_parts_.size() == screen_parts_.first()[2]) {

                ScreenHandler();
            }

        }

}

void InteractionWindow::ScreenHandler() {

    QByteArray scr;

    for(auto& part : screen_parts_) {
        scr.append(QByteArray(part.constData() + 3, part.size() - 3));
    }

    QPixmap pix;
    pix.loadFromData(scr, "JPEG");

    ui->Window->setPixmap(pix);
    screen_parts_.clear();

    ui->Window->show();



}

void InteractionWindow::mouseMoveEvent(QMouseEvent *event) {

    if(event->type() == QEvent::MouseMove) {


        QPoint res_pos = ui->Window->mapFromGlobal(event->globalPos());

        quint32 x = res_pos.x();
        quint32 y = res_pos.y();

        utilities::CreateMouseCommandPacket(cmd_pkt_, std::move(x), std::move(y));

        SendCommand();

        cmd_pkt_.clear();
    }
}

void InteractionWindow::mousePressEvent(QMouseEvent *event) {
    if(event->type() == QEvent::MouseButtonPress) {

        utilities::CreateMousePressPacket(cmd_pkt_, (event->buttons() == Qt::LeftButton) ? true : false);

        SendCommand();
    }
}

void InteractionWindow::mouseReleaseEvent(QMouseEvent *event) {
    if(event->type() == QEvent::MouseButtonRelease) {

        utilities::CreateMouseReleasePacket(cmd_pkt_, (event->buttons() == Qt::LeftButton) ? true : false);

        SendCommand();

    }
}


void InteractionWindow::keyPressEvent(QKeyEvent *event) {
    if(event->type() == QEvent::KeyPress) {

        qDebug() << event->key();

        int k = event->key();

        utilities::CreateKeyboardCommandPacket(cmd_pkt_, std::move(k));

        SendCommand();

        cmd_pkt_.clear();

    }
}

InteractionWindow::~InteractionWindow()
{
    delete ui;
}
