#include "logging.hpp"
using namespace std;
using namespace pros;
FILE* logfile = NULL;
FILE* logGraphFile = NULL;

pros::Task *logTask = nullptr;

graphingEntries graphParams;
pros::Mutex mutex;
bool log_done = true;

void log_init() {
  logfile = fopen("/usd/log.txt","a");
  if(logfile==NULL) {printf("could not open logfile\n"); return;}
  else printf("logfile found\n");
  if(logfile != NULL)fprintf(logfile, "\n>>>>>START LOGGING FOR PROGRAM\n");


  logGraphFile = fopen("/usd/graph.csv","a");
  if(logGraphFile==NULL) {printf("could not open logfile\n"); return;}
  else printf("logfile found\n");
  if(logGraphFile != NULL) return;
}

void log(const char * format, ...){
  // mutex.take(50);
  va_list arguments;
  va_start(arguments,format);
  vprintf(format,arguments);
  printf("\n");
  if(logfile == NULL) return;
  vfprintf(logfile, format, arguments);
  fclose(logfile);
  // while ((logfile = fopen("/usd/log.txt","a")) == NULL) pros::delay(3);
  va_end(arguments);
  // mutex.give();
}


void log_task(void *params) {
  if(logGraphFile == NULL) return;
  printf("%d,%f,%f\n", graphParams.entry1,graphParams.entry2,graphParams.entry3 );
  fprintf(logGraphFile,"%d,%d,%f,%f,%f,%f,%f\n",millis(),graphParams.entry1,graphParams.entry2,graphParams.entry3,graphParams.entry4,graphParams.entry5,graphParams.entry6);
  fclose(logGraphFile);
  while ((logGraphFile = fopen("/usd/graph.csv","a")) == NULL) pros::delay(1);
  log_done = true;
  logStopTask();
}

void logStartTask() {
  logTask = new Task(log_task);
}

void logStopTask() {
  if(logTask != nullptr)
  {
    logTask->remove();
    delete logTask;
    logTask = nullptr;
  }
}

void log_graph(int en1, double entry2, double entry3, double entry4, double entry5, double entry6){
  // mutex.take(50);
  if(!log_done) return;
  if(logTask != nullptr) logTask = nullptr;
  graphParams.entry1 = en1;
  graphParams.entry2 = entry2;
  graphParams.entry3 = entry3;
  graphParams.entry4 = entry4;
  graphParams.entry5 = entry5;
  graphParams.entry6 = entry6;
  log_done = false;
  logStartTask();
  // mutex.give();
}
