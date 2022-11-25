#ifndef RTC_H
#define RTC_H

#include <stdio.h>
#include <time.h>
#include "types.h"

// Defines taken from ds1742 linux kernel driver
#define bcd2bin(x) (((x) & 0x0f) + ((x) >> 4) * 10)
#define bin2bcd(x) ((((x) / 10) << 4) + (x) % 10)


#define RTC_SIZE           8
#define RTC_ADDRESS        (0x800 - RTC_SIZE)

#define RTC_CONTROL        (0 + RTC_ADDRESS)
#define RTC_CENTURY        (0 + RTC_ADDRESS)
#define RTC_SECONDS        (1 + RTC_ADDRESS)
#define RTC_MINUTES        (2 + RTC_ADDRESS)
#define RTC_HOURS          (3 + RTC_ADDRESS)
#define RTC_DAY            (4 + RTC_ADDRESS)
#define RTC_DATE           (5 + RTC_ADDRESS)
#define RTC_MONTH          (6 + RTC_ADDRESS)
#define RTC_YEAR           (7 + RTC_ADDRESS)

#define RTC_CENTURY_MASK    0x3f
#define RTC_SECONDS_MASK    0x7f
#define RTC_DAY_MASK        0x07

/* Bits in the Control/Century register */
#define RTC_WRITE        0x80
#define RTC_READ        0x40

/* Bits in the Seconds register */
#define RTC_STOP        0x80

/* Bits in the Day register */
#define RTC_BATT_FLAG        0x80

uint8_t rtc_read(cpu_t *cpu, uint32_t offset) {
    offset -= RTC_ADDRESS;
    if (offset > 3) {
        return (cpu->rtc1 >> ((offset - 4) * 8)) & 0xff;
    }
    return (cpu->rtc0 >> (offset * 8)) & 0xff;
}

void rtc_write(cpu_t *cpu, uint32_t offset, uint8_t data) {
    switch (offset) {
        case RTC_CONTROL:
            if (data == RTC_READ) {
                if (VERBOSE >= 1)
                    printf("RTC update!\n");
                // Get real time from host
                struct timespec ts;
                clock_gettime(CLOCK_REALTIME, &ts);
                struct tm *t = localtime(&ts.tv_sec);
                cpu->rtc0 =
                    bin2bcd((t->tm_year + 1900) / 100) |
                    bin2bcd(t->tm_sec) << 8 |
                    bin2bcd(t->tm_min) << 16 |
                    bin2bcd(t->tm_hour) << 24;
                cpu->rtc1 =
                    bin2bcd(t->tm_wday) |
                    bin2bcd(t->tm_mday) << 8 |
                    bin2bcd(t->tm_mon + 1) << 16 |
                    bin2bcd(t->tm_year % 100) << 24;
            }
            break;
    }
}

#endif
