// Setup000_RP2040_ILI9488.h
// Works with Waveshare "Pico-ResTouch-LCD-3.5" HAT (SKU: 19907)

#define RPI_DISPLAY_TYPE
#define USER_SETUP_INFO "User_Setup"

////////////////////////////////////////////////////////////////////////////////////////////
// Display driver type
////////////////////////////////////////////////////////////////////////////////////////////
#define ILI9488_DRIVER

////////////////////////////////////////////////////////////////////////////////////////////
// RP2040 pins used
////////////////////////////////////////////////////////////////////////////////////////////

// Define RP2040 pins used for the display
#define TFT_MISO 12  // MISO pin (if used)
#define TFT_MOSI 11  // Pin for SPI MOSI
#define TFT_SCLK 10  // Pin for SPI SCLK
#define TFT_CS   9   // Pin for Chip Select (CS)
#define TFT_DC   8   // Pin for Data/Command (DC)
#define TFT_RST  15  // Pin for Reset (can be -1 if not used)
#define TFT_BL   13  // Pin for backlight control

// Optional touch screen pins if using a touch screen module
//#define TOUCH_CS 21     // Chip select pin (T_CS) of touch screen

////////////////////////////////////////////////////////////////////////////////////////////
// Fonts to be available
////////////////////////////////////////////////////////////////////////////////////////////
#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT
////////////////////////////////////////////////////////////////////////////////////////////

#define TFT_SPI_PORT 1 // Set to 0 if SPI0 pins are used, or 1 if spi1 pins used

#define SPI_FREQUENCY  20000000

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  20000000

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
#define SPI_TOUCH_FREQUENCY  2500000

////////////////////////////////////////////////////////////////////////////////////////////
// Parallel Interface //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// #define TFT_PARALLEL_8_BIT

// #define TFT_CS   -1  // Do not define, chip select control pin permanently connected to 0V

// // These pins can be moved and are controlled directly by the library software
// #define TFT_DC   28    // Data Command control pin
// #define TFT_RST   2    // Reset pin

// //#define TFT_RD   -1  // Do not define, read pin permanently connected to 3V3

// // Note: All the following pins are PIO hardware configured and driven
//   #define TFT_WR   22

//   // PIO requires these to be sequentially increasing - do not change
//   #define TFT_D0    6
//   #define TFT_D1    7
//   #define TFT_D2    8
//   #define TFT_D3    9
//   #define TFT_D4   10
//   #define TFT_D5   11
//   #define TFT_D6   12
//   #define TFT_D7   13
// //*/