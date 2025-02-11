#include <stdio.h>
#include <string.h>
int main() {
          
    char str[100];
    int count=0,temp=0;
    printf("Enter a string: ");
    scanf("%s", str);


     
     for (int i = 0; i < strlen(str); i++)
     {
        if(str[i]=='b'){
            count++;
             temp=1;
        }
         else{
            if(temp==1 && str[i]=='a'){
                count++;
            }
         }

     }

     if(count==2) { printf("valid string \n"); }
     else      {   printf("string is invalid"); }

    return 0;
}
