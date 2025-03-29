#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista=(List*)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * list) {
    if(list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if(list->current == NULL)return NULL;
    if(list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if(list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list->current == NULL) return NULL;
    if(list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* nodo = createNode(data);
    if (list->head == NULL) {
        list->head = nodo;
        list->tail = nodo;
    } else {
        nodo->next = list->head;
        list->head->prev = nodo;
        list->head = nodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* nodo = createNode(data);
    nodo->prev = list->current;
    nodo->next = list->current->next;
    nodo->prev->next = nodo;
    nodo->next = nodo;
    list->current = nodo;
    list->tail = nodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    void* popCurrent(List* list) {
    if (list == NULL || list->current == NULL) {
        // Si la lista o el nodo actual es NULL, no hay nada que eliminar
        return NULL;
    }

    Node* temp = list->current;
    void* data = temp->data; // Guardamos el dato para devolverlo

    // Actualizamos los punteros de los nodos vecinos
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        // Si no hay nodo anterior, significa que el nodo actual es el primero
        list->head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        // Si no hay nodo siguiente, significa que el nodo actual es el último
        list->tail = temp->prev;
    }

    // Movemos el current al siguiente nodo
    list->current = temp->next;

    // Liberamos la memoria del nodo eliminado
    free(temp);

    return data;
}

}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}