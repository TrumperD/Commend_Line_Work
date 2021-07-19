#pragma once
#include "AD_File.h"
class DataFile :public AD_File
{
	string data;
public:
	DataFile(string f) :AD_File(f) { data=nullptr; }
	DataFile(string name, string d) :AD_File(name) { this->data = d; }
	string getData() { return data; }
	virtual bool operator==(const AD_File&)const;
	unsigned int getSize()const { return data.size();}
	virtual const DataFile& operator=(const AD_File&);
	DataFile(const DataFile&);
};

