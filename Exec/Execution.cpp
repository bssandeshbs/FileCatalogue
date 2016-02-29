/////////////////////////////////////////////////////////////////////
//  Exceution.cpp - The first package that gets called             //
//					Oversees the control flow in the application   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013, Update 2                       //
//  Platform:      ASUS TP300L, Windows 8.1						   //
//  Application:   File Catalogue Project		                   //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University //
//                 (315) 751-4826, sbellurs@syr.edu		           //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "../FileManager/FileManager.h"
#include "../FileSystem/FileSystem.h"
#include "../Display/Display.h"
#include "../Catalogue/Catalogue.h"
#include "../DataStore/DataStore.h"

#ifdef TEST_EXECUTION

//----< First entry point to the applcation which contains user inputs >-----------------------------------
int main(int argc, char* argv[])
{
	try {
		DataStore ds;
		FileManager fm(ds, argc, argv);
		fm.processInput();
		fm.search();
		Catalogue c(ds);
		Display dr(ds);
		if (argc < 2)
		{
			dr.printCountResults(ds.getFileCounter(), 1, false);
		}
		else {
			dr.printFileResults(false);
			dr.printCountResults(ds.getFileCounter(), fm.getDirCount(), false);
			bool is_dir = std::find(fm.optionBegin(), fm.optionEnd(), "/d") != fm.optionEnd();
			if (is_dir) { //If the option starts with /d
				dr.printFileResults(true);
				dr.printCountResults(ds.getFileCounter(), fm.getDirCount(), true);
			}
			Catalogue c(ds); 
			if (std::find(fm.optionBegin(), fm.optionEnd(), "/f") != fm.optionEnd()) {
				if (fm.getSearchString() != "") { //If the option starts with /f and no search string
					c.searchCatalog(fm.getSearchString());
					dr.printTextSearch(c.getFileSet(), fm.getDirCount());
				}
			}
		}
		std::string inputString = "";
		std::cout << "\nEnter the Text to Search \n";
		while (std::getline(std::cin, inputString)) // loop untill Enter button is pressed
		{
			if (inputString.size() == 0) {
				exit(0);
			}
			else
			{
				c.processTextInput(inputString);
				dr.printTextSearch(c.getFileSet(), fm.getDirCount());
			}
			std::cout << "Please provide the Search text or Press Enter to Exit\n";
		}
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;
}

#endif