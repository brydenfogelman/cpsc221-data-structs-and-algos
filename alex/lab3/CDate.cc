// ..................................................  
// CDate class definitions
// Adapted from Hagit Schechter, Jan 2007 for 2014W2 
// ..................................................

#include <iostream>
#include <string>
#include "CDate.h"
#include <map>

CDate::CDate(void){
  m_year = m_month = m_day = 0;
}

CDate::CDate(int year, int month, int day){
  setDate( year, month, day );        
}

CDate::CDate(int year, std::string month, int day){
  //********
  setDate( year, monthStr2Num(month), day);
  
}

bool CDate::isValidDate(int year, int month, int day){
  
  if(year < 0){
    return false;
  }
  if(month > 12 || month < 1){
    return false;
  }
  if(!isValidDay(year, month, day)){
    return false;
  }
  return true;
  
}

bool CDate::isValidDate(int year, std::string month, int day){
  
  return isValidDate(year, monthStr2Num(month), day);

}

//Returns -1 if month not found, else returns month number
int CDate::monthStr2Num(std::string month){
  
  int monthNum;
  // TODO you need to fill in the code here        ********
  
  std::map<std::string, int> monthMap;
  monthMap["January"] = 1;
  monthMap["February"] = 2;
  monthMap["March"] = 3;
  monthMap["April"] = 4;
  monthMap["May"] = 5;
  monthMap["June"] = 6;
  monthMap["July"] = 7;
  monthMap["August"] = 8;
  monthMap["September"] = 9;
  monthMap["October"] = 10;
  monthMap["November"] = 11;
  monthMap["December"] = 12;

  if (monthMap.find(month)!=monthMap.end()){
    monthNum = monthMap[month];
  }
  else{
    monthNum = -1;
  }
  
  return monthNum;
}

bool CDate::isValidDay(int year, int month, int day){ //DONE!
  if ((day < 1) || (day > 31)) return false;
  
  bool valid = false;
  switch (month) {
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    valid = true;
    break;
    //********
  case 2:
    // Don't worry about this code too much.
    // It handles all the leap year rules for February.
    if ((year % 4) != 0) {
      valid = (day <=28);
    } else if ((year % 400) == 0) {
      valid = (day <= 29);
    } else if ((year % 100) == 0) {
      valid = (day <= 28);
    } else {
      valid = (day <= 29);
    }
    break;
  case 4:
  case 6:
  case 9:
  case 11:
    if(day > 30){
      valid = false;
      break;
    }
    //********
  default:
    valid = true;
    //********
    break; 
  }
  return valid;
}

void CDate::setDate(int year, int month, int day){
  if(isValidDate(year, month, day)){    
    m_year = year;
    m_month = month;
    m_day = day;
  }
  else {
    m_year = m_month = m_day = 0;
  }
}


void CDate::setDate(int year, std::string month, int day){
  
  setDate(year, monthStr2Num(month), day);

}

void CDate::print(void){
  std::cout << m_year << "/" << m_month << "/" << m_day << std::endl;
}

int CDate::getDate(void){
  return (m_year * 10000) + (m_month * 100) + m_day;
}

