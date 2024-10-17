#ifndef utils_h
#define utils_h

#include <cmath>

namespace viator::dsp
{
    namespace decibels
    {
        static double db_to_gain(const double db_input)
        {
            return std::pow(10, db_input * 0.05f);
        }
    }

    namespace clippers
    {
        static float get_hard_clipped_data(float input)
        {
            if (std::abs(input) >= 0.99f)
            {
                input = std::copysign(0.99f, input);
            }

            return input;
        }
    }
}

#endif /* utils_h */
