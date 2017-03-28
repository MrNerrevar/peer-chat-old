#ifndef ADDRESS_H
#define ADDRESS_H

#include <QObject>

class address : public QObject
{
    Q_OBJECT
public:
    explicit address(QObject *parent = 0);

    void writeAddress(const QJsonObject &json);
    void readAddress(QJsonObject &json) const;

};

#endif // ADDRESS_H
