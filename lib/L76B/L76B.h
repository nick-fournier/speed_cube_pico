#ifndef L76B_H
#define L76B_H

#include <string>

class L76B {
public:
    // Constructor
    L76B();

    // Function to read data from UART and process NMEA sentences
    void readNMEA();

    // Function to process NMEA sentence
    bool processNMEA(const std::string& nmea);

    // Getters
    std::string getTime() const;
    double getLatitude() const;
    double getLongitude() const;
    double getSpeed() const;
    double getBearing() const;


private:
    std::string time;
    double latitude;
    double longitude;
    double speed;   // Speed in knots
    double bearing; // Bearing in degrees

    // Helper function to parse $GNRMC NMEA sentence
    void parseGNRMC(const std::string& nmea);

    // Helper function to convert NMEA coordinates to decimal degrees
    double convertToDecimalDegrees(const std::string& coordinate, const std::string& direction);
};

#endif // L76B_H
