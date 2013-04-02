#pragma once

#include "src/gps/gpsReceiverInterface.h"

namespace PlaneTracking {
  class GPSProtocol;
  class SerialConnection;

  class PlaneGPSReceiver : public GPSReceiverInterface {
    PlaneGPSReceiver(shared_ptr<GPSProtocol> protocol,
                     shared_ptr<SerialConnection> serial);

  }
}
