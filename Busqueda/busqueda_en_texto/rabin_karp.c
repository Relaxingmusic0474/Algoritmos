#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#define TEXT "La Motita es la perrita más linda del mundo"
#define PATTERN "perri"
#define MAX_LENGTH_PATTERN 100
#define NOT_VALID_INDEX -1
#define NUM_OF_LETTERS 26

#define q 101

typedef unsigned int Natural;

Natural code_character(unsigned char ch);
Natural power(Natural base, Natural exponent);
Natural hash_of_pattern(const char* pattern, Natural length);
Natural hash_of_window(const char* text, Natural start_idx, Natural end_idx, Natural prev_hash);
int rabin_karp(const char* text, const char* pattern);

Natural dp_powers[MAX_LENGTH_PATTERN+1] = {0};

int main() 
{
    int idx;

    if ((idx = rabin_karp(TEXT, PATTERN)) == NOT_VALID_INDEX) {
        printf("No se pudo encontrar el patrón %s dentro del texto %s.\n", PATTERN, TEXT);
        return 0;
    }

    printf("El patrón \"%s\" se pudo encontrar en el índice %d (posición %d) del texto \"%s\".\n", PATTERN, idx, idx+1, TEXT);

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
    if (dp_powers[exponent] != 0) {
        return dp_powers[exponent];
    }

    if (exponent == 0) {
        return dp_powers[0] = 1;
    }

    if (exponent == 1) {
        return dp_powers[1] = base;
    }

    if (base == 1) {
        for (Natural i=0; i<strlen(PATTERN); i++) {
            dp_powers[i] = 1;
        }
        return dp_powers[exponent];
    }

    if (exponent & 1) {
        return dp_powers[exponent] = base * power(base, exponent - 1);
    }

    Natural half = power(base, exponent >> 1);

    return dp_powers[exponent] = half * half;
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

Natural hash_of_window(const char* text, Natural start_idx, Natural end_idx, Natural prev_hash) 
{
    Natural result = prev_hash;

    if (start_idx == 0) 
    {
        result = 0;

        for (Natural i = start_idx; i <= end_idx; i++) {
            result += code_character(text[i]) *
                      power(NUM_OF_LETTERS, end_idx - i);
        }
    }
    else 
    {
        Natural old = code_character(text[start_idx - 1]);
        Natural new = code_character(text[end_idx]);

        result = (result - old * power(NUM_OF_LETTERS, end_idx - start_idx)) * NUM_OF_LETTERS + new;
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

    if (m > MAX_LENGTH_PATTERN) {
        printf("No es posible buscar un patrón tan largo debido a limitaciones del sistema.\n");
        return NOT_VALID_INDEX;
    }

    Natural pattern_hash = hash_of_pattern(pattern, m);

    printf("El hash del patrón es %u\n", pattern_hash);

    Natural i = 0, num_of_windows = n-m+1;
    Natural window_final_hash = 0, last_window_hash = 0;

    while (i < num_of_windows) 
    {
        last_window_hash = hash_of_window(text, i, i+m-1, last_window_hash);
        window_final_hash = last_window_hash % q;

        printf("i = %u, prev_hash_before_moduling_arithmetic = %u, hash = %u\n", i, last_window_hash, window_final_hash);
        
        if (window_final_hash == pattern_hash) 
        {
            Natural txt_idx = i;
            Natural pattern_idx = 0;

            while (pattern_idx < m) 
            {
                if (text[txt_idx + pattern_idx] != pattern[pattern_idx]) {
                    break;
                }

                if (pattern_idx == m-1) {
                    return txt_idx;
                }
                
                pattern_idx++;
            }
        }

        i++;
    }

    return NOT_VALID_INDEX;
}