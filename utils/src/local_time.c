#include "local_time.h"

char *convert_millis_to_date(long long millis,
                             bool include_year) {
    const char *months[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
    };
    const char *days_of_the_week[] = {
            "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",
            "Sunday"
    };

    time_t seconds = millis / 1000;
    struct tm *local_time = localtime(&seconds);
    char *time_str;

    const char *month = months[local_time->tm_mon];
    int day_of_the_month = local_time->tm_mday;
    const char *day_of_the_week = days_of_the_week[local_time->tm_wday];

    if (include_year) {
        const int minimum_year = 1900;
        int year = minimum_year + local_time->tm_year;
        asprintf(&time_str, "%d, %s %d, %s", year, month, day_of_the_month,
                 day_of_the_week);
    }
    else {
        asprintf(&time_str, "%s %d, %s", month, day_of_the_month,
                 day_of_the_week);
    }
    return time_str;
}

char *convert_millis_to_hour_and_minute(long long millis) {
    time_t seconds = millis / 1000;
    struct tm *local_time = localtime(&seconds);
    char *time_str;
    asprintf(&time_str, "%02d:%02d", local_time->tm_hour, local_time->tm_min);
    return time_str;
}

bool check_year_same(long long millis1,
                     long long millis2) {
    long seconds1 = millis1 / 1000;
    struct tm local_time1;
    localtime_r(&seconds1, &local_time1);

    long seconds2 = millis2 / 1000;
    struct tm local_time2;
    localtime_r(&seconds2, &local_time2);

    return local_time1.tm_year == local_time2.tm_year;
}

bool check_day_same(long long millis1,
                    long long millis2) {
    long seconds1 = millis1 / 1000;
    struct tm local_time1;
    localtime_r(&seconds1, &local_time1);

    long seconds2 = millis2 / 1000;
    struct tm local_time2;
    localtime_r(&seconds2, &local_time2);

    return local_time1.tm_yday == local_time2.tm_yday &&
           local_time1.tm_year == local_time2.tm_year;
}

bool check_time_same(long long millis1,
                     long long millis2) {
    long seconds1 = millis1 / 1000;
    struct tm local_time1;
    localtime_r(&seconds1, &local_time1);

    long seconds2 = millis2 / 1000;
    struct tm local_time2;
    localtime_r(&seconds2, &local_time2);

    return local_time1.tm_min == local_time2.tm_min &&
           local_time1.tm_hour == local_time2.tm_hour &&
           local_time1.tm_yday == local_time2.tm_yday &&
           local_time1.tm_year == local_time2.tm_year;
}

long long get_current_time_millis(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000;
}

long long convert_to_epoch(const char *datetime_str) {
    struct tm tm_time;
    memset(&tm_time, 0, sizeof(struct tm));

    if (strptime(datetime_str, "%Y-%m-%d %H:%M:%S", &tm_time) == NULL) {
        fprintf(stderr, "Error parsing datetime string\n");
    }

    time_t time_seconds = mktime(&tm_time);
    if (time_seconds == -1) {
        fprintf(stderr, "Error converting time to seconds since epoch\n");
    }

    return (long long) time_seconds;
}
