#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>

using namespace std;
using namespace std::chrono;

int main() {
    // -------------------------
    // Input locale
    // -------------------------
    cout << "Locale: Enter locale name or press Enter for system default.\n";
    cout << "Example: en_US.UTF-8, de_CH.UTF-8\n";

    string localeInput;
    getline(cin, localeInput);

    try {
        if (!localeInput.empty()) {
            locale::global(locale(localeInput.c_str()));
            cout.imbue(locale());
        }
    }
    catch (const runtime_error& e) {
        cerr << "Invalid locale: " << e.what() << '\n';
        return 1;
    }

    // -------------------------
    // Input time zone
    // -------------------------
    cout << "\nTime zone: Enter IANA time zone.\n";
    cout << "Examples: Europe/Zurich, Europe/London, Asia/Tokyo\n";

    string timezoneInput;
    getline(cin, timezoneInput);

    // -------------------------
    // Input birthday
    // -------------------------
    cout << "\nEnter your birthday (YYYY-MM-DD): ";
    string birthdayStr;
    getline(cin, birthdayStr);

    cout << "Enter your birth time (HH:MM): ";
    string birthTimeStr;
    getline(cin, birthTimeStr);

    // Parse input
    int year, month, day;
    int hour, minute;
    char dash1, dash2, colon;

    istringstream dateStream(birthdayStr);
    dateStream >> year >> dash1 >> month >> dash2 >> day;

    istringstream timeStream(birthTimeStr);
    timeStream >> hour >> colon >> minute;

    year_month_day birthday{
        std::chrono::year{year},
        std::chrono::month{static_cast<unsigned>(month)},
        std::chrono::day{static_cast<unsigned>(day)}
    };

    // Create local birth date/time
    local_seconds birthLocal =
        local_days{birthday}
        + hours{hour}
        + minutes{minute};

    try {
        // Find the IANA time zone
        const time_zone* tz = locate_zone(timezoneInput);

        // Convert local birth time to an actual point in time
        zoned_time birthZoned{tz, birthLocal};

        // Current time in the same time zone
        zoned_time currentZoned{tz, system_clock::now()};

        auto birthSys = birthZoned.get_sys_time();
        auto currentSys = currentZoned.get_sys_time();

        // -------------------------
        // Calculate elapsed time
        // -------------------------
        auto elapsed =
            duration_cast<seconds>(currentSys - birthSys);

        long long totalSeconds = elapsed.count();
        long long totalMinutes = totalSeconds / 60;
        long long totalHours = totalSeconds / 3600;
        long long totalDays = totalHours / 24;

        // Approximate calendar age
        auto currentLocal =
            floor<days>(currentZoned.get_local_time());

        year_month_day currentDate{currentLocal};

        int years =
            int(currentDate.year()) - int(birthday.year());

        if (
            currentDate.month() < birthday.month() ||
            (
                currentDate.month() == birthday.month() &&
                currentDate.day() < birthday.day()
            )
        ) {
            --years;
        }

        // -------------------------
        // Output
        // -------------------------
        cout << "\nTime zone: " << timezoneInput << '\n';

        cout << "Birth date/time: "
             << birthZoned << '\n';

        cout << "Current date/time: "
             << currentZoned << '\n';

        cout << "\nYou have been alive for approximately:\n";
        cout << years << " years\n";

        cout << "\nIn individual time units:\n";
        cout << totalDays << " total days\n";
        cout << totalHours << " total hours\n";
        cout << totalMinutes << " total minutes\n";
        cout << totalSeconds << " total seconds\n";
    }
    catch (const exception& e) {
        cerr << "Time-zone error: "
             << e.what() << '\n';

        return 1;
    }

    return 0;
}
