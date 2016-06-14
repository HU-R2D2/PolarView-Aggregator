#include "../include/PolarViewAggregator.hpp"
#include <iostream>

namespace r2d2{


            MapPolarView PolarViewAggregator::aggregate(){

                    std::forward_list<std::pair<const r2d2::MapPolarView&,const r2d2::Coordinate &>> untranslated_polarviews_list;

                    for(LocatedDistanceSensor * sensor : sensors){
                            untranslated_polarviews_list.push_front(
                                        std::make_pair(
                                            *static_cast<r2d2::MapPolarView*>(sensor->get_data().get_value().release()),
                                            sensor->get_coordinate_attitude().get_coordinate()));
                        }

                    return aggregate_polarviews(untranslated_polarviews_list);
                }


            MapPolarView PolarViewAggregator::aggregate_polarviews(
                    const std::forward_list<
                    std::pair<const r2d2::MapPolarView &,
                    const r2d2::Coordinate &>> & polarviews_list){


                    std::forward_list<MapPolarView> translated_polarviews;
                    for (auto it = polarviews_list.begin(); it != polarviews_list.end(); ++it ){
                            //fill translated_polarviews
                            translated_polarviews.push_front(
                                        translate_base_polarview(
                                                         it->first,
                                                         it->second));
                        }
                    return merge_translated_polarviews(translated_polarviews);
                }


        MapPolarView PolarViewAggregator::translate_base_polarview(const r2d2::MapPolarView & polarview,
                                                      const r2d2::Coordinate & coordinate_of_sensor){
                r2d2::Translation translation_of_sensor = coordinate_of_sensor-Coordinate::origin;

            MapPolarView translated_polarview;

            for (const pair<r2d2::Angle,
                DistanceReading> & polar_view_iterator : polarview.get_distances() ){
                    if(polar_view_iterator.second.get_result_type() ==
                     r2d2::DistanceReading::ResultType::CHECKED){

                        //calculate Coordinate of translated polarpoint
                        r2d2::Translation PolarPoint =
                        translation_of_sensor +
                        generate_polar_point(polar_view_iterator);

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
                        safe_add_polarview(translated_polarview,std::make_pair(translated_angle,translated_distance_reading));
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

        void PolarViewAggregator::safe_add_polarview(MapPolarView &map, pair<Angle, DistanceReading> polar_coord)
            {
                if (polar_coord.second.get_result_type() == DistanceReading::ResultType::CHECKED){
                       DistanceReading old_distance=  map.get_distance(polar_coord.first);
                       if(old_distance.get_result_type() == DistanceReading::ResultType::CHECKED){
                               if(polar_coord.second.get_length() < old_distance.get_length()){
                                       map.add_distancereading(polar_coord.first,polar_coord.second);
                                   }
                           } else{
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
