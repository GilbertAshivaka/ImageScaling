#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "imagescaling.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    qmlRegisterType<Images>("com.images", 1, 0, "ImageDownloader");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/ImageScaling/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
