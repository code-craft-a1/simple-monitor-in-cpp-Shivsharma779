#include "./monitor.h"
#include <iostream>
#include <chrono>
#include <thread>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

struct VitalThreshold {
    float min;
    float max;
    const char* name;
    const char* alertMessage;
};

bool isVitalInRange(float value, VitalThreshold threshold) {
    return value >= threshold.min && value <= threshold.max;
}

void showAlert(const char* message) {
    cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

bool checkAndAlert(float value, VitalThreshold threshold) {
    if (!isVitalInRange(value, threshold)) {
        showAlert(threshold.alertMessage);
        return false;
    }
    return true;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalThreshold tempThresh = {95, 102, "Temperature", "Temperature is critical!"};
    VitalThreshold pulseThresh = {60, 100, "Pulse Rate", "Pulse Rate is out of range!"};
    VitalThreshold spo2Thresh = {90, 100, "SPO2", "Oxygen Saturation out of range!"};

    return checkAndAlert(temperature, tempThresh)
        && checkAndAlert(pulseRate, pulseThresh)
        && checkAndAlert(spo2, spo2Thresh);
}
