#include <iostream>

using namespace std;

// ==============================================================

#define FILENAME "data.json"

#define RELEASE( x )\
	{\
		if(x != nullptr)\
		{\
			delete x;\
			x = nullptr;\
		}\
	}

#define RELEASE_ARRAY( x )\
	{\
		if(x != nullptr)\
		{\
			delete[] x;\
			x = nullptr;\
		}\
	}

// ==============================================================

int ReadFile(const char* fileName, char** buffer);

// ==============================================================

int main(int argc, char** argv)
{
	cout << "Hello world" << endl;

	system("PAUSE");
	return 0;
}

// ==============================================================

int ReadFile(const char* fileName, char** buffer)
{
	if (!fileName) return -1;

	FILE* f = fopen(fileName, "rb");
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);

	*buffer = new char[size + 1];
	fread(*buffer, size, 1, f);
	fclose(f);

	*buffer[size] = 0;

	return size + 1;
}