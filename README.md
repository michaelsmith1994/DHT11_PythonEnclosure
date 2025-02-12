# DHT11_PythonEnclosure
Code is for my daughters python enclosure. Being new into the world of reptiles I had to do my research and have found that snakes require consistantly humid and warm environments. Anything else can result in health issues for the snake. I build this project with the intentions to replace the unreliable analog meter that came with the tank with something of less margin of error. It should be noted that the DHT11 sensor is not great for accuracy and I soon intend to create another repository and upload a new sketch using an SHT41 sensor. 

Standards for the DHT11 sensor:
Temperature range: 0 - 50°C
Humidity range: 20 - 80% RH
Temperature accuracy: ±2°C
Humidity accuracy: ±5% RH 

The equipment consist of a DHT11 sensor, Arduino Nano, and a 0.91 inch I2C OLED display.

Equipment links:
Display - 
https://www.amazon.com/dp/B09MZ8DW4R?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1

MCU (Nano V3, compatible with Arduino Nano) - 
https://www.amazon.com/dp/B0DFGX3MSL?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1

DHT11 (mine came in a sensor kit but the link contains a comparable quality DHT11) -
https://www.amazon.com/BOJACK-Temperature-Humidity-Digital-Raspberry/dp/B09TKTZMSL/ref=sr_1_2_sspa?crid=1YR0AW4JM6IC0&dib=eyJ2IjoiMSJ9.QSKrnrv22xYVI1SPvUOVU7f12has-6hn1sGejPmT6-_TH-GXxH6MV7UCrUXH1UMrhXMtTHz8KsfMC4CeYIP2ElbDElCbVX__TQqxRRghcJPsPm32-jW0XQ0Ka2Ck4OaY6lZ_jzcUQy03fso0dbysKcUPDwpdo7hXETHQyO9qcxsKo7eE8DDsh9RpJwUPkzt_a_pUEZwBlzUnEMMGU_jyMMBwiEgEJpcP_MtKqOqzh4E.XFmGPDymv8QnyjKzfL-k_qcKmeM4mdwG9XYkMI2sY6k&dib_tag=se&keywords=DHT11&qid=1739342818&sprefix=dht11%2Caps%2C153&sr=8-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1

Application Behavior:
Application will start on power-up "Initializing.." should appear on the display to signify the program start. After a 2 second wait period the MCU will begin communicating with the sensor toggling between the display of "Temp: " or "Humidity: ". The interval between the two readings is 5000 miliseconds (5 seconds), if a different delay is desired simply change the last line "delay(5000);" for delays between loops or change "const long interval = 5000;" for between reading delays to better suit your purposes.

Main Loop Code Description:
Get our readings from the sensor and initialize them to a variable.
```
    float humi = dht.readHumidity();       // Get humidity
    float tempC = dht.readTemperature();   // Get temperature in Celsius
    float tempF = (tempC * 9.0 / 5.0) + 32;  // Convert Celsius to Fahrenheit
```
The following code controls the toggle between the "show temp state" and the "show humidity state" by applying "!showTemp" to the showTemp variable.  
```
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  // Update the last time switch happened
        showTemp = !showTemp;  // Toggle between temperature and humidity
    }
```
The code below takes the alternating showTemp from the above code snip. Its purpose is to create a display for temp or for humidity.
```
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
```
Finally display the previously created display setup and wait 5 seconds before repeating the loop.
```
// Update the display
    display.display();

    // Wait for 5 seconds before the next loop (for smooth transitions)
    delay(5000);
```

Wiring Documentation will be uploaded soon.
