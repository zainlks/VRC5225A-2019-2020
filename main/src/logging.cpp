#pragma once
#include <iostream>
#include <fstream>
using namespace std;
FILE* logfile = NULL;

void log_init() {
  logfile = fopen("/usd/log.txt","r");
  if(logfile==NULL) printf("could not open logfile\n");
  else printf("logfile found\n");
}

void log_text(){
  ofstream logfile;
  logfile.open("/usd/example.txt");
  if (logfile.is_open()){
    logfile << "Successfully opened SD log file \n" ;
    logfile.close();
  }
  else{
    logfile <<"Unable to open SD log file \n";
  }
}
