#include "Server.h"

namespace QiDiTu {
Server::Server(QObject *parent)
    : QObject(parent)
{
    QObject::connect(&socket, &QUdpSocket::readyRead, this, &Server::receive);
    timer.setInterval(1000);
    timer.setSingleShot(true);
    QObject::connect(&timer, &QTimer::timeout, this, &Server::timeout);
}

QVariantList Server::networkList()
{
    QVariantList list;
    for(auto interface : QNetworkInterface::allInterfaces()) {
        //此网络接口被激活并且正在运行并且不是回环地址
        if(interface.flags().testFlag(QNetworkInterface::IsUp)
                && interface.flags().testFlag(QNetworkInterface::IsRunning)
                && !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            QString hardwareAddress = interface.hardwareAddress();
            for(auto entrie: interface.addressEntries()) {
                QHostAddress hostAddress = entrie.ip();
                bool ok = false;
                hostAddress.toIPv4Address(&ok);
                if(!ok) {
                    continue;
                }
                QString ipv4 = hostAddress.toString();
                list.append(QVariantMap{{"MAC", hardwareAddress}, {"IPV4", ipv4}});
            }
        }
    }
    return list;
}

void Server::connect(QVariantMap json)
{
    QByteArray data;
    data.append(30, 0x00);

    QByteArray ip;
    for(const auto& s : json["ip"].toString().split('.')) {
        ip.append(static_cast<unsigned char>(s.toInt()));
    }
    lastIp = ip;
    data.append(ip);

    QString mac = json["mac"].toString();
    data.append(mac).append(20 - mac.length(), 0x00);

    data.append(json["service"].toString().toInt())
        .append(json["connectType"].toString().toInt());

    QByteArray checkSum = getCheckSum(data);
    isWaitUdpReceive = true;
    timer.start();
    lastData = data.append(checkSum);
    socket.writeDatagram(lastData, QHostAddress("172.16.1.1"), 20015);
}

QByteArray Server::getCheckSum(const QByteArray data)
{
    quint32 ecx = 0x4E67C6A7;
    quint32 esi;
    for(auto b : data) {
        esi = ecx << 5;
        quint32 ebx = ecx >> 2;
        if ((qint32)ecx <= 0) {
            ebx |= 0x0C0000000;     //按位或
        }
        esi += static_cast<unsigned char>(b);
        ebx += esi;
        ecx ^= ebx;     //按位异或
    }
    ecx &= 0x7FFFFFFF;
    return QByteArray(reinterpret_cast<char*>(&ecx), 4);
}

void Server::receive()
{
    QNetworkDatagram datagram = socket.receiveDatagram();
    if(datagram.senderAddress().toString() != "172.16.1.1"
        && datagram.senderPort() != 20015
        && !isWaitUdpReceive) {
        return;
    }
    isWaitUdpReceive = false;
    timer.stop();
    QByteArray data = datagram.data();
    if(data != QByteArray(lastIp).append(static_cast<char>(0x00))) {
        emit error(tr("错误的服务器返回值：") + data.toHex());
    }
    else {
        lastData[lastData.length() - 1] = static_cast<char>(0x02);
        socket.writeDatagram(lastData, QHostAddress("172.16.1.1"), 20015);
        emit success();
    }
}

void Server::timeout()
{
    isWaitUdpReceive = false;
    emit error(tr("注册服务器超时"));
}

}
