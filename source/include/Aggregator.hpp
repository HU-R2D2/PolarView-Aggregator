#ifndef AGGREGATOR_H
#define AGGREGATOR_H

namespace R2D2{
    class SensorAggregator{
    public:
        virtual T aggregate() = 0;
    };
}
#endif
