#include "CPPHelper.h"
#include "Server.h"

namespace QiDiTu {
CPPHelper::CPPHelper(QObject *parent)
    : QObject(parent)
{
}

QVariantList CPPHelper::networkList()
{
    return Server::networkList();
}

void CPPHelper::run(const QString &arguemnt)
{
    system(arguemnt.toLatin1().data());
}

}
