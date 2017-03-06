#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QObject>

class Participant
{
private:
    QString _name;
    QString _connection;
public:
    Participant();
    Participant(QString n, QString c);
    QString getName();
    QString getConnection();
};

#endif // PARTICIPANT_H
