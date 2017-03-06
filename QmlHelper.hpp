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
    static_assert(std::is_base_of<QObject, T>::value, "Not QObject");

    static void registerSingleton(const QString &url, int versionMajor, int versionMinor,
                                const QString& typeName)
    {
        qmlRegisterSingletonType<T>(url.toStdString().c_str(), versionMajor, versionMinor,
                                    typeName.toStdString().c_str(), callback);
    }

    static void registerSingleton(const QString &url, int versionMajor, int versionMinor)
    {
        QString fullName = T::staticMetaObject.className();
        qint32 index = fullName.lastIndexOf(':');
        registerSingleton(url, versionMajor, versionMinor,
                          (index >= 0 ? fullName.right(fullName.length() - index - 1) : fullName));
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
