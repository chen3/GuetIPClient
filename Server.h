#pragma once

namespace QiDiTu {
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    static QVariantList networkList();

    Q_INVOKABLE void connect(QVariantMap json);

};
}
