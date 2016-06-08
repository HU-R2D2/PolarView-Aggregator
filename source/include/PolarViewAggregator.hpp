#ifndef POLARVIEWAGGREGATOR_H
#define POLARVIEWAGGREGATOR_H

#include "../../../polarview/source/include/MapPolarView.hpp"
// #include "SensorAggregator.hpp"

namespace R2D2{
    class PolarViewAggregator{
    public:
        PolarViewAggregator();
        PolarView& aggregate();
    };

}
#endif
