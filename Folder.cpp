#include "Folder.h"

Folder* Folder::root = new Folder("root");


Folder::Folder(string name, string path) : AD_File(name)
{ 
	Path = path + "/" + name;
	Array = new AD_File*;
	Array = NULL;
	arryaSize = 0;
}

Folder::Folder():AD_File()
{
	
	Array = new AD_File*;
	Array = NULL;
	arryaSize = 0;
}

Folder::Folder(string name) :AD_File(name)
{
		
	    Array = new AD_File*;
		Array = NULL;
		arryaSize = 0;
}


Folder::Folder(const Folder& f) :AD_File(f)
{
	*this = f;
}

const Folder& Folder::operator=(const AD_File& other)
{
	if (this != &other)
	{
		AD_File::AD_File(other);
		Path = ((Folder*)&other)->getfullpath();
		for (int i = 0; i < arryaSize; i++)
			delete[] Array[i];
		delete [] Array;
		arryaSize = ((Folder*)&other)->getArraySize();
		Array = new AD_File*[arryaSize];
		for (int i = 0; i < arryaSize; i++)
		{
			Array[i] = new AD_File(*((Folder*)&other)->getArray()[i]);
		}
	}
	return *this;
}

Folder::Folder(Folder &f, string path):AD_File(this->FileName)
{
	if (this != &f)
	{
		Path = path;
		for (int i = 0; i < arryaSize; i++)
			delete[] Array[i];
		delete Array;
		arryaSize = f.arryaSize;
		Array = new AD_File*[arryaSize];
		for (int i = 0; i < arryaSize; i++)
			Array[i] = f.Array[i];
	}
}

void Folder::AddToArray(AD_File* f) throw(char*)
{
	DataFile *tmp= dynamic_cast<DataFile*>(f);
	if (tmp)
	{
		for (int i = 0; i < arryaSize; i++)
		{
			tmp = dynamic_cast<DataFile*>(Array[i]);
			if (Array[i]->getFileName() == f->getFileName() && tmp != NULL)throw ERROR;
		}
		Array = Realloc();
		Array[arryaSize]=f;
		arryaSize++;
		return;
	}
	Folder* tmp2 = dynamic_cast<Folder*>(f);
	if (tmp2)
	{
		for (int i = 0; i < arryaSize; i++)
		{
			tmp2 = dynamic_cast<Folder*>(Array[i]);
			if (Array[i]->getFileName()==f->getFileName()&&tmp2!=NULL)throw ERROR;
		}
		Array = Realloc();
		if (Path.size() == 0) ((Folder*)f)->Path = "root ";
		else ((Folder*)f)->Path = this->Path +'/'+ this->FileName;
		Array[arryaSize] =f;
		arryaSize++;
		return;
	}
	throw ERROR;
}

void Folder::mkfile(string name, string data)
{
	AD_File* add = new DataFile(name, data);
	try { AddToArray(add); }
	catch (const char* ex)
	{
		cout << ex << endl;
		delete add;
	}
}

void Folder::mkdir(string name)
{
	AD_File* add = new Folder(name);
	try { AddToArray(add); }
	catch (const char* ex)
	{
		cout << ex << endl;
		delete add;
	}
}

void Folder::dir()
{
	cout << "Files in directory " + getFileName()+":"<<endl;
	DataFile*tmpD;
	float siz, x;
	for (int i = 0; i < arryaSize; i++)
	{
		tmpD = dynamic_cast<DataFile*>(Array[i]);
		if (tmpD)
		{
			cout << getTime() + "\t\t";
			siz = (((DataFile*)Array[i])->getSize()+1);
			(siz<10)?x=0:x = siz / 1000;
			/*cout << fixed;*/
			cout << setprecision(2) << x; cout << " KB ";
			cout << Array[i]->getFileName()<<endl;
		}
		else
		{
			cout << getTime() + "  <DIR>\t\t" + Array[i]->getFileName()<<endl;
		}
	}
}

AD_File* Folder::FindAddres(string path,Folder& locatoin)
{
	/*Folder * end;*/
	AD_File* tmp = &locatoin;
	AD_File* check;
	int x = path.size() + 1, counter = 0;
	char str[50];
	while (counter != x)
	{
		check = tmp;
		for (int i = counter, j = 0; i < x; j++, i++)
		{
			if (path[i] == '\0')
			{
				str[j] = '\0';
				for (int i = 0; i < ((Folder*)tmp)->getArraySize(); i++)
				{
					if (str == ((Folder*)tmp)->Array[i]->getFileName())
					{
						return tmp = ((Folder*)tmp)->Array[i];
						/*return end = dynamic_cast<Folder*>(tmp);*/
					}
				}
			}
			if (path[i] != '/')
			{
				str[j] = path[i];
				counter++;
			}
			else
			{
				str[j] = '\0';
				for (int i = 0; i < ((Folder*)tmp)->getArraySize(); i++)
				{
					if (str == ((Folder*)tmp)->Array[i]->getFileName())
						tmp = ((Folder*)tmp)->Array[i];
					j = -1;
					str[0] = '\0';
				}
			}
		}
		if (check == tmp) throw ERROR;
		counter++;
	}
	throw ERROR;
	return NULL;
}

Folder* Folder::cd(string path)throw(char*)
{
	Folder * end;
	AD_File* tmp = root;
	AD_File* check;
	int x = path.size() + 1, counter = 0;
	char str[100];
	while (counter != x)
	{
		check = tmp;
		for (int i = counter,j=0; i < x;j++,i++)
		{
			if (path[i] == '\0')
			{
				str[j] = '\0';
				for (int i = 0; i < ((Folder*)tmp)->getArraySize(); i++)
				{
					if (str == ((Folder*)tmp)->Array[i]->getFileName())
					{
						tmp = ((Folder*)tmp)->Array[i];
						return end = dynamic_cast<Folder*>(tmp);
					}
				}				
			}
			if (path[i] != '/')
			{
				str[j] = path[i];
				counter++;
			}
			else
			{
				str[j] = '\0';
				for (int i = 0; i < ((Folder*)tmp)->getArraySize(); i++)
				{
					if (str == ((Folder*)tmp)->Array[i]->getFileName())
					{
						tmp = ((Folder*)tmp)->Array[i];
						j = -1;
						str[0] = '\0';
						continue;
					}
				}
			}
		}
		if (check == tmp) throw ERROR;
		counter++;
	}
	throw ERROR;
	return NULL;
}

AD_File** Folder::Realloc()
{
		AD_File** newFileArray = new AD_File*[arryaSize + 1];
		for (int i = 0; i < arryaSize; i++)
		{
			newFileArray[i] = Array[i];
		}
		Array = NULL;
		delete[] Array;
		return newFileArray;
}

bool Folder::operator==(const AD_File&other)const
{
	const Folder* p = dynamic_cast<const Folder*>(&other);
	if (p)
	{
		if (arryaSize != p->arryaSize) return false;
		for (int i = 0; i < arryaSize; i++)
		{
			if (Array[i]->getFileName() != p->Array[i]->getFileName())return false;
			Array[i]->operator==(*p->Array[i]);
		}
		return true;
	}	
	return false;
}

Folder::~Folder()
{
	
	for (int i = 0; i < arryaSize; i++)
	{
		delete Array[i];
	}
	delete[] Array;
}