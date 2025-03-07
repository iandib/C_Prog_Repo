#include <stdio.h>

int str_in_str(const char *chain, const char *subchain)
{
    int chain_idex, subchain_index;
    int found;

    // Recorremos la cadena principal hasta encontrar el terminador
    for(chain_idex = 0; chain[chain_idex] != '\0'; chain_idex++)
    {
        // Inicializamos la variable encontrado
        found = 1;

        // Comparamos cada caracter de la subcadena (hasta su terminador) con la porción actual de la cadena principal
        for(subchain_index = 0; subchain[subchain_index] != '\0'; subchain_index++)
        {
            if(chain[chain_idex + subchain_index] != subchain[subchain_index])
            {
                found = 0;
                break;
            }
        }

        // Si la subcadena fue encontrada, retornamos 1
        if(found && (subchain[subchain_index] == '\0'))
        {
            return 1;
        }
    }

    // Si la subcadena no fue encontrada, retornamos 0
    return 0;
}

int main()
{
    // Cadena de prueba
    const char *chain = "Nos van a matar en el parcial";

    // Subcadena de prueba
    const char *subchain = "aprobado";

    // Comprobamos si subcadena está en cadena
    if(str_in_str(chain, subchain))
    {
        printf("'%s' is in '%s' \n", subchain, chain);
    }
    else
    {
        printf("'%s' is NOT in '%s' \n", subchain, chain);
    }

    return 0;
}
