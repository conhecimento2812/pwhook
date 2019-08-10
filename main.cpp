#include <QCoreApplication>
#include "echoserver.h"
#include "Utils.h"
#include "Settings.h"
#include "Server.h"
#include "Network/GDeliveryd.h"
#include "Workers/BroadcasterWorker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Utils::print("PWChat - Discord: Conhecimento#2812 | v0.2.0");
	Utils::print("Build for Halysim");
    Utils::print(QString("Build date: %1 at %2").arg(__DATE__).arg(__TIME__));

    Settings::Init(a.applicationDirPath());
	
    Server server;
    GDeliveryd::Instance()->connect();
    BroadcasterWorker broadcast;

    EchoServer *chat = new EchoServer(static_cast<quint16>(Settings::websocket_port), false);
    QObject::connect(chat, &EchoServer::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
