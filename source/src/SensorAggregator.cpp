#include "../include/SensorAggregator.hpp"
namespace R2D2{
    template<typename T>
    void SensorAggregator<T>::add_sensor(Sensor<T> sensor){
        sensors.push_back(sensor);
    }
}
