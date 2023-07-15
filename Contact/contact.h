#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>

#include <cstdint>
#include <vector>

/*
 * file that contains the contact widget class
*/

namespace Ui {
class Contact;
}

class Contact : public QWidget
{
    Q_OBJECT

public:
    explicit Contact(uint16_t id, QWidget *parent = nullptr);

    const uint16_t& GetId();

    bool SetImg(quint32 pkt_size, std::vector<uint8_t> &buf);

    QLabel* GetScreen();

    ~Contact();

signals:
   void ChangedPixmap(QPixmap &pix);

private:
    Ui::Contact *ui;
    uint16_t id_;

    std::vector<uint8_t> screen_bytes_;
};

#endif // CONTACT_H
