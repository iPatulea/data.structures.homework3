#include <iostream>
#include <string.h>

template<typename T> struct Node {
    T info;
    struct Node<T> *next, *prev;
};

template <typename T> class LinkedList {
    public:
        struct Node<T> *pfirst, *plast;

        void addFirst(T x) {
            struct Node<T> *paux;

            paux = new struct Node<T>;
            paux->info = x;
            paux->prev = NULL;
            paux->next = pfirst;

            if (pfirst != NULL) pfirst->prev = paux;
            pfirst = paux;

            if (plast==NULL) plast=pfirst;
        }
        void addLast(T x) {
            struct Node<T> *paux;

            paux = new struct Node<T>;
            paux->info = x;
            paux->prev = plast;
            paux->next = NULL;

            if (plast != NULL) plast->next = paux;
            plast = paux;
            if (pfirst == NULL) pfirst = plast;
        }

        void removeFirst() {
            struct Node<T>* paux;

            if (pfirst != NULL) {
                paux = pfirst->next;
                if (pfirst == plast) plast = NULL;
                delete pfirst;
                pfirst = paux;
                if (pfirst != NULL) pfirst->prev = NULL;
            }
           // else cout<<"Error 101 - The list is empty\n";
        }

        void removeLast() {
            struct Node<T> *paux;

            if (plast != NULL) {
                paux = plast->prev;
                if (pfirst == plast) pfirst = NULL;
                delete plast;
                plast = paux;
                if (plast != NULL) plast->next = NULL;
            }
          //  else cout<<"Error 102 - The list is empty\n";
        }

        struct Node<T>* findFirstOccurrence(T x) {
            struct Node<T> *paux;

            paux = pfirst;
            while (paux != NULL) {
                if (strcmp(paux->info,x)==0)
                    return paux;
                paux = paux->next;
            }
            return NULL;
        }
        struct Node<T>* findLastOccurrence(T x) {
            struct Node<T> *paux;

            paux = plast;
            while (paux != NULL) {
                if (paux->info == x)
                    return paux;
                paux = paux->prev;
            }

            return NULL;
        }

        int isEmpty() {
            return (pfirst == NULL);
        }

    LinkedList() {
        pfirst = plast = NULL;
    }

        void removeFirstOccurrence(T x) {
            struct Node<T> *px;

            px = findFirstOccurrence(x);

            if (px != NULL) {
                if (px->prev != NULL)
                    px->prev->next = px->next;
                if (px->next != NULL)
                    px->next->prev = px->prev;

                if (px->prev == NULL) // px == pfirst
                    pfirst = px->next;

                if (px->next == NULL) // px == plast
                    plast = px->prev;

                delete px;
            }
        }
        void removeLastOccurrence(T x) {
            struct Node<T> *px;

            px = findLastOccurrence(x);

            if (px != NULL) {
                if (px->prev != NULL)
                    px->prev->next = px->next;
                if (px->next != NULL)
                    px->next->prev = px->prev;

                if (px->prev == NULL) // px == pfirst
                    pfirst = px->next;

                if (px->next == NULL) // px == plast
                    plast = px->prev;

                delete px;
            }
        }
};
