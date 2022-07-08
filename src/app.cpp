#include <stdio.h>
#include <cstring>
#include <tuple>
#include <optional>
#include <string>
#include <cmath>

using namespace std;

tuple<double, int>* append(tuple<double, int>* existing, tuple<double, int> added){
    tuple<double, int> newarr[sizeof(existing)/sizeof(tuple<double, int>) + 1];
    memcpy(newarr, existing, sizeof(existing));
    memcpy(newarr + sizeof(existing), &added, sizeof(tuple<double, int>));
    return newarr;
}

optional<tuple<double, int>*> tokener(char* inputString){
    tuple<double, int> tokens[100];
    int last = 0;
    double mem = 0;
    double digitcount = 1;
    for (int i = 0; i < strlen(inputString); i++)
    {
        const char c = inputString[i];
        if(isdigit(c)){
            mem += digitcount * (int)c;
            digitcount *= 10; 
            continue;
        }
        if(c == '+'){
            tuple<double, int> number = {mem, 0};
            append(tokens, number);
            digitcount = 1;
            mem = 0;
            continue;
        }
        if(c == '-'){
            tuple<double, int> number = {mem, 1};
            append(tokens, number);
            digitcount = 1;
            mem = 0;
            continue;
        }
        if(c == '*'){
            tuple<double, int> number = {mem, 2};
            append(tokens, number);
            digitcount = 1;
            mem = 0;
            continue;
        }
        if(c == '/'){
            tuple<double, int> number = {mem, 3};
            append(tokens, number);
            digitcount = 1;
            mem = 0;
            continue;
        }
        if(c == '^'){
            tuple<double, int> number = {mem, 4};
            append(tokens, number);
            digitcount = 1;
            mem = 0;
            continue;
        }
        // if(c == '('){
        //     tuple<double, int> number = {mem, 5};
        //     digitcount = 1;
        //     mem = 0;
        //     continue;
        // }
        // if(c == ')'){
        //     tuple<double, int> number = {mem, 6};
        //     digitcount = 1;
        //     mem = 0;
        //     continue;
        // }
        if(c == '.'){
            digitcount = 1;
            digitcount /= 10;
            continue;
        }
    }
    return nullopt;
}

int main(){
    char input[20];
    printf("Hello, I'm Call Culator\n");
    printf("Write here your equation:\n");
    scanf("%19[^\n]", &input);
    optional<tuple<double, int>*> tokens = tokener(input);
    if(tokens != nullopt){
        for(int i = 0; i < sizeof(tokens)/sizeof(tuple<double, int>); i++){
            printf("%d. %g and %d", i, get<0>(tokens.value()[i]), get<1>(tokens.value()[i]));
        }
    }
    return 0;
} 