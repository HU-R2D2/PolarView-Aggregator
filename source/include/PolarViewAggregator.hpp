#ifndef POLARVIEWAGGREGATOR_H
#define POLARVIEWAGGREGATOR_H

#ifdef debug
#define debug_PolarViewAggregator
#endif

// #include "SensorAggregator.hpp"
#include "Translation.hpp"
#include "Length.hpp"
#include "DistanceReading.hpp"
#include <map>
#include "Angle.hpp"
#include <math.h>
#include <vector>

namespace r2d2{
    class PolarViewAggregator{

    private:

        const r2d2::Translation generate_polar_point(const pair<r2d2::Angle, DistanceReading> & polar_view_pair);

        void safe_add_polarview(std::map<r2d2::Angle, DistanceReading> & map, pair<r2d2::Angle, DistanceReading> polar_coord);

        std::map<r2d2::Angle, DistanceReading> merge_translated_polarviews(const std::vector<std::map<r2d2::Angle, DistanceReading>> & polarview);

        std::map<r2d2::Angle, DistanceReading> translate_base_polarview(
                                    const std::map<r2d2::Angle, DistanceReading> & polarview,
                                    const r2d2::Translation & position_of_sensor);

    public:
        PolarViewAggregator();
        std::map<r2d2::Angle, DistanceReading> aggregate();
        };
}
#endif
