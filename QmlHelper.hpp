#pragma once

namespace QiDiTu {

/**
 *  qmlRegisterSingletonType helper class
 */
template<class T>
class QmlHelper
{
public:
    QmlHelper() = delete;
    static_assert(std::is_base_of<QObject, T>::value, "not QObject");

    static void registerSingleton(const QString &url, int versionMajor, int versionMinor,
                                const QString& typeName = typeid(T).name())
    {
        qmlRegisterSingletonType<T>(url.toStdString().c_str(), versionMajor, versionMinor,
                                    typeName.toStdString().c_str(), callback);
    }

private:
    static QObject* callback(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return new T;
    }

};
}
