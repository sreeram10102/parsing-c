#include "list.h"

#include <assert.h>
#include <stdlib.h>

#include "err.h"
#include "util.h"

/**
 * Struct for encapsulating a single list element.
 */
typedef struct ListItem {
    struct ListItem* next;  // pointer to the next element (NULL if last)
    void* data;             // pointer to the data
} ListItem;

List mkList(void) {
    List res;
    res.head = NULL;
    return res;
}

void clearList(List* s) {
    // TODO Implement me!
    //NOT_IMPLEMENTED;
    //UNUSED(s);
    ListItem *temp ;
   
     
     
     while (s->head != NULL) {
        pop(s);}
}

void push(List* s, void* data) {
    // TODO Implement me!
   // NOT_IMPLEMENTED;
    //UNUSED(s);
    //UNUSED(data);
    ListItem *temp ;
     temp  = malloc(sizeof(ListItem));
     temp -> data= data;
     temp ->next = s->head;
     s->head= temp ;
}

void* peek(List* s) {
    // TODO Implement me!
   // NOT_IMPLEMENTED;
    //UNUSED(s);
     ListItem *temp = s ->head ;
      
      
        if(s->head == NULL){
        return NULL;
     }
        else  { 
       
       return temp->data;
     }
}

void pop(List* s) {
    // TODO Implement me!
    //NOT_IMPLEMENTED;
   // UNUSED(s);
   ListItem *temp;
   temp = s->head;
   if (s->head ==NULL){
      return ;
   }
   else{
    s->head =temp ->next;
    free(temp);
   }
}

char isEmpty(List* s) {
    // TODO Implement me!
    //NOT_IMPLEMENTED;
    //UNUSED(s);
    if (s->head == NULL){
        return 1;
        
    }
    else{
        return 0;
    }
    

}

ListIterator mkIterator(List* list) {
    ListIterator res;
    res.list = list;
    res.prev = NULL;
    res.current = list->head;

    return res;
}

void* getCurr(ListIterator* it) {
    assert(it->current != NULL);
    return it->current->data;
}

void next(ListIterator* it) {
    assert(isValid(it));
    it->prev = it->current;
    it->current = it->current->next;
}

char isValid(ListIterator* it) { return it->current != NULL; }
