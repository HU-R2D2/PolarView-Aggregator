#ifndef POLARVIEWAGGREGATOR_H
#define POLARVIEWAGGREGATOR_H

#ifdef debug
#define debug_PolarViewAggregator
#endif

#include "SensorAggregator.hpp"
#include "Translation.hpp"
#include "Length.hpp"
#include "DistanceReading.hpp"
#include <map>
#include "Angle.hpp"
#include <math.h>
#include <vector>
#include "LocatedDistanceSensor.hpp"

namespace r2d2{
    class PolarViewAggregator: public r2d2::SensorAggregator<LocatedDistanceSensor,PolarViewAggregator>{

    private:

        const r2d2::Translation generate_polar_point(
            const pair<r2d2::Angle,
            DistanceReading> & polar_view_pair);

        void safe_add_polarview(
            std::map<r2d2::Angle,
            DistanceReading> & map,
            pair<r2d2::Angle, DistanceReading> polar_coord);

        //merge vector of polarviews
        std::map<r2d2::Angle, DistanceReading> merge_translated_polarviews(
            const std::vector<std::map<r2d2::Angle,
            DistanceReading>> & polarview);

        //translated polarview
        std::map<r2d2::Angle, DistanceReading> translate_base_polarview(
            const std::map<r2d2::Angle, DistanceReading> & polarview,
            const r2d2::Coordinate & position_of_sensor);

    public:
        LocatedDistanceSensor * aggregate();

        PolarViewAggregator();

        };
}
#endif
