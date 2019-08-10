#ifndef SETTINGS_H
#define SETTINGS_H

#include <QVariant>
#include <QSettings>
#include <QMetaEnum>
#include <QRegExp>
#include <QList>
#include <Utils.h>

class Settings
{
public:
    static void Init(const QString &file);

    static QString path;

	static QString Z_pF22bgVxJ;
    static int websocket_port;

    static bool enable_global;
    static bool enable_broadcast;

    static QString gdeliveryd_host;
    static quint16 gdeliveryd_port;

    static QString gprovider_host;
    static quint16 gprovider_port;
};

#endif // SETTINGS_H
