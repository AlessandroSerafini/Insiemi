#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void acquisisci_cardinalita(int *cardinalita,
                            bool primo_insieme);

void libera_buffer();

void acquisisci_elementi(float *insieme,
                         int cardinalita,
                         bool primo_insieme);

void ordina_insieme(float *insieme,
                    int cardinalita);

int uguaglianza(float primo_insieme[],
                float secondo_insieme[],
                int cardinalita_primo_insieme,
                int cardinalita_secondo_insieme,
                int i);

int unione(float *insieme_unione,
           float primo_insieme[],
           float secondo_insieme[],
           int cardinalita_primo_insieme,
           int cardinalita_secondo_insieme);

int intersezione(float *insieme_intersezione,
                 float primo_insieme[],
                 float secondo_insieme[],
                 int cardinalita_primo_insieme,
                 int cardinalita_secondo_insieme,
                 int i,
                 int j,
                 int cardinalita_intersezione);

int differenza(float *insieme_differenza,
               float primo_insieme[],
               float secondo_insieme[],
               int cardinalita_primo_insieme,
               int cardinalita_secondo_insieme,
               int i,
               int cardinalita_differenza);

int differenza_simmetrica(float *insieme_differenza_simmetrica,
                          float primo_insieme[],
                          float secondo_insieme[],
                          int cardinalita_primo_insieme,
                          int cardinalita_secondo_insieme);

void stampa_operazione(int operazione,
                       int cardinalita,
                       float insieme[]);

bool cerca_in_insieme(float insieme[],
                      int cardinalita,
                      float numero_reale);

int main()
{
    
    int cardinalita_primo_insieme,
        cardinalita_secondo_insieme,
        cardinalita_intersezione,
        cardinalita_differenza,
        cardinalita_differenza_simmetrica;
    
    acquisisci_cardinalita(&cardinalita_primo_insieme,
                           true);
    acquisisci_cardinalita(&cardinalita_secondo_insieme,
                           false);
    
    float insieme_intersezione[100],
          insieme_differenza[100],
          insieme_differenza_simmetrica[100],
          primo_insieme[cardinalita_primo_insieme],
          secondo_insieme[cardinalita_secondo_insieme];
    
    
    acquisisci_elementi(primo_insieme,
                        cardinalita_primo_insieme,
                        true);
    acquisisci_elementi(secondo_insieme,
                        cardinalita_secondo_insieme,
                        false);
    cardinalita_intersezione = intersezione(insieme_intersezione,
                                            primo_insieme,
                                            secondo_insieme,
                                            cardinalita_primo_insieme,
                                            cardinalita_secondo_insieme,
                                            0,
                                            0,
                                            0);
    cardinalita_differenza   = differenza(insieme_differenza,
                                          primo_insieme,
                                          secondo_insieme,
                                          cardinalita_primo_insieme,
                                          cardinalita_secondo_insieme,
                                          0,
                                          0);
    
    cardinalita_differenza_simmetrica = differenza_simmetrica(insieme_differenza_simmetrica,
                                                              primo_insieme,
                                                              secondo_insieme,
                                                              cardinalita_primo_insieme,
                                                              cardinalita_secondo_insieme);
    
    printf("\n[UGUAGLIANZA]: ");
    if (uguaglianza(primo_insieme,
                    secondo_insieme,
                    cardinalita_primo_insieme,
                    cardinalita_secondo_insieme,
                    0) == 1)
    {
        printf("I due insiemi sono uguali\n");
    }
    else
    {
        printf("I due insiemi non sono uguali\n");
    }
    stampa_operazione(1,
                      cardinalita_intersezione,
                      insieme_intersezione);
    stampa_operazione(2,
                      cardinalita_differenza,
                      insieme_differenza);
    stampa_operazione(3,
                      cardinalita_differenza_simmetrica,
                      insieme_differenza_simmetrica);
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

void stampa_operazione(int operazione,
                       int cardinalita,
                       float insieme[])
{
    int i;
    switch (operazione)
    {
        case 1:
            printf("[INTERSEZIONE]: ");
            break;
        case 2:
            printf("[DIFFERENZA]: ");
            break;
        case 3:
            printf("[DIFFERENZA SIMMETRICA]: ");
            break;
        default:
            printf("[ERRORE]: L'identificativo dell'operazione non è valido!\n");
    }
    
    printf("{");
    for (i = 0;
         i < cardinalita;
         i++)
    {
        if (i != 0)
        {
            printf(", ");
        }
        //TODO: gli va bene a Bernardo che stampo i float con un decimale?
        printf("%.1f",
               insieme[i]);
    }
    printf("}\n");
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
    ordina_insieme(insieme,
                   cardinalita);
}

void ordina_insieme(float *insieme,
                    int cardinalita)
{
    int   i,
          j;
    float temp;
    for (i = 0;
         i < cardinalita;
         i++)
    {
        /*
         * Place currently selected element array[i]
         * to its correct place.
         */
        for (j = i + 1;
             j < cardinalita;
             j++)
        {
            /*
             * Swap if currently selected array element
             * is not at its correct position.
             */
            if (insieme[i] > insieme[j])
            {
                temp = insieme[i];
                insieme[i] = insieme[j];
                insieme[j] = temp;
            }
        }
    }
}

int unione(float *insieme_unione,
           float primo_insieme[],
           float secondo_insieme[],
           int cardinalita_primo_insieme,
           int cardinalita_secondo_insieme)
{
    int i                  = 0,
        j                  = 0,
        cardinalita_unione = 0;
    
    while (i < cardinalita_primo_insieme &&
           j < cardinalita_secondo_insieme)
    {
        if (primo_insieme[i] < secondo_insieme[j])
        {
            insieme_unione[cardinalita_unione] = primo_insieme[i++];
            cardinalita_unione++;
        }
        else if (secondo_insieme[j] < primo_insieme[i])
        {
            insieme_unione[cardinalita_unione] = secondo_insieme[j++];
            cardinalita_unione++;
        }
        else
        {
            insieme_unione[cardinalita_unione] = secondo_insieme[j++];
            cardinalita_unione++;
            i++;
        }
    }
    
    while (i < cardinalita_primo_insieme)
    {
        insieme_unione[cardinalita_unione] = primo_insieme[i++];
        cardinalita_unione++;
    }
    while (j < cardinalita_secondo_insieme)
    {
        insieme_unione[cardinalita_unione] = secondo_insieme[j++];
        cardinalita_unione++;
    }
    return cardinalita_unione;
}

int uguaglianza(float primo_insieme[],
                float secondo_insieme[],
                int cardinalita_primo_insieme,
                int cardinalita_secondo_insieme,
                int i)
{
    int risultato = 0;
    
    if (cardinalita_primo_insieme == cardinalita_secondo_insieme &&
        i < cardinalita_primo_insieme &&
        primo_insieme[i] == secondo_insieme[i])
    {
        risultato = (i + 1 == cardinalita_primo_insieme) ?
                    1 :
                    uguaglianza(primo_insieme,
                                secondo_insieme,
                                cardinalita_primo_insieme,
                                cardinalita_secondo_insieme,
                                i + 1);
    }
    return risultato;
}

int differenza(float *insieme_differenza,
               float primo_insieme[],
               float secondo_insieme[],
               int cardinalita_primo_insieme,
               int cardinalita_secondo_insieme,
               int i,
               int cardinalita_differenza)
{
    if (i < cardinalita_primo_insieme)
    {
        int j = 0;
        while (j < cardinalita_secondo_insieme &&
               primo_insieme[i] != secondo_insieme[j])
        {
            j++;
        }
        if (j == cardinalita_secondo_insieme &&
            cerca_in_insieme(insieme_differenza,
                             cardinalita_differenza,
                             primo_insieme[i]) == 0)
        {
            insieme_differenza[cardinalita_differenza] = primo_insieme[i];
            cardinalita_differenza++;
        }
        
        cardinalita_differenza = differenza(insieme_differenza,
                                            primo_insieme,
                                            secondo_insieme,
                                            cardinalita_primo_insieme,
                                            cardinalita_secondo_insieme,
                                            i + 1,
                                            cardinalita_differenza);
    }
    return cardinalita_differenza;
}


int intersezione(float *insieme_intersezione,
                 float primo_insieme[],
                 float secondo_insieme[],
                 int cardinalita_primo_insieme,
                 int cardinalita_secondo_insieme,
                 int i,
                 int j,
                 int cardinalita_intersezione)
{
    
    if (i < cardinalita_primo_insieme &&
        j < cardinalita_secondo_insieme)
    {
        if (primo_insieme[i] < secondo_insieme[j])
        {
            i++;
        }
        else if (secondo_insieme[j] < primo_insieme[i])
        {
            j++;
        }
        else /* if primo_insieme[i] == secondo_insieme[j] */
        {
            i++;
            if (cerca_in_insieme(insieme_intersezione,
                                 cardinalita_intersezione,
                                 secondo_insieme[j]) == 0)
            {
                insieme_intersezione[cardinalita_intersezione] = secondo_insieme[j++];
                cardinalita_intersezione++;
            }
        }
        cardinalita_intersezione = intersezione(insieme_intersezione,
                                                primo_insieme,
                                                secondo_insieme,
                                                cardinalita_primo_insieme,
                                                cardinalita_secondo_insieme,
                                                i,
                                                j,
                                                cardinalita_intersezione);
    }
    return cardinalita_intersezione;
}

int differenza_simmetrica(float *insieme_differenza_simmetrica,
                          float primo_insieme[],
                          float secondo_insieme[],
                          int cardinalita_primo_insieme,
                          int cardinalita_secondo_insieme)
{
    
    int cardinalita_prima_differenza,
        cardinalita_seconda_differenza,
        cardinalita_differenza_simmetrica;
    
    float primo_insieme_differenza[100],
          secondo_insieme_differenza[100];
    
    cardinalita_prima_differenza   = differenza(primo_insieme_differenza,
                                                primo_insieme,
                                                secondo_insieme,
                                                cardinalita_primo_insieme,
                                                cardinalita_secondo_insieme,
                                                0,
                                                0);
    cardinalita_seconda_differenza = differenza(secondo_insieme_differenza,
                                                secondo_insieme,
                                                primo_insieme,
                                                cardinalita_secondo_insieme,
                                                cardinalita_primo_insieme,
                                                0,
                                                0);
    
    cardinalita_differenza_simmetrica = unione(insieme_differenza_simmetrica,
                                               primo_insieme_differenza,
                                               secondo_insieme_differenza,
                                               cardinalita_prima_differenza,
                                               cardinalita_seconda_differenza);
    
    return cardinalita_differenza_simmetrica;
}

bool cerca_in_insieme(float insieme[],
                      int cardinalita,
                      float numero_reale)
{
    bool trovato = false;
    int  i       = 0;
    do
    {
        if (insieme[i] == numero_reale)
        {
            trovato = true;
        }
        i++;
    }
    while (i < cardinalita &&
           !trovato);
    return trovato;
}