
#include <WiFi.h>
#include <Thingpings.h>

/* Replace with your local wireless network credentials */
const char* ssid = "example-network";
const char* pass = "example-password";

void setup() {

    /* Configure serial port for debug */
    Serial.begin(115200);

    /* Connect to Wi-Fi */
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to WiFi ");
    while (WiFi.status() != WL_CONNECTED) { delay(100); }
    Serial.println(WiFi.localIP());

    /* Send a ping to Thingpings */
    Thingpings::ping("Example Company", "Example Widget");
    Serial.println("Sent ping to Thingpings");
}

void loop() {

}
