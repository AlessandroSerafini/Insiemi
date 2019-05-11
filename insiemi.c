#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


typedef struct elemento_insieme
{
    float                   valore;
    struct elemento_insieme *prossimo;
} elemento_insieme_t;

void acquisisci_cardinalita(int *cardinalita,
                            bool primo_insieme);

void libera_memoria();

bool cerca_in_insieme(elemento_insieme_t *elemento_corrente,
                      float elemento_ricercato);

void acquisisci_elementi(elemento_insieme_t **testa,
                         int cardinalita);

void inserisci_acquisizione(elemento_insieme_t **testa,
                            elemento_insieme_t *elemento_acquisito);

bool verifica_uguaglianza(elemento_insieme_t *elemento_primo_insieme,
                          elemento_insieme_t *elemento_secondo_insieme);

elemento_insieme_t *calcola_intersezione(elemento_insieme_t *elemento_primo_insieme,
                                         elemento_insieme_t *elemento_secondo_insieme);

elemento_insieme_t *calcola_differenza(elemento_insieme_t *elemento_primo_insieme,
                                       elemento_insieme_t *elemento_secondo_insieme);

elemento_insieme_t *calcola_differenza_simmetrica(elemento_insieme_t *elemento_primo_insieme,
                                                  elemento_insieme_t *elemento_secondo_insieme);

void stampa_insieme(elemento_insieme_t *elemento);

int main()
{
    elemento_insieme_t *testa_primo_insieme           = NULL,
                       *testa_secondo_insieme         = NULL,
                       *insieme_intersezione          = NULL,
                       *insieme_differenza            = NULL,
                       *insieme_differenza_simmetrica = NULL;
    int                cardinalita_primo_insieme,
                       cardinalita_secondo_insieme;
    
    
    printf("\n********************\nINSIEMI\n********************\n");
    printf("\nQuesto software fa uso di una libreria esterna per effettuare operazioni sugli insiemi.");
    printf("\nGli insiemi in questione sono due e accettano esclusivamente numeri reali ed unici.");
    printf("\nLe operazioni effettuate sono le seguenti:");
    printf("\n- Verifica uguaglianza\n- Intersezione\n- Differenza\n- Differenza simmetrica\n\n");
    
    
    acquisisci_cardinalita(&cardinalita_primo_insieme,
                           true);
    acquisisci_elementi(&testa_primo_insieme,
                        cardinalita_primo_insieme);
    acquisisci_cardinalita(&cardinalita_secondo_insieme,
                           false);
    acquisisci_elementi(&testa_secondo_insieme,
                        cardinalita_secondo_insieme);
    
    insieme_intersezione = calcola_intersezione(testa_primo_insieme,
                                                testa_secondo_insieme);
    
    insieme_differenza = calcola_differenza(testa_primo_insieme,
                                            testa_secondo_insieme);
    
    insieme_differenza_simmetrica = calcola_differenza_simmetrica(testa_primo_insieme,
                                                                  testa_secondo_insieme);
    
    printf(verifica_uguaglianza(testa_primo_insieme,
                                testa_secondo_insieme) ?
           "\n\n[UGUAGLIANZA]: I due insiemi sono uguali" :
           "\n\n[UGUAGLIANZA]: I due insiemi sono diversi");
    
    printf("\n[INTERSEZIONE]: ");
    stampa_insieme(insieme_intersezione);
    
    printf("\n[DIFFERENZA]: ");
    stampa_insieme(insieme_differenza);
    
    printf("\n[DIFFERENZA SIMMETRICA]: ");
    stampa_insieme(insieme_differenza_simmetrica);
    
    
    return 0;
}

void libera_memoria()
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
    int  esito_lettura,
         carattere;
    bool acquisizione_valida = false;
    do
    {
        
        printf(primo_insieme ?
               "Inserisci la cardinalità del primo insieme:\n" :
               "Inserisci la cardinalità del secondo insieme:\n");
        
        esito_lettura  = scanf("%d",
                               cardinalita);
        
        if (esito_lettura != 1 ||
            *cardinalita <= 0)
        {
            printf("[ERRORE]: L'input deve essere un numero intero maggiore di 0!\n");
        }
        else
        {
            acquisizione_valida = true;
        }
        if ((carattere = getchar()) != EOF &&
            !isspace(carattere))
        {
            libera_memoria();
        }
        
    }
    while (!acquisizione_valida);
}

void acquisisci_elementi(elemento_insieme_t **testa,
                         int cardinalita)
{
    
    int   esito_lettura,
          carattere,
          i                   = 0;
    float valore_ingresso;
    bool  acquisizione_valida = false;
    
    printf("Inserisci gli elementi dell'insieme (uno per riga):\n");
    do
    {
        do
        {
            printf("Inserisci l'elemento %d\n",
                   i + 1);
            esito_lettura = scanf("%f",
                                  &valore_ingresso);
            
            if (esito_lettura != 1)
            {
                printf("[ERRORE]: L'input deve essere un numero reale!\n");
            }
            else if (cerca_in_insieme(*testa,
                                      valore_ingresso))
            {
                printf("[ERRORE]: Questo valore è già stato acquisito precedentemente!\n");
            }
            else
            {
                elemento_insieme_t *nuovo_elemento = (elemento_insieme_t *) malloc(sizeof(elemento_insieme_t));
                nuovo_elemento->valore   = valore_ingresso;
                nuovo_elemento->prossimo = NULL;
                inserisci_acquisizione(testa,
                                       nuovo_elemento);
                acquisizione_valida = true;
                i++;
            }
            
            if ((carattere = getchar()) != EOF &&
                !isspace(carattere))
            {
                libera_memoria();
            }
        }
        while (!acquisizione_valida);
    }
    while (i < cardinalita);
}

void inserisci_acquisizione(elemento_insieme_t **testa,
                            elemento_insieme_t *elemento_acquisito)
{
    elemento_insieme_t *elemento_corrente;
    if (*testa == NULL ||
        (*testa)->valore > elemento_acquisito->valore)
    {
        elemento_acquisito->prossimo = *testa;
        *testa = elemento_acquisito;
    }
    else
    {
        elemento_corrente = *testa;
        while (elemento_corrente->prossimo != NULL &&
               elemento_corrente->prossimo->valore < elemento_acquisito->valore)
        {
            elemento_corrente = elemento_corrente->prossimo;
        }
        elemento_acquisito->prossimo = elemento_corrente->prossimo;
        elemento_corrente->prossimo  = elemento_acquisito;
    }
}

bool verifica_uguaglianza(elemento_insieme_t *elemento_primo_insieme,
                          elemento_insieme_t *elemento_secondo_insieme)
{
    bool risultato = true;
    if (elemento_primo_insieme != NULL)
    {
        if (elemento_secondo_insieme != NULL)
        {
            if (elemento_primo_insieme->valore == elemento_secondo_insieme->valore)
            {
                risultato = verifica_uguaglianza(elemento_primo_insieme->prossimo,
                                                 elemento_secondo_insieme->prossimo);
            }
            else
            {
                risultato = false;
            }
        }
        else
        {
            risultato = false;
        }
    }
    else
    {
        risultato = (elemento_secondo_insieme == NULL);
    }
    
    return (risultato);
}

elemento_insieme_t *calcola_intersezione(elemento_insieme_t *elemento_primo_insieme,
                                         elemento_insieme_t *elemento_secondo_insieme)
{
    elemento_insieme_t *nuovo_elemento = NULL;
    if (elemento_primo_insieme != NULL &&
        elemento_secondo_insieme != NULL)
    {
        if (elemento_primo_insieme->valore < elemento_secondo_insieme->valore)
        {
            nuovo_elemento = calcola_intersezione(elemento_primo_insieme->prossimo,
                                                  elemento_secondo_insieme);
        }
        else if (elemento_primo_insieme->valore > elemento_secondo_insieme->valore)
        {
            nuovo_elemento = calcola_intersezione(elemento_primo_insieme,
                                                  elemento_secondo_insieme->prossimo);
        }
        else
        {
            nuovo_elemento = (elemento_insieme_t *) malloc(sizeof(elemento_insieme_t));
            nuovo_elemento->valore   = elemento_primo_insieme->valore;
            nuovo_elemento->prossimo = calcola_intersezione(elemento_primo_insieme->prossimo,
                                                            elemento_secondo_insieme->prossimo);
        }
    }
    return (nuovo_elemento);
}

elemento_insieme_t *calcola_differenza(elemento_insieme_t *elemento_primo_insieme,
                                       elemento_insieme_t *elemento_secondo_insieme)
{
    elemento_insieme_t *nuovo_elemento = NULL;
    if (elemento_primo_insieme != NULL)
    {
        if (elemento_secondo_insieme != NULL)
        {
            if (elemento_primo_insieme->valore < elemento_secondo_insieme->valore)
            {
                nuovo_elemento = (elemento_insieme_t *) malloc(sizeof(elemento_insieme_t));
                nuovo_elemento->valore   = elemento_primo_insieme->valore;
                nuovo_elemento->prossimo = calcola_differenza(elemento_primo_insieme->prossimo,
                                                              elemento_secondo_insieme);
            }
            else if (elemento_primo_insieme->valore > elemento_secondo_insieme->valore)
            {
                nuovo_elemento = calcola_differenza(elemento_primo_insieme,
                                                    elemento_secondo_insieme->prossimo);
            }
            else
            {
                nuovo_elemento = calcola_differenza(elemento_primo_insieme->prossimo,
                                                    elemento_secondo_insieme->prossimo);
            }
        }
        else
        {
            nuovo_elemento = (elemento_insieme_t *) malloc(sizeof(elemento_insieme_t));
            nuovo_elemento->valore   = elemento_primo_insieme->valore;
            nuovo_elemento->prossimo = calcola_differenza(elemento_primo_insieme->prossimo,
                                                          elemento_secondo_insieme);
        }
    }
    return (nuovo_elemento);
}

elemento_insieme_t *calcola_differenza_simmetrica(elemento_insieme_t *elemento_primo_insieme,
                                                  elemento_insieme_t *elemento_secondo_insieme)
{
    elemento_insieme_t *nuovo_elemento = NULL;
    if (elemento_primo_insieme != NULL &&
        elemento_secondo_insieme != NULL)
    {
        if (elemento_primo_insieme->valore < elemento_secondo_insieme->valore)
        {
            nuovo_elemento = (elemento_insieme_t *) malloc(sizeof(elemento_insieme_t));
            nuovo_elemento->valore   = elemento_primo_insieme->valore;
            nuovo_elemento->prossimo = calcola_differenza_simmetrica(elemento_primo_insieme->prossimo,
                                                                     elemento_secondo_insieme);
        }
        else if (elemento_primo_insieme->valore > elemento_secondo_insieme->valore)
        {
            nuovo_elemento = (elemento_insieme_t *) malloc(sizeof(elemento_insieme_t));
            nuovo_elemento->valore   = elemento_secondo_insieme->valore;
            nuovo_elemento->prossimo = calcola_differenza_simmetrica(elemento_primo_insieme,
                                                                     elemento_secondo_insieme->prossimo);
        }
        else
        {
            nuovo_elemento = calcola_differenza_simmetrica(elemento_primo_insieme->prossimo,
                                                           elemento_secondo_insieme->prossimo);
        }
    }
    else if (elemento_primo_insieme != NULL &&
             elemento_secondo_insieme == NULL)
    {
        nuovo_elemento = (elemento_insieme_t *) malloc(sizeof(elemento_insieme_t));
        nuovo_elemento->valore   = elemento_primo_insieme->valore;
        nuovo_elemento->prossimo = calcola_differenza_simmetrica(elemento_primo_insieme->prossimo,
                                                                 elemento_secondo_insieme);
        
    }
    else if (elemento_primo_insieme == NULL &&
             elemento_secondo_insieme != NULL)
    {
        nuovo_elemento = (elemento_insieme_t *) malloc(sizeof(elemento_insieme_t));
        nuovo_elemento->valore   = elemento_secondo_insieme->valore;
        nuovo_elemento->prossimo = calcola_differenza_simmetrica(elemento_primo_insieme,
                                                                 elemento_secondo_insieme->prossimo);
    }
    return (nuovo_elemento);
}


void stampa_insieme(elemento_insieme_t *elemento)
{
    printf("{");
    while (elemento != NULL)
    {
        printf("%lf",
               elemento->valore);
        if (elemento->prossimo != NULL)
        {
            printf(", ");
        }
        elemento = elemento->prossimo;
    }
    printf("}");
}

bool cerca_in_insieme(elemento_insieme_t *elemento_corrente,
                      float elemento_ricercato)
{
    bool trovato;
    if (elemento_corrente == NULL)
    {
        trovato = false;
    }
    else if (elemento_corrente->valore == elemento_ricercato)
    {
        trovato = true;
    }
    else
    {
        trovato = cerca_in_insieme(elemento_corrente->prossimo,
                                   elemento_ricercato);
    }
    
    return (trovato);
}