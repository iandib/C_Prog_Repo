// ************************************************************
//      * GENERAL *
// ************************************************************

#include <stdio.h>

// Llamamos a los prototipos de las funciones
int get_date(int max_char);
int check_date(int value, int min, int max);
int get_max_day(int month, int year);
int days_calculator(int initial_day, int initial_month, int initial_year, int final_day, int final_month, int final_year);

/* Nota: Escribimos los mensajes en inglés para evitar conflictos con los caracteres 'ñ' (en años) y '´' (en días) */


// ************************************************************
//      * FUNCIÓN PRINCIPAL *
// ************************************************************

// La función principal imprime los mensajes en pantalla y llama a las otras funciones
int main(void)
{
    // Definimos variables para cada dato
    int initial_day, initial_month, initial_year;
    int final_day, final_month, final_year;

    /* --------------- FECHA INICIAL --------------- */

    // Solicitamos el año inicial
    printf("Type the starting year: ");
    initial_year = get_date(4);
    // Validamos el dato pasando el 1 como valor mínimo y el 9999 como máximo
    if (check_date(initial_year, 1, 9999) == -1)
    {
        printf("Invalid year value \n");
        return -1;
    }

    // Solicitamos el mes inicial
    printf("Type the starting month: ");
    initial_month = get_date(2);
    // Validamos el dato pasando el 1 como valor mínimo y el 12 como máximo
    if (check_date(initial_month, 1, 12) == -1)
    {
        printf("Invalid month value \n");
        return -1;
    }

    // Solicitamos el día inicial
    printf("Type the starting day: ");
    initial_day = get_date(2);
    // Obtenemos el día máximo al que llega el mes
    int max_days = get_max_day(initial_month, initial_year);
    // Validamos el dato pasando el 1 como valor mínimo y una variable como máximo
    if (check_date(initial_day, 1, max_days) == -1)
    {
        printf("Invalid day value\n");
        return -1;
    }

    /* --------------- FECHA FINAL --------------- */

    // Solicitamos el año final
    printf("Type the finishing year: ");
    final_year = get_date(4);
    // Validamos el dato pasando el 1 como valor mínimo y el 9999 como máximo
    if (check_date(final_year, 1, 9999) == -1)
    {
        printf("Invalid year value\n");
        return -1;
    }

    // Solicitamos el mes final
    printf("Type the finishing month: ");
    final_month = get_date(2);
    // Validamos el dato pasando el 1 como valor mínimo y el 12 como máximo
    if (check_date(final_month, 1, 12) == -1)
    {
        printf("Invalid month value\n");
        return -1;
    }

    // Solicitamos el día final
    printf("Type the finishing day: ");
    final_day = get_date(2);
    // Obtenemos el día máximo al que llega el mes
    max_days = get_max_day(final_month, final_year);
    // Validamos el dato pasando el 1 como valor mínimo y una variable como máximo
    if (check_date(final_day, 1, max_days) == -1)
    {
        printf("Invalid day value\n");
        return -1;
    }

    /* --------------- CÁLCULO DE DÍAS --------------- */

    // Calculamos la diferencia de días entre ambas fechas
    int days_between = days_calculator(initial_day, initial_month, initial_year, final_day, final_month, final_year);
    // Verificamos que la fecha final sea posterior a la inicial
    if (days_between == -1)
    {
        printf("Invalid date value: the final date is earlier than the initial date. \n");
    }
    // Imprimimos los días entre ambas fechas
    else
    {
        printf("There are %d days between both dates\n", days_between);
    }

    return 0;
}


// ************************************************************
//      * FUNCIÓN PARA GUARDAR LA FECHA DEL USUARIO  *
// ************************************************************

/* La función recibe el número máximo de caracteres que puede tener un dato (2 para días y meses, 4 para años)
y en base a ellos calcula la fecha que quiere insertar el usuario */ 
int get_date(int max_char)
{
    // Definimos la variable que tendrá la fecha que quiere el usuario
    int date = 0;
    // Definimos una variable que irá recibiendo el caracter más reciente que inserte el usuario
    unsigned char user_digit;
    // Definimos una variable para cada posible dígito de la fecha que quiera el usuario
    int first_digit = -1;
    int second_digit = -1;
    int third_digit = -1;
    int fourth_digit = -1;
    // Definimos un contador que registra la cantidad de dígitos que vamos añadiendo a la fecha
    unsigned int count = 0;

    // Leemos los caracteres de entrada hasta que se presione Enter
    while ((user_digit = getchar()) != '\n')
    {
        /* --------------- VERIFICACIÓN DE ERRORES --------------- */

        /* Verificamos si el carácter ingresado es un dígito (0-9), no podemos usar la función 
        check_date en este caso porque estamos trabajando con caracteres */
        if (user_digit < '0' || user_digit > '9')
        {
            // Retornamos -1 si el valor es inválido (número negativo o caracteres no numéricos)
            return -1;
        }

        /* --------------- ACTUALIZACIÓN DE LA FECHA --------------- */

        // Actualizamos el contador para registrar que estamos por guardar un dígito de la fecha
        count++;
        switch (count)
        {
            // Caso para el primer dígito que añadimos a la fecha
            case 1:
                // Restamos '0' (48) para convertir el ASCII del usuario a valor entero
                first_digit = user_digit - '0';
                // Actualizamos la fecha con el valor del primer dígito
                date = first_digit;
                break;

            // Caso para el segundo dígito que añadimos a la fecha
            case 2:
                // Restamos '0' (48) para convertir el ASCII del usuario a valor entero
                second_digit = user_digit - '0';
                // Actualizamos la fecha desplazando los dígitos como corresponde
                date = (first_digit * 10) + second_digit;
                break;

            // Verificamos si es necesario seguir tomando dígitos (depende del tipo de dato, es solo para años)
            if (max_char == 4)
            {
                // Caso para el tercer dígito que añadimos a la fecha
                case 3:
                    third_digit = user_digit - '0';
                    // Actualizamos la fecha desplazando los dígitos como corresponde
                    date = (first_digit * 100) + (second_digit * 10) + third_digit;
                    break;

                // Caso para el cuarto (y último) dígito que añadimos a la fecha
                case 4:
                    fourth_digit = user_digit - '0';
                    // Actualizamos la fecha desplazando los dígitos como corresponde
                    date = (first_digit * 1000) + (second_digit * 100) + (third_digit * 10) + fourth_digit;
                    break;
            }
        }
    }
    return date;
}


// ************************************************************
//      * FUNCIÓN PARA OBTENER EL MÁXIMO DE DÍAS  *
// ************************************************************

// La función recibe el número de mes y el año para determinar la cantidad máxima de días
int get_max_day(int month, int year)
{
    // Verificamos si el año es bisiesto
    int is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

    // Retornamos el número máximo de días dependiendo del mes
    switch (month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return is_leap ? 29 : 28;
        // Si el valor de mes es inválido, cae en caso default y retornamos -1
        default:
            return -1;
    }
}


// ************************************************************
//      * FUNCIÓN PARA VALIDAR LA FECHA DEL USUARIO  *
// ************************************************************

/* La función valida si dado valor está dentro de un determinado rango variable.
La usamos para verificar si los días, meses y años están en su respectivo rango aceptado. */ 
int check_date(int value, int min, int max)
{
    // Si la fecha no se encuentra en el rango permitido, retornamos -1
    if (value < min || value > max)
    {
        return -1;
    }
    // Caso contrario, retornamos el mismo valor que recibió la función como parámetro
    else
    {
        return value;
    }
}


// ************************************************************
//      * FUNCIÓN PARA CALCULAR LA DIFERENCIA EN DÍAS  *
// ************************************************************

// La función calcula la cantidad de días entre las dos fechas presentadas
int days_calculator(int initial_day, int initial_month, int initial_year, int final_day, int final_month, int final_year)
{
    // Definimos la variable que contará los días entre ambas fechas
    int days_between = 0;

    /* --------------- VERIFICACIÓN DE ERRORES --------------- */

    // Verificamos que la fecha final sea posterior a la fecha inicial
    if (final_year < initial_year || 
       ((final_year == initial_year) && (final_month < initial_month)) || 
       ((final_year == initial_year) && (final_month == initial_month) && (final_day < initial_day)))
    {
        // Si no fuera así, retornamos -1
        return -1;
    }

    /* --------------- ACTUALIZACIÓN DEL CONTADOR --------------- */

    // Mientras la fecha inicial sea anterior a la final
    while ((initial_year < final_year) || 
           ((initial_year == final_year) && (initial_month < final_month)) || 
           ((initial_year == final_year) && (initial_month == final_month) && (initial_day < final_day)))
    {
        // Aumentamos en uno al contador de días entre ambas fechas
        days_between++;

        // Avanzamos al siguiente día
        initial_day++;

        // Si llegamos al número máximo de días en el mes actual
        if (initial_day > get_max_day(initial_month, initial_year))
        {
            // Volvemos al primer día
            initial_day = 1;
            // Avanzamos al siguiente mes
            initial_month++;

            // Si llegamos al último mes del año
            if (initial_month > 12)
            {
                // Volvemos al primer mes
                initial_month = 1;
                // Avanzamos al siguiente año
                initial_year++;
            }
        }
    }
    // Retornamos la cantidad de días entre ambas fechas
    return days_between;
}




/* Nota: Dejo comentada una implementación alternativa de la función days_calculator que usaba condicionales anidados 
y bloques for en lugar del ciclo while.
Tal vez sea más rápida, pero es mucho más compleja de seguir y se me hacía imposible de debuggear.

int days_calculator(int initial_day, int initial_month, int initial_year, int final_day, int final_month, int final_year)
{
    int days_between = 0;
    int year, month;

    if (initial_year == final_year)
    {
        if (initial_month == final_month)
        {
            return final_day - initial_day;
        }
        else
        {
            days_between += get_max_day(initial_month, initial_year) - initial_day;
            
            for (month = initial_month + 1; month < final_month; month++)
            {
                days_between += get_max_day(month, initial_year);
            }
            days_between += final_day;
        }
    }
    else
    {
        if (initial_month == final_month)
        {
            days_between += (final_day - initial_day);
            
            for (year = initial_year + 1; year < final_year; year++)
            {
                days_between += ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) ? 366 : 365;
            }
        }

        else
        {
            days_between += get_max_day(initial_month, initial_year) - initial_day;
            for (month = initial_month + 1; month <= 12; month++)
            {
                days_between += get_max_day(month, initial_year);
            }
            
            for (year = initial_year + 1; year < final_year; year++)
            {
                days_between += ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) ? 366 : 365;
            }

            for (month = 1; month < final_month; month++)
            {
                days_between += get_max_day(month, final_year);
            }

            days_between += final_day;
        }
    }
    return days_between;
}


*/
