#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H
 
#include "StringCalculator.h"
#include <stdbool.h>

int charToInt(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else {
        return -1;
    }
}

int stringCalculator(const char * str)
{
    bool additionFlag=false;
    int ans=0, num1=0, num2=0;
 
    for (int i = 0; str[i] != '\0'; i++) {
        
       if(str[i]==',') additionFlag=true;
       
       if(isdigit(str[i]) && additionFlag==false)
       {
           num1=charToInt(str[i]);
           ans+=num1;
       }
       else if(isdigit(str[i]) && additionFlag==true)
       {
           num2=charToInt(str[i]);
           ans+=num2;
           additionFlag=false;
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
