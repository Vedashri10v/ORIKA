/*
 * ESP32 FSR Emergency Alert System
 * Detects pressure on FSR sensor and sends alert to backend server
 */

#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials - MUST MATCH YOUR LAPTOP'S WIFI!
// Both ESP32 and Laptop must be on the SAME WiFi network
const char* ssid = "OnePlus Nord Ce 2";
const char* password = "12345678";

// Server configuration - YOUR LAPTOP'S IP ADDRESS
// Your laptop IP: 10.203.164.130 (from ipconfig)
// Backend server must be running on port 3000
// To start server: Double-click START-SERVER.bat OR run: cd backend && npm start
const char* serverUrl = "http://10.203.164.130:3000/api/fsr-trigger";

// FSR sensor pin - MUST BE AN ADC PIN!
// Recommended ADC pins: GPIO32, GPIO33, GPIO34, GPIO35, GPIO36, GPIO39
// Using GPIO34 (best for analog sensors)
const int FSR_PIN = 34;  // GPIO34 (ADC1_CH6)

// Threshold for FSR activation (0-4095)
// Lowered to 300 to detect lighter presses
// Adjust this value based on your FSR sensor
const int FSR_THRESHOLD = 300;

// Debounce settings
unsigned long lastTriggerTime = 0;
const unsigned long DEBOUNCE_DELAY = 3000;  // 3 seconds

// LED indicator (built-in)
const int LED_PIN = 2;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FSR_PIN, INPUT);
  
  Serial.println("\n=== ESP32 FSR Emergency System ===");
  
  // Connect to WiFi
  connectWiFi();
}

void loop() {
  // Read FSR value multiple times and average (noise filtering)
  int fsrSum = 0;
  for (int i = 0; i < 5; i++) {
    fsrSum += analogRead(FSR_PIN);
    delay(10);
  }
  int fsrValue = fsrSum / 5;  // Average of 5 readings
  
  // Debug: Print FSR value every 2 seconds
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 2000) {
    Serial.print("FSR Value: ");
    Serial.print(fsrValue);
    Serial.print(" | Threshold: ");
    Serial.print(FSR_THRESHOLD);
    if (fsrValue > FSR_THRESHOLD) {
      Serial.print(" | PRESSED!");
    }
    Serial.println();
    lastPrint = millis();
  }
  
  // Check if FSR is pressed (with hysteresis to avoid false triggers)
  if (fsrValue > FSR_THRESHOLD) {
    unsigned long currentTime = millis();
    
    // Debounce check
    if (currentTime - lastTriggerTime > DEBOUNCE_DELAY) {
      lastTriggerTime = currentTime;
      
      Serial.println("\n🚨 FSR PRESSED!");
      Serial.print("FSR Value: ");
      Serial.println(fsrValue);
      
      // Blink LED
      blinkLED(3);
      
      // Send alert to server
      sendEmergencyAlert(fsrValue);
    }
  }
  
  delay(100);  // Check every 100ms
}

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Server URL: ");
    Serial.println(serverUrl);
    
    // Success blink
    blinkLED(5);
  } else {
    Serial.println("\n❌ WiFi Connection Failed!");
    Serial.println("Please check credentials and restart");
  }
}

void sendEmergencyAlert(int fsrValue) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ WiFi not connected. Reconnecting...");
    connectWiFi();
    return;
  }
  
  HTTPClient http;
  
  Serial.println("📡 Sending alert to server...");
  
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  
  // Create JSON payload
  String payload = "{\"fsrValue\":" + String(fsrValue) + 
                   ",\"deviceId\":\"ESP32_001\"" +
                   ",\"timestamp\":\"" + String(millis()) + "\"}";
  
  Serial.print("Payload: ");
  Serial.println(payload);
  
  int httpResponseCode = http.POST(payload);
  
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("✅ Server Response (");
    Serial.print(httpResponseCode);
    Serial.print("): ");
    Serial.println(response);
    
    // Success blink
    blinkLED(2);
  } else {
    Serial.print("❌ HTTP Error: ");
    Serial.println(httpResponseCode);
    Serial.println(http.errorToString(httpResponseCode));
  }
  
  http.end();
}

void blinkLED(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}
