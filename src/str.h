#include <stdbool.h>

int str_find(char * str, int c);
int str_find_n(char * str, int c, int n);
bool str_starts_with(char * str, char * look_for);
bool str_ends_with(char * str, char * look_for);
// bool str_contains(char * str, char * look_for);
// bool * str_equal(char * s1, char * s2);
// char * str_reverse(char * str);
// char * str_copy(char * str);
void str_upper(char * str);
void str_lower(char * str);
