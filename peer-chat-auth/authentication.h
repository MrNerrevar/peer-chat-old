#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include <QObject>

class Peer;
class Message;
class DbManager;
class Authentication : public QObject
{
    Q_OBJECT
public:
    Authentication();

public slots:
    void checkUser(Message*);
    void sendAuthenticate(QString);

private:
    void initParticipants();

    Peer* peer;
    DbManager* dbmanager;
};

#endif // AUTHENTICATION_H
