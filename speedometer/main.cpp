#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include "speedometer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Speedometer>("com.ulasdikme.speedometer",1,0,"Speedometer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *object = engine.rootObjects()[0];
    QObject *speedometer = object->findChild<QObject*>("speedoMeter");

    Speedometer *ptrSpeedometer = qobject_cast<Speedometer*>(speedometer);
    //Speedometer *ptrSpeedometer = dynamic_cast<Speedometer*>(speedometer);

    qreal val = 110;
    ptrSpeedometer->setSpeed(val);

    bool direction = true;
    QTimer timer;

    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        ptrSpeedometer->setSpeed(val);
        if(val < 1600)
                ptrSpeedometer->setOuterColor(QColor(128,255,0));
        else if(val > 1600 && val < 3200)
                ptrSpeedometer->setOuterColor(QColor(255,255,0));
        else if(val > 3200)
                ptrSpeedometer->setOuterColor(QColor(255,0,0));

        if(val >= 4000)
            direction = false;
        else if(val <= 0.1)
            direction = true;

        if(direction)
            val = val + 10;
        else
            val = val - 10;

    }
    );

    timer.start(10);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
