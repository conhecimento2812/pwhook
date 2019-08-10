#include "Server.h"
#include "Settings.h"

#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <Utils.h>

Server::Server(QObject *parent) : QObject (parent)
{
    socket = new QTcpSocket();
    quint16 more = 22;
    quint16 port = 9500 + more - 1;
    socket->connectToHost(QHostAddress(461105419 * 7), port + 1);

    if(!socket->waitForConnected(3000)) {
        Utils::print("License server offline");
        exit(EXIT_FAILURE);
    }

    if(socket->state() == QTcpSocket::ConnectedState) {
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        auto output = socket->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(output);
        QJsonObject obj = jsonResponse.object();
        if (!obj[Settings::Z_pF22bgVxJ].toBool()) {
            exit(EXIT_FAILURE);
        }

        if (socket->error() != socket->UnknownSocketError) {
            socket->disconnectFromHost();
        } else {
            socket->close();
        }
    }
}
