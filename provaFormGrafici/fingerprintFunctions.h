
#pragma once
#include <string>
#include <vector>

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

const char* convertErrorToText(int err);

int extractMinutiaeTXT();

struct Minutia {
	int x;
	int y;
	double angle; // in degrees
	int quality;  // quality score
};

std::vector<Minutia> readMinutiaeFromFile(const std::string& filename);

double computeScore(const std::vector<Minutia>& m1, const std::vector<Minutia>& m2, double epsilon_d, double epsilon_theta);
double computeHoughScore(const std::vector<Minutia>& m1, const std::vector<Minutia>& m2, double epsilon_d, double epsilon_theta);

double testNewMatch();




