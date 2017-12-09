#include "timer.h"
#include "isr.h"
#include "screen.h"
#include "process.h"
#include "common.h"

uint32 gSystemTickCount = 0;

BOOL gSchedulerEnabled = FALSE;

//called from assembly
void handleTimerIRQ(TimerInt_Registers registers)
{
    gSystemTickCount++;

    if (gSystemTickCount % 10 == 0 && gSchedulerEnabled == TRUE)
    {
        schedule(&registers);
    }
}

uint32 getSystemTickCount()
{
    return gSystemTickCount;
}

void enableScheduler()
{
    gSchedulerEnabled = TRUE;
}

void disableScheduler()
{
    gSchedulerEnabled = FALSE;
}

void initTimer(uint32 frequency)
{
    uint32 divisor = 1193180 / frequency;

    outb(0x43, 0x36);

    uint8 l = (uint8)(divisor & 0xFF);
    uint8 h = (uint8)( (divisor>>8) & 0xFF );

    outb(0x40, l);
    outb(0x40, h);
}
