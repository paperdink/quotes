
#include <Arduino.h>
#include <sys/time.h>
#include <esp_attr.h>

#include "config.h"
#include "date_time.h"

RTC_DATA_ATTR struct time_struct now; // keep track of time
String time_zone_base = "UTC";

// Time APIs
int8_t get_date_dtls(String time_zone) {
  String time_zone_string = time_zone_base+time_zone;
  setenv("TZ", time_zone_string.c_str(), 1);
  
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    DEBUG.println("Failed to obtain time");
    return -1;
  }
  time_t epoch = mktime(&timeinfo);

  sscanf(ctime(&epoch), "%s %s %hhd %hhd:%hhd:%hhd %d", now.wday, now.month, &now.mday, &now.mil_hour, &now.min, &now.sec, &now.year);
  
  now.month_num = timeinfo.tm_mon + 1;
  // convert to 12 hour
  if (now.mil_hour > 12) {
    now.hour = now.mil_hour - 12;
  } else {
    now.hour = now.mil_hour;
  }

  DEBUG.printf("Time is %d %d:%d:%d on %s on the %d/%d/%d . It is the month of %s. day_offset: %d\n",now.mil_hour,now.hour,now.min,now.sec,now.wday,now.mday,now.month_num,now.year, now.month, now.day_offset);
  return 0;
}
