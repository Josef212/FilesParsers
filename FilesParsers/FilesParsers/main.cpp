#include <iostream>

#include "JsonFile.h"
#include "BinaryFile.h"

using namespace std;

// ==============================================================

#pragma warning(disable  : 4996)

#define JSON_FILENAME "data.json"
#define BINARY_FILENAME "file.f"

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

int a[6] = { 0, 1, 2, 3, 4, 5 };
float b[4] = { .1f, .2f, .3f, .4f };


// ==============================================================

int ReadFile(const char* fileName, char** buffer);
bool WriteFile(const char* fileName, char* buffer, int bufferSize);

void JsonReadTest();
void JsonWriteTest();

void BinaryReadTest();
void BinaryWriteTest();

// ==============================================================

int main(int argc, char** argv)
{
	bool exit = false;

	while (!exit)
	{
		cout << "Files parsers tests." << endl;
		cout << "Select the prefered test: " << endl
			<< "\ta) Json read test (only if write test done before)" << endl
			<< "\tb) Json write test" << endl
			<< "\tc) Binary read test (only if write test done before)" << endl
			<< "\td) Binary write test" << endl
			<< "\tq) Exit" << endl << endl;

		string answer;
		cin >> answer;

		system("cls");

		if (answer == "a") JsonReadTest();
		else if (answer == "b") JsonWriteTest();
		else if (answer == "c") BinaryReadTest();
		else if (answer == "d") BinaryWriteTest();
		else if (answer == "q") exit = true;
		else cout << "Invalid option." << endl << endl;
			
		system("PAUSE");
	}
	
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

	//*buffer[size - 1] = '\0';

	return size + 1;
}

bool WriteFile(const char* fileName, char* buffer, int bufferSize)
{
	if (!fileName || !buffer || bufferSize <= 0) return false;

	FILE* f = fopen(fileName, "wb");
	if (!f) return false;

	fwrite(buffer, bufferSize, 1, f);
	fclose(f);

	return true;
}

// --------------------

void JsonReadTest()
{
	cout << "JSON read test ---------------------------" << endl;

	char* buf = nullptr;
	int size = ReadFile(JSON_FILENAME, &buf);

	if (size <= 0)
	{
		cout << "Error reading json file: " << JSON_FILENAME << endl;
		system("PAUSE");
		return;
	}

	JsonFile file(buf);
	
	cout << "tmp[0]: " << file.GetInt("tmp", -1, 0) << endl
		<< "tmp[1]: " << file.GetInt("tmp", -1, 1) << endl
		<< "tmp[2]: " << file.GetInt("tmp", -1, 2) << endl;

	cout << "k1: " << file.GetInt("k1", -1) << endl
		<< "k2: " << file.GetFloat("k2", -1.f) << endl
		<< "k3: " << file.GetString("k3", "juasjuas") << endl;

	for (int i = 0; i < file.GetArraySize("k4"); ++i)
		cout << "k4[" << i << "]: " << file.GetInt("k4", -1, i) << endl;

	for (int i = 0; i < file.GetArraySize("k5"); ++i)
		cout << "k5[" << i << "]: " << file.GetFloat("k5", -1.f, i) << endl;

	JsonFile file2 = file.GetSection("k6");

	cout << "k6-0: " << file2.GetInt("k6-0", -1) << endl;
	for (int i = 0; i < file2.GetArraySize("k6-1"); ++i)
		cout << "k6-1[" << i << "]: " << file2.GetInt("k6-1", -1, i) << endl;


	RELEASE_ARRAY(buf);
}

void JsonWriteTest()
{
	cout << "JSON write test ---------------------------" << endl;

	JsonFile file;

	file.AppendArrayValue("tmp", 1);
	file.AppendArrayValue("tmp", 2);
	file.AppendArrayValue("tmp", 3);

	file.AddInt("k1", 2);
	file.AddFloat("k2", 3.2);
	file.AddString("k3", "wuaaa");

	for (int i = 0; i < 6; ++i) file.AddArrayValue("k4", a[i], i);
	file.AddFloatArray("k5", b, 4);

	JsonFile file2;
	file2.AddInt("k6-0", 4);
	file2.AddIntArray("k6-1", a, 6);

	file.AddSection("k6", file2);

	auto buf = file.Write(true);

	if (!WriteFile(JSON_FILENAME, (char*)buf.c_str(), buf.size() + 1))
	{
		cout << "ERROR writing json file." << endl;
	}
}

void BinaryReadTest()
{
	cout << "BINARY read test ---------------------------" << endl;

	char* buf = nullptr;
	int size = ReadFile(BINARY_FILENAME, &buf);

	if (size <= 0)
	{
		cout << "Error reading binary file: " << BINARY_FILENAME << endl;
		system("PAUSE");
		return;
	}

	BinaryFile file(buf, size);



	RELEASE_ARRAY(buf);
}

void BinaryWriteTest()
{
	cout << "BINARY write test ---------------------------" << endl;


}