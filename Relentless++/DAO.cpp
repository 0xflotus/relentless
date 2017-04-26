#include "DAO.h"

namespace relentless {

	DAO::DAO(const char * db)
	{
		try { sqlite3_open(db, &datenbank); }
		catch (std::exception e) { std::cout << e.what() << std::endl; }
	}

	void DAO::insertEntry(Entry& e)
	{
		//SQL-String zum einfuegen in die Datenbank
		std::string sql = "INSERT INTO entries (title,price,timestamp) VALUES ("
			+ quoted(&e.getTitle()) + ", "
			+ std::to_string(e.getPrice()) + ", "
			+ std::to_string(e.getTimestamp()) + ");";
		if (sqlite3_exec(datenbank, sql.c_str(), 0, 0, &fehlermeldung)) { std::cout << "Fehler: " << fehlermeldung << std::endl; }
	}


	void DAO::gibAlleAus(std::string query)
	{
		char** ergebnisse = NULL;
		int zeilen, spalten;

		try {
			std::string sql = "SELECT rowId AS 'Nr.', title AS 'Titel', price AS 'Preis' FROM entries ORDER BY " + query;
			if (sqlite3_get_table(datenbank, sql.c_str(), &ergebnisse, &zeilen, &spalten, &fehlermeldung))
			{
				std::cout << "Fehler: " << fehlermeldung << std::endl;
			}
			else {
				for (int zeile = 0; zeile <= zeilen; zeile++)
				{
					for (int spalte = 0; spalte < spalten; spalte++)
					{
						int zelle = (zeile * spalten) + spalte;
						std::cout.width(30);
						std::cout.setf(std::ios::left);
						std::cout << *(ergebnisse + zelle);
					}
					std::cout << std::endl;
				}
			}
			sqlite3_free_table(ergebnisse);
		}
		catch (std::exception ex) { std::cout << ex.what() << std::endl; exit(-1); }
	}

	void DAO::filter(std::string sqlWhere)
	{
		auto start = std::chrono::system_clock::now().time_since_epoch().count();

		char** ergebnisse = NULL;
		int zeilen, spalten;

		try {
			std::string sql = "SELECT rowId AS 'Nr.', title AS 'Titel', price AS 'Preis' FROM entries WHERE " + sqlWhere;
			if (sqlite3_get_table(datenbank, sql.c_str(), &ergebnisse, &zeilen, &spalten, &fehlermeldung))
			{
				std::cout << "Fehler: " << fehlermeldung << std::endl;
			}
			else {
				for (int zeile = 0; zeile <= zeilen; zeile++)
				{
					for (int spalte = 0; spalte < spalten; spalte++)
					{
						int zelle = (zeile * spalten) + spalte;
						std::cout.width(30);
						std::cout.setf(std::ios::left);
						std::cout << *(ergebnisse + zelle);
					}
					std::cout << std::endl;
				}
			}
			sqlite3_free_table(ergebnisse);
			std::cout << "\n" << zeilen << " Ergebnis" << (zeilen != 1 ? "se" : "") << std::endl;
			auto end = std::chrono::system_clock::now().time_since_epoch().count();
			printf("\nDie Anfrage dauerte %3.2f Millisekunden", ((double)(end - start) / 1000000));
		}
		catch (std::exception ex) { std::cout << ex.what() << std::endl; exit(-1); }
	}

	void DAO::tableToVector(std::vector<Entry>& v)
	{
		char** ergebnisse = NULL;
		int zeilen, spalten;

		try {
			std::string sql = "SELECT rowId, title AS 'Titel', price AS 'Preis' FROM entries ORDER BY rowId";
			if (sqlite3_get_table(datenbank, sql.c_str(), &ergebnisse, &zeilen, &spalten, &fehlermeldung))
			{
				std::cout << "Fehler: " << fehlermeldung << std::endl;
			}
			else {
				for (int zeile = 1; zeile <= zeilen; zeile++)
				{
					for (int spalte = 0; spalte < spalten; spalte += 3)
					{
						int zelle = (zeile *spalten) + spalte;
						Entry e(*(ergebnisse + zelle + 1), std::stof(*(ergebnisse + zelle + 2)));
						e.setId(std::stol(*(ergebnisse + zelle)));
						v.push_back(e);
					}
				}
			}
			sqlite3_free_table(ergebnisse);
		}
		catch (std::exception ex) { std::cout << ex.what() << std::endl; exit(-2); }
	}

	String DAO::quoted(String * str)
	{
		return "'" + *str + "'";
	}
}