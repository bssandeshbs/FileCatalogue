#ifndef DATASTORE_H
#define DATASTORE_H

//////////////////////////////////////////////////////////////////////////////////
//  DataStore.h - Creates the DataStore Container to Store File Search Results  //
//  ver 1.0																		//
//  Language:      Visual C++ 2013, Update 2									//
//  Platform:      ASUS TP300L, Windows 8.1										//
//  Application:   File Catalogue Project										//
//  Author:        Sandesh Bellur Shashidhara, Syracuse University				//
//                 (315) 751-4826, sbellurs@syr.edu								//
//////////////////////////////////////////////////////////////////////////////////
/*
*
* Package Operations:
* ===================
* This Class contains a save method. It creates a datastore by taking absolute file name
* along with path as input and then storing the path to set and filename to a map as key
* and also list of path reference as value.
*
* Required Files:
* ===============
* DataStore.h, DataStore.cpp
*
* Build Process:
* ==============
* cl /DTEST_DATASTORE DataStore.cpp
*
* Public Interface:
* =================
* save() :  Builds the datastore container by storing file name and path which
*			are passed from the file system
*			Input : std::string &absfilename - Contains the absolute path along with path
* pathIterator = std::set<std::string>::iterator;
* pathIterator pathReference; - Iterator for path set
* fmap = std::map < std::string, std::list<pathIterator> >;
* iterator = fmap::iterator; - Iterator to map which stores file and list of path reference
* int getFileCounter() - returns the count of files in data store
* Maintenance History:
* ====================
* ver 1.0 : 10 Feb 14
* - first release
*/

#include<iostream>
#include<set>
#include<map>
#include<string>
#include <vector>
#include<list>

class DataStore {

public:
	using path = std::set < std::string > ;
	using pathIterator = std::set<std::string>::iterator;
	pathIterator pathReference;
	int getFileCounter();
	std::vector<std::string> getDataStore();;
	void save(const std::string &absfilename);
	using fmap = std::map < std::string, std::list<pathIterator> > ;
	using iterator = fmap::iterator;

	//----< returns Iterator pointing to first element of the map>-------------------
	inline iterator DataStore::begin() {
		return filemap.begin();
	}

	//----< returns Iterator pointing to last element of the map>--------------------
	inline iterator DataStore::end() {
		return filemap.end();
	}

	

private:
	fmap filemap;
	path pathSet;
	int fileCounter;
};
#endif