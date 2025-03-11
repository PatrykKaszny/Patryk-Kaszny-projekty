#ifndef INVOKEASM_H
#define INVOKEASM_H

//#include <stdlib.h>
//#include <windows.h>

using namespace std;

class InvokeGrayscaleAsm {
public:
	static void grayscale(BYTE* _data, BYTE* _result, const BYTE limit);
	static void grayscaleForNBytesUsingXCoresASM(BYTE* _begin, BYTE* _result, BYTE limit, const long n, const int numberOfCores);
};


#endif 