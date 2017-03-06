#include "CPPHelper.h"
#include "QmlHelper.hpp"
#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QiDiTu::QmlHelper<QiDiTu::CPPHelper>::registerSingleton("cn.qiditu", 1, 0);
    qmlRegisterType<QiDiTu::Server>("cn.qiditu", 1, 0, "Server");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
