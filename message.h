#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "participant.h"
#include <QDateTime>

class Message : public QObject
{
    Q_OBJECT
private:
    Participant _sender;
    //Participant _receiver;
    QDateTime _time;
    QString _data;
public:
    explicit Message(QObject *parent = 0);
    Message(Participant s, Participant r);
    void setData(QString d);
    QString toRawString();
    QByteArray toByteArray();
signals:

public slots:
};

#endif // MESSAGE_H
