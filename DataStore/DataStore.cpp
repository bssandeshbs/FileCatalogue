//////////////////////////////////////////////////////////////////////////
//  DataStore.cpp - Contains the Container to Store File Search Results //
//  ver 1.0                                                             //
//  Language:      Visual C++ 2013, Update 2                            //
//  Platform:      ASUS TP300L, Windows 8.1						        //
//  Application:   File Catalogue Project		                        //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University      //
//                 (315) 751-4826, sbellurs@syr.edu		                //
//////////////////////////////////////////////////////////////////////////
#include "DataStore.h"
#include <vector>

//----< stores the file path and name >------------------------------------
void DataStore::save(const std::string &absfilename) {

	unsigned found = absfilename.find_last_of("/\\");
	std::string  fpath = absfilename.substr(0, found);
	std::string  fname = absfilename.substr(found + 1);
	bool is_in = pathSet.find(fpath) != pathSet.end();
	//If path is not present, inside into pathSet
	if (!is_in)
		pathSet.insert(fpath);

	for (pathReference = pathSet.begin(); pathReference != pathSet.end(); ++pathReference)
	{
		//If the input file path is present in set
		if (*pathReference == fpath)
		{
			// find if the filename is already present. If not, insert as a new key with filename to map
			bool is_in = filemap.find(fname) != filemap.end();
			if (!is_in)
			{
				fileCounter++;
				std::list<pathIterator> pRef;
				pRef.push_back(pathReference);
				filemap.insert(make_pair(fname, pRef));
			}
			else
			{
				// Retrieve the Iterator list and add the path reference to the list and update map			
				std::list<pathIterator> pRefList = filemap.at(fname);
				bool found = (std::find(pRefList.begin(), pRefList.end(), pathReference) != pRefList.end());
				if (!found)
				{
					fileCounter++;
					pRefList.push_back(pathReference);
					filemap[fname] = pRefList;
				}
			}
		}
	}
}

//----< returns the file counter>------------------------------------
int DataStore::getFileCounter() {
	return fileCounter;
}

std::vector<std::string> DataStore::getDataStore() {
	DataStore::iterator iter = begin();
	using pathref = DataStore::pathIterator;
	std::cout << "\n FILE NAME \t\t PATH \n";
	std::cout << "---------------------------------------\n\n";
	std::vector<std::string> data;
	for (iter = begin(); iter != end(); iter++)
	{
		std::string fileName = iter->first;
		std::cout << iter->first << "\n";
		std::list<pathref> itss = iter->second;
		std::list<pathref>::iterator itssr;
		for (itssr = itss.begin(); itssr != itss.end(); itssr++)
		{
			std::cout << "\t\t\t" << (*(*itssr)) << "\n";
			std::string res = (*(*itssr)) + "/" + fileName;
			data.push_back(res);
		}
	}
	return data;
}


#ifdef TEST_DATASTORE
int main() {
	DataStore ds;
	ds.save("C://system/projects/filesystem.cpp");
	ds.save("C://system/projects/filesystem.h");
	ds.save("c://system/projects/ood/catalogue.h");
	ds.save("c://system/projects/ood/catalogue.cpp");
	ds.save("c://system/projects/ood/system/filemanager.h");
	ds.save("c://system/projects/ood/system/filemanager.cpp");
	ds.save("C://system/projects/test/filesystem.h");

	ds.getDataStore();

	std::cout << "\n\n";
}
#endif
