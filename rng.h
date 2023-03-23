#include <cstdint> 
// Modified version of the Numerical Recipes ran2 generator. 
class Ran
{
private:
    uint64_t u, v, w;
    inline uint64_t int64()
    {
        u = u * 2862933555777941757UL + 704602954386353087UL;
        v ^= v >> 17; v ^= v << 31; v ^= v >> 8;
        w = 4294957665U * (w & 0xffffffff) + (w >> 32);
        uint64_t x = u ^ (u << 21); x ^= x >> 35; x ^= x << 4;
        return (x + v) ^ w;
    }
public:
    inline explicit Ran(uint64_t seed = 123456789UL) :
        u(0), v(4101842887655102017UL), w(1)
    {
        u = seed ^ v; int64();
        v = u; int64();
        w = v; int64();
    }
    inline operator double() { return 5.42101086242752217e-20 * int64(); }
}; 
