#define CHANNELS 40

/*
 * Frequency look up table :
 * To avoid Wifi channels, 40 Bluetooth channels are defined below (they already
 * avoid Wifi common channels) : from 2402 MHz to 2480 MHz, step 2 MHz.
 * User can define channel count for Ranging run, and it is optimized to have
 * several frequencies in the largest band as possible. Also the 40 frequencies 
 * are generated by random sorting to preferate the 10 first in the largest band
 * as possible (10 is the shortest channel count the user can choose).
 */
const uint32_t Channels[] =
{
 2450000000,
 2402000000,
 2476000000,
 2436000000,
 2430000000,
 2468000000,
 2458000000,
 2416000000,
 2424000000,
 2478000000,
 2456000000,
 2448000000,
 2462000000,
 2472000000,
 2432000000,
 2446000000,
 2422000000,
 2442000000,
 2460000000,
 2474000000,
 2414000000,
 2464000000,
 2454000000,
 2444000000,
 2404000000,
 2434000000,
 2410000000,
 2408000000,
 2440000000,
 2452000000,
 2480000000,
 2426000000,
 2428000000,
 2466000000,
 2418000000,
 2412000000,
 2406000000,
 2470000000,
 2438000000,
 2420000000,
};
