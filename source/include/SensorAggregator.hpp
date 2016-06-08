#ifndef SENSORAGGREGATOR_H
#define SENSORAGGREGATOR_H

#include <vector>
#include "../../../sensorInterfaces/source/include/Sensor.hpp"

namespace R2D2{
    template<typename T>
    class SensorAggregator{
    public:
        virtual T aggregate() = 0;
        void add_sensor(Sensor<T> sensor);

    private:
        std::vector<Sensor<T>> sensors;
    };
}
#endif
