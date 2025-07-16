// memento mori

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>  // for sleep()

#define SAVE_FILE "dob.txt"
#define LIFE_EXPECTANCY_YEARS 72

int parse_birthdate(const char *dob_str, struct tm *dob) {
    if (strlen(dob_str) != 8) {
        printf("Invalid DOB length.");
        return 0;
    }

    char year_str[5], month_str[3], day_str[3];
    strncpy(year_str, dob_str, 4);
    year_str[4] = '\0'; // add these so atoi works
    strncpy(month_str, dob_str + 4, 2);
    month_str[2] = '\0';
    strncpy(day_str, dob_str + 6, 2);
    day_str[2] = '\0';

    int year = atoi(year_str);
    int month = atoi(month_str);
    int day = atoi(day_str);

    if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid DOB");
        return 0;
    }

    // struct tm has many members beyond just the year, month, and day (like hour, minute, second, weekday, etc.) zeroing them our prevents unpredictable behavior
    memset(dob, 0, sizeof(struct tm));
    dob->tm_year = year - 1900;
    dob->tm_mon = month - 1;
    dob->tm_mday = day;
    return 1;
}

int get_dob(struct tm *dob) {
    FILE *file = fopen(SAVE_FILE, "r");
    char dob_str[16];

    if (file) {
        fscanf(file, "%15s", dob_str);
        fclose(file);
    } else {
        printf("Enter your birthdate (YYYYMMDD): ");
        if (!fgets(dob_str, sizeof(dob_str), stdin)) {
            return 0;
        }
        dob_str[strcspn(dob_str, "\n")] = '\0'; // Remove newline
        file = fopen(SAVE_FILE, "w");
        if (file) {
            fprintf(file, "%s\n", dob_str);
            fclose(file);
        }
    }

    return parse_birthdate(dob_str, dob);
}

void display_time_left(time_t death_time) {
    while (1) {
        time_t now = time(NULL);
        double seconds_left = difftime(death_time, now);
        if (seconds_left < 0) {
            seconds_left = 0;
        }

        int days = (int)(seconds_left / (60 * 60 * 24));
        int hours = ((int)(seconds_left / 3600)) % 24;
        int minutes = ((int)(seconds_left / 60)) % 60;
        int seconds = ((int)(seconds_left)) % 60;

        // printf("\rTime left: %d days %02d:%02d:%02d (%0.0f seconds left)   ", days, hours, minutes, seconds, seconds_left);
        printf("\r%0.0f    ", seconds_left);
        fflush(stdout);
        sleep(1);
    }
}

int main() {
    struct tm dob;
    if (!get_dob(&dob)) {
        fprintf(stderr, "Invalid date format.\n");
        return 1;
    }

    struct tm death = dob;
    death.tm_year += LIFE_EXPECTANCY_YEARS;
    time_t death_time = mktime(&death);

    printf("\n\n\n\n\n\n\n\n\n\nMemento Mori.\n\n");
    display_time_left(death_time);
    return 0;
}

// gcc mm.c -o mm
// ./mm
