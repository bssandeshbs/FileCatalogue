#ifndef DISPLAY_H
#define DISPLAY_H
/////////////////////////////////////////////////////////////////////
//  Display.h -  Functionailty to Format the Search Results        //
//				 and Display 									   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013, Update 2                       //
//  Platform:      ASUS TP300L, Windows 8.1						   //
//  Application:   File Catalogue Project		                   //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University //
//                 (315) 751-4826, sbellurs@syr.edu		           //
/////////////////////////////////////////////////////////////////////
/*
*
* Module Operations:
* ===================
* The purpose of this module is to display the File and Text search results
*
* Required Files:
* ===============
* DataStore.h, DataStore.cpp, FileManager.h, FileManager.cpp, FileSystem.h, FileSystem.cpp Display.h,
* Display.cpp
*
* Build Process:
* ==============
* cl /DTEST_DISPLAY /EHsc ../DataStore/DataStore.cpp ../FileSystem/FileSystem.cpp ../FileManager/FileManager.cpp
* ../Catalogue/Catalogue.cpp Display.cpp
*
* Public Interface:
* =================
* constructor () :  Display(DataStore& ds)
*			Input : DataStore& ds - data store object to display the file contents
* void printFileResults() : print file results to console
* void printTextSearch(const std::set<std::string>,int dirCount)
*			Input : const std::set<std::string> - list of files matching the input text
* void printDuplicateFiles(); - print duplicate file details
* void printCountResults(int fileCount, int direcCount,bool isDuplicate)
*			Input : file counter and directory counter
*			Input : is Duplicate, Indicate whether the count of duplicate files needs to be displayed
* Usage :
* ==================
* display dr(DataStore &ds);
* dr.printFileResults(true);
* dr.printTextSearch(c.getFileSet(), fm.dirCount());
* FileManager fm(ds, argc, argv);
* dr.printCountResults(fm.getFileCount(), fm.getDirCount(), false);
* Maintenance History:
* ====================
* ver 1.0 : 10 Feb 14
* - first release
*/
#include <iostream>
#include "../DataStore/DataStore.h"
#include "../Catalogue/Catalogue.h"
#include "../FileManager/FileManager.h"

class Display {
private:
	DataStore& store_;
	int duplicateCounter;
public:
	//----< constructor>-------------------
	Display(DataStore& ds) : store_(ds) {
	}
	void printFileResults(bool);
	void printTextSearch(const std::set<std::string>, int dirCount);
	void printDuplicateFiles();
	void printCountResults(int fileCounter, int dirCount, bool isDuplicate);
};
#endif