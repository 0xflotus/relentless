#include <iostream>
#include <string>
#include <chrono>
#include "sqlite3.h"
#include "Entry.h"
#include "DAO.h"
#include "tinyxml2.h"

using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::vector;

using namespace relentless;

auto newEntry(DAO* d) -> void;
auto sortierteAusgabe(DAO* d) -> void;
auto vec(DAO* d) -> void;
auto sortVec(DAO* d) -> void;
auto sortAlphabetically(DAO* d) -> void;
auto sortLength(DAO* d) -> void;
auto saveXML(DAO* d) -> void;
auto wrapAngebotDatabase(DAO* d) -> void;
auto wrapAngebot() -> void;
auto search(DAO* d) -> void;

auto help() -> void;
auto filter(vector<Entry> &v, float f) -> void;
auto filter(vector<Entry> &v, char c) -> void;
auto loadXML()->vector<Entry>;

inline auto gibVectorAus(vector<Entry>& v) -> void { for (auto it = v.begin(); it != v.end(); cout << *it << endl, it++); }
inline auto sortLen(Entry& e1, Entry& e2) -> bool { return e1.getAllLength() < e2.getAllLength(); }
inline auto to_Upper(char c) -> char { return (char)(c >= 'a' && c <= 'z' ? c - 32 : c); }
inline auto eingabe(std::string& speicher, std::string&& phrase)->void { cout << phrase; std::getline(std::cin, speicher); }

inline auto wrapLoadXML(DAO* d) -> void { gibVectorAus(loadXML()); };
inline auto wrapAlleAusgeben(DAO* d) -> void { d->gibAlleAus(); }

string exitString = "exit";

int main() {
	DAO *dao{ new DAO };
	string *cmd{ new string };
	do {
		cout << "Was willst du tun?" << endl;
		help();
		cout << ">># ";
		std::getline(std::cin, *cmd);
		if (*cmd == exitString) break;
		[&](string& s) {for (size_t i = 0; i < s.length(); i++) s[i] += s[i] >= 'A' && s[i] <= 'Z' ? 32 : 0; }(*cmd);
		void(*fptr)(DAO*) { 0 };
		void(*fpt)() { 0 };
		switch ((*cmd)[0]) {
		case 'a': fptr = newEntry; break;// neuer Eintrag in die Datenbank
		case 'b': fptr = wrapAlleAusgeben; break;
		case 'c': fptr = sortierteAusgabe; break;
		case 'd': fptr = vec; break;
		case 'e':
		{
			string input;
			eingabe(input, "Wonach soll sortiert werden? Preis, Laenge oder Alphabet (P/L/A):");
			fptr = to_Upper(input[0]) == 'P' ? sortVec : to_Upper(input[0]) == 'L' ? sortLength : sortAlphabetically;
			break;
		}
		case 'f': fptr = search; break;
		case 'g': fptr = saveXML; break;
		case 'h': fptr = wrapLoadXML; break;
		case 'i':
		{
			string input;
			eingabe(input, "Wo soll gefiltert werden? XML oder DB (X/D):");
			to_Upper(input[0]) == 'X' ? fpt = wrapAngebot, 0 : fptr = wrapAngebotDatabase, 0;
			break;
		}
		default: cout << (*cmd == exitString ? "" : "Tut mir leid. Diesen Befehl kenne ich nicht. "); continue;
		}
		fptr ? fptr(dao) : fpt();
		cout << endl;
	} while (true);

	delete dao;
	delete cmd;
	dao = nullptr;
	cmd = nullptr;
	return 0;
}

void newEntry(DAO * d)
{
	char in{ 'j' };
	while (in != 'n') {
		string title, link, price, buffer;
		eingabe(title, "Bitte gib den Titel ein: ");
		eingabe(price, "Bitte gib den Preis ein: ");
		try
		{
			Entry entry(title, std::stof(price));
			cout << entry << endl;
			d->insertEntry(entry);
		}
		catch (exception ex)
		{
			cout << "Fehler. Bitte versuch es erneut." << endl;
			continue;
		}
		eingabe(buffer, "Weiterer Datensatz? (j/n): ");
		in = buffer[0];
	}
}

void help()
{
	string str[] = {
		"a) - neuer Eintrag in die Datenbank",
		"b) - alle Eintraege aus der Datenbank ausgeben",
		"c) - sortierte Ausgabe der Datenbank",
		"d) - alle Eintraege als Vector ausgeben",
		"e) - alle Eintraege als Vector, sortiert ausgeben",
		"f) - Nach einem Eintrag anhand des Titels in der Datenbank suchen",
		"g) - in XML speichern",
		"h) - aus XML laden",
		"i) - Suchergebnisse eingrenzen",
	};
	for (auto &s : str) { cout << s << endl; }
}

void sortierteAusgabe(DAO * d)
{
	string input;
	eingabe(input, "1 - id\n2 - Titel\n3 - Preis\n\n");
	switch (input[0])
	{
	case '1': d->gibAlleAus(); break;
	case '2': d->gibAlleAus("title"); break;
	case '3': d->gibAlleAus("price"); break;
	default: cout << "Diese Moeglichkeit gibt es nicht." << endl;
	}
}

void vec(DAO* d)
{
	vector<Entry> vector;
	d->tableToVector(vector);
	gibVectorAus(vector);
}

void sortVec(DAO * d)
{
	vector<Entry> vec;
	d->tableToVector(vec);
	std::sort(vec.begin(), vec.end(), [&](Entry e1, Entry e2) { return e1.getPrice() < e2.getPrice(); });
	gibVectorAus(vec);
}

void sortAlphabetically(DAO * d)
{
	vector<Entry> vec;
	d->tableToVector(vec);
	std::sort(vec.begin(), vec.end(), [&](Entry e1, Entry e2) { return e1.getTitle() < e2.getTitle(); });
	gibVectorAus(vec);
}

void sortLength(DAO * d)
{
	vector<Entry> vec;
	d->tableToVector(vec);
	std::sort(vec.begin(), vec.end(), &sortLen);
	gibVectorAus(vec);
}

void saveXML(DAO * d)
{
	namespace tx = tinyxml2;
	tx::XMLDocument* doc{ new tx::XMLDocument };
	tx::XMLNode* pRoot = doc->NewElement("entries");
	doc->InsertFirstChild(pRoot);
	vector<Entry> vec;
	d->tableToVector(vec);
	for (const auto & e : vec)
	{
		tx::XMLElement* elem = doc->NewElement("entry");
		elem->SetAttribute("id", e.getId());
		tx::XMLElement* title = doc->NewElement("title");
		title->SetText(e.getTitle().c_str());
		tx::XMLElement* price = doc->NewElement("price");
		price->SetText(e.getPrice());
		elem->InsertEndChild(title);
		elem->InsertEndChild(price);
		pRoot->InsertEndChild(elem);
	}
	string filename = "output.xml";
	tx::XMLError err = doc->SaveFile(filename.c_str());
	delete doc;
	doc = nullptr;
	cout << (err == tx::XMLError::XML_SUCCESS ? filename + " wurde erfolgreich erstellt." : "Es gab Fehler beim Erstellen der XML-Datei.") << endl;
}

void wrapAngebotDatabase(DAO * d)
{
	string input;
	eingabe(input, "Wonach soll gefiltert werden? Titel oder Preis? (T/P):");
	char cTemp = input[0];
	cout << "Filter: ";
	std::getline(std::cin, input);
	d->filter(to_Upper(cTemp) == 'T' ? "title LIKE '" + input + "%';" : "price < " + input + ";");
}

void filter(vector<Entry> &v, float grenze)
{
	v.erase(std::remove_if(v.begin(), v.end(), [&](Entry e) {return e.getPrice() > grenze; }), v.end());
	std::sort(v.begin(), v.end(), [=](const Entry& e1, const Entry& e2) {return e1.getPrice() < e2.getPrice(); });
}

void filter(vector<Entry> &v, char character)
{
	v.erase(std::remove_if(v.begin(), v.end(), [&](Entry e) {return to_Upper(e.getTitle()[0]) != character; }), v.end());
	std::sort(v.begin(), v.end(), [=](const Entry& e1, const Entry& e2) {return e1.getTitle() < e2.getTitle(); });
}

vector<Entry> loadXML()
{
	tinyxml2::XMLDocument doc;
	vector<Entry> vec;
	if (!doc.LoadFile("output.xml") == tinyxml2::XMLError::XML_SUCCESS) { cout << "Fehler beim XML laden." << endl; }
	else
	{
		try {
			tinyxml2::XMLNode* pRoot = doc.FirstChild();
			if (pRoot == nullptr) { cout << "kein Rootelement gefunden." << endl; }
			tinyxml2::XMLElement* elem = pRoot->FirstChildElement("entry");
			while (elem != nullptr)
			{
				Entry e(elem->FirstChildElement("title")->GetText(),
					std::stof(elem->FirstChildElement("price")->GetText()));
				vec.push_back(e);
				elem = elem->NextSiblingElement("entry");
			}
		}
		catch (exception ex) { cout << "Fehler beim XML einlesen." << endl; }
	}
	return vec;
}

void wrapAngebot()
{
	string filt;
	eingabe(filt, "Gib den Filter ein (Zeichen oder Zahl, help fuer Hilfe): ");
	while (filt == "help") 
	{
		cout << "Wenn du eine Zahl eingibst, die einstellig ist, wirst du gefragt, ob du nach Preis oder Name filtern willst.\n"
			"Gibst du eine Zeichenkette ein, wird nach dem Anfangsbuchstaben gefiltert.\n"
			"Gibst du eine Zahl ein, so wird diese Zahl als Obergrenze interpretiert und alle Eintraege, deren Preis \n"
			"kleiner als die Obergrenze ist, werden dir angezeigt." << endl;
		eingabe(filt, "Gib den Filter ein (Zeichen oder Zahl, help fuer Hilfe): ");
	}
	vector<Entry> v = loadXML();
	try {
		float fTemp = std::stof(filt);
		if (std::to_string((int)fTemp).length() < 2) {
			string sTemp;
			eingabe(sTemp, "Nach Preis oder Name filtern? (p/n): ");
			to_Upper(sTemp[0]) == 'P' ? filter(v, fTemp) : filter(v, to_Upper(filt[0]));
		}
		else { filter(v, fTemp); }
	}
	catch (exception ex) { filter(v, to_Upper(filt[0])); }
	if (v.size() < 1) cout << "Keine Ergebnisse gefunden" << endl;
	gibVectorAus(v);
}

void search(DAO * d)
{
	string input;
	eingabe(input, "Wonach suchen Sie?: ");
	d->filter("title LIKE '%" + input + "%';");
}
