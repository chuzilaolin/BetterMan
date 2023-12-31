#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

bool judge_leap_year(int year);
int judge_total_leap_years(int start_year, int end_year);
int find_gap_from_year(int base_year, int year, int month, int day);
int find_date_gap (char *start_day, char *end_day);
int judge_week_day(char *now_day);
void output_calendar (int year);
void printf_calendar (int year, int *months, int *first_day_of_months);
