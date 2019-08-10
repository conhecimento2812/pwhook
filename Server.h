#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>

class Server : QObject
{
    Q_OBJECT
public:
    explicit Server(QObject  *parent = nullptr);
    //void Init();

private:
    QTcpSocket *socket = nullptr;

public slots:
    //void readyToRead();

};

#endif // SERVER_H