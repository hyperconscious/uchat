#define _GNU_SOURCE
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdbool.h>
#include "string_utils.h"

char *convert_millis_to_date(long long millis,
                             bool include_year);

char *convert_millis_to_hour_and_minute(long long millis);

bool check_year_same(long long millis1,
                     long long millis2);

bool check_day_same(long long millis1,
                    long long millis2);

bool check_time_same(long long millis1,
                     long long millis2);

long long get_current_time_millis(void);
