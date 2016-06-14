#include <gtest/gtest.h>
#include "../source/include/PolarViewAggregator.hpp"
#include "MapPolarView.hpp"
#include "Angle.hpp"
#include "Length.hpp"
#include "Coordinate.hpp"
#include <forward_list>

TEST(PolarViewAggregator, Aggregate_polarviews){
    r2d2::Coordinate trans1 {2 * r2d2::Length::METER, -2* r2d2::Length::METER, -5* r2d2::Length::METER};
    r2d2::Coordinate trans2 {4 * r2d2::Length::METER, 2* r2d2::Length::METER, 5* r2d2::Length::METER};

    r2d2::MapPolarView testpolar1 = r2d2::MapPolarView();
    r2d2::MapPolarView testpolar2 = r2d2::MapPolarView();

    r2d2::Length len1 = 6*r2d2::Length::METER;
    r2d2::Length len2 = 3*r2d2::Length::METER;

    r2d2::DistanceReading distread1 = r2d2::DistanceReading(len1, r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distread2 = r2d2::DistanceReading(len2, r2d2::DistanceReading::ResultType::CHECKED);

    for (int i = 5; i < 350; i+=10){
        testpolar1.add_distancereading(i*r2d2::Angle::deg, distread1);
    }

    for (int i = 1; i < 350; i+=10){
        testpolar2.add_distancereading(i*r2d2::Angle::deg, distread2);
    }

    std::forward_list<std::pair<const r2d2::MapPolarView&,const r2d2::Coordinate &>> fw_polar_list;
   fw_polar_list.push_front( std::pair<const r2d2::MapPolarView &,
                            const r2d2::Coordinate &>(testpolar1,trans1));
   fw_polar_list.push_front( std::pair<const r2d2::MapPolarView &,
                            const r2d2::Coordinate &>(testpolar2,trans2));

   r2d2::MapPolarView aggregated_polarview = r2d2::PolarViewAggregator::aggregate_polarviews(fw_polar_list);
}

TEST(PolarViewAggregator, translate_polarview){
    r2d2::Coordinate trans1 {2 * r2d2::Length::METER, -2* r2d2::Length::METER, -5* r2d2::Length::METER};

    r2d2::MapPolarView testpolar1 = r2d2::MapPolarView();

    r2d2::Length len1 = 6*r2d2::Length::METER;

    r2d2::DistanceReading distread1 = r2d2::DistanceReading(len1, r2d2::DistanceReading::ResultType::CHECKED);

    testpolar1.add_distancereading(5*r2d2::Angle::deg, distread1);
    testpolar1.add_distancereading(15*r2d2::Angle::deg, distread1);
    testpolar1.add_distancereading(25*r2d2::Angle::deg, distread1);
    testpolar1.add_distancereading(35*r2d2::Angle::deg, distread1);
    testpolar1.add_distancereading(45*r2d2::Angle::deg, distread1);
    testpolar1.add_distancereading(55*r2d2::Angle::deg, distread1);
    testpolar1.add_distancereading(65*r2d2::Angle::deg, distread1);
    testpolar1.add_distancereading(75*r2d2::Angle::deg, distread1);

    std::forward_list<std::pair<const r2d2::MapPolarView&,const r2d2::Coordinate &>> fw_polar_list;
   fw_polar_list.push_front( std::pair<const r2d2::MapPolarView &,
                            const r2d2::Coordinate &>(testpolar1,trans1));

   r2d2::MapPolarView aggregated_polarview = r2d2::PolarViewAggregator::aggregate_polarviews(fw_polar_list);
}
