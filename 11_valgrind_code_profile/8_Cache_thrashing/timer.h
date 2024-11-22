#ifndef CMC_TIMER_H
#define CMC_TIMER_H

#include <time.h>

typedef struct timer_s
{
    clock_t start;
    clock_t stop;
    //double result;
    void Start()
    {
        start = clock();
    }

    void Stop()
    {
        stop = clock();
    }

    double Elapsed()
    {
        return (double)(stop -start);
    }
} Timer;

#endif /* CMC_TIMER_H */
