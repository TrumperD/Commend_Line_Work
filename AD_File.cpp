#include "AD_File.h"

void AD_File::setTime()
{
	time_t now = time(0);
	lastUpadateTime = localtime(&now);}
string AD_File::getTime() const
{
	char buf[80];
	strftime(buf, sizeof(buf), "%d/%m/%Y %X", lastUpadateTime);
	return buf;
}

AD_File::AD_File()
{
	FileName = nullptr;
	this->setTime();
}

AD_File::AD_File(string name)
{
	this->setFileName(name);
	this->setTime();
}

bool AD_File::operator==(const AD_File& F)const
{
	return(FileName == F.FileName);
}

AD_File::AD_File(const AD_File& other)
{
	*this= other;
}

const AD_File& AD_File::operator=(const AD_File& other)
{
	if (this != &other)
	{
		FileName = other.FileName;
		lastUpadateTime = other.lastUpadateTime;
	}
	return *this;
}


