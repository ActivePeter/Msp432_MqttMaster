#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H
#include <QObject>
#include <QMqttClient>
class MqttManager : public QObject
{
    Q_OBJECT

public:
    static MqttManager instance;
    explicit MqttManager(QObject *parent = 0);
    void init(QObject *parent);
    void startMqtt();

private:
    QMqttClient *mqttClient;
    void connected();
    void disconnected();
};

#endif // MQTTMANAGER_H