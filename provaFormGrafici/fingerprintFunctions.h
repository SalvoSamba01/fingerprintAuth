
#pragma once
#include <string.h>

int CaptureFinger(char* filename);

int CreateModel(char* image, char* model);

float TestMatch(char* first, char* second);

int Work(const char* nome, const char* cognome, const char* cf);

int work(const char* nome, const char* cognome, const char* cf);

int init();

int end();

int createUserModel(const char* nome, const char* cognome, const char* cf);

int authenticate();

int editModel(const char* cf);

