#include "signinwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    SignInWindow w;
    w.show();

    return a.exec();
}
