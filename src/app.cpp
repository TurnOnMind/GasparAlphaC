#include <stdio.h>
#include <cstring>
#include <tuple>
#include <optional>
#include <string>

using namespace std;

double trim(char* s){
    int i;
    while(isspace(*s)) s++;
    for(i = strlen(s) - 1; isspace(s[i]); i--) s[i + 1] = '\0';
    return strtod(s,&s);
}

tuple<char*, char*, int> spliter2(char* tosplit, int i, int op){
    static char str0[10],str1[10];
    memcpy(str0, tosplit, i * sizeof(char));
    memcpy(str1, tosplit + i + 1, (strlen(tosplit) - i - 1) * sizeof(char));
    return {str0, str1, op};
}

double calc(tuple<char*, char*, int> set){
    while(get<2>(set) == 0) return (trim(get<0>(set)) * trim(get<1>(set)));
    while(get<2>(set) == 1) return (trim(get<0>(set)) / trim(get<1>(set)));
    while(get<2>(set) == 2) return (trim(get<0>(set)) + trim(get<1>(set)));
    while(get<2>(set) == 3) return (trim(get<0>(set)) - trim(get<1>(set)));
    return 0.0;
}

optional<tuple<char*, char*, int>> spliter(char* tosplit){
    for (int i = 0; i < strlen(tosplit); i++)
    {
        const char c = tosplit[i];
        while(c == '*'){
            return spliter2(tosplit, i, 0);
        } 
        while(c == '/'){
            return spliter2(tosplit, i, 1);
        } 
        while(c == '+'){
            return spliter2(tosplit, i, 2);
        } 
        while(c == '-'){
            return spliter2(tosplit, i, 3);
        } 
    }
    return nullopt;
}

int main(){
    char input[10];
    printf("Hello, I'm Call Culator\n");
    printf("Write here your equation:\n");
    scanf("%s", &input);
    optional<tuple<char*, char*, int>> tuple = spliter(input);
    if(tuple != nullopt){
        //printf("%s %s %d \n", get<0>(tuple.value()), get<1>(tuple.value()), get<2>(tuple.value()));
        printf("%.9g", calc(tuple.value()));
    }
    return 0;
} 