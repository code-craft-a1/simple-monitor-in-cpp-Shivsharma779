#include "./monitor.h"
#include <iostream>
#include <chrono>
#include <thread>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

struct VitalThreshold {
  float min;
  float max;
  const char* alertMessage;
};

bool isVitalInRange(float value, const VitalThreshold& threshold) {
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

int vitalsOk(float temperature, float pulseRate, float spo2) {
  const VitalThreshold thresholds[] = {
    {95, 102, "Temperature is critical!"},
    {60, 100, "Pulse Rate is out of range!"},
    {90, 100, "Oxygen Saturation out of range!"}
  };
  const float values[] = {temperature, pulseRate, spo2};

  for (int i = 0; i < 3; ++i) {
    if (!isVitalInRange(values[i], thresholds[i])) {
      showAlert(thresholds[i].alertMessage);
      return 0;
    }
  }
  return 1;
}
