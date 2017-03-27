#include "CPPHelper.h"
#include "Server.h"

#include <QProcess>

namespace QiDiTu {
CPPHelper::CPPHelper(QObject *parent)
    : QObject(parent)
{
}

QVariantList CPPHelper::networkList()
{
    return Server::networkList();
}

void CPPHelper::run(const QString &command)
{
    QProcess::startDetached(command);
//    system(arguemnt.toLatin1().data());
}

}
