/**
  * @file DataLog.cpp
  * @author Daniel Amodio
  *
  */
  
#include "stdafx.h"
#include "DataLog.h"
#include <stdio.h>
#include <iostream>

DataLog::DataLog(LogTypeName newLogType)
{
     logType = newLogType;
     
     // this is where it would be handy to have derived classes... no long switch statements
     // some types would require startup code to be more efficient
}

void DataLog::log(char* data)
{
     // derived classes would be faster than doing a switch every time aswell
     switch(logType)
     {
     case DEBUG:
          std::cout << data;
          break;
     case LOCAL_FILE:
          FILE *file;
          file=fopen("log.txt","a+");
          fputs(data,file);
          fclose(file);
          break;
     default:
          ;
     }
}
