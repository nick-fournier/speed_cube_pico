#ifndef GPS_H
#define GPS_H

#include <string>

class GPS {
public:
    // Constructor
    GPS();

    // Function to read data from UART and process NMEA sentences
    void readDataFromUART();

    // Function to process NMEA sentence
    void processNMEA(const std::string& nmea);

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

#endif // GPS_H
