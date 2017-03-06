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
}
