#include <QObject>
#include <QDebug>
#include "mqtt.h"
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

mqtt::mqtt(): QObject()
{
    m_client = new QMqttClient(this);
}

mqtt::~mqtt()
{


}

int mqtt::getValue() const
{
    return value;
}
bool mqtt::getStatu() const
{
    return statu;
}

void mqtt::setValue(int val)
{
    value = val;
    emit valueChanged();
}

void mqtt::setStatu(bool stat)
{
    statu = stat;
    emit statuChanged();
}

void mqtt::connect_a(QString host, QString port, QString user, QString pass)
{



    if (m_client->state() == QMqttClient::Disconnected) {
        m_client->setHostname(host);

        m_client->setPort(port.toInt());
        m_client->setUsername(user);
        m_client->setPassword(pass);

        m_client->connectToHost();
        setStatu(false);
    }
    else {
        m_client->disconnectFromHost();
        setStatu(true);
    }

    return;
}

void mqtt::subs_a(QString topic)
{
    qDebug()<<"subscribe to topic";
    auto subscription = m_client->subscribe(topic, 0);
    if (!subscription) {
        qDebug()<<"Can not subscribe to topic";
        return;
    }

    connect(subscription, &QMqttSubscription::messageReceived, this, &mqtt::subMess);

    return;
}


void mqtt::subMess(const QMqttMessage &msg)
{
    qDebug()<<msg.payload();

    QString str(msg.payload());
    QByteArray br = str.toUtf8();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(br);
    QString res = jsonDoc.object().value("command").toObject().value("result").toObject().value("temperature").toString();
    qDebug()<<res.toInt();
    int tmp = res.toInt();
    setValue(tmp);

    return;

}
