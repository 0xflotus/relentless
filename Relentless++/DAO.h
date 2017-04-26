#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include "sqlite3.h"
#include "Entry.h"

namespace relentless {
	typedef std::string String;

	class DAO
	{
	public:
		static String quoted(String* str);

		DAO() : DAO("relentless.sqlite") {}
		DAO(const char* dbname);

		auto virtual insertEntry(Entry& e) -> void;
		auto virtual gibAlleAus(std::string query = "rowId") -> void;
		auto virtual filter(std::string sqlWhere) -> void;
		auto virtual tableToVector(std::vector<Entry>& v)->void;

	private:
		sqlite3* datenbank;
		char* fehlermeldung;
	};
}