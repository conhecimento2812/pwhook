#ifndef UTILS_H
#define UTILS_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
#endif

#include <iostream>
#include <QTextCodec>
#include <QDateTime>
#include <QString>
#include <IO/Octets.h>

class Utils
{
public:
    static QString toUtf8(Octets octets);
    static QString toASCII(Octets octets);
    static QByteArray toUtf16LE(QByteArray text);
    static Octets fromUtf8(QByteArray text);
    static void print(QString text);
    static void danger(QString text);
    static QString getIp(int ip);
    static Octets emptyOctets();
};

#endif // UTILS_H
