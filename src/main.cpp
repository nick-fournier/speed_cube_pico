#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

int counter = 0;
void setup(void) {
  tft.init();
}

void loop() {
  // Print a message to the screen
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(3);
  tft.setCursor(10, 10);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.println("Hello World! " + String(counter));
  delay(1000);
  counter++;
}

// #include "pico/stdlib.h"
// #include "GPSData.h"

// int main() {
//     stdio_init_all();  // Initialize standard I/O
//     GPSData gps;
//     gps.readDataFromUART();  // Start reading GPS data over UART
//     return 0;
// }

// // Example usage
// int main() {
//     GPSData gps;
//     std::string sampleNMEA = "$GNRMC,092204.999,A,5321.6802,N,00630.3372,W,0.06,31.66,280511,,,A*43";
    
//     gps.processNMEA(sampleNMEA);

//     std::cout << "Time: " << gps.getTime() << std::endl;
//     std::cout << "Latitude: " << gps.getLatitude() << std::endl;
//     std::cout << "Longitude: " << gps.getLongitude() << std::endl;
//     std::cout << "Speed (knots): " << gps.getSpeed() << std::endl;
//     std::cout << "Bearing (degrees): " << gps.getBearing() << std::endl;

//     return 0;
// }
