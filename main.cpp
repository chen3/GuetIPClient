#include "PreCompiled.h"

#include "CPPHelper.h"
#include "QmlHelper.hpp"
#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("QiDiTu");
    app.setOrganizationDomain("qiditu.cn");
    app.setApplicationName(QObject::tr("桂林电子科技大学出校器"));

    QQmlApplicationEngine engine;
    QiDiTu::QmlHelper<QiDiTu::CPPHelper>::registerSingleton("cn.qiditu", 1, 0);
    qmlRegisterType<QiDiTu::Server>("cn.qiditu", 1, 0, "Server");
    QUrl file = QUrl("qrc:/main.qml");
    if(QFile::exists("main.qml")) {
        file = QUrl::fromLocalFile("main.qml");
    }
    engine.load(QUrl(file));

    return app.exec();
}
