#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

struct Elemento
{
    float           valore;
    struct Elemento *prossimo;
};

void acquisisci_cardinalita(int *cardinalita,
                            bool primo_insieme);

void libera_memoria();

bool cerca_in_insieme(struct Elemento *elemento_corrente,
                      float elemento_ricercato);

void acquisisci_elementi(struct Elemento **testa,
                         int cardinalita);

struct Elemento *ordina_lista(struct Elemento *elemento_primo_insieme,
                              struct Elemento *elemento_secondo_insieme);

bool verifica_uguaglianza(int cardinalita_primo_insieme,
                          int cardinalita_secondo_insieme,
                          struct Elemento *elemento_primo_insieme,
                          struct Elemento *elemento_secondo_insieme,
                          struct Elemento *testa_secondo_insieme);

struct Elemento *calcola_intersezione(struct Elemento *elemento_primo_insieme,
                                      struct Elemento *elemento_secondo_insieme,
                                      struct Elemento *testa_secondo_insieme);

struct Elemento *calcola_differenza(struct Elemento *elemento_primo_insieme,
                                    struct Elemento *elemento_secondo_insieme,
                                    struct Elemento *testa_secondo_insieme);

struct Elemento *calcola_differenza_simmetrica(struct Elemento *elemento_primo_insieme,
                                               struct Elemento *elemento_secondo_insieme,
                                               struct Elemento *ultimo_elemento_inserito);

void stampa_insieme(struct Elemento *elemento);

int main()
{
    struct Elemento *testa_primo_insieme           = NULL,
                    *testa_secondo_insieme         = NULL,
                    *insieme_intersezione          = NULL,
                    *insieme_differenza            = NULL,
                    *insieme_differenza_simmetrica = NULL;
    int             cardinalita_primo_insieme,
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
                                                testa_secondo_insieme,
                                                testa_secondo_insieme);
    
    insieme_differenza = calcola_differenza(testa_primo_insieme,
                                            testa_secondo_insieme,
                                            testa_secondo_insieme);
    
    insieme_differenza_simmetrica = calcola_differenza_simmetrica(testa_primo_insieme,
                                                                  testa_secondo_insieme,
                                                                  insieme_differenza_simmetrica);
    
    printf("\n[PRIMO INSIEME]: ");
    stampa_insieme(testa_primo_insieme);
    
    printf("\n[SECONDO INSIEME]: ");
    stampa_insieme(testa_secondo_insieme);
    
    printf(verifica_uguaglianza(cardinalita_primo_insieme,
                                cardinalita_secondo_insieme,
                                testa_primo_insieme,
                                testa_secondo_insieme,
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
        
        esito_lettura = scanf("%d",
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
        if ((carattere     = getchar()) != EOF &&
            !isspace(carattere))
        {
            libera_memoria();
        }
        
    }
    while (!acquisizione_valida);
}

struct Elemento *ordina_lista(struct Elemento *elemento_primo_insieme,
                              struct Elemento *elemento_secondo_insieme)
{
    struct Elemento *result = NULL;
    
    if (elemento_primo_insieme == NULL)
    {
        return (elemento_secondo_insieme);
    }
    else if (elemento_secondo_insieme == NULL)
    {
        return (elemento_primo_insieme);
    }
    
    if (elemento_primo_insieme->valore <= elemento_secondo_insieme->valore)
    {
        result = elemento_primo_insieme;
        result->prossimo = ordina_lista(elemento_primo_insieme->prossimo,
                                        elemento_secondo_insieme);
    }
    else
    {
        result = elemento_secondo_insieme;
        result->prossimo = ordina_lista(elemento_primo_insieme,
                                        elemento_secondo_insieme->prossimo);
    }
    return (result);
}

void acquisisci_elementi(struct Elemento **testa,
                         int cardinalita)
{
    
    int   esito_lettura,
          carattere,
          i            = 0;
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
                struct Elemento *nuovo_elemento = (struct Elemento *) malloc(sizeof(struct Elemento));
                struct Elemento *ultimo         = *testa;
                nuovo_elemento->valore   = valore_ingresso;
                nuovo_elemento->prossimo = NULL;
                
                if (*testa == NULL)
                {
                    *testa = nuovo_elemento;
                }
                else
                {
                    while (ultimo->prossimo != NULL)
                    {
                        ultimo = ultimo->prossimo;
                    }
                    ultimo->prossimo = nuovo_elemento;
                }
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

bool verifica_uguaglianza(int cardinalita_primo_insieme,
                          int cardinalita_secondo_insieme,
                          struct Elemento *elemento_primo_insieme,
                          struct Elemento *elemento_secondo_insieme,
                          struct Elemento *testa_secondo_insieme)
{
    bool risultato;
    if (cardinalita_primo_insieme == cardinalita_secondo_insieme)
    {
        if (elemento_primo_insieme != NULL)
        {
            risultato = false;
            if (elemento_secondo_insieme != NULL)
            {
                risultato = elemento_primo_insieme->valore == elemento_secondo_insieme->valore ?
                            verifica_uguaglianza(cardinalita_primo_insieme,
                                                 cardinalita_secondo_insieme,
                                                 elemento_primo_insieme->prossimo,
                                                 testa_secondo_insieme,
                                                 testa_secondo_insieme) :
                            verifica_uguaglianza(cardinalita_primo_insieme,
                                                 cardinalita_secondo_insieme,
                                                 elemento_primo_insieme,
                                                 elemento_secondo_insieme->prossimo,
                                                 testa_secondo_insieme);
            }
        }
        else
        {
            risultato = true;
        }
    }
    else
    {
        risultato = false;
    }
    
    return risultato;
}

struct Elemento *calcola_intersezione(struct Elemento *elemento_primo_insieme,
                                      struct Elemento *elemento_secondo_insieme,
                                      struct Elemento *testa_secondo_insieme)
{
    struct Elemento *nuovo_elemento = NULL;
    if (elemento_primo_insieme != NULL)
    {
        if (elemento_secondo_insieme != NULL)
        {
            if (elemento_primo_insieme->valore == elemento_secondo_insieme->valore)
            {
                nuovo_elemento = (struct Elemento *) malloc(sizeof(struct Elemento));
                nuovo_elemento->valore   = elemento_primo_insieme->valore;
                nuovo_elemento->prossimo = calcola_intersezione(elemento_primo_insieme->prossimo,
                                                                testa_secondo_insieme,
                                                                testa_secondo_insieme);
            }
            else
            {
                nuovo_elemento = calcola_intersezione(elemento_primo_insieme,
                                                      elemento_secondo_insieme->prossimo,
                                                      testa_secondo_insieme);
            }
        }
        else
        {
            nuovo_elemento = calcola_intersezione(elemento_primo_insieme->prossimo,
                                                  testa_secondo_insieme,
                                                  testa_secondo_insieme);
        }
    }
    return nuovo_elemento;
}

struct Elemento *calcola_differenza(struct Elemento *elemento_primo_insieme,
                                    struct Elemento *elemento_secondo_insieme,
                                    struct Elemento *testa_secondo_insieme)
{
    struct Elemento *nuovo_elemento = NULL;
    if (elemento_primo_insieme != NULL)
    {
        if (elemento_secondo_insieme != NULL)
        {
            nuovo_elemento = elemento_primo_insieme->valore == elemento_secondo_insieme->valore ?
                             calcola_differenza(elemento_primo_insieme->prossimo,
                                                testa_secondo_insieme,
                                                testa_secondo_insieme) :
                             calcola_differenza(elemento_primo_insieme,
                                                elemento_secondo_insieme->prossimo,
                                                testa_secondo_insieme);
        }
        else
        {
            nuovo_elemento = (struct Elemento *) malloc(sizeof(struct Elemento));
            nuovo_elemento->valore   = elemento_primo_insieme->valore;
            nuovo_elemento->prossimo = calcola_differenza(elemento_primo_insieme->prossimo,
                                                          testa_secondo_insieme,
                                                          testa_secondo_insieme);
        }
    }
    return nuovo_elemento;
}

//TODO: FARLO FUNZIONARE ANCHE CON LISTE NON ORDINATE
struct Elemento *calcola_differenza_simmetrica(struct Elemento *elemento_primo_insieme,
                                               struct Elemento *elemento_secondo_insieme,
                                               struct Elemento *ultimo_elemento_inserito)
{
    struct Elemento *nuovo_elemento = NULL;
    if (elemento_primo_insieme != NULL &&
        elemento_secondo_insieme != NULL)
    {
        if (elemento_primo_insieme->valore > elemento_secondo_insieme->valore)
        {
            if (!ultimo_elemento_inserito ||
                ultimo_elemento_inserito->valore != elemento_secondo_insieme->valore)
            {
                nuovo_elemento = (struct Elemento *) malloc(sizeof(struct Elemento));
                nuovo_elemento->valore   = elemento_secondo_insieme->valore;
                nuovo_elemento->prossimo = calcola_differenza_simmetrica(elemento_primo_insieme,
                                                                         elemento_secondo_insieme->prossimo,
                                                                         nuovo_elemento);
            }
            else
            {
                nuovo_elemento = calcola_differenza_simmetrica(elemento_primo_insieme,
                                                               elemento_secondo_insieme->prossimo,
                                                               nuovo_elemento);
            }
        }
        else if (elemento_primo_insieme->valore < elemento_secondo_insieme->valore)
        {
            if (!ultimo_elemento_inserito ||
                ultimo_elemento_inserito->valore != elemento_primo_insieme->valore)
            {
                nuovo_elemento = (struct Elemento *) malloc(sizeof(struct Elemento));
                nuovo_elemento->valore   = elemento_primo_insieme->valore;
                nuovo_elemento->prossimo = calcola_differenza_simmetrica(elemento_primo_insieme->prossimo,
                                                                         elemento_secondo_insieme,
                                                                         nuovo_elemento);
            }
            else
            {
                nuovo_elemento = calcola_differenza_simmetrica(elemento_primo_insieme->prossimo,
                                                               elemento_secondo_insieme,
                                                               nuovo_elemento);
            }
        }
        else if (elemento_primo_insieme->valore == elemento_secondo_insieme->valore)
        {
            nuovo_elemento = calcola_differenza_simmetrica(elemento_primo_insieme->prossimo,
                                                           elemento_secondo_insieme->prossimo,
                                                           ultimo_elemento_inserito);
        }
    }
    else if (elemento_primo_insieme == NULL &&
             elemento_secondo_insieme != NULL)
    {
        if (!ultimo_elemento_inserito ||
            ultimo_elemento_inserito->valore != elemento_secondo_insieme->valore)
        {
            nuovo_elemento = (struct Elemento *) malloc(sizeof(struct Elemento));
            nuovo_elemento->valore   = elemento_secondo_insieme->valore;
            nuovo_elemento->prossimo = calcola_differenza_simmetrica(elemento_primo_insieme,
                                                                     elemento_secondo_insieme->prossimo,
                                                                     nuovo_elemento);
        }
        else
        {
            nuovo_elemento = calcola_differenza_simmetrica(elemento_primo_insieme,
                                                           elemento_secondo_insieme->prossimo,
                                                           nuovo_elemento);
        }
    }
    else if (elemento_secondo_insieme == NULL &&
             elemento_primo_insieme != NULL)
    {
        if (!ultimo_elemento_inserito ||
            ultimo_elemento_inserito->valore != elemento_primo_insieme->valore)
        {
            nuovo_elemento = (struct Elemento *) malloc(sizeof(struct Elemento));
            nuovo_elemento->valore   = elemento_primo_insieme->valore;
            nuovo_elemento->prossimo = calcola_differenza_simmetrica(elemento_primo_insieme->prossimo,
                                                                     elemento_secondo_insieme,
                                                                     nuovo_elemento);
        }
        else
        {
            nuovo_elemento = calcola_differenza_simmetrica(elemento_primo_insieme->prossimo,
                                                           elemento_secondo_insieme,
                                                           nuovo_elemento);
        }
    }
    return nuovo_elemento;
}


void stampa_insieme(struct Elemento *elemento)
{
    printf("{");
    while (elemento != NULL)
    {
        printf("%.2f",
               elemento->valore);
        if (elemento->prossimo != NULL)
        {
            printf(", ");
        }
        elemento = elemento->prossimo;
    }
    printf("}");
}

bool cerca_in_insieme(struct Elemento *elemento_corrente,
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
    
    return trovato;
}