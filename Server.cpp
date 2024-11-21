#include <Arduino.h>
#include "Server.h"
#include <WiFi.h>
#include "AnimationSystem.h"
#include "Animation_Rainbow.h"
#include "Animation_Random.h"
#include "tmp_index_html.h"

#define TIMEOUT_TIME 5000

const char* ssid = "Esp32Testzeugs";
const char* password = "Heifbeidbwbfirbdj";

// Server
WiFiServer server(80);

void setupServer() {
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
    server.begin();
}


void send404Back(WiFiClient* client){
    client->println("HTTP/1.1 404 Not Found");
    client->println("Content-type:text/html");
    client->println("Connection: close");
    client->println();
    client->println("The page you are trying to access, doesn't exist");
    client->stop();
}

void sendInvalidRequest(WiFiClient* client){
    client->println("HTTP/1.1 400 Bad request");
    client->println("Content-type:text/html");
    client->println("Connection: close");
    client->println();
    client->println("The request is not valid.");
    client->stop();
}

void sendActionAccepted(WiFiClient* client){
    client->println("HTTP/1.1 200 Ok");
    client->println("Content-type:text/html");
    client->println("Connection: close");
    client->println();
    client->println("Accepted");
    client->stop();
}

void sendNormalpageBack(WiFiClient* client){

    client->println("HTTP/1.1 200 OK");
    client->println("Content-type:text/html");
    client->println("Connection: close");
    client->println();
    client->println(index_html);
    client->println("<script> const settings = [");
    client->println(rainbow_Speed); client->println(",");
    client->println(rainbow_offset_x); client->println(",");
    client->println(rainbow_offset_y); client->println(",");
    client->println(anm_random_chanceOn); client->println(",");
    client->println("]</script>");
    client->stop();
}

// Event: When a mode-change request is retreived
void handleRequestMode(WiFiClient* client, String* header){

    int animationState = header->toInt();

    // Checks for an error
    if(animationState == 0){
        sendInvalidRequest(client);
        return;
    }

    setCurrentAnimation(animationState);
    sendActionAccepted(client);
}


void handleRandomSetting(NetworkClient* client, String* header) {
    Serial.println("Subheader: "+ *header);
    /**
     * Checks setting-type:
     * Allowed: c (chance)
     */

    if(header->length() <= 0){
        sendInvalidRequest(client);
        return;
    }

    char c = header->charAt(0);

    byte type = (c == 'c' ? 1 : 9);

    if(type == 9){
        sendInvalidRequest(client);
        return;
    }

    *header = header->substring(1);

    byte value = (byte)header->toInt();
    if(value <= 0){
        sendInvalidRequest(client);
        return;
    }

    random_setting(value-1);

    // Checks mode
    sendActionAccepted(client);
}

// Event: When a rainbow-settings request is retreived
void handleRainbowSetting(WiFiClient* client, String* header){

    Serial.println("Subheader: "+ *header);
    /**
     * Checks setting-type:
     * Allowed: x (Offset X), y (Offset-Y), s (Speed)
     */

    if(header->length() <= 0){
        sendInvalidRequest(client);
        return;
    }

    char c = header->charAt(0);

    byte type = (c == 'x' ? 1 : (c == 'y' ? 2 : (c == 's' ? 0 : 6)));

    if(type == 6){
        sendInvalidRequest(client);
        return;
    }

    *header = header->substring(1);

    byte value = (byte)header->toInt();
    if(value <= 0){
        sendInvalidRequest(client);
        return;
    }

    rainbow_setting(type, value-1);

    // Checks mode
    sendActionAccepted(client);
}

bool serverReadInHeader(WiFiClient* client, String* header){
    static long startTime; startTime = millis();
    static unsigned int byteIdx; byteIdx = 0;


    while (client->connected() && millis() - startTime <= TIMEOUT_TIME) {
        if(!client->available())
            continue;

        byteIdx++;
        if(byteIdx >= 100)
            return false;

        char c = client->read();
        *header += c;

        // As we are only interested in the first line, we can discard anything after the "\n"
        if(c != '\n')
            continue;

        return true;
    }
}

// Call on loop. Handles clients for the webserver
void handleClient() {
    WiFiClient client = server.available();

    if (!client)
        return;

    static String header; header = "";

    if(!serverReadInHeader(&client, &header)){
        send404Back(&client);
        return;
    }

    Serial.println("    =>"+String(header));

    int idx;

    // Checks if this is an "mode/" request
    idx = header.indexOf("mode/");
    if(idx >= 0){
        header = header.substring(idx+5);
        handleRequestMode(&client, &header);
        return;
    }

    // Checks if this is an "srbow/" request
    idx = header.indexOf("srbow/");
    if(idx >= 0){
        header = header.substring(idx+6);
        handleRainbowSetting(&client, &header);
        return;
    }

    // Checks if this is an "srbow/" request
    idx = header.indexOf("rdm/");
    if(idx >= 0){
        header = header.substring(idx+6);
        handleRandomSetting(&client, &header);
        return;
    }    


    sendNormalpageBack(&client);
}