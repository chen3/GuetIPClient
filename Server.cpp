#include "Server.h"

namespace QiDiTu {
Server::Server(QObject *parent)
    : QObject(parent)
{
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
                quint32 ipv4 = hostAddress.toIPv4Address(&ok);
                if(!ok) {
                    continue;
                }
                QString ip = QString::number(ipv4, 16);
                //insert ':' to MAC String  em."AABBCCDD" to "AA:BB:CC:DD"
                ip.insert(2, ':');
                ip.insert(5, ':');
                ip.insert(8, ':');
                list.append(QVariantMap{{"MAC", hardwareAddress}, {"IPV4", ip}});
            }
        }
    }
    return list;
}

}
