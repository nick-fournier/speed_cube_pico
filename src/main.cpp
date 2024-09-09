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

  tft.setCursor(0, 50);
  tft.print("Latitude: ");
  
  tft.setCursor(0, 80);
  tft.print("Longitude: ");
  
  tft.setCursor(0, 110);
  tft.print("Speed (knots): ");
  
  tft.setCursor(0, 140);
  tft.print("Bearing (degrees): ");
   
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
  tft.setCursor(120, 50);  // Position to overwrite Latitude value
  tft.print(String(GPS.getLatitude(), 6));  // Print the new Latitude value

  tft.setCursor(120, 80);  // Position to overwrite Longitude value
  tft.print(String(GPS.getLongitude(), 6));  // Print the new Longitude value

  tft.setCursor(160, 110);  // Position to overwrite Speed value
  tft.print(String(GPS.getSpeed(), 2));  // Print the new Speed value

  tft.setCursor(200, 140);  // Position to overwrite Bearing value
  tft.print(String(GPS.getBearing(), 2));  // Print the new Bearing value

  // Add a small delay to avoid flickering and reduce the update rate
  delay(500);
}
