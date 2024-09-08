#include "gps.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 0  // Replace with the appropriate TX pin for your setup
#define UART_RX_PIN 1  // Replace with the appropriate RX pin for your setup

GPS::GPS() : latitude(0.0), longitude(0.0), speed(0.0), bearing(0.0) {
    // Initialize UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Set UART format
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
}

void GPS::readDataFromUART() {
    char buffer[128];
    size_t index = 0;

    while (true) {
        // Read characters from UART
        while (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);
            if (c == '\n' || c == '\r') {
                buffer[index] = '\0';  // Null-terminate the string
                processNMEA(std::string(buffer));  // Process the NMEA sentence
                index = 0;  // Reset buffer index
            } else {
                buffer[index++] = c;  // Add character to buffer
                if (index >= sizeof(buffer) - 1) {  // Prevent buffer overflow
                    index = 0;
                }
            }
        }
        sleep_ms(100);  // Sleep for a short time to avoid busy-waiting
    }
}

void GPS::processNMEA(const std::string& nmea) {
    if (nmea.find("$GNRMC") != std::string::npos) {
        parseGNRMC(nmea);
    }
    // Add additional parsing functions here for other NMEA sentences
}

void GPS::parseGNRMC(const std::string& nmea) {
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

double GPS::convertToDecimalDegrees(const std::string& coordinate, const std::string& direction) {
    double decimal = std::stod(coordinate.substr(0, 2)) + (std::stod(coordinate.substr(2)) / 60.0);
    if (direction == "S" || direction == "W") {
        decimal = -decimal;
    }
    return decimal;
}

std::string GPS::getTime() const { return time; }
double GPS::getLatitude() const { return latitude; }
double GPS::getLongitude() const { return longitude; }
double GPS::getSpeed() const { return speed; }
double GPS::getBearing() const { return bearing; }
