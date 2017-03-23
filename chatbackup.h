#ifndef CHATBACKUP_H
#define CHATBACKUP_H

#include <QObject>

class chatBackup : public QObject
{
    Q_OBJECT
public:
    explicit chatBackup(QObject *parent = 0);
    enum SaveFormat {Json, Binary};

    void writeBackup();
    void readBackup();
};

#endif // CHATBACKUP_H
