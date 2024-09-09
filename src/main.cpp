#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include <L76B.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// Create an instance of the L76B class
L76B GPS;

// Rotating status symbol characters
const char statusSymbols[] = {'|', '/', '-', '\\'};
int currentSymbolIndex = 0;  // Index to track the current symbol

void setup(void) {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize LCD
  tft.init();
  tft.invertDisplay(true);
  tft.setRotation(1);

  // Set text properties for static labels
  tft.setTextColor(TFT_WHITE);  // Set text color to white
  tft.setTextSize(2);  // Set text size

  // Display static labels on the TFT display
  tft.fillScreen(TFT_BLACK);  // Clear the screen once at the beginning
  tft.setCursor(0, 20);
  tft.print("GPS ");  // Print "GPS" label

  tft.setCursor(0, 40);
  tft.print("Time: ");

  tft.setCursor(0, 60);
  tft.print("Position: ");
  
  tft.setCursor(0, 80);
  tft.print("Speed (knots): ");
  
  tft.setCursor(0, 100);
  tft.print("Bearing: ");
   
}

void loop() {

  // Update the rotating status symbol
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color to white with black background
  tft.setCursor(40, 20);  // Set cursor position after "GPS"
  tft.print(statusSymbols[currentSymbolIndex]);  // Print the current status symbol

  // Advance to the next symbol in the sequence
  currentSymbolIndex = (currentSymbolIndex + 1) % 4;  // Loop back to 0 after 3

  // Read GPS data
  GPS.readNMEA();  // This should read new data from the GPS

  // Update dynamic values without clearing the screen
  tft.setCursor(120, 40);  // Position to overwrite Time value
  tft.print(GPS.getTime().c_str());  // Print the new Time value

  tft.setCursor(120, 60);  // Position to overwrite Latitude and Longitude values
  tft.print(String(GPS.getLatitude(), 6) + ", " + String(GPS.getLongitude(), 6));  // Print the new Latitude and Longitude values

  tft.setCursor(180, 80);  // Position to overwrite Speed value
  tft.print(String(GPS.getSpeed(), 2));  // Print the new Speed value

  tft.setCursor(100, 100);  // Position to overwrite Bearing value
  tft.print(String(GPS.getBearing(), 2));  // Print the new Bearing value

  // Add a small delay to avoid flickering and reduce the update rate
  delay(500);
}
