<<<<<<< HEAD

#include <Arduino.h>

constexpr uint8_t LED1_PIN = 18;
constexpr uint8_t LED2_PIN = 19;

constexpr uint8_t PWM_CHANNEL1 = 0;
constexpr uint8_t PWM_CHANNEL2 = 2;

constexpr uint32_t PWM_FREQUENCY1 = 1000;
constexpr uint32_t PWM_FREQUENCY2 = 5000;

constexpr uint8_t PWM_RESOLUTION = 8;
constexpr uint16_t PWM_MAX_DUTY = (1 << PWM_RESOLUTION) - 1;

void setup()
{
    Serial.begin(115200);

    double actualFreq1 = ledcSetup(
        PWM_CHANNEL1, PWM_FREQUENCY1, PWM_RESOLUTION
    );

    double actualFreq2 = ledcSetup(
        PWM_CHANNEL2, PWM_FREQUENCY2, PWM_RESOLUTION
    );

    if (actualFreq1 == 0 || actualFreq2 == 0)
    {
        Serial.println("ERROR: PWM setup failed.");
        while (true)
        {
            delay(1000);
        }
    }

    ledcAttachPin(LED1_PIN, PWM_CHANNEL1);
    ledcAttachPin(LED2_PIN, PWM_CHANNEL2);

    ledcWrite(PWM_CHANNEL1, 0);
    ledcWrite(PWM_CHANNEL2, 0);

    Serial.println("Dual LED PWM Fade Started");

    Serial.print("LED 1 Frequency: ");
    Serial.print(actualFreq1);
    Serial.println(" Hz");

    Serial.print("LED 2 Frequency: ");
    Serial.print(actualFreq2);
    Serial.println(" Hz");
}

void loop()
{
    // Fade in both LEDs
    for (int duty = 0; duty <= PWM_MAX_DUTY; duty++)
    {
        ledcWrite(PWM_CHANNEL1, duty);
        ledcWrite(PWM_CHANNEL2, duty);

        delay(10);
    }

    // Fade out both LEDs
    for (int duty = PWM_MAX_DUTY; duty >= 0; duty--)
    {
        ledcWrite(PWM_CHANNEL1, duty);
        ledcWrite(PWM_CHANNEL2, duty);

        delay(10);
    }
=======
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C
#define DHT_PIN 14
#define DHT_TYPE DHT11

Adafruit_SSD1306 display(
    SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1
);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(115200);
    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED initialization failed!");
        while (true) { delay(100); }
    }

    dht.begin();

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("ESP32 Environment");
    display.println("Initializing...");
    display.display();

    delay(2000);
}

void loop() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("DHT11 read failed!");

        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.println("Sensor Error");
        display.println("Check DHT11");
        display.display();

        delay(2000);
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.print(" %   Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" C");

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("ENVIRONMENT MONITOR");
    display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

    display.setCursor(0, 20);
    display.print("Humidity: ");
    display.print(humidity, 1);
    display.println(" %");

    display.setCursor(0, 36);
    display.print("Temp: ");
    display.print(temperature, 1);
    display.println(" C");

    display.display();
    delay(2000);
>>>>>>> e172d5a0970f46143dcd571428a8a985163c0126
}