#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<regex>
#include<tuple>
#include<forward_list>
#include<thread>
using namespace std;

static const string fullpath = "log/";
static const int num_threads = 3;  //must be greater than 0
static const int num_files = 12;

typedef tuple<uint32_t, string, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t> T12;

ostream& operator<<(ostream &out, const T12 t) {
	out << get<0>(t) << ' ' << get<1>(t) << " [" << get<2>(t) << ' '<< get<3>(t) << ' ' << get<4>(t) << ' '
		<< get<5>(t) << ' ' << get<6>(t) << ' ' << get<7>(t) << ' ' << get<8>(t) << ' '
		<< get<9>(t) << ' ' << get<10>(t) << ' ' << get<11>(t) << ']';
	return out;
}

uint32_t string2uint(const string &s) {
	istringstream is(s);
	uint32_t d;
	is >> d;
	return d;
}

regex json(R"(\{\s*"ts_fact"\s*:\s*([0-9]+),\s*)"
	R"("fact_name"\s*:\s*"(.*?)["],\s*)"
	R"("actor_id"\s*:\s*([0-9]+),\s*)"
	R"("props"\s*:\s*)"
	R"(\{\s*)"
	R"("prop1"\s*:\s*([0-9]+),\s*)"
	R"("prop2"\s*:\s*([0-9]+),\s*)"
	R"("prop3"\s*:\s*([0-9]+),\s*)"
	R"("prop4"\s*:\s*([0-9]+),\s*)"
	R"("prop5"\s*:\s*([0-9]+),\s*)"
	R"("prop6"\s*:\s*([0-9]+),\s*)"
	R"("prop7"\s*:\s*([0-9]+),\s*)"
	R"("prop8"\s*:\s*([0-9]+),\s*)"
	R"("prop9"\s*:\s*([0-9]+),\s*)"
	R"("prop10"\s*:\s*([0-9]+),?\s*\}\s*\})");

void file_processing(unsigned start, unsigned n, forward_list<T12> *p) {
	for (int i = start; i < start + n; i++) {
		ifstream fi(fullpath + "file" + to_string(i) + ".log");
		fi.seekg (0, fi.end);
		int length = fi.tellg();
		fi.seekg (0, fi.beg);
		char *buffer = new char [length + 1];
		const char *q = buffer;
		fi.read (buffer, length);
		cmatch cm;
		while (regex_search(q, cm, json)) {
			p->push_front(make_tuple(string2uint(cm[1]), cm[2].str(), string2uint(cm[4]), string2uint(cm[5]),
				string2uint(cm[6]), string2uint(cm[7]), string2uint(cm[8]), string2uint(cm[9]),
				string2uint(cm[10]), string2uint(cm[11]), string2uint(cm[12]), string2uint(cm[13])));
		        q = cm.suffix().first;
		}
		delete [] buffer;
		fi.close();
	}
}

int main() {
        forward_list<T12> *pfacts = new forward_list<T12> [num_threads];
	unsigned start = 1, //starting file number for a thread
		fpt = num_files/num_threads + (num_files%num_threads > num_threads/2), //files per a thread
		nf = num_files, thread_cnt = 0;
	thread threads[num_threads - 1];
	while (thread_cnt < num_threads - 1) {
		threads[thread_cnt] = thread(file_processing, start, fpt, &pfacts[thread_cnt + 1]);
		thread_cnt++;
		start += fpt;
		nf -= fpt;
	}
	file_processing(start, nf, &pfacts[0]);
	for (int i = 1; i < num_threads; i++) {
		threads[i - 1].join();
		pfacts[0].splice_after(pfacts[0].begin(), pfacts[i]);
	}
	pfacts[0].sort();
	auto p = pfacts[0].begin(), q = p++;
	unsigned count = 1;
	ofstream fo("agr.txt");
        while (p != pfacts[0].end()) {
		if (*p != *q) {
			fo << *q << ' ' << count << endl;
			count = 1;
		}
		else
			count++;
		q = p++;
	}
	fo << *q << ' ' << count << endl;
	fo.close();
	delete [] pfacts;
	return 0;
}

