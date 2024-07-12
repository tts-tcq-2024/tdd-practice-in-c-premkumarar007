#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H
 
#include "StringCalculator.h"
#include <stdbool.h>

int charToInt(char c) {
        return c - '0';
}

int stringCalculator(const char * str)
{
    bool additionFlag=false;
    int ans=0, num1=0, num2=0;
 
    for (int i = 0; str[i] != '\0'; i++) {

       if(isdigit(str[i]))
       {
           ans+=charToInt(str[i]);
       }
       
    }

 return ans; 
}

int add(const char * input)
{
   if(input=="" || input=="0") return 0;

   return stringCalculator(input);
   return -1;
}

#endif
