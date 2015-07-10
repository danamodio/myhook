/**
  * @file LogType.h
  * @author Daniel Amodio
  * @date July 22, 2009
  * @class LogType
  *
  * The LogType class will be a pure virtual (abstract) class
  * to use as a base for different log types (LOCAL_FILE, DEBUG, etc)
  * The constructor and destructor will be used for startup and shutdown code
  * and the log() function will handle any logged data
  */
#ifndef LOGTYPE_H

class LogType
{
public:
       
       /**
         * Method that will add data to the log
         * @param data Data to add to the log
         */
       virtual void log(char* data);
       
private:

};


#define LOGTYPE_H
#endif
