#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include "my_calendar.h"


int main(void) {
    int year;
    printf("输入你要查询的年份日历（仅支持1900之后）：");
    scanf("%d", &year);
    output_calendar(year);
    return 0;
}

/**
 * 判断闰年
*/
bool judge_leap_year(int year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

/**
 * 判断两个年份之间有多少个闰年
*/
int judge_total_leap_years(int start_year, int end_year) {
    int count = 0;
    for (int i = start_year; i < end_year; i++) {
        if (judge_leap_year(i)) {
            count++;
        }
    }
    return count;
}

/**
 * 求一个日期到基准日期的天数
*/
int find_gap_from_year(int base_year, int year, int month, int day) {
    int months[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // 先以365天乘以间隔的年数、以及日的天数
    int total_days = (year - base_year) * 365 + day;
    // 再加上间隔年之间的n个闰年的n天
    total_days += judge_total_leap_years(base_year, year);
    // 加上所有月份的天数
    for(int i = 1; i < month; i++) {
        if (i == 2 && judge_leap_year(year)) {
            total_days++;
        }
        total_days += months[i];
    }
    return total_days;
}


/**
 * 求两个日期的间隔
*/
int find_date_gap (char *start_day, char *end_day) {
    int year1, month1, day1, year2, month2, day2;
    sscanf(start_day, "%d-%d-%d", &year1, &month1, &day1);
    sscanf(end_day, "%d-%d-%d", &year2, &month2, &day2);
    // 设置一个基准年
    int base_year = year1;
    int total_start_days = find_gap_from_year(base_year, year1, month1, day1);
    int total_end_days = find_gap_from_year(base_year, year2, month2, day2);
    return total_end_days - total_start_days;
}

/**
 * 判断输入的日期是星期几
 * 已知1900年1月1日是星期一
*/
int judge_week_day(char *now_day) {
    int year, month, day;
    sscanf(now_day, "%d-%d-%d", &year, &month, &day);
    int total_days = find_date_gap("1900-1-1", now_day);
    total_days += 1; // 每个月第一天是周日，加一天对齐
    int week_day = total_days % 7;
    return week_day;
}

/**
 * 打印日历
*/
void printf_calendar (int year, int *months, int *first_day_of_months) {
    // 获取当前时间
    time_t current_time;
    struct tm *time_info;
    time(&current_time);
    time_info = localtime(&current_time);
    int current_year = time_info->tm_year + 1900;
    int current_mon = time_info->tm_mon + 1;
    int current_mday = time_info->tm_mday;
    bool is_current_year = (current_year == year);
    // 打印日历
    int left_count, right_count; // 左、右月日历计数
    int left_days, right_days; // 左、右月日历的总天数
    int left_first_day, right_first_day; // 左、右月日历的第一天的星期数（日~六：0~6）
    int left_blanks, right_blanks; // 左、右月日历第一排打印空格数
    printf("|=====================\033[1;37mThe Calendar of Year %4d\033[0m====================|\n", year);
    for (int i = 1; i <= 6; i++) {
        printf(": \033[1;37m%2d\033[0m  \033[0;32mSUN MON TUE WED THU FRI SAT\033[0m  \033[1;37m%2d\033[0m  \033[0;32mSUN MON TUE WED THU FRI SAT\033[0m :\n", i, i + 6);
        left_count = right_count = 0;
        left_days = months[i];
        right_days = months[i+6];
        left_blanks = left_first_day = first_day_of_months[i];
        right_blanks = right_first_day = first_day_of_months[i+6];
        // 循环转行打印日历
        while (left_count < left_days || right_count < right_days) {
            printf(":     ");
            for(int j = 0; j <= 6; j++) {
                if (left_blanks > 0 || left_count >= left_days) {
                    printf("    ");
                    left_blanks--;
                }else {
                    left_count++;
                    if (is_current_year && current_mon == i && current_mday == left_count) {
                        printf("\033[1;31m%3d \033[0m", left_count);
                    }else {
                        printf("%3d ", left_count);
                    }
                }
            }
            printf("     ");
            for(int j = 0; j <= 6; j++) {
                if (right_blanks > 0 || right_count >= right_days) {
                    printf("    ");
                    right_blanks--;
                }else {
                    right_count++;
                    if (is_current_year && current_mon == (i+6) && current_mday == right_count) {
                        printf("\033[1;31m[%2d]\033[0m", right_count);
                    }else {
                        printf("%3d ", right_count);
                    }
                }
            }
            printf(":\n");
        }
    }   
    printf("|==================================================================|\n");
}

/**
 * 输出输入的年份的日历
*/
void output_calendar (int year) {
    // 设置每个月的第一天是星期几（星期日~星期六用0~6表示）
    int first_day_of_months[13] = {-1};
    char date_str[20];
    for (int i = 1; i <= 12; i++) {
        sprintf(date_str, "%d-%d-1", year, i);
        first_day_of_months[i] = judge_week_day(date_str);
    }
    // 设置查询年每个月的天数
    int months[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (judge_leap_year(year)) {
        months[2] = 29;
    }
    printf_calendar(year, months, first_day_of_months);
}
