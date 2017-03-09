#pragma once

namespace QiDiTu {
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    static QVariantList networkList();

    Q_INVOKABLE void connect(QVariantMap json);
    static QByteArray getCheckSum(const QByteArray data);

signals:
    void error(const QString& message);
    void success();

private:
    QUdpSocket socket;
    bool isWaitUdpReceive{false};
    QByteArray lastIp;
    QByteArray lastData;
    QTimer timer;

    void receive();
    void timeout();

};
}
