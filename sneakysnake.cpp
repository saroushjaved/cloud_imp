#include<iostream> 
#include "SneakySnake.h"
using namespace std;



int upper_hrt(char* q, char* r, int E, int N, int checkpoint);
int lower_hrt(char* q, char* r, int E, int N, int checkpoint);
int main_hrt(char* q, char* r, int N, int checkpoint);


int SneakySnake(int ReadLength, char* Ref, char* Que, int EditThreshold, int KmerSize, int DebugMode, int IterationNo) {

	int N = ReadLength;
	
	int p_delay = 0;
	int Debug_mode = DebugMode;

	int checkpoint = 0;


	while ((checkpoint < N) && (p_delay <= EditThreshold)) {
		int count = 0;
		int longest_es = upper_hrt(Que, Ref, EditThreshold, N, checkpoint);
		count = main_hrt(Que, Ref, N, checkpoint);
		if (count == N) {
			return 1;
		}
		else if (count > longest_es) {
			longest_es = count;
		}
		count = lower_hrt(Que, Ref, EditThreshold, N, checkpoint);
		if (count > longest_es) {
			longest_es = count;
		}
		checkpoint = checkpoint + longest_es;
		if (checkpoint < N) {
			p_delay++;
			checkpoint++;
		}
	}


	if (p_delay > EditThreshold) {
		return 0;
	}
	else if (p_delay <= EditThreshold) {
		return 1;
	}

return 0;

}


int upper_hrt(char* q, char* r, int E, int N, int checkpoint) {
	int longest_es = 0;
	for (int i = E; i >= 1; i--) {
		int count = 0;
		for (int j = checkpoint; j < N ; j++) {
			if (j < i) {
				goto EXIT;
			}
			else if (q[j - i] != r[j]) {
				goto EXIT;
			}
			else if (q[j - i] == r[j]) {
				count++;
			}
		}
	EXIT:
		if (count > longest_es) {
			longest_es = count;
		}
		/*if (count == N) {
			break;
		}*/
	}

	return longest_es;

}


int lower_hrt(char* q, char* r, int E, int N, int checkpoint) {
	int longest_es = 0;
	for (int i = 1; i <= E ; i++) {
		int count = 0;
		for (int j = checkpoint; j < N ; j++) {
			if (j > N - i - 1) {
				goto EXIT;
			}
			else if (q[j + i] != r[j]) {
				goto EXIT;
			}
			else if (q[j + i] == r[j]) {
				count++;
			}
		}
	EXIT:
		if (count > longest_es) {
			longest_es = count;
		}
		/*if (count == N) {
			break;
		}*/
	}

	return longest_es;

}

int main_hrt(char* q, char* r, int N, int checkpoint) {
	int longest_es = 0;
	for (int i = checkpoint; i < N ; i++) {
		if (q[i] != r[i]) {
			return longest_es;
		}
		else if (q[i] == r[i]) {
			longest_es = longest_es + 1;
		}
		
	}
	return longest_es;
}
