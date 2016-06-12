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
#include "PolarView.hpp"
#include <forward_list>
#include <MapPolarView.hpp>

namespace r2d2{
    class PolarViewAggregator: public r2d2::SensorAggregator<LocatedDistanceSensor,PolarViewAggregator>{

    private:

        static const r2d2::Translation generate_polar_point(
            const pair<r2d2::Angle,
            DistanceReading> & polar_view_pair);

        static void safe_add_polarview(
            std::map<r2d2::Angle,
            DistanceReading> & map,
            pair<r2d2::Angle, DistanceReading> polar_coord);

        //merge vector of polarviews
        static MapPolarView merge_translated_polarviews(const std::forward_list<MapPolarView> &polarview_list);

        //translated polarview
        static MapPolarView translate_base_polarview(const r2d2::MapPolarView & polarview, const r2d2::Coordinate &position_of_sensor);

    public:
        //this method overwrites the "virtual" aggregate method in SensorAggegator
        LocatedDistanceSensor * aggregate();
        //PolarView * aggregate_polarviews(std::vector<std::pair<PolarView,Coordinate>> harry);

        PolarViewAggregator();

        static MapPolarView aggregate_polarviews(const std::forward_list<std::pair<const r2d2::MapPolarView &, const r2d2::Coordinate &> > &harry);
        };
}
#endif
