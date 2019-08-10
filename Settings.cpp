#include "Settings.h"

QString Settings::path = "";

int Settings::websocket_port = 5700;

QString Settings::Z_pF22bgVxJ = "";

bool Settings::enable_global = false;
bool Settings::enable_broadcast = false;

QString Settings::gdeliveryd_host = "127.0.0.1";
quint16 Settings::gdeliveryd_port = 29100;

QString Settings::gprovider_host = "127.0.0.1";
quint16 Settings::gprovider_port = 29300;

void Settings::Init(const QString &file)
{
    QSettings settings(file + "/pwchat.conf", QSettings::IniFormat);

    path = file;

	Z_pF22bgVxJ = settings.value("pwchat/license").toString();

    websocket_port = settings.value("pwchat/port").toInt();

    enable_global = settings.value("pwchat/global").toBool();
    enable_broadcast = settings.value("pwchat/broadcast").toBool();

    gdeliveryd_host = settings.value("gdeliveryd/host").toString();
    gdeliveryd_port = static_cast<quint16>(settings.value("gdeliveryd/port").toInt());

    gprovider_host = settings.value("gprovider/host").toString();
    gprovider_port = static_cast<quint16>(settings.value("gprovider/port").toInt());
}
