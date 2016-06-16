//! \addtogroup 0028 PolarView Aggregator
//! \brief A PolarView Aggregator turns several PolarViews into one PolarView
//!
//! A PolarView Aggregator takes multiple PolarViews that are given to it by
//! sensors and moves the origin of the polarviews to the actual origin of the
//! system. This way you only have to check one polarview from a good origin
//! instead of several that are apart from eachother.
//!
//! \file   PolarViewAggregator.cpp
//! \author Koen de Gruijter
//! \date   Created: 14-06-2016
//! \date   Last Modified: 14-06-2016
//! \brief  the aggregator of MapPolarview sensors
//!
//! This class is used to aggregate the sensors from the
//! SensorAggregator<locatedDistanceSensor> to one single MapPolarView.
//!
//! \copyright Copyright © 2016, HU University of Applied Sciences Utrecht.
//! All rights reserved.
//!
//! License: newBSD
//!
//! Redistribution and use in source and binary forms,
//! with or without modification, are permitted provided that
//! the following conditions are met:
//! - Redistributions of source code must retain the above copyright notice,
//!   this list of conditions and the following disclaimer.
//! - Redistributions in binary form must reproduce the above copyright notice,
//!   this list of conditions and the following disclaimer in the documentation
//!   and/or other materials provided with the distribution.
//! - Neither the name of the HU University of Applied Sciences Utrecht
//!   nor the names of its contributors may be used to endorse or promote
//!   products derived from this software without specific prior written
//!   permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//! "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
//! BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
//! AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//! IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
//! BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//! OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//! WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//! OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//! EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ~< HEADER_VERSION 2016 04 12 >~
#include "../include/PolarViewAggregator.hpp"
#include <iostream>

namespace r2d2{

    MapPolarView PolarViewAggregator::aggregate(){
        std::forward_list<std::pair<const r2d2::MapPolarView&,
        const r2d2::Coordinate &>> untranslated_polarviews_list;

        for(LocatedDistanceSensor * sensor : sensors){
            untranslated_polarviews_list.push_front(
                std::make_pair(
                    *static_cast<r2d2::MapPolarView*>(
                    sensor->get_data().get_value().release()),
                    sensor->get_coordinate_attitude().get_coordinate()));
        }
        return aggregate_polarviews(untranslated_polarviews_list);
    }


    MapPolarView PolarViewAggregator::aggregate_polarviews(
        const std::forward_list<
        std::pair<const r2d2::MapPolarView &,
        const r2d2::Coordinate &>> & polarviews_list){


        std::forward_list<MapPolarView> translated_polarviews;
        //constructs translated_polarviews list out of Sensors
        for (auto it = polarviews_list.begin(); it != polarviews_list.end();
         ++it ){
            translated_polarviews.push_front(translate_base_polarview(
                it->first,
                it->second));
        }
        return merge_translated_polarviews(translated_polarviews);
    }


    MapPolarView PolarViewAggregator::translate_base_polarview(
        const r2d2::MapPolarView & polarview,
        const r2d2::Coordinate & coordinate_of_sensor){

        //calculates translation out of coordinate
        r2d2::Translation translation_of_sensor =
            coordinate_of_sensor-Coordinate::origin;

        MapPolarView translated_polarview;

        for (const std::pair<r2d2::Angle,
        DistanceReading> & polar_view_iterator : polarview.get_distances()){
            if(polar_view_iterator.second.get_result_type() ==
            r2d2::DistanceReading::ResultType::CHECKED){

                //calculate translated polarpoint(Cartesian coordinate system)
                // of untranslated polarpoint(Polar coordinate system)
                r2d2::Translation PolarPoint =
                    translation_of_sensor +
                        generate_polar_point(polar_view_iterator);

                //calculate angle of translated polarpoint.
                //needed to save polarpoint in Polar coordinate system.
                //use of atan2 needed because atans domain is to
                // small for an full polarview.
                r2d2::Angle translated_angle(
                    atan2(PolarPoint.get_y()/Length::CENTIMETER,
                        PolarPoint.get_x()/Length::CENTIMETER)*Angle::rad);

                //calculate distance of translated polarpoint
                //needed to save polarpoint in Polar coordinate system.
                r2d2::DistanceReading translated_distance_reading(
                    r2d2::Length(PolarPoint.get_length()),
                        polar_view_iterator.second.get_result_type());

                //make sure angle(deg) is a real number, not flotingpoint
                //to increase collision chance of angels.
                translated_angle =  nearbyint(translated_angle/
                    r2d2::Angle::deg)*r2d2::Angle::deg;

                //save translation in translated_polarview. if
                //angle collision, shortest distanceReading is dominant.
                safe_add_polarview(translated_polarview,std::make_pair(
                    translated_angle,translated_distance_reading));
            }
        }
        //collepse so polarview does not contain out of range angle collisions.
        translated_polarview.collapse();
        return translated_polarview;
    }



    const r2d2::Translation PolarViewAggregator::generate_polar_point(
        const std::pair<r2d2::Angle,
        DistanceReading> & polar_view_pair){
        return r2d2::Translation(
            polar_view_pair.second.get_length()*cos(
            polar_view_pair.first/r2d2::Angle::rad),
            polar_view_pair.second.get_length()*sin(
            polar_view_pair.first/r2d2::Angle::rad),
            0*r2d2::Length::CENTIMETER);
        }

    void PolarViewAggregator::safe_add_polarview(
        MapPolarView &map,
        std::pair<Angle, DistanceReading> polar_coord){

        if(polar_coord.second.get_result_type() ==
        DistanceReading::ResultType::CHECKED){
            DistanceReading old_distance=  map.get_distance(polar_coord.first);
            if(old_distance.get_result_type() ==
            DistanceReading::ResultType::CHECKED){
                if(polar_coord.second.get_length() < old_distance.get_length()){
                    map.add_distancereading(
                        polar_coord.first,
                        polar_coord.second);
                }
            }
            else{
                map.add_distancereading(polar_coord.first,polar_coord.second);
             }
        }
    }



    MapPolarView PolarViewAggregator::merge_translated_polarviews(
        const std::forward_list<MapPolarView> &
        polarview_list){

        MapPolarView merged_polarview;

        for(int x = -180; x<180; x++){
            r2d2::Angle angle= x*r2d2::Angle::deg;
            for(const MapPolarView & polarview  : polarview_list ){
                DistanceReading polar_coord = polarview.get_distance(angle);
                if(polar_coord.get_result_type() ==
                r2d2::DistanceReading::ResultType::CHECKED){
                    merged_polarview.add_distancereading(angle,polar_coord);
                }
            }
        }
        return merged_polarview;
    }
}
