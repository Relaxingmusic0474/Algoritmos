#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#define TEXT "ALGORITMOS"
#define PATTERN "GOR"
#define NOT_VALID_INDEX -1
#define SEARCHING_NOT_SUCESSFUL_MSG(txt, ptn) (strcat(strcat(strcat("No se pudo encontrar el patrón ", ptn), " dentro del texto "), txt))
#define NUM_OF_LETTERS 26

#define q 101

typedef unsigned int Natural;
typedef struct window Window;

struct window
{
    char* string;
    Natural start_idx;
    Natural end_idx;
};

Natural code_character(unsigned char ch);
Natural power(Natural base, Natural exponent);
Natural hash_of_pattern(const char* pattern, Natural length);
Natural prev_hash_of_window(Window window, Natural prev_hash);
int rabin_karp(const char* text, const char* pattern);

int main() 
{
    int idx;

    if ((idx = rabin_karp(TEXT, PATTERN)) == NOT_VALID_INDEX) {
        SEARCHING_NOT_SUCESSFUL_MSG(TEXT, PATTERN);
        return 0;
    }

    printf("El patrón %s se pudo encontrar en la posición %d del texto %s.\n", PATTERN, idx, TEXT);

    return 0;
}

Natural code_character(unsigned char ch) 
{
    if (ch >= 'a' && ch <= 'z') {
        return (Natural) (ch - 'a' + 1);
    }
    
    else if (ch >= 'A' && ch <= 'Z') {
        return (Natural) (ch - 'A' + 1);
    }

    else {
        return (Natural) (ch + (NUM_OF_LETTERS + 1));
    }
}

Natural power(Natural base, Natural exponent) 
{
    if (exponent == 0) {
        return 1;
    }

    if (base == 0 || base == 1 || exponent == 1) {
        return base;
    }

    if (exponent & 1) {
        return base * power(base, exponent - 1);
    }

    Natural half = power(base, exponent >> 1);

    return half*half;
}

Natural hash_of_pattern(const char* pattern, Natural length) 
{
    Natural result = 0;
    Natural i = 0;  

    while (i < length) {
        result += code_character(pattern[i]) * power(NUM_OF_LETTERS, length - 1 - i);
        i++;
    }

    result %= q;

    return result;
}


Natural prev_hash_of_window(Window window, Natural prev_hash) 
{
    Natural result = prev_hash;

    if (window.start_idx == 0) 
    {
        result = 0;

        for (Natural i = window.start_idx; i <= window.end_idx; i++) {
            result += code_character(window.string[i]) *
                      power(NUM_OF_LETTERS, window.end_idx - i);
        }
    }
    else 
    {
        Natural old = code_character(window.string[window.start_idx - 1]);
        Natural new = code_character(window.string[window.end_idx]);

        result = (result - old * power(NUM_OF_LETTERS, window.end_idx - window.start_idx))
                 * NUM_OF_LETTERS
                 + new;
    }

    return result;
}


int rabin_karp(const char* text, const char* pattern) 
{
    if (!text || !pattern) {
        printf("El texto y/o el patrón es NULL\n");
        return NOT_VALID_INDEX;
    }

    Natural n = strlen(text);
    Natural m = strlen(pattern);

    if (m > n) {
        return NOT_VALID_INDEX;
    }

    Natural pattern_hash = hash_of_pattern(pattern, m);

    const Natural num_of_windows = n-m+1;

    Window windows[num_of_windows];

    for (Natural i=0; i<num_of_windows; i++) 
    {
        windows[i].string = (char*) calloc(strlen(text) + 1, sizeof(char));
        strcpy(windows[i].string, text);
        windows[i].start_idx = i;
        windows[i].end_idx = i+m-1;
    }


    Natural i = 0;
    Natural hash = 0, prev_hash_before_moduling_arithmetic = 0;

    printf("num_windows = %u\n", num_of_windows);

    while (i < num_of_windows) 
    {
        prev_hash_before_moduling_arithmetic = prev_hash_of_window(windows[i], prev_hash_before_moduling_arithmetic);
        hash = prev_hash_before_moduling_arithmetic % q;

        printf("prev_hash_before_moduling_arithmetic = %u, hash = %u, i=%u\n",prev_hash_before_moduling_arithmetic, hash, i);
        
        if (hash == pattern_hash) 
        {
            Natural txt_idx = i;
            Natural pattern_idx = 0;

            while (pattern_idx < m) 
            {
                if (text[txt_idx + pattern_idx] != pattern[pattern_idx]) {
                    break;
                }

                if (pattern_idx == m-1) {

                    for (Natural x=0; x<num_of_windows; x++) {
                        free(windows[x].string);
                        windows[x].string = NULL;
                    }

                    return txt_idx;
                }
                
                pattern_idx++;
            }
        }

        i++;
    }

    return NOT_VALID_INDEX;
}