#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

struct Elemento
{
    float           valore;
    struct Elemento *next;
};

void acquisisci_cardinalita(int *cardinalita,
                            bool primo_insieme);

void libera_buffer();

void acquisisci_elementi(float *insieme,
                         int cardinalita,
                         bool primo_insieme);

int main()
{
    int cardinalita_primo_insieme;
    acquisisci_cardinalita(cardinalita_primo_insieme,
                           true);
    return 0;
}

void libera_buffer()
{
    char c;
    while ((c = getchar()) != '\n' &&
           c != EOF)
    {
    }
}

void acquisisci_cardinalita(int *cardinalita,
                            bool primo_insieme)
{
    //TODO: rinominare in italiano e documentare "peek"
    int  esito_lettura,
         peek;
    bool input_valido = false;
    do
    {
        if (primo_insieme)
        {
            printf("Inserisci la cardinalità del primo insieme:\n");
        }
        else
        {
            printf("Inserisci la cardinalità del secondo insieme:\n");
        }
        esito_lettura = scanf("%d",
                              cardinalita);
        
        if (esito_lettura != 1 ||
            ((peek = getchar()) != EOF &&
             !isspace(peek)) ||
            *cardinalita <= 0)
        {
            printf("[ERRORE]: L'input deve essere un numero intero maggiore di 0!\n");
            libera_buffer();
        }
        else
        {
            input_valido = true;
        }
        
    }
    while (!input_valido);
}

void acquisisci_elementi(float *insieme,
                         int cardinalita,
                         bool primo_insieme)
{
    
    //TODO: rinominare in italiano e documentare "peek"
    
    int  esito_lettura,
         peek,
         i            = 0;
    bool input_valido = false;
    
    if (primo_insieme)
    {
        printf("Inserisci gli elementi del primo insieme (uno per riga):\n");
    }
    else
    {
        printf("Inserisci gli elementi del secondo insieme (uno per riga):\n");
    }
    do
    {
        do
        {
            printf("Inserisci l'elemento %d\n",
                   i + 1);
            esito_lettura = scanf("%f",
                                  &insieme[i]);
            if (esito_lettura != 1 ||
                ((peek    = getchar()) != EOF &&
                 !isspace(peek)))
            {
                printf("[ERRORE]: L'input deve essere un numero reale!\n");
                libera_buffer();
            }
            else
            {
                input_valido = true;
                i++;
            }
        }
        while (!input_valido);
    }
    while (i < cardinalita);
}