#include "participant.h"

QString Participant::UnidentifiedName = "UnidentifiedName";
QString Participant::UnidentifiedHost = "UnidentifiedHost";
qint16 Participant::UnidentifiedPort = ~(0x0);

Participant::Participant()
{

}

bool Participant::isEmpty()
{
    return this->Name.isEmpty() && this->Host.isEmpty();
}

bool Participant::setHost(QString h, qint16 p)
{
    this->Host = h;
    this->Port = p;
    if(h != Participant::UnidentifiedHost && p != Participant::UnidentifiedPort)
        this->Status |= Participant::HostKnown;
    return true;
}

bool Participant::setName(QString n)
{
    this->Name = n;
    if(n != Participant::UnidentifiedName)
        this->Status |= Participant::NameKnown;
    return true;
}

bool Participant::isWellKnown()
{
    return this->Status == (Participant::HostKnown | Participant::NameKnown);
}
