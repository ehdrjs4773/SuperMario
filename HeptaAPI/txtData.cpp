#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{

}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{

}


//Save
void txtData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;

	string str;
	DWORD write;

	str = vectorArrayCombine(vStr);
	//strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//strlen 등 문자열 길이 함수를 쓰면 먹통된다
	WriteFile(file, str.c_str(), strlen(str.c_str()), &write, NULL);

	CloseHandle(file);
}

string txtData::vectorArrayCombine(vector<string> vArray)			
{
	//버퍼를 정해두지 말고, 속성이 들어오면 속성이 들어온만큼
	//잡을 수 있게 고쳐봅시다 ^_^*

	//버퍼는 우선 128로 한다. 나중에 늘여도 무관
	string str;

	//X Axis, Y Axis, CurrentHP, MaxHP
	//100, 100, 100, 100
	for (int i = 0; i < vArray.size(); i++)
	{
		str += vArray[i].c_str();
		//strncat_s(str, 128, vArray[i].c_str(), 126);
		//
		if (i + 1 < vArray.size()) str += ","; // strcat(str, ",");
	}

	return str;
}


//Load
vector<string> txtData::txtLoad(const char* loadFileName)	 
{
	HANDLE file;
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	char* str = new char [GetFileSize(file, NULL) + 1];
	ZeroMemory(str, sizeof(str));

	ReadFile(file, str, GetFileSize(file, NULL) + 1, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	delete [] charArray;

	return vArray;
}
