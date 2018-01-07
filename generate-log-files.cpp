#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<string>
using namespace std;

static const string fullpath = "log/";
static const int num_files = 12;

int main() {
	srand(time(0));
	for (int i = 0; i < num_files; i++) {
		ofstream fo(fullpath + "file" + to_string(i + 1) + ".log");
		int num_records = rand()%1000 + 500;
		for (int j = 0; j < num_records; j++) {
			fo << R"({"ts_fact":)" << time(0) + rand()%3 << R"(,"fact_name":"fact)" << 88*(rand()%3 + 1)
				<< R"(","actor_id":)" << time(0)%100 + rand()%5 + 55555
				<< R"(,"props":{"prop1":)" << rand()%2 + 1
				<< R"(,"prop2":)" << rand()%2 + 1
				<< R"(,"prop3":)" << rand()%2 + 1
				<< R"(,"prop4":)" << rand()%2 + 1
				<< R"(,"prop5":)" << rand()%2 + 1
				<< R"(,"prop6":)" << rand()%2 + 1
				<< R"(,"prop7":)" << rand()%2 + 1
				<< R"(,"prop8":)" << rand()%2 + 1
				<< R"(,"prop9":)" << rand()%2 + 1
				<< R"(,"prop10":)" << rand()%2 + 1 << ",}}\n";
		}
		fo.close();
	}
	return 0;
}

