#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum { English, Italian, Spanish } language;
const char * month(int number, language lang);
const char *lang2str(language lang);

int main() {
    printf("%s\n", month(1, English));
    printf("%s\n", lang2str(1));
    return 0;
}

const char * month(int number, language lang) {
    if (number < 1 || number > 12 || lang < 0 || lang > 2) {
        return "Error";
    }

    const char *this_language = lang2str(lang);
    if (strcmp(this_language, "English") == 0) {
        static const char *months_in_eng[] = {
            "January", "February", "March", "April", "May", "June", "July",
            "August", "September", "October", "November", "December"
        };
        return months_in_eng[number-1];
    }
    if (strcmp(this_language, "Italian") == 0) {
        static const char *months_in_it[] = {
            "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio",
            "Giugno", "Luglio", "Agosto", "Settembre", "Ottobre",
            "Novembre", "Dicembre"
        };
        return months_in_it[number-1];
    }
    if (strcmp(this_language, "Spanish") == 0) {
        static const char *months_in_sp[] = {
            "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio",
            "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
        };
        return months_in_sp[number-1];
    }
    return "Error";
}

const char *lang2str(language lang) {
    if (lang >= 0 && lang < 3) {
        static const char *languages[] = {"English", "Italian", "Spanish"};
        return languages[lang];
    }
    return "Error";
}