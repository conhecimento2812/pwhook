#include "echoserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <IO/Octets.h>
#include <IO/OctetsStream.h>
#include <Utils.h>
#include <Settings.h>

QT_USE_NAMESPACE

EchoServer::EchoServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &EchoServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &EchoServer::closed);
    }

    socket = new QTcpSocket();
    socket->connectToHost(Settings::gdeliveryd_host, Settings::gdeliveryd_port);
    if(!socket->waitForConnected(5000)) {
        Utils::print("Gdeliveryd offline");
        exit(EXIT_FAILURE);
    }
    connect(socket, &QTcpSocket::readyRead, this, &EchoServer::readyRead, Qt::DirectConnection);
    connect(socket, &QTcpSocket::disconnected, this, &EchoServer::unconnected, Qt::DirectConnection);
}

EchoServer::~EchoServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void EchoServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    connect(pSocket, &QWebSocket::disconnected, this, &EchoServer::socketDisconnected);
    m_clients << pSocket;
}

void EchoServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Message received:" << message;
    if (pClient) {
        pClient->sendTextMessage(message);
    }
}

void EchoServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void EchoServer::readyRead()
{
    QByteArray data = socket->readAll();
    try {
        OctetsStream stream(data, false);
        uint opcode = stream.uncompact_uint32();
        stream.uncompact_uint32();

        QByteArray name;
        QByteArray message;

        if(opcode == 133 && Settings::enable_global) {
            stream.readByte();
            stream.readByte();
            stream.readInt32();
            name = QByteArray::fromStdString(stream.readOctet().text.toStdString()).replace(QChar::Null, "");
            message = QByteArray::fromStdString(stream.readOctet().text.toStdString()).replace(QChar::Null, "");

            for(int i = 0; i < m_clients.length(); i++) {
                m_clients[i]->sendTextMessage(name + ":" + message);
            }
        }

        else if (opcode == 120 && Settings::enable_broadcast) {
            stream.readByte();
            stream.readByte();
            stream.readInt32();
            name = "";
            message = QByteArray::fromStdString(stream.readOctet().text.toStdString()).replace(QChar::Null, "");

            for(int i = 0; i < m_clients.length(); i++) {
                m_clients[i]->sendTextMessage(name + ":" + message);
            }
        }

    }
    catch (...) {
        Utils::print("Protocol parse error");
    }
}

void EchoServer::unconnected()
{
    Utils::print("pwhook::OnAbortSession");
}
