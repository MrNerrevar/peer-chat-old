#include "participant.h"

Participant::Participant()
{

}

Participant::Participant(QString n, QString c)
{
    this->_name = n;
    this->_connection = c;
}

QString Participant::getName()
{
    return this->_name;
}

QString Participant::getConnection()
{
    return this->_connection;
}
