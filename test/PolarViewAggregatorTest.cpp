
#include "PolarViewAggregator.hpp"

using namespace r2d2;

// constructors:


//generate_polar_point;
    //check input domein
        //positieve hoek <360
        //negatief hoek input > -360
        //input negatieve hoek < -360deg (bijboorbeeld 400deg)
        //input hoek > 360 deg
        //input hoek groter > 360
    //genegeer output mogelijkheden en check voor > 0 of < 0
        // x+ y+
        // x+ y-
        // x- y-
        // x- y+

//safe_add_polarview
    //controleer dan hij de kortste polar pakt bij een duplicaat
        //voor zowel eerst kort toevoegen als eerst lang invoegen
    //controleer of hij positieve hoek terug kan geven
    //contoleren of hij negatieve hoeken terug geeft (mag niet)

//merge_translated_polarviews
    //????

//translate_base_polarview
    //???

//PolarViewAggregator();

//aggregate();
