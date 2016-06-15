//! \addtogroup 0028 PolarView Aggregator
//! \brief A PolarView Aggregator turns several PolarViews into one PolarView
//!
//! A PolarView Aggregator takes multiple PolarViews that are given to it by
//! sensors and moves the origin of the polarviews to the actual origin of the
//! system. This way you only have to check one polarview from a good origin
//! instead of several that are apart from eachother.
//!
//! \file   PolarViewAggregator.hpp
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


#ifndef POLARVIEWAGGREGATOR_H
#define POLARVIEWAGGREGATOR_H

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
#include "Coordinate.hpp"

namespace r2d2{
    class PolarViewAggregator: public r2d2::SensorAggregator<
                                LocatedDistanceSensor,
                                r2d2::MapPolarView>{

    private:

        static const r2d2::Translation generate_polar_point(
            const std::pair<r2d2::Angle,
            DistanceReading> & polar_view_pair);

        static void safe_add_polarview(
            MapPolarView & map,
            std::pair<r2d2::Angle, DistanceReading> polar_coord);

        //merge vector of polarviews
        static MapPolarView merge_translated_polarviews(
                        const std::forward_list<MapPolarView> &polarview_list);

        //translated polarview
        static MapPolarView translate_base_polarview(
                        const r2d2::MapPolarView & polarview,
                        const r2d2::Coordinate &position_of_sensor);

    public:
        //! this method overwrites the virtual SensorAggregator::aggregate()
		//! \return An aggregated(merged) MapPolarView of all the sensors in
        //! the sensor list.
        MapPolarView aggregate();

		//! constructor
        PolarViewAggregator();

        //! Merges an polarview forward_list to one polarview
        //! \param polarviews_list an list polarviews per sensor and their
        //! location that that will be aggregated.
        //! \return A single merged MapPolarView.
        static MapPolarView aggregate_polarviews(
                const std::forward_list<std::pair<const r2d2::MapPolarView &,
                const r2d2::Coordinate &> > &polarviews_list);
        };
}
#endif
