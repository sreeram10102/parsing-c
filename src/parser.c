#include "parser.h"
#include <stdio.h>

#include "err.h"
#include "lexer.h"
#include "list.h"
#include "propformula.h"
#include "util.h"
#include "string.h"
#include "ctype.h"

/**
 * Assigns symbols to strings.
 *
 * Aborts the program with an error message if an invalid input is detected.
 *
 * @param str  a string to translate
 * @return     the resulting symbol
 */
 
  
 
FormulaKind toKind(const char* str) {
    // TODO Implement me!
    //NOT_IMPLEMENTED;
    //UNUSED(str);
    //char* ptr1;
    // char str1[3] = "&&";
    // char str2[3] ="||";
    // char str3[3] = "=>";
    // char str4[3] = "<=>";
    if(strcmp(str,"&&")==0){
     return AND;
    }else if(strcmp(str,"||")==0){
     return OR;  
    }
    else if(strcmp(str,"=>")==0){
     return IMPLIES;  
    }
    else if(strcmp(str,"<=>")==0){
     return EQUIV;  
    }
    else if(strcmp(str ,"!")==0){
      return NOT;  
    }
    else {
      for (int i=0 ; str[i]!= '\0';i++){
             if(!((str[i]>='A'&& str[i]<='Z') || (str[i]>='a'&& str[i]<='z')|| (str[i]>='0'&& str[i]<='9'))){
              //g =g+0;}
             //else {
                //g = g+1;
                err(str);
              
          }}
    return VAR;
    }
}

PropFormula* parseFormula(FILE* input, VarTable* vt) {
    // TODO Implement me!
    //NOT_IMPLEMENTED;
    //UNUSED(input);
    //UNUSED(vt);
    int a=0;
    List me = mkList();
//int g=0;
    //char*operand;
   
   char *ptr1 ;
   
   PropFormula*res = NULL;
   //char*res;
while((ptr1=nextToken(input))!= NULL){  

   
 
    //  if (isalnum(*ptr1)) {
    //     toKind(ptr1);
    //   char*operand =  mkVarFormula( vt,ptr1);
    //   push(&me,operand);
    //    nextToken(input);
    //    a=1;}
      if((toKind(ptr1)==NOT)&& a>=1){
        PropFormula* c = peek(&me);
         pop(&me); a--;
        res = mkUnaryFormula(NOT,c) ;
         // pop(&me);
          
          push( &me,res);
          a++;
          //free(ptr1);
          }
      else if (toKind(ptr1)== VAR){
         
            res =  mkVarFormula( vt,ptr1);
            push(&me,res);
            a++;
           
        }
      else if (a >= 2 && (toKind(ptr1) == AND || toKind(ptr1) == OR ||
              toKind(ptr1) == IMPLIES ||toKind(ptr1) == EQUIV)){
               PropFormula* s = peek(&me); 
               pop(&me);
               a--;

                PropFormula* c = peek(&me); 
                pop(&me);
                a--;
        res = mkBinaryFormula(toKind(ptr1), c, s);
          
          push( &me,res);
          a++;
        //free(ptr1);   
       }
    
      else {
           err(ptr1);
         }
        
    
}     
 
if (isEmpty(&me)) {
  err("Invalid");}
else if (a>1) {
   err("it has something unusual");
  }
else {
    res = peek(&me);
    pop(&me);
  }
 return res;

}