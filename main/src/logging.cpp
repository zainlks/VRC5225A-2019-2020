#include "logging.hpp"
using namespace std;
FILE* logfile = NULL;

bool log_done = false;

void log_init() {
  logfile = fopen("/usd/log.txt","a");
  if(logfile==NULL) {printf("could not open logfile\n"); return;}
  else printf("logfile found\n");
  fprintf(logfile, "\n>>>>>START LOGGING FOR PROGRAM\n");
}

void log(const char * format, ...){
  va_list arguments;
  va_start(arguments,format);
  vprintf(format,arguments);
  printf("\n");
  if(logfile == NULL) return;
  vfprintf(logfile, format, arguments);
  fclose(logfile);
  // while ((logfile = fopen("/usd/log.txt","a")) == NULL) pros::delay(3);
  va_end(arguments);
}
