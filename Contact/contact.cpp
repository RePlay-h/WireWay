#include "contact.h"
#include "ui_contact.h"

Contact::Contact(uint16_t id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contact),
    id_(std::move(id))
{
    ui->setupUi(this);
    ui->Data->setText(QString::number(id)); // set the contact id in the text field
}

const uint16_t& Contact::GetId() {
    return id_;
}

bool Contact::SetImg(quint32 pkt_size, std::vector<uint8_t> &buf) {

    // size of the part of the image in the packet
    pkt_size -= 2;

    // current size of contact's screen
    size_t size_of_screen = screen_bytes_.size();


    if(size_of_screen + pkt_size > 240'000) {

        qDebug() << "CLEAR";

        screen_bytes_.clear();
        return false;
    }

    std::copy(buf.begin() + 2, buf.end(), back_inserter(screen_bytes_));


    // if the size of the image in the buffer is equal to the desired one, then set it to the screen
    if(size_of_screen + pkt_size == 240'000) {

        QImage img(screen_bytes_.data(), 300, 200, QImage::Format_ARGB32);

        QPixmap pix = QPixmap::fromImage(img);

        ui->Screen->setPixmap(pix);

        emit ChangedPixmap(pix);

        screen_bytes_.clear();

        return true;

    }

    return false;
}

QLabel* Contact::GetScreen() {
    return ui->Screen;
}

inline void Contact::ChangedPixmap(QPixmap &pix) {}

Contact::~Contact()
{
    delete ui;
}
