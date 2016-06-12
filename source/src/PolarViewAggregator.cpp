#include "../include/PolarViewAggregator.hpp"
#include <iostream>



namespace r2d2{


            LocatedDistanceSensor *PolarViewAggregator::aggregate(){

                    std::forward_list<std::pair<const r2d2::MapPolarView&,const r2d2::Coordinate &>> harry_henk_alles;

                    for(LocatedDistanceSensor * sensor : sensors){
                            harry_henk_alles.push_front(
                                        std::make_pair(
                                            *static_cast<r2d2::MapPolarView*>(sensor->get_data().get_value().release()),
                                            sensor->get_coordinate_attitude().get_coordinate()));
                        }

                    aggregate_polarviews(harry_henk_alles);
                    //TODO: construct locatedDistance Sensor
                    return nullptr;
                }


            MapPolarView PolarViewAggregator::aggregate_polarviews(
                    const std::forward_list<
                    std::pair<const r2d2::MapPolarView &,
                    const r2d2::Coordinate &>> & harry){


                    std::forward_list<MapPolarView> translated_polarviews;
                    for (auto it = harry.begin(); it != harry.end(); ++it ){
                            //fill translated_polarviews

                            translated_polarviews.push_front(translate_base_polarview(
                                                                 it->first,
                                                                 it->second));
                        }


                    //merge translated_polarviews
                    return merge_translated_polarviews(translated_polarviews);


                    //return PolarView();
                }


        MapPolarView PolarViewAggregator::translate_base_polarview(const r2d2::MapPolarView & polarview,
                                                      const r2d2::Coordinate & sdaf){
                r2d2::Translation position_of_sensor = sdaf-Coordinate::origin;

            std::map<r2d2::Angle, DistanceReading> bobby = polarview.get_distances();
            MapPolarView translated_polarview;

            for (const pair<r2d2::Angle,
                DistanceReading> & polar_view_iterator : bobby ){
                    if(polar_view_iterator.second.get_result_type() ==
                     r2d2::DistanceReading::ResultType::CHECKED){

                        //calculate Coordinate of translated polarpoint
                        r2d2::Translation PolarPoint =
                        position_of_sensor +
                        generate_polar_point(polar_view_iterator);

                        //prints debug info if debug_PolarViewAggregator is
                        //defined at the top of this file
                        #ifdef debug_PolarViewAggregator
                        std::cout <<
                        "PolarViewAggregator@translate_base_polarview. x: " <<
                        PolarPoint.get_x()/r2d2::Length::CENTIMETER <<
                        ", y: " << PolarPoint.get_y()/r2d2::Length::CENTIMETER
                        << std::endl;
                        #endif

                        //calculate angle of translated polarpoint
                        r2d2::Angle translated_angle(
                            atan2(PolarPoint.get_y()/Length::CENTIMETER,
                            PolarPoint.get_x()/Length::CENTIMETER)*Angle::rad);

                        //calculate distance of translated polarpoint
                        r2d2::DistanceReading translated_distance_reading(
                                r2d2::Length(PolarPoint.get_length()),
                                polar_view_iterator.second.get_result_type());

                        //make sure angle is a real number, not flotingpoint
                        translated_angle =  nearbyint(translated_angle/
                                            r2d2::Angle::deg)*r2d2::Angle::deg;

                        //save translation in translated_polarview. if
                        //duplicates, shortest is dominant.

                        translated_polarview.add_distancereading(translated_angle,translated_distance_reading);
                    }
                }
            translated_polarview.collapse();
            return translated_polarview;
            }



        const r2d2::Translation PolarViewAggregator::generate_polar_point(
                                            const pair<r2d2::Angle,
                                            DistanceReading> & polar_view_pair){
                return r2d2::Translation(
                    polar_view_pair.second.get_length()*cos(
                        polar_view_pair.first/r2d2::Angle::rad),
                    polar_view_pair.second.get_length()*sin(
                        polar_view_pair.first/r2d2::Angle::rad),
                    0*r2d2::Length::CENTIMETER);
            }

        void PolarViewAggregator::safe_add_polarview(
                                std::map<r2d2::Angle, DistanceReading> & map,
                                pair<r2d2::Angle, DistanceReading> polar_coord){
                polar_coord.first = polar_coord.first.normalize();
                std::pair<std::map<r2d2::Angle, DistanceReading>::iterator,bool>
                 emplaced_translation = map.emplace(polar_coord);
                if(!emplaced_translation.second){
                        if(emplaced_translation.first->second.get_length() >
                                            polar_coord.second.get_length() ){
                                map.insert(polar_coord);
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
