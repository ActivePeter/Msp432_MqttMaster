#include "MqttManager.h"
#include "QmlCppInterface/QmlCppInterface.h"
MqttManager MqttManager::instance;

MqttManager::MqttManager(QObject *parent)
{
}

void MqttManager::init(QObject *parent)
{
    this->setParent(parent);
    mqttClient = new QMqttClient(parent);
    mqttClient->setHostname("192.168.199.145");
    mqttClient->setPort(1883);
    mqttClient->setClientId("msp432master");
    connect(mqttClient, &QMqttClient::connected, this, &MqttManager::connected);
    connect(mqttClient, &QMqttClient::disconnected, this, &MqttManager::disconnected);
    connect(mqttClient, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        int16_t vx = ((uint16_t)message[0] << 8) | (uint8_t)message[1];
        int16_t vy = ((uint16_t)message[2] << 8) | (uint8_t)message[3];
        int16_t vz = ((uint16_t)message[4] << 8) | (uint8_t)message[5];
        const QString content = QLatin1String(" Received Topic: ") +
                                topic.name() +
                                QLatin1String(" Message: ") +
                                QString::number(vx / 5.0, 'f', 3) +
                                // QString::number(vx) +

                                "," +
                                QString::number(vy / 5.0, 'f', 3) +

                                // QString::number(vy) +
                                "," +
                                QString::number(vz / 5.0, 'f', 3) +

                                // QString::number(vz) +
                                QLatin1Char('\n');

        QmlCppInterface::instance->setAttitude(
            vx / 5.0,
            vy / 5.0,
            vz / 5.0);
        qDebug()
            << (content);
    });
}

void MqttManager::startMqtt()
{
    if (mqttClient->state() == QMqttClient::Disconnected)
    {
        qDebug() << ("Disconnected, starting Mqtt!");
        mqttClient->connectToHost();
    }
}

void MqttManager::connected()
{
    qDebug() << ("connected!");
    auto subscription = mqttClient->subscribe(QMqttTopicFilter("/simplelink/bno055"), 2);
    if (!subscription)
    {
        qDebug() << ("subscript fail!");
        // return;
    }
}

void MqttManager::disconnected()
{
    qDebug() << ("disconnected!");
}
