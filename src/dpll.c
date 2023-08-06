#include "dpll.h"
//#include <cstddef>

#include "cnf.h"
#include "err.h"
#include "list.h"
#include "util.h"
#include "variables.h"

typedef enum Reason { CHOSEN, IMPLIED } Reason;

/**
 * Struct to represent an entry in the assignment stack. Should only be created
 * and freed by pushAssignment and popAssignment.
 */
typedef struct Assignment {
    VarIndex var;
    Reason reason;
} Assignment;

/**
 * Adds a new assignment to the assignment stack.
 *
 * @param stack  an assignment stack
 * @param var    the variable to assign
 * @param r      the reason for the assignment
 */
void pushAssignment(List* stack, VarIndex var, Reason r) {
    Assignment* a = (Assignment*)malloc(sizeof(Assignment));
    a->var = var;
    a->reason = r;
    push(stack, a);
}

/**
 * Removes the head element of an assignment stack and frees it.
 *
 * @param stack  an assignment stack
 */
void popAssignment(List* stack) {
    Assignment* a = (Assignment*)peek(stack);
    free(a);
    pop(stack);
}

/**
 * Führt eine Iteration des DPLL Algorithmus aus.
 *
 * @param vt       die zugrunde liegende Variablentabelle
 * @param stack    der Zuweisungsstack
 * @param cnf      die zu prüfende Formel
 * @return         1 falls der Algorithmus mit SAT terminieren sollte,
 *                 0 falls der Algorithmus weiterlaufen sollte,
 *                 -1 falls der Algorithmus mit UNSAT terminieren sollte
 */
/**
 * Performs one iteration of the DPLL algorithm.
 *
 * @param vt       the underlying variable table
 * @param stack    an assignment stack
 * @param cnf      the formula to check
 * @return         1 if the algorithm should terminate with SAT,
 *                 0 if the algorithm should continue,
 *                -1 if the algorithm should terminate with UNSAT
 */
 
   
int iterate(VarTable* vt, List* stack, CNF* cnf) {
    // TODO Implement me!
    //NOT_IMPLEMENTED;
    //UNUSED(vt);
    //UNUSED(stack);
   // UNUSED(cnf);
   //List me = mkList();
    if(evalCNF(cnf)==TRUE)
     return 1;
    else if (evalCNF(cnf)==FALSE){
        while(!isEmpty(stack)){
                 Assignment* a=(Assignment*)peek(stack);
                if(a->reason==CHOSEN){
                updateVariableValue(vt, a->var, FALSE);
                a->reason=IMPLIED;
                 return 0;
                popAssignment(stack);}
                        
                else if(a->reason==IMPLIED){
                  updateVariableValue(vt, a->var, UNDEFINED);
                   popAssignment(stack); }
                   
        }return -1;
        }       
    else if (evalCNF(cnf)==UNDEFINED){
        ListIterator it = mkIterator(&cnf->clauses);
          
     //Clause* current = (Clause*) getCurr(&it);
     while(isValid(&it)) { 
        //Clause* current = (Clause*) getCurr(&it);
          Clause* current = (Clause*) getCurr(&it);
        // if(getUnitLiteral(vt, current)==0 && evalCNF(cnf)==UNDEFINED){
        //      break;
        //   }
           if(getUnitLiteral(vt, current)!=0 ){
            Literal store = getUnitLiteral(vt,current);
         // if(store!=0 && (store == 1||store==-1)){
          // VarIndex x = getVariableValue(vt, store);
          
            if ( store > 0){
               updateVariableValue(vt, store, TRUE);
               pushAssignment(stack, store, IMPLIED);
               return 0;
            }
            else{
             updateVariableValue(vt, -store, FALSE);
             pushAssignment(stack, -store, IMPLIED);
             return 0;
          }
          
         }
        
         
        next(&it);
         
      }     
          
           Literal get= getNextUndefinedVariable(vt);
           if(get==0){
            return 1;
           }
            updateVariableValue(vt, get, TRUE);
            pushAssignment(stack, get, CHOSEN);
            return 0;

            
            
}
 return 0;
    

   
}

char isSatisfiable(VarTable* vt, CNF* cnf) {
    List stack = mkList();

    int res;
    do {
        res = iterate(vt, &stack, cnf);
    } while (res == 0);

    while (!isEmpty(&stack)) {
        popAssignment(&stack);
    }

    return (res < 0) ? 0 : 1;
}
