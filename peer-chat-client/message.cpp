#include "message.h"
#include "participantmanager.h"
#include <QRegExp>

QString Message::MessageRegex = "(\\[[\\w\\d: \\+\\-]+\\]){2}: [^\\[.\\]]+\\[.\\]";
QString Message::HeaderRegex = "(\\[[\\w\\d: \\+\\-]+\\]){2}: ";
QString Message::TrailerRegex = "\\[.\\]";
QString Message::NameAndDateRegex = "(\\[[\\w\\d: \\+\\-]+\\])";
QString Message::NameLastIndexRegex = "\\](\\[[\\w\\d: \\+\\-]+\\]): [^\\[.\\]]+\\[.\\]";
QString Message::DateLastIndexRegex = "\\]: [^\\[.\\]]+\\[.\\]";
QString Message::HeaderIndexRegex = "[^:\\[.\\]]+\\[.\\]";

QString Message::JoinMessage = "[Join]:";
QString Message::JoinFailMessage = "[Join][Failed]:";
QString Message::JoinRespondMessage = "[Join][Success]:";
QString Message::ChatMessage = "[Chat]:";
QString Message::Terminator = "[;;]";

Message::Message()
{

}

Message::Message(Participant* p, QString s)
{
    this->Receiver = p;
    this->Data = s;
    this->Time = QDateTime::currentDateTime();
}

void Message::setData(QString d)
{
    this->Data = d;
    this->Time = QDateTime::currentDateTime();
}

QString Message::toRawString()
{
    QString s = "[" + this->Sender->Name + "]["
    + this->Time.toString(Qt::ISODate) + "]: "
    + this->Data + "[.]";
    return s;
}

QByteArray Message::toByteArray()
{
    return this->toRawString().toUtf8();
}

bool Message::isEmpty()
{
    return this->Sender->isEmpty() && this->Data.isEmpty();
}

Message Message::fromRawString(QString s)
{
    auto index = 1;
    auto last = s.indexOf(QRegExp(NameLastIndexRegex));
    auto length = s.length() - index;
    auto raw = QString(s);

    this->Sender = ParticipantManager::getParticipant(raw.replace(0, index, "").replace(last - index, length, ""));

    index = this->Sender->Name.length() + 3;
    last = s.indexOf(QRegExp(DateLastIndexRegex));
    length = s.length() - index;
    raw = QString(s);

    this->Time = QDateTime::fromString(raw.replace(0, index, "").replace(last - index, length, ""), Qt::ISODate);

    index = s.indexOf(QRegExp(HeaderIndexRegex));
    last = s.indexOf(QRegExp(TrailerRegex));
    length = s.length() - index;
    raw = QString(s);

    this->Data = raw.replace(0, index, "").replace(last - index, length, "").trimmed();
    return *(this);
}
