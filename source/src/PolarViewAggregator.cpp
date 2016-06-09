#include "../include/PolarViewAggregator.hpp"
#include <iostream>

//#define debug

namespace r2d2{
    PolarViewAggregator::PolarViewAggregator(){
    }

    // PolarView& PolarViewAggregator::aggregate(){
    // }
	
		std::map<r2d2::Angle, DistanceReading> PolarViewAggregator::translate_base_polarview(
            const std::map<r2d2::Angle, DistanceReading> & polarview,
            const r2d2::Translation & position_of_sensor){

                std::map<r2d2::Angle, DistanceReading> translated_polarview;

                for (const pair<r2d2::Angle, DistanceReading> & polar_view_iterator : polarview )
                    if(polar_view_iterator.second.get_result_type() == r2d2::DistanceReading::ResultType::CHECKED){



                        //calculate translation of translated polarpoint
                        r2d2::Translation PolarPoint = position_of_sensor+generate_polar_point(polar_view_iterator);


                        //prints debug info if debug_PolarViewAggregator is defined at the top of this file
                        #ifdef debug
                        std::cout << "debug info: x: " << PolarPoint.get_x()/r2d2::Length::CENTIMETER << ", y: " << PolarPoint.get_y()/r2d2::Length::CENTIMETER << std::endl;
                        #endif


                        //calculate angle of translated polarpoint
                        r2d2::Angle translated_angle(atan2(PolarPoint.get_y()/Length::CENTIMETER,PolarPoint.get_x()/Length::CENTIMETER)*Angle::rad);

                        //calculate distance of translated polarpoint
                        r2d2::DistanceReading translated_distance_reading(
                                    r2d2::Length(PolarPoint.get_length()),
                                    polar_view_iterator.second.get_result_type());

                        //make sure angle is a real number, not flotingpoint
                        translated_angle = nearbyint(translated_angle/r2d2::Angle::deg)*r2d2::Angle::deg;


                        //save translation in translated_polarview. if duplicates, shortest is dominant.
                        safe_add_polarview(translated_polarview,std::pair<r2d2::Angle, DistanceReading>(
                                               translated_angle,
                                               translated_distance_reading));



                    }
                return translated_polarview;
            }

        const r2d2::Translation PolarViewAggregator::generate_polar_point(const pair<r2d2::Angle, DistanceReading> & polar_view_pair){
                return r2d2::Translation(
                        polar_view_pair.second.get_length()*cos(polar_view_pair.first/r2d2::Angle::rad),
                        polar_view_pair.second.get_length()*sin(polar_view_pair.first/r2d2::Angle::rad),
                        0*r2d2::Length::CENTIMETER);
            }



        void PolarViewAggregator::safe_add_polarview(std::map<r2d2::Angle, DistanceReading> & foo, const pair<r2d2::Angle, DistanceReading> & bar){
                std::pair<std::map<r2d2::Angle, DistanceReading>::iterator,bool> emplaced_translation = foo.emplace(bar);
                if(!emplaced_translation.second){
                        if(emplaced_translation.first->second.get_length() > bar.second.get_length() ){
                                foo.insert(bar);
                            }
                    }
            }
	
















}
