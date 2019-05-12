#include <stdbool.h>
#include <stdlib.h>

typedef struct el_insieme
{
    float             valore;
    struct el_insieme *prossimo;
} el_insieme_t;

extern bool verifica_uguaglianza(el_insieme_t *el_primo_insieme,
                                 el_insieme_t *el_secondo_insieme);

extern el_insieme_t *calcola_intersezione(el_insieme_t *el_primo_insieme,
                                          el_insieme_t *el_secondo_insieme);

extern el_insieme_t *calcola_differenza(el_insieme_t *el_primo_insieme,
                                        el_insieme_t *el_secondo_insieme);

extern el_insieme_t *calcola_diff_simm(el_insieme_t *el_primo_insieme,
                                       el_insieme_t *el_secondo_insieme);