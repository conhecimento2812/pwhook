#include "Utils.h"

QString Utils::toUtf8(Octets octets)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    return codec->fromUnicode(octets.text).mid(0, octets.length);
}

QString Utils::toASCII(Octets octets)
{
    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-1");
    return codec->fromUnicode(octets.text).mid(0, octets.length);
}

QByteArray Utils::toUtf16LE(QByteArray text)
{
    QTextCodec *codec_utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec *codec_utf16le = QTextCodec::codecForName("UTF-16LE");
    return codec_utf16le->fromUnicode(codec_utf8->toUnicode(text)).remove(0, 2);
}

Octets Utils::fromUtf8(QByteArray text)
{
    Octets o;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    o.text = codec->fromUnicode(text.data());
    o.length = o.text.length();
    return o;
}

void Utils::print(QString text)
{
    QDateTime date = QDateTime::currentDateTime();
    std::cout << QString("[PWCHAT][%1] %2").arg(date.toString("hh:mm:ss")).arg(text).toStdString() << std::endl;
}

void Utils::danger(QString text)
{
    auto output = QString(" \033[0m \033[1;31m%1\033[0m").arg(text);
    print(output);
}

QString Utils::getIp(int ip)
{
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;

    return QString("%1.%2.%3.%4").arg(bytes[3]).arg(bytes[2]).arg(bytes[1]).arg(bytes[0]);
}

Octets Utils::emptyOctets()
{
    Octets o;
    o.text = QByteArray();
    o.length = 0;
    return o;
}
