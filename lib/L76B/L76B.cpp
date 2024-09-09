#include "L76B.h"
#include <Arduino.h>
// #include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 0  // Replace with the appropriate TX pin for your setup
#define UART_RX_PIN 1  // Replace with the appropriate RX pin for your setup

L76B::L76B() : latitude(0.0), longitude(0.0), speed(0.0), bearing(0.0) {
    // // Initialize UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // // Set UART format
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
}

void L76B::readNMEA() {
    char buffer[128];
    size_t index = 0;
    bool isSentence = false;
    
    // Read characters from UART
    char c = uart_getc(UART_ID);
    while (uart_is_readable(UART_ID) || !isSentence) {
        char c = uart_getc(UART_ID);
        if (c == '\n' || c == '\r') {
            buffer[index] = '\0';  // Null-terminate the string
            isSentence = processNMEA(std::string(buffer));  // Process the NMEA sentence
            index = 0;  // Reset buffer index
        } else {
            buffer[index++] = c;  // Add character to buffer
            if (index >= sizeof(buffer) - 1) {  // Prevent buffer overflow
                index = 0;
            }
        }
    }
}

bool L76B::processNMEA(const std::string& nmea) {
    // Check if the protocol is GNRMC
    if (nmea.find("$GNRMC") != std::string::npos) {
        Serial.println("GNRMC Sentence");
        parseGNRMC(nmea);
        return true;
    }
    return false;
}

void L76B::parseGNRMC(const std::string& nmea) {
    // Example of GNRMC Sentence: 
    // $GNRMC,092204.999,A,5321.6802,N,00630.3372,W,0.06,31.66,280511,,,A*43

    std::string token;
    size_t pos = 0;
    int fieldIndex = 0;
    std::string delimiter = ",";

    std::string nmea_copy = nmea;  // Make a copy for processing
    while ((pos = nmea_copy.find(delimiter)) != std::string::npos) {
        token = nmea_copy.substr(0, pos);
        
        switch (fieldIndex) {
            case 1: // Time
                time = token;
                break;
            case 3: // Latitude
                latitude = convertToDecimalDegrees(token, nmea_copy.substr(pos + 1, 1));
                break;
            case 5: // Longitude
                longitude = convertToDecimalDegrees(token, nmea_copy.substr(pos + 1, 1));
                break;
            case 7: // Speed in knots
                speed = std::stod(token);
                break;
            case 8: // Bearing in degrees
                bearing = std::stod(token);
                break;
            default:
                break;
        }

        nmea_copy.erase(0, pos + delimiter.length());
        fieldIndex++;
    }
}

double L76B::convertToDecimalDegrees(const std::string& coordinate, const std::string& direction) {
    double decimal = std::stod(coordinate.substr(0, 2)) + (std::stod(coordinate.substr(2)) / 60.0);
    if (direction == "S" || direction == "W") {
        decimal = -decimal;
    }
    return decimal;
}

std::string L76B::getTime() const { return time; }
double L76B::getLatitude() const { return latitude; }
double L76B::getLongitude() const { return longitude; }
double L76B::getSpeed() const { return speed; }
double L76B::getBearing() const { return bearing; }
