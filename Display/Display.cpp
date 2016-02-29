/////////////////////////////////////////////////////////////////////
//  Display.cpp -  Functionailty to Format the File & Text Search  //
//				 Results and Display in command prompt			   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013, Update 2                       //
//  Platform:      ASUS TP300L, Windows 8.1						   //
//  Application:   File Catalogue Project		                   //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University //
//                 (315) 751-4826, sbellurs@syr.edu		           //
/////////////////////////////////////////////////////////////////////
#include "Display.h"

//----< Display catalogue >------------------------------------------
void Display::printFileResults(bool isDuplicateFiles) {
	DataStore::iterator iter = store_.begin();
	using pathref = DataStore::pathIterator;
	duplicateCounter = 0;

	if (isDuplicateFiles) {
		std::cout << "==================================================================\n";
		std::cout << "\t\tDUPLICATE FILES \n";
		std::cout << "==================================================================\n";
		std::cout << "\n File name " << "\t\t" << "Path\n";
		std::cout << "------------------------------------------------------------------\n";
	}
	else{
		std::cout << "===================================================================\n";
		std::cout << "\t\tCATALOGUE\n";
		std::cout << "===================================================================\n";
		std::cout << "\n File name " << "\t\t" << "Path\n";
		std::cout << "-------------------------------------------------------------------\n";
	}

	for (iter = store_.begin(); iter != store_.end(); iter++)
	{
		std::list<pathref> itss = iter->second;
		std::list<pathref>::iterator itssr;
		if (!isDuplicateFiles) {
			std::cout << iter->first << "\n";
		}
		else if (isDuplicateFiles && itss.size() > 1) {
			std::cout << iter->first << "\n";
		}

		if (!isDuplicateFiles) {
			for (itssr = itss.begin(); itssr != itss.end(); itssr++)
			{
				std::cout << "\t\t\t" << (*(*itssr)) << "\n";
			}
		}
		else {
			for (itssr = itss.begin(); itssr != itss.end(); itssr++)
			{
				if (itss.size() > 1)
				{
					duplicateCounter++;
					std::cout << "\t\t\t" << (*(*itssr)) << "\n";
				}
			}
		}
	}
}

//----< Display text search results>------------------------------------------
void Display::printTextSearch(const std::set<std::string> inputSet, int dirCount) {

	bool searchTextExists = false;
	std::string prevFile = "";
	for (auto element : inputSet) {
		unsigned found = element.find_last_of("/\\");
		std::string path = element.substr(0, found);
		std::string file = element.substr(found + 1);
		if (prevFile != file) {
			if (!searchTextExists) {
				std::cout << "==================================================================\n";
				std::cout << "\t\t TEXT SEARCH RESULTS\n";
				std::cout << "==================================================================\n";
				std::cout << "\n File name " << "\t\t\t" << "Path\n";
				std::cout << "------------------------------------------------------------------\n";
				searchTextExists = true;
			}
			std::cout << file << "\n";
			std::cout << "\t\t\t" << path << "\n";
			prevFile = file;
		}
		else {
			std::cout << "\t\t\t" << path << "\n";
		}
	}

	if (!searchTextExists) {
		std::cout << "\n \n No items matches your search \n \n";
	}
	else {
		std::cout << "\n\n\t" << inputSet.size() <<
			" files found in " << dirCount << " directories" << "\n\n";
	}
	std::cout << "\n";
}

//----< display count of file and directories >------------------------------------------
void Display::printCountResults(int fileCount, int direcCount, bool isDuplicate) {
	if (isDuplicate) fileCount = duplicateCounter;
	std::cout << "\n\n\t" << fileCount <<
		" files found in " << direcCount << " directories" << "\n\n";
}

#ifdef TEST_DISPLAY
int main() {
	DataStore ds;

	int argc = 4;
	char* argv[] = { "C://filename.cpp", "/s", "*.cpp", "*.h" };

	FileManager fm(ds, argc, argv);
	fm.processInput();
	fm.search();

	DataStore::iterator iter = ds.begin();
	using pathref = DataStore::pathIterator;

	Display d(ds);
	d.printFileResults(false);

	Catalogue c(ds);
	c.processTextInput("include");
	std::cout << "\n";
	d.printTextSearch(c.getFileSet(), fm.getDirCount());
}
#endif
