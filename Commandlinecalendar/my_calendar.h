#ifndef __MY_CALENDAR__
#define __MY_CALENDAR__

/**
 * 判断闰年
*/
bool judge_leap_year(int year);
/**
 * 判断两个年份之间有多少个闰年
*/
int judge_total_leap_years(int start_year, int end_year);
/**
 * 求一个日期到基准日期的天数
*/
int find_gap_from_year(int base_year, int year, int month, int day);
/**
 * 求两个日期的间隔
*/
int find_date_gap (char *start_day, char *end_day);
/**
 * 判断输入的日期是星期几
 * 已知1900年1月1日是星期一
*/
int judge_week_day(char *now_day);
/**
 * 输出输入的年份的日历
*/
void output_calendar (int year);
/**
 * 打印日历
*/
void printf_calendar (int year, int *months, int *first_day_of_months);


#endif