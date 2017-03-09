#pragma once

#include <QObject>

namespace QiDiTu {
class CPPHelper : public QObject
{
    Q_OBJECT
public:
    explicit CPPHelper(QObject *parent = 0);
    Q_INVOKABLE QVariantList networkList();
    Q_INVOKABLE void run(const QString& arguemnt);

};
}
