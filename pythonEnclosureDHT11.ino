#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define DHT_PIN 2
#define DHT_TYPE DHT11

// Initialize the OLED display and DHT sensor
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHT_PIN, DHT_TYPE);

unsigned long previousMillis = 0;  // Store the last time a change was made
const long interval = 5000;  // Interval at which to change (in milliseconds)
bool showTemp = true;  // Flag to switch between displaying temperature or humidity

void setup() {
    Serial.begin(9600);  // Start serial monitor for debugging

    // Initialize OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);  // Halt if the display cannot be initialized
    }

    // Initialize DHT sensor
    dht.begin();

    // Initial display setup
    display.clearDisplay();
    display.setTextSize(1);  // Start with larger text for initial message
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(F("Initializing..."));
    display.display();
    delay(2000);  // Display initial message for 2 seconds
}

void loop() {
    unsigned long currentMillis = millis();

    // Get sensor readings
    float humi = dht.readHumidity();       // Get humidity
    float tempC = dht.readTemperature();   // Get temperature in Celsius
    float tempF = (tempC * 9.0 / 5.0) + 32;  // Convert Celsius to Fahrenheit

    // Clear display before updating it
    display.clearDisplay();

    // Check if it's time to switch between temperature and humidity
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  // Update the last time switch happened
        showTemp = !showTemp;  // Toggle between temperature and humidity
    }

    // Display the label for temperature or humidity
    display.setTextSize(2);  // Use a medium size for the labels
    display.setTextColor(SSD1306_WHITE);

    if (showTemp) {
        // Display temperature label
        display.setCursor(0, 0);  // Position on the first line
        display.print(F("Temp:"));

        // Display temperature reading below the label
        display.setTextSize(2);  // Larger text for the reading
        display.setCursor(0, 16);  // Move to the second line
        if (isnan(tempF)) {
            display.print(F("NaN"));
        } else {
            display.print(tempF);  // Print temperature in Fahrenheit
            display.print(F(" F"));
        }
    } else {
        // Display humidity label
        display.setCursor(0, 0);  // Position on the first line
        display.print(F("Humidity:"));

        // Display humidity reading below the label
        display.setTextSize(2);  // Larger text for the reading
        display.setCursor(0, 16);  // Move to the second line
        if (isnan(humi)) {
            display.print(F("NaN"));
        } else {
            display.print(humi);   // Print humidity
            display.print(F("%"));
        }
    }

    // Update the display
    display.display();

    // Wait for 5 seconds before the next loop (for smooth transitions)
    delay(5000);
}
