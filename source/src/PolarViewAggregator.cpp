#include "../include/PolarViewAggregator.hpp"
#include <iostream>
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
                        r2d2::Translation PolarPoint(position_of_sensor+r2d2::Translation{
                                        polar_view_iterator.second.get_length()*cos(polar_view_iterator.first/r2d2::Angle::rad),
                                        polar_view_iterator.second.get_length()*sin(polar_view_iterator.first/r2d2::Angle::rad),
                                        0*r2d2::Length::CENTIMETER});

                        std::cout << "debug info: x: " << PolarPoint.get_x()/r2d2::Length::CENTIMETER << ", y: " << PolarPoint.get_y()/r2d2::Length::CENTIMETER << std::endl;

                        //calculate angle of translated polarpoint
                        r2d2::Angle translated_angle(atan2(PolarPoint.get_y()/Length::CENTIMETER,PolarPoint.get_x()/Length::CENTIMETER)*Angle::rad);

                        //calculate distance of translated polarpoint
                        r2d2::DistanceReading translated_distance_reading(
                                    //r2d2::Length(sin(translated_angle/r2d2::Angle::rad)*PolarPoint.get_y()*500),
                                    r2d2::Length(PolarPoint.get_length()),
                                    polar_view_iterator.second.get_result_type());

                        //make sure angle is a real number, not flotingpoint
                        translated_angle = nearbyint(translated_angle/r2d2::Angle::deg)*r2d2::Angle::deg;

                        //save in new (check for duplicates)
                        translated_polarview.insert(std::pair<r2d2::Angle, DistanceReading>(
                                    translated_angle,
                                    translated_distance_reading));
                    }
                return translated_polarview;
            }


	
}
