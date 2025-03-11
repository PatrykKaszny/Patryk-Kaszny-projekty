#include "stdafx.h"
#include "InvokeAsm.h"

void InvokeGrayscaleAsm::grayscale(BYTE* _data, BYTE* _result, const BYTE limit) {
	if (int(*(_data)) >= limit) {
		*_result = 255 - *_data;
	}
	else {
		*_result = *_data;
	}
}



void InvokeGrayscaleAsm::grayscaleForNBytesUsingXCoresASM(BYTE* _begin, BYTE* _result, BYTE limit, const long n, const int numberOfCores) {
	long size = n / numberOfCores;
	int rest = n % numberOfCores;
	long firstSize = size + rest;
	vector<BYTE*> begins(numberOfCores);
	vector<BYTE*> results(numberOfCores);
	begins[0] = _begin;
	results[0] = _result;
	for (int i = 1; i < numberOfCores; i++)
	{
		if (i == 1) {
			begins[i] = _begin + firstSize;
			results[i] = _result + firstSize;
		}
		else {
			begins[i] = _begin + (i - 1) * size + firstSize;
			results[i] = _result + (i - 1) * size + firstSize;
		}
	}
	vector<thread> threads;
	for (int i = 0; i < numberOfCores; i++)
	{
		long localSize = size;
		if (i == 0) {
			localSize = firstSize;
		}
		threads.push_back(std::thread(&grayscaleAsm, begins[i], localSize, limit, results[i]));
	}
	for (int i = 0; i < numberOfCores; i++)
	{
		threads.at(i).join();
	}
}