#include "participant.h"

Participant::Participant()
{

}

Participant::Participant(QString n, QString c, qint16 p)
{
    this->Name = n;
    this->Host = c;
    this->Port = p;
    this->Status = n.isEmpty() ? ParticipantStatus::HostUnknown : ParticipantStatus::HostKnown;
}


bool Participant::isEmpty()
{
    return this->Name.isEmpty() && this->Host.isEmpty();
}
