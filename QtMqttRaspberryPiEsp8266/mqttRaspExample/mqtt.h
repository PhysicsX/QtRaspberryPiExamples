#ifndef MQTT_H
#define MQTT_H

#include <QObject>
#include <QTcpSocket>
#include <QtMqtt/QMqttClient>

class mqtt : public QObject
{
    Q_OBJECT


    public:

    Q_INVOKABLE void connect_a(QString host, QString port, QString user, QString pass);
    Q_INVOKABLE void subs_a(QString topic);

    Q_PROPERTY(int value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(bool statu READ getStatu WRITE setStatu NOTIFY statuChanged)

public:
    mqtt();
    ~mqtt();
    void subMess(const QMqttMessage &msg);

public slots:
    int getValue() const;
    bool getStatu() const;

    void setValue(int val);
    void setStatu(bool stat);

signals:
    void valueChanged();
    void statuChanged();

private:
    QMqttClient *m_client;
    int value;
    bool statu;
};

#endif // MQTT_H
