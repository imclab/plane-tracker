#pragma once

#include "src/commanding/commanders/interface.h"
#include "src/commanding/gimbalCommander.h"

namespace PlaneTracking {
  class DataAggregator;
  class GPSOnlyCommander : public GPSAvailable,
                                  GimbalCommander {
    GPSOnlyCommander(shared_ptr<DataAggregator> aggregator);
  };
}
