#pragma once
#include <WiFi.h>

// Setups the server-stuff
void setupServer();

// Call on loop. Handles clients for the webserver
void handleClient();

// Sends back a 404 page to the client
void send404Back(NetworkClient* c);

//TODO: Comments
void sendInvalidRequest(NetworkClient* client);
void sendActionAccepted(NetworkClient* client);



// Sends the webpage back to the client
void sendNormalpageBack(NetworkClient* c);

bool serverReadInHeader(NetworkClient* client, String* header);

void handleRequestMode(NetworkClient* client, String* header);
void handleRainbowSetting(NetworkClient* client, String* header);
void handleRandomSetting(NetworkClient* client, String* header);
