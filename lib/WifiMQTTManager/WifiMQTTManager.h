#ifndef WIFIMQTTMANAGER_H
#define WIFIMQTTMANAGER_H

#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "SimpleTimer.h"

#undef min
#undef max

#include <map>
#include <string>
#include <vector>

class WifiMQTTManager
{
private:
    std::string m_wifiSSID;
    std::string m_wifiPASS;
    std::string m_mqttServer;
    uint16_t m_mqttPort;
    std::string m_mqttUsername;
    std::string m_mqttPassword;

    IPAddress m_ip;
    IPAddress m_mask;
    IPAddress m_gateway;

    std::string m_deviceName;
    std::string m_deviceType;
    String m_deviceMac;
    std::string m_fw;
    std::string m_fwVersion;

    String m_deviceMacTopic;
    std::string m_deviceIpTopic;
    std::string m_deviceNameTopic;
    std::string m_deviceTypeTopic;
    std::string m_fwTopic;
    std::string m_fwVersionTopic;

    std::map<std::string, std::string> m_statusTopics;
    std::vector<std::string> m_subscribeTopics;

    WiFiClient m_wifiClient;
    PubSubClient* m_pubSubClient;

    bool m_connected;
    std::string m_tempTopic;
    std::string m_tempPayload;
    bool m_publishMQTT;

    unsigned long m_deviceStatusInfoTime;
    SimpleTimer m_deviceStatusInfoTimer;

    unsigned long m_checkConnectivityTime;
    SimpleTimer m_checkConnectivityTimer;

    void initWifi();
    void connectWifi();
    String getMacAddress();
    void publishDeviceStatusInfo();
    void checkConnectivity();
    void refreshStatusTopics();

public:
    WifiManager();

    void setup(std::string wifiSSID, std::string wifiPASS, std::string mqttServer, uint16_t mqttPort,
               std::string mqttUsername, std::string mqttPassword, String ip, String mask, String gateway,
               std::string deviceName, std::string deviceType, std::string fw, std::string fwVersion);

    ~WifiMQTTManager();

    void setCallback(void (*callback)(char*, uint8_t*, unsigned int));

    void addSubscribeTopic(std::string subscribeTopic);
    void eraseSubscribeTopic(std::string statusTopic);

    void addStatusTopic(std::string statusTopic);
    void eraseStatusTopic(std::string statusTopic);

    void startConnection();

    void publishMQTT(std::string topic, std::string payload);

    bool connected();

    void loop();
};

#endif
