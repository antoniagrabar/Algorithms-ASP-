#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

typedef struct element {
    char *key;
    char *value;
    struct element *next;
} Element;

typedef struct hashtable {
    int size;
    Element **table;
} Hashtable;


Hashtable *initialize_hashtable(int size) {
    Hashtable *hashtable = NULL;
    int i;

    if (size < 1) return NULL;
    if ((hashtable = malloc(sizeof(Hashtable)))==NULL) {
        return NULL;
    }

    if ((hashtable->table = malloc(sizeof(Element *) * size))==NULL) {
        return NULL;
    }
    for (i=0; i<size; i++) {
        hashtable->table[i] = NULL;
    }
    hashtable->size = size;
    return hashtable;
}


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


Element *create_element(char *key, char *value) {
    Element *novi;
    if ((novi = malloc(sizeof(Element)))==NULL) return NULL;
    if ((novi->key = duplicate_string(key))==NULL) return NULL;
    if ((novi->value = duplicate_string(value))==NULL) return NULL;
    novi->next = NULL;
    return novi;
}

void insert_element(Hashtable *hashtable, char *key, char *value) {
    int slot;  // pretinac
    Element *novi = NULL;
    Element *trenutni = NULL;

    slot = hash(hashtable, key);
    if (slot==-1) return;
    trenutni = hashtable->table[slot];
    while (trenutni!=NULL && trenutni->key!=NULL && strcmp(key, trenutni->key)!=0) {
        trenutni = trenutni->next;
    }
    // Ako element s istim kljucem postoji zamijeni vrijednost
    if (trenutni!=NULL && trenutni->key!=NULL && strcmp(key, trenutni->key)==0) {
        free(trenutni->value);
        trenutni->value = duplicate_string(value);
    } else {
        novi = create_element(key, value);
        novi->next = hashtable->table[slot];
        hashtable->table[slot] = novi;
    }
}

Element *search(Hashtable *hashtable, char *key) {
    int slot;
    Element *trenutni;

    if (hashtable==NULL) return NULL;
    slot = hash(hashtable, key);
    trenutni = hashtable->table[slot];
    while (trenutni!=NULL && trenutni->key!=NULL && strcmp(key, trenutni->key)!=0) {
        trenutni = trenutni->next;
    }
    return trenutni;
}

void print_list(Element *el) {
    while (el) {
        printf("%s ", el->key);
        el = el->next;
    }
    printf("\n");
}

void print_usage(Hashtable *hashtable) {
    int i, num;
    Element *trenutni;

    for (i=0; i<hashtable->size; i++) {
        trenutni = hashtable->table[i];
        printf("%d ", i);
        while (trenutni) {
            printf("%s ", trenutni->key);
            trenutni = trenutni->next;
        }
        printf("\n");
    }
}

Element *hashtable_to_list(Hashtable *hashtable) {
    Element *trenutni = NULL, *head = NULL, *tail = NULL;

    for(int slot = 0; slot < hashtable->size; ++slot){
        trenutni = hashtable->table[slot];
        if(trenutni == NULL) continue;
        if(!head){
            head = trenutni;
        } else {
            tail->next = trenutni;
        }
        while(trenutni->next) trenutni = trenutni->next;
        tail = trenutni;
    }
    return head;
}

int main() {
    int menu_choice, slot, size;
    Element *el, *head=NULL;
    Hashtable *hashtable;
    char c, key[10], value[20];


    DEBUG("Unesite velicinu tablice: ");
    scanf("%d", &size);
    hashtable = initialize_hashtable(size);
    do {
        DEBUG("1. Pretvori u listu\n");
        DEBUG("2. Dodaj\n");
        DEBUG("3. Dohvati\n");
        DEBUG("4. Ispisi zauzece tablice\n");
        DEBUG("5. Ispisi listu\n");
        DEBUG("6. Izlaz\n");
        DEBUG("Odabir:\t");
        scanf("%d", &menu_choice);

        switch(menu_choice) {
            case 1:
                head = hashtable_to_list(hashtable);
                break;
            case 2:
                scanf("%s", key);
                scanf("%s", value);
                insert_element(hashtable, key, value);
                break;
            case 3:
                scanf("%s", key);
                el = search(hashtable, key);
                if (el) printf("%s\n", el->value);
                else printf("Element s kljucem %s ne postoji.\n", key);
                break;
            case 4:
                printf("Tablica:\n");
                print_usage(hashtable);
                break;
            case 5:
                printf("Lista:\n");
                print_list(head);
                break;
            case 6:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=6);
    return 0;
}
