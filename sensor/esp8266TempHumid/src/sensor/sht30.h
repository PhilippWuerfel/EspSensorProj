#include <WEMOS_SHT3X.h>

class Sht30{
    private:
        SHT3X sht30;
    public:
        Sht30();
        ~Sht30();

        bool measure();
        float getTempCelsius();
        float getTempFahrenheit();
        float getHumidity();
};