#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_HEAP 524 + 1
#define DIM_ARR_PTR 50
#define GROWTH 5
#define LIST_LENGTH 50

#define MAX_CMD_LENGTH 19

#define PIANIFICA_DEMOLISCI 19
#define ROTTAMA 13
#define AGG_STAZIONE 18
#define AGG_AUTO 14

char cmd_pianifica[] = "pianifica-percorso";
char cmd_agg_stazione[] = "aggiungi-stazione";
char cmd_demolisci[] = "demolisci-stazione";
char cmd_rottama[] = "rottama-auto";
char cmd_agg_auto[] = "aggiungi-auto";

char cmd_error[] = "comando non riconosciuto";
char format_error[] = "errore formato stringa";
char mem_alloc_error[] = "memory allocation failure";
char err_heap_full[] = "posti per auto finiti";

typedef int Heap[DIM_HEAP];

int add_heap(Heap h, int data);
void max_heapify(Heap h, int i);
int rm_heap(Heap h, int data);

typedef struct NODE{
    int km;
    Heap h;
    struct NODE *next;
    struct NODE *prec;
} *List;

void add_node(List *l, List node);
List search_until(List l, int km);
int rm_node(List *l, int data);

typedef struct ROAD{
    List *ptr;
    int size;
    int max_size;
    int nodi;
} *Road;

int binary_search(List *l, int size, int km);
List search_s(Road r, int km);
int add_s(Road r, List s);
int rm_s(Road r, int km);

typedef struct JUMP{
    List s;
    int jump;
    struct JUMP *next;
} *Jump;

Jump add_jump(Jump j, List s, int jump);

int pianifica_percorso(Road r, int partenza, int arrivo, int *ptr_percorso[]);

int main(){
    struct ROAD road;
    road.ptr = (List*)malloc(DIM_ARR_PTR*sizeof(List));
    road.size = 0;
    road.max_size = DIM_ARR_PTR;
    road.nodi = 0;

    char cmd[MAX_CMD_LENGTH];
    
    int km;
    while(fscanf(stdin, "%s", cmd) != EOF){
        
        //aggiungi-stazione distanza numero-auto autonomia-auto-1 ... autonomia-auto-n
        if(!strcmp(cmd, cmd_agg_stazione)){
            int res = fscanf(stdin, "%d", &km);
            
            if(res == 1){
                if(search_s(&road, km) == NULL){
                    int num;
                    int res = fscanf(stdin, "%d", &num);

                    if(res == 1){
                        List s = (List)malloc(sizeof(struct NODE));
                        s->km = km;
                        s->h[0] = 0;

                        int data;
                        for(int i=0;i<num;i++){
                            res = fscanf(stdin, "%d", &data);
                            if(res == 1){
                                add_heap(s->h, data);
                            }
                            else{
                                fprintf(stdout, "non aggiunta\n");
                                fprintf(stderr, "%s\n", format_error);

                                break;
                            }
                        }

                        if(res == 1){
                            if(add_s(&road, s) == -1){
                                return -1;
                            }

                            fprintf(stdout, "aggiunta\n");
                        }
                    }
                    else{
                        fprintf(stdout, "non aggiunta\n");
                        fprintf(stderr, "%s\n", format_error);
                    }
                }
                else{
                    fprintf(stdout, "non aggiunta\n");
                }
            }
            else{
                fprintf(stdout, "non aggiunta\n");
                fprintf(stderr, "%s\n", format_error);
            }
        }

        //pianifica-percorso distanza-stazione-partenza distanza-stazione-arrivo
        else if(!strcmp(cmd, cmd_pianifica)){
            int arrivo, partenza;
            int res = fscanf(stdin, "%d %d", &partenza, &arrivo);
            
            if(res == 2){
                int *percorso = NULL;
                int len = pianifica_percorso(&road, partenza, arrivo, &percorso);

                if(len == 0){
                    fprintf(stdout, "nessun percorso\n");
                }
                else{
                    for(int i = 0; i<len - 1; i++){
                        fprintf(stdout, "%d ", percorso[i]);
                    }
                    fprintf(stdout, "%d\n", percorso[len - 1]);

                    free(percorso);
                }
            }
            else{
                fprintf(stdout, "nessun percorso\n");
                fprintf(stderr, "%s\n", format_error);
            }
        }

        //demolisci-stazione distanza
        else if(!strcmp(cmd, cmd_demolisci)){
            int res = fscanf(stdin, "%d", &km);
            if(res == 1){
                if(rm_s(&road, km) == 1){
                    fprintf(stdout, "demolita\n");
                }
                else{
                    fprintf(stdout, "non demolita\n");
                }
            }
            else{
                fprintf(stdout, "non demolita\n");
                fprintf(stderr, "%s\n", format_error);
            }
        }

        //aggiungi-auto distanza-stazione autonomia-auto-da-aggiungere
        else if(!strcmp(cmd, cmd_agg_auto)){
            int autonomia;
            int res = fscanf(stdin, "%d %d", &km, &autonomia);

            if(res == 2){
                List s = search_s(&road, km);
                if(s != NULL){
                    if(add_heap(s->h, autonomia) == 1){
                        fprintf(stdout, "aggiunta\n");
                    }
                    else{
                        fprintf(stdout, "non aggiunta\n");
                    }
                }
                else{
                    fprintf(stdout, "non aggiunta\n");
                }
            }
            else{
                fprintf(stdout, "non aggiunta\n");
                fprintf(stderr, "%s\n", format_error);
            }

        }

        //rottama-auto distanza-stazione autonomia-auto-da-rottamare
        else if(!strcmp(cmd, cmd_rottama)){
            int autonomia;
            int res = fscanf(stdin, "%d %d", &km, &autonomia);

            if(res == 2){
                List s = search_s(&road, km);
                if(s != NULL){
                    if(rm_heap(s->h, autonomia) == 1){
                        fprintf(stdout, "rottamata\n");
                    }
                    else{
                        fprintf(stdout, "non rottamata\n");
                    }
                }
                else{
                    fprintf(stdout, "non rottamata\n");
                }
            }
            else{
                fprintf(stdout, "non aggiunta\n");
                fprintf(stderr, "%s\n", format_error);
            }
                
        }

        //comando non trovato
        else{
            fprintf(stderr, "%s: %s",cmd_error, cmd);
        }
        
        //leggi fino a \n
        char c;
        do{
            c = getchar();
        }while(c != '\n' && c != EOF);
    }

    return 0;
}

// Heap function
int add_heap(Heap h, int data){
    if(h[0] == DIM_HEAP - 1){
        fprintf(stderr, "%s\n", err_heap_full);
        return 0;
    }
    
    int i = ++h[0];
    while(i > 1 && h[i/2] < data){
        h[i] = h[i/2];
        i = i/2;
    }
    
    h[i] = data;

    return 1;
}

void max_heapify(Heap h, int i){
    /*
MAX-HEAPIFY(A, i)
1 l := LEFT(i)
2 r := RIGHT(i)
3 if l ≤ A.heap-size and A[l] > A[i]
4 max := l
5 else max := i
6 if r ≤ A.heap-size and A[r] > A[max]
7 max := r
8 if max ≠ i then
9 swap A[i] ⟷ A[max]
10 MAX-HEAPIFY(A, max)
*/
    int size, l, r, max;
    size = h[0];
    l = 2*i;
    r = 2*i+1;

    if(l <= size && h[l] > h[i]){
        max = l;
    }
    else{
        max = i;
    }
    
    if(r <= size && h[r] > h[max]){
        max = r;
    }

    if(max != i){
        int tmp = h[i];
        h[i] = h[max];
        h[max] = tmp;
        max_heapify(h, max);
    }
}

int rm_heap(Heap h, int data){
    int size, i;
    size = h[0];
    
    for(i = 1; i <= size; i++){
        if(h[i] == data){
            break;
        }
    }

    if(i > size){
        return 0;
    }
    else if(i == size){
        h[0]--;
        return 1;
    }

    h[i] = h[size];
    h[0]--;
    
    max_heapify(h, i);

    return 1;
}

// List function
void add_node(List *l, List node){
    List cur = *l;
    while(cur != NULL){
        if(cur->km < node->km){

        }
    }
}

List search_until(List l, int km){
    while(l != NULL && l->km <= km){
        if(l->km == km){
            return l;
        }
        l = l->next;
    }
    return NULL;
}

int rm_node(List *l, int km){
    List rm = search_until(*l, km);
    if(rm == NULL){
        return 0;
    }

    if(rm->next != NULL){
        rm->next->prec = rm->prec;
    }

    if(rm->prec != NULL){
        rm->prec->next = rm->next;
    }

    if(rm == *l){
        *l = rm->next;
    }

    free(rm);
    return 1;
}

// Road function
int binary_search(List *l, int size, int km){
    int a, b, i;
    a = 0;
    b = size - 1;
    while(a<=b){
        i = (a+b)/2;

        if(l[i]->km < km){
            if(i == size - 1 || l[i+1]->km > km){
                return i;
            }
            a = i + 1;
        }

        else if(l[i]->km > km){
            if(i == 0){
                return 0;
            }
            else if(l[i-1]->km < km){
                return i - 1;
            }
            b = i - 1;
        }

        else{
            return i;
        }
    }
    return 0;
}

List search_s(Road r, int km){
    if(r->size == 0){
        return NULL;
    }
    int i = binary_search(r->ptr, r->size, km);
    return search_until(r->ptr[i], km);
}

int add_s(Road r, List s){
    if(r->size == 0){
        r->ptr[0] = s;
        s->prec = NULL;
        s->next = NULL;
        r->size++;
        r->nodi++;
        return 1;
    }
    else{
        int i = binary_search(r->ptr, r->size, s->km);
        List cur = r->ptr[i];

        List prec = NULL;
        while(cur != NULL && cur->km < s->km){
            prec = cur;
            cur = cur->next;
        }

        if(cur != NULL){
            cur->prec = s;
        }

        if(prec != NULL){
            prec->next = s;
        }
        else{
            r->ptr[i] = s;
        }

        s->next = cur;
        s->prec = prec;

        for(int j = i + 1; j < r->size; j++){
            r->ptr[j] = r->ptr[j]->prec;
        }

        r->nodi++;

        if(r->nodi/LIST_LENGTH == r->size){
            List l  = r->ptr[r->size - 1];
            while(l->next != NULL){
                l = l->next;
            }
            r->ptr[r->size] = l;
            r->size++;

            if(r->size == r->max_size){
                List *new_arr = realloc(r->ptr, (r->size + GROWTH)*sizeof(List));
                if(new_arr != NULL){
                    r->ptr = new_arr;
                    r->max_size += GROWTH;
                }
                else{
                    fprintf(stderr, "%s", mem_alloc_error);
                    return -1;
                }
            }
        }

        return 1;
    }
}

int rm_s(Road r, int km){
    if(r->size == 0){
        return 0;
    }

    int i = binary_search(r->ptr, r->size, km);
    int res = rm_node(&r->ptr[i], km);

    if(res == 1){
        r->nodi--;
        for(int j = i + 1; j < r->size; j++){
            r->ptr[j] = r->ptr[j]->next;
        }
        if(r->ptr[r->size-1] == NULL){
            r->size--;
        }
    }

    return res;
}

// Jump function
Jump add_jump(Jump j, List s, int jump){
    Jump new_j = (Jump)malloc(sizeof(struct JUMP));
    new_j->s = s;
    new_j->jump = jump;
    new_j->next = j;
    return new_j;
}

// Pianifica percorso
int pianifica_percorso(Road r, int partenza, int arrivo, int *ptr_percorso[]){
    List p = search_s(r, partenza);
    if(partenza == arrivo){
        return partenza;
    }

    if(p == NULL || p->h[0] == 0 || search_s(r, arrivo) == NULL){
        return 0;
    }

    Jump aux = NULL;
    int len = 2;

    if(partenza < arrivo){
        if(p->km + p->h[1] >= arrivo){
            *ptr_percorso = (int *)malloc(len*sizeof(int));
            (*ptr_percorso)[0] = partenza;
            (*ptr_percorso)[1] = arrivo;
            return len;
        }

        int jump = p->km + p->h[1];
        List cur = p->next;
        aux = add_jump(aux, cur, jump);

        int back_trace=0;

        int found = 0;
        while(cur != NULL){
            len++;
            int new_jump = jump;
            while(cur != NULL && cur->km <= jump){
                if(cur->h[0] > 0 && cur->km + cur->h[1] > new_jump){
                    new_jump = cur->km + cur->h[1];
                    if(new_jump >= arrivo){
                        back_trace = cur->km;
                        found = 1;
                        break;
                    }
                }
                cur = cur->next;
            }

            if(cur->km > new_jump){
                return 0;
            }
            else if(found == 1){
                break;
            }
            
            aux = add_jump(aux, cur, new_jump);
            jump = new_jump;
        }

        *ptr_percorso = (int *)malloc(len*sizeof(int));

        int *percorso = *ptr_percorso;
        percorso[0] = partenza;
        percorso[len - 2] = back_trace;
        percorso[len - 1] = arrivo;

        Jump tmp = aux;
        tmp = aux->next;
        free(aux);
        aux = tmp;

        for(int i = len - 3; i > 0; i--){
            cur = aux->s;
            while(cur->km <= aux->jump){
                if(cur->h[0] > 0 && cur->km + cur->h[1] >= back_trace){
                    back_trace = cur->km;
                    percorso[i] = cur->km;
                    break;
                }
                cur = cur->next;
            }
            
            tmp = aux->next;
            free(aux);
            aux = tmp;
        }
    }
    else{
        if(p->km - p->h[1] <= arrivo){
            *ptr_percorso = (int *)malloc(len*sizeof(int));
            (*ptr_percorso)[0] = partenza;
            (*ptr_percorso)[1] = arrivo;
            return len;
        }

        int jump = p->km - p->h[1];
        List cur = p->prec;
        aux = add_jump(aux, cur, jump);

        int back_trace = 0;

        int found = 0;
        while(cur != NULL){
            len++;
            int new_jump = jump;
            while(cur != NULL && cur->km >= jump){
                if(cur->h[0] > 0 && cur->km - cur->h[1] < new_jump){
                    new_jump = cur->km - cur->h[1];
                    if(new_jump <= arrivo){
                        back_trace = cur->km;
                        found = 1;
                    }
                }
                else if(found == 1 && cur->h[0] > 0 && cur->km - cur->h[1] <= arrivo){
                    back_trace = cur->km;
                }
                cur = cur->prec;
            }

            if(cur != NULL && cur->km < new_jump){
                return 0;
            }
            else if(found == 1){
                break;
            }
            
            aux = add_jump(aux, cur, new_jump);
            jump = new_jump;
        }

        *ptr_percorso = (int *)malloc(len*sizeof(int));

        int *percorso = *ptr_percorso;
        percorso[0] = partenza;
        percorso[len - 2] = back_trace;
        percorso[len - 1] = arrivo;

        Jump tmp = aux;
        tmp = aux->next;
        free(aux);
        aux = tmp;

        int new_backtrace = 0;

        for(int i = len - 3; i > 0; i--){
            cur = aux->s;
            while(cur->km >= aux->jump){
                if(cur->h[0] > 0 && cur->km - cur->h[1] <= back_trace){
                    new_backtrace = cur->km;
                    percorso[i] = cur->km;
                }
                cur = cur->prec;
            }
            back_trace = new_backtrace;
            
            tmp = aux->next;
            free(aux);
            aux = tmp;
        }
    }

    return len;
}
