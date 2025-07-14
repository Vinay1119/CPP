#include <iostream>
#include <vector>
#include <map>
#include <cmath>    // for fabs
#include <string>
using namespace std;

// Struct to store one consumer's load
struct Load {
    string consumer_id;
    float power_kw;
    char phase; // 'A', 'B', or 'C'
};

// Feeder class that holds all loads and performs calculations
class Feeder {
private:
    string name;
    vector<Load> loads;

public:
    Feeder(string feeder_name) {
        name = feeder_name;
    }

    // Add a new load to the feeder
    void addLoad(const Load& load) {
        loads.push_back(load);
    }

    // Calculate total load per phase (A, B, C)
    map<char, float> calculatePhaseLoad() {
        map<char, float> phaseLoad;
        phaseLoad['A'] = 0.0;
        phaseLoad['B'] = 0.0;
        phaseLoad['C'] = 0.0;

        for (int i = 0; i < (int)loads.size(); ++i) {
            char phase = toupper(loads[i].phase); // in case user enters 'a' instead of 'A'
            if (phaseLoad.find(phase) != phaseLoad.end()) {
                phaseLoad[phase] += loads[i].power_kw;
            }
        }

        return phaseLoad;
    }

    // Calculate imbalance factor: (max deviation from average) / average
    float calculateImbalanceFactor() {
        map<char, float> phaseLoad = calculatePhaseLoad();

        float total = phaseLoad['A'] + phaseLoad['B'] + phaseLoad['C'];
        float avg = total / 3.0;

        float devA = fabs(phaseLoad['A'] - avg);
        float devB = fabs(phaseLoad['B'] - avg);
        float devC = fabs(phaseLoad['C'] - avg);

        float max_dev = devA;
        if (devB > max_dev) max_dev = devB;
        if (devC > max_dev) max_dev = devC;

        if (avg == 0) return 0;
        return (max_dev / avg) * 100;
    }

    // Display the result in readable format
    void displayReport() {
        map<char, float> phaseLoad = calculatePhaseLoad();

        cout << "Feeder: " << name << endl;
        cout << "  Phase A Load: " << phaseLoad['A'] << " kW" << endl;
        cout << "  Phase B Load: " << phaseLoad['B'] << " kW" << endl;
        cout << "  Phase C Load: " << phaseLoad['C'] << " kW" << endl;
        cout << "  Imbalance Factor: " << calculateImbalanceFactor() << " %" << endl;
    }
};

int main() {
    Feeder feeder1("Feeder-1");

    int n;
    cout << "Enter number of loads: ";
    cin >> n;

    cout << "Enter load details (consumer_id power_kW phase[A/B/C]):" << endl;
    for (int i = 0; i < n; ++i) {
        Load load;
        cin >> load.consumer_id >> load.power_kw >> load.phase;
        load.phase = toupper(load.phase); // convert to uppercase
        feeder1.addLoad(load);
    }

    cout << "\n=== Load Balance Report ===" << endl;
    feeder1.displayReport();

    return 0;
}