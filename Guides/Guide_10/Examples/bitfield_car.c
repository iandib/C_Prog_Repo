//Notas sobre el Uso del bitfield

// Ningun campo puede tener mas de 16 bits (uint_16)!!
// La cantidad de bytes depende de la suma de bits de todos los campos
// si los puede poner en un unsigned int (16 bit en la pc) lo hace.
// de lo contrario usa mas bytes
// Si un bit no se usa se puede poner sin nombre (dïont care)
// pero ocupa espacio. Otra es llamarlo unused directamente
// pero si tengo varios tengo que numerarlos!!! (unused0,unused1,etc)
// pues no puedo repetir el nombre.

#include <stdio.h>
#include <stdint.h>


enum { OFF, ON };
enum { FUEL_EMPTY, FUEL_LOW = 2, FUEL_MEDIUM = 8, FUEL_FULL = 15 };


typedef struct
{
    uint8_t  Engine      : 1;  // Engine control
    uint8_t  Fan         : 1;  // Fan Control
    uint8_t  unused      : 2;  // unused
    uint8_t  Fuel_level  : 4;  // Fuel level sensor (4 bits MAX 15)
} car_status_t;

typedef struct
{
    char * car_id;
    car_status_t car_status;
} CAR;


void print1_car_status(const CAR car);
void print2_car_status(const CAR * my_car);


int main(void)
{
    CAR car1,car2;

    car1.car_id="ARR123";
    car1.car_status.Engine=ON;
    car1.car_status.Fan=OFF;
    car1.car_status.Fuel_level=FUEL_FULL;

    car2.car_id="ABC345";
    car2.car_status.Engine=ON;
    car2.car_status.Fan=ON;
    car2.car_status.Fuel_level=14;

    print1_car_status(car1);
    print2_car_status(&car2);

    return 0;
}

void  print1_car_status(const CAR car)
{
    printf("\n\nThe car status is:\n");
    printf("Engine: %s\n", car.car_status.Engine? "ON":"OFF");
    printf("Fan: %s\n", car.car_status.Fan? "ON":"OFF");
    printf("Fuel Level: %d%%\n", 100*(int16_t)car.car_status.Fuel_level/FUEL_FULL);
    //printf("Fuel Level: %d\%\n", (int)car.car_status.Fuel_level);
    printf("Car ID: %s\n", car.car_id);

    if (car.car_status.Fuel_level <= FUEL_LOW)
    {
        printf("Warning Low Fuel level !!!!!\n");
    }
}

void  print2_car_status(const CAR * my_car)
{
    printf("\n\nThe car status is:\n");
    printf("Engine: %s\n", my_car->car_status.Engine? "ON":"OFF");
    printf("Fan: %s\n", my_car->car_status.Fan? "ON":"OFF");
    printf("Fuel Level: %d%%\n", 100*(int16_t)my_car->car_status.Fuel_level/FUEL_FULL);
    printf("Car ID: %s\n", my_car->car_id);

    if (my_car->car_status.Fuel_level <= FUEL_LOW)
    {
        printf("Warning Low Fuel level !!!!!\n");
    }
}
