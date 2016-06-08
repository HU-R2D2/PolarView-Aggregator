#ifndef POLARVIEWAGGREGATOR_H
#define POLARVIEWAGGREGATOR_H

#include "../../../polarview/source/include/MapPolarView.hpp"
// #include "SensorAggregator.hpp"
#include "Translation.hpp"
#include "length.hpp"
#include "DistanceReading.hpp"
#include <map>
#include "Angle.hpp"
#include <math.h>

namespace r2d2{
    class PolarViewAggregator{


    public:
        PolarViewAggregator();
        PolarView& aggregate();


        std::map<r2d2::Angle, DistanceReading> translate_base_polarview(
                                    const std::map<r2d2::Angle, DistanceReading> & polarview,
                                    const r2d2::Translation & position_of_sensor);
    };

}
#endif
