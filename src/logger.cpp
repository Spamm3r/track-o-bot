#include "logger.h"
#include <ctime>

string Logger::Timestamp() {
  char buffer[256];
  time_t t = time(0);
  struct tm *now = localtime(&t);
  strftime(buffer, sizeof(buffer), "[%T] ", now);
  return buffer;
}

void Logger::Add(const string& message) {
  Notify(message);
}

void Logger::RegisterObserver(LoggingObserver *observer) {
  observers.push_back(observer);
}

void Logger::UnregisterObserver(LoggingObserver *observer) {
  observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Logger::Notify(const string& message) {
  vector<LoggingObserver*>::iterator it;
  for(it = observers.begin(); it != observers.end(); ++it) {
    (*it)->HandleLogEntry(message);
  }
}