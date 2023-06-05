#ifndef CSV_H
#define CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "skiplist.h"

#define MAX_LINE_LENGTH 1000
#define MAX_FIELD_LENGTH 1000
#define delimiter ";"

int findColum(int *array, int size, int colum);
int leitor_csv();

#endif