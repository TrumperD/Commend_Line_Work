#include "DataFile.h"

bool DataFile::operator==(const AD_File& File)const 
{
	const DataFile *temp = dynamic_cast<const DataFile*>(&File);
	if (temp) return(AD_File::operator==(File) && this->data == temp->data);//לבדוקהאם צריך לעשות שונה עם טמפ
	else  return 0;
}

DataFile::DataFile(const DataFile& d):AD_File(d)
{
	*this = d;
}

const DataFile& DataFile::operator=(const AD_File& other)
{
	if (this != &other)
	{
		AD_File::AD_File(other);
		data = ((DataFile*)&other)->getData();
	}
	return *this;
}



