#include <iostream>
#include <fstream>
#include <string>
#include <limits>   // for FLT_MAX, FLT_MIN
#include <iomanip>  // for formatting
using namespace std;

// Struct to store a single meter record
struct MeterReading {
    string meter_id;
    float initial_reading;
    float final_reading;
};

// Class to process meter readings and generate report
class EnergyReport {
private:
    MeterReading reading;
    float energyConsumed;
    float loadFactor;
    float minLoad;
    float maxLoad;

public:
    void inputReadings() {
        cout << "Enter Meter ID: ";
        cin >> reading.meter_id;

        cout << "Enter Initial Reading (kWh): ";
        cin >> reading.initial_reading;

        cout << "Enter Final Reading (kWh): ";
        cin >> reading.final_reading;
    }

    void calculateMetrics() {
        energyConsumed = reading.final_reading - reading.initial_reading;

        // Dummy values for min/max load (replace with real hourly data in advanced version)
        minLoad = energyConsumed / 24.0 - 1.5f;
        maxLoad = energyConsumed / 24.0 + 1.5f;

        if (maxLoad != 0)
            loadFactor = (energyConsumed / 24.0f) / maxLoad;
        else
            loadFactor = 0;
    }

    void generateReport() {
        ofstream report("Daily_Energy_Report.txt");

        if (!report) {
            cout << "Error: Could not create report file.\n";
            return;
        }

        report << "=== Daily Energy Report ===\n";
        report << "Meter ID       : " << reading.meter_id << "\n";
        report << fixed << setprecision(2);
        report << "Initial Reading: " << reading.initial_reading << " kWh\n";
        report << "Final Reading  : " << reading.final_reading << " kWh\n";
        report << "Energy Consumed: " << energyConsumed << " kWh\n";
        report << "Min Load       : " << minLoad << " kW\n";
        report << "Max Load       : " << maxLoad << " kW\n";
        report << "Load Factor    : " << loadFactor * 100 << " %\n";

        report.close();
        cout << "\nReport generated successfully: Daily_Energy_Report.txt\n";
    }
};

int main() {
    EnergyReport report;
    report.inputReadings();
    report.calculateMetrics();
    report.generateReport();
    return 0;
}