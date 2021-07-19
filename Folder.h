#pragma once
#include "AD_File.h"
#include  "DataFile.h"
class Folder : public AD_File
{
	AD_File** Array;
	unsigned int arryaSize;
	string Path;
	
public:
	static Folder* root;
	Folder();
	Folder(string name, string path);
	Folder(string name);
	string getfullpath() { return Path;}
	unsigned int getArraySize() { return arryaSize; }
	AD_File** getArray() { return Array; }
	void AddToArray(AD_File *Ftoadd)throw(char*);
	AD_File** Realloc();
	Folder(Folder &f, string);
	virtual const Folder& operator=(const AD_File&);
	virtual bool operator==(const AD_File&)const;
	void mkfile(string name, string data);
	void mkdir(string name);
	Folder(const Folder&);
	void dir();
	AD_File* FindAddres(string,Folder&);
	static Folder* cd(string);
    friend bool FC(Folder&, string, string);
	virtual ~Folder();
};


