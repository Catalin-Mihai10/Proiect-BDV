#ifndef TORNADO_HEADER
#define TORNADO_HEADER

typedef struct Tornado
{
    /**
     * NOTE: Use 2bytes to store values since windows encodes
     *  character in two bytes. Switch this to 1byte to store the
     * values in Linux. Idk about MacOs.
     */
    u16 year,
        tornadoWidth,
        month,
        day,
        injuries,
        fatalities;

    s16 magnitude;

    char date[11],
        state[3],
        lengthCat[7],
        widthCat[7];

    d32 beginningLatitude,
        beginningLongitude,
        endLatitude,
        endLongitude,
        tornadoLength;
} Tornado;

#endif