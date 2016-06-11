//! \addtogroup 0028 PolarView Aggregator
//! \brief A PolarView Aggregator turns several PolarViews into one PolarView
//!
//! A PolarView Aggregator takes multiple PolarViews that are given to it by
//! sensors and moves the origin of the polarviews to the actual origin of the
//! system. This way you only have to check one polarview from a good origin
//! instead of several that are apart from eachother.
//!
//! \file   Aggregator.hpp
//! \author Christiaan van den Berg - 1660475
//! \date   Created: 06-06-2016
//! \date   Last Modified: 08-06-2016
//! \brief  Header of SensorAggregator
//!
//! This class is used to add sensors to a vector so they can be used to easily
//! get the data from the sensors.
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
#ifndef SENSORAGGREGATOR_H
#define SENSORAGGREGATOR_H

#include <vector>
#include "../sensorInterfaces/source/include/Sensor.hpp"

namespace r2d2{
    template<typename SENSOR_TYPE , typename DERIVED_AGGREGATOR_TYPE>
    class SensorAggregator{
    public:

        SENSOR_TYPE * aggregate(){
               return static_cast<DERIVED_AGGREGATOR_TYPE*>(this)->aggregate();
            }

        // Adds the sensor to the sensors vector for later use
        // \param Sensor<T> sensor a sensor that has to be added to the vector.
        void add_sensor(SENSOR_TYPE * sensor){
                        sensors.push_back(sensor);
                    }

    protected:
        std::vector<SENSOR_TYPE*> sensors;
    };
}
#endif
