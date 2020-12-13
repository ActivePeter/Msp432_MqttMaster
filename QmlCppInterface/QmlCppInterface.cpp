#include "QmlCppInterface.h"

QmlCppInterface *QmlCppInterface::instance;

Q_INVOKABLE QString
QmlCppInterface::getAttitude()
{
    return attitudeData;
}

Q_INVOKABLE float QmlCppInterface::getAttitudes(int id, int index)
{
    if (attitudes[id].size() <= index)
    {
        return 0;
    }
    return attitudes[id].at(index);
}

// void QmlCppInterface::onAttitudeChange()
// {
// }

void QmlCppInterface::setAttitude(float x, float y, float z)
{
    attitudeData = ("陀螺仪姿态: \n  ") +
                   QString::number(x, 'f', 1) +
                   // QString::number(vx) +
                   "," +
                   QString::number(y, 'f', 1) +
                   // QString::number(vy) +
                   "," +
                   QString::number(z, 'f', 1);
    attitudes[0].push_back(x);
    attitudes[1].push_back(y);
    attitudes[2].push_back(z);

    for (int i = 0; i < 3; i++)
    {
        if (attitudes[i].size() > 300)
        {
            attitudes[i].pop_front();
        }
    }
    emit attitudeChange();
}

void QmlCppInterface::startMqtt()
{
    qDebug() << ("starting Mqtt!");
    mqttManager.startMqtt();
}

QmlCppInterface::QmlCppInterface(QObject *parent)
{
    QmlCppInterface::instance = this;
    mqttManager.init(this);
}
