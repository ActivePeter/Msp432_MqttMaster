#ifndef __QMLCPPINTERFACE_H__
#define __QMLCPPINTERFACE_H__
#include <QObject>
#include <QQueue>
#include "MqttManager/MqttManager.h"
class QmlCppInterface : public QObject

{
    Q_OBJECT

public:
    explicit QmlCppInterface(QObject *parent = 0);
    Q_INVOKABLE QString getAttitude();
    Q_INVOKABLE float getAttitudes(int id, int index);
    // Q_INVOKABLE
    static QmlCppInterface *instance;
signals:

    void attitudeChange();

public slots:

    void setAttitude(float x, float y, float z);
    void startMqtt();

private:
    QQueue<float> attitudes[3];
    QString attitudeData;
    MqttManager &mqttManager = MqttManager::instance;
};
#endif // __QMLCPPINTERFACE_H__
