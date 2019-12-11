#include "sht30.h"
//#include <WEMOS_SHT3X.h>

Sht30::Sht30(){
  sht30 = SHT3X(0x45);
}
Sht30::~Sht30(){
};

bool Sht30::measure(){
  if(sht30.get()==0){
    return true;
  }else{
    return false;
  }
}
float Sht30::getTempCelsius(){
  return sht30.cTemp;
}
float Sht30::getTempFahrenheit(){
  return sht30.fTemp;
}
float Sht30::getHumidity(){
  return sht30.humidity;
}