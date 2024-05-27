#include "WiFi.h" // Include the WiFi library for ESP32
#include "esp_wifi.h" // Include the ESP32-specific WiFi library
#include "WiFiClientSecure.h" // Include the library for secure WiFi client
#include "HTTPClient.h" // Include the HTTP client library
const char *ssid = "ESP32AP"; // Define the SSID for the ESP32 access point
const char *password = "123456789"; // Define the password for the ESP32 access point
const char* serverName = "https://YOUR_WEBSERVER/post-esp-data.php"; // Define the URL of the server script for receiving data
String apiKeyValue = "YOUR_API"; // Define the API key for secure communication
String previousMacAddresses = ""; // Initialize a variable to store previous MAC addresses

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  WiFi.softAP(ssid, password, 1, 0, 1); // Set up ESP32 as an access point with provided SSID and password
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP()); // Print the IP address of the ESP32 access point
  WiFi.begin("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD"); // Connect ESP32 to another WiFi network
}

void loop() {
if (WiFi.softAPgetStationNum() == 1) { // Check if there is one device connected to the ESP32 access point
  String macAddresses = ""; // Initialize a variable to store MAC addresses of connected devices
  wifi_sta_list_t stationList; // Define a structure to store information about connected stations
  esp_wifi_ap_get_sta_list(&stationList); // Get the list of connected stations
    wifi_sta_info_t station = stationList.sta[0]; // Get the information of the first connected station
    for (int j = 0; j < 6; j++) {
      char str[2];
      sprintf(str, "%02x", (int)station.mac[j]); // Convert MAC address to hexadecimal string
      macAddresses += str; // Append MAC address to the string
    }
    macAddresses += "\n"; // Add newline character at the end
  if (macAddresses != previousMacAddresses) { // Check if there are changes in connected devices
    previousMacAddresses = macAddresses; // Update previous MAC addresses with current MAC addresses
  }

  WiFiClientSecure *client = new WiFiClientSecure; // Create a new secure WiFi client
  client->setInsecure(); // Set client to accept insecure connections
  HTTPClient https; // Create an HTTP client object
  https.begin(*client, serverName); // Begin HTTP request to server with secure client and server URL
  https.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Add header for content type
  String httpRequestData = "api_key=" + apiKeyValue + "&Name=" + macAddresses + ""; // Create HTTP request data
  Serial.println(httpRequestData); // Print HTTP request data to serial monitor
  int httpResponseCode = https.POST(httpRequestData); // Send HTTP POST request with data
  https.end(); // End HTTP request
  delay(5000); // Check every 10 seconds for changes in connected stations
}
else {
    // If no device is connected, print an error message
    Serial.println("No device connected!");
  }
}
