#include "message.h"

Message::Message(QObject *parent) : QObject(parent)
{

}

Message::Message(Participant s, Participant r)
{
    this->_sender = s;
    this->_receiver = r;
    this->_data = "";
}

void Message::setData(QString d)
{
    this->_data = d;
    this->_time = QDateTime::currentDateTime();
}

QString Message::toRawString()
{
    QString s = "[" + this->_sender.getName() + "::"
    + this->_receiver.getName() + "]["
    //+ this->_time.toString() + "]: "
    + this->_data;
    return s;
}

QByteArray Message::toByteArray()
{
    return this->toRawString().toUtf8();
}
