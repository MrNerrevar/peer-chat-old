#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class login;
}

class Peer;
class Message;
class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);

    void sendAuthRequest(Message*);


private:
    Ui::login *ui;
    Peer* peer;
};

#endif // LOGIN_H
