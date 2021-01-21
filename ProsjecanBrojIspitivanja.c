#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

typedef struct {
    char *key;
    char *value;
} Element;

typedef struct hashtable {
    int size;
    Element *table;
} Hashtable;


int (*oahash)(Hashtable*, char*, int);  // pokazivac na funkciju

Hashtable *initialize_hashtable(int size) {
    Hashtable *hashtable = NULL;
    int i;

    if (size < 1) return NULL;
    if ((hashtable = malloc(sizeof(Hashtable)))==NULL) {
        return NULL;
    }

    if ((hashtable->table = malloc(sizeof(Element) * size))==NULL) {
        return NULL;
    }
    for (i=0; i<size; i++) {
        hashtable->table[i].key = NULL;
        hashtable->table[i].value = NULL;
    }
    hashtable->size = size;
    return hashtable;
}

/*
 * Kopira string u novo alocirani prostor te vraca pokazivac na kopiju.
 */
char *duplicate_string(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d!=NULL) strcpy(d, s);
    return d;
}

int hash(Hashtable *hashtable, char *key) {
    unsigned long long int hashval=0;
    int i=0;

    if (hashtable==NULL) return -1;
    // Pretvori string u integer
    while (hashval < ULLONG_MAX && i < strlen(key)) {
        // pomak za 8 bitova u lijevo odnosno mnozenje s 256
        hashval = hashval << 8;
        hashval += key[i];
        i++;
    }
    // metoda dijeljenja
    return hashval % hashtable->size;
}


// Vraca adresu (indeks) pretinca koristeci funkciju hash i linearno ispitivanje
int oahash_linear(Hashtable *hashtable, char *key, int i) {
    return (hash(hashtable, key) + i) % hashtable->size;
}

// Vraca adresu (indeks) pretinca koristeci funkciju hash i kvadratno ispitivanje uz konstante c_1 = c_2 = 0.5
int oahash_quadratic(Hashtable *hashtable, char *key, int i) {
    return (hash(hashtable, key) + i/2 + i*i/2) % hashtable->size;
}


/*
 * Upisuje element u tablicu koristeci kljuc i funkciju oahash.
 * Ukoliko su svi pretinci u nizu zauzeti vraca -1.
 */
int insert_element(Hashtable *hashtable, char *key, char *value) {
    int i, slot;

    for (i=0; i<hashtable->size; i++) {
        slot = oahash(hashtable, key, i);
        if (hashtable->table[slot].key==NULL) {
            hashtable->table[slot].key = duplicate_string(key);
            hashtable->table[slot].value = duplicate_string(value);
            return slot;
        } else if (strcmp(hashtable->table[slot].key, key)==0) {
            // Ako element s istim kljucem postoji zamijeni vrijednost
            free(hashtable->table[slot].value);
            hashtable->table[slot].value = duplicate_string(value);
            return slot;
        }
    }
    return -1;
}

/*
 * Dohvaca element u tablici koristeci kljuc i funkciju oahash i vraca njegovu adresu.
 * Ukoliko element s trazenim kljucem ne postoji vraca NULL.
 */
Element *search(Hashtable *hashtable, char *key) {
    int i, slot;

    for (i=0; i<hashtable->size; i++) {
        slot = oahash(hashtable, key, i);
        if (hashtable->table[slot].key==NULL) break;
        if (strcmp(hashtable->table[slot].key, key)==0) {
            return (Element *)&(hashtable->table[slot]);
        }
    }
    return NULL;
}

float average_probing_count(Hashtable *hashtable) {
    int element_number = 0, probing_sum = 0;
    for(int index = 0; index < hashtable->size; ++index){
        int num = -1;
        if(hashtable->table[index].key != NULL){
            for(num = 0; num < hashtable->size; ++num){
                if(oahash(hashtable, hashtable->table[index].key, num) == index){
                    element_number++;
                    probing_sum += num+1;
                    break;
                }
            }
        }
    }
    return element_number ? (float) probing_sum/element_number : 0;
}

int main() {
    int menu_choice, slot, size, i, retval;
    Element *el;
    Hashtable *hashtable;
    char c, key[10], value[20];

    DEBUG("Odaberite funkciju otvorenog adresiranja.\n");
    do {
        DEBUG("1. Linearno ispitivanje\n");
        DEBUG("2. Kvadratno ispitivanje\n");
        DEBUG("Odabir:\t");
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                oahash = oahash_linear;
                break;
            case 2:
                oahash = oahash_quadratic;
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice<1 || menu_choice>2);

    DEBUG("Unesite velicinu tablice: ");
    scanf("%d", &size);
    hashtable = initialize_hashtable(size);
    do {
        DEBUG("1. Prosjecan broj ispitivanja\n");
        DEBUG("2. Dodaj\n");
        DEBUG("3. Dohvati\n");
        DEBUG("4. Adresiraj\n");
        DEBUG("5. Izlaz\n");
        DEBUG("Odabir:\t");
        scanf("%d", &menu_choice);

        switch(menu_choice) {
            case 1:
                printf("%.2f\n", average_probing_count(hashtable));
                break;
            case 2:
                DEBUG("Kljuc: ");
                scanf("%s", key);
                DEBUG("Vrijednost: ");
                scanf("%s", value);
                retval = insert_element(hashtable, key, value);
                if (retval==-1) printf("Dodavanje elementa s kljucem %s nije uspjelo.\n", key);
                break;
            case 3:
                DEBUG("Kljuc: ");
                scanf("%s", key);
                el = search(hashtable, key);
                if (el) printf("%s\n", el->value);
                else printf("Element s kljucem %s ne postoji.\n", key);
                break;
            case 4:
                DEBUG("Kljuc: ");
                scanf("%s", key);
                DEBUG("Redni broj ispitivanja: ");
                scanf("%d", &i);
                slot = oahash(hashtable, key, i);
                printf("%d\n", slot);
                break;
            case 5:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=5);
    return 0;
}
