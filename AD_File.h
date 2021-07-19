#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define ERROR "code inconsistency"
#include <string>
#include<iostream>
#include <ctime>
#include <iomanip>

using namespace::std;

class AD_File
{
protected:
	string FileName;
	tm* lastUpadateTime;

public:

	AD_File();
	AD_File(string);
	AD_File(const AD_File&);
	string getFileName() { return FileName; }
	void setFileName(string F_name) { FileName = F_name; }
	string getTime()const;
	void setTime();
	virtual bool operator==(const AD_File&)const;
    virtual const AD_File& operator=(const AD_File&);
	virtual ~AD_File() {};
};

