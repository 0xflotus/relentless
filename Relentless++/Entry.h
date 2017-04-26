#pragma once

#include <string>
#include <iostream>
#include <iomanip>

namespace relentless {
	class Entry final
	{
		std::string Title, Link;
		float Price;
		int Timestamp;
		long Id;

	public:
		Entry(std::string title, float price, std::string link = "http://example.org", int timestamp = 0) :
			Title(title), Price(price), Link(link), Timestamp(timestamp) {}

		auto getTitle() const -> std::string { return Title; }
		auto getPrice() const -> float { return Price; }
		auto getTimestamp() const -> int { return Timestamp; }
		auto getLink() const -> std::string { return Link; }

		auto getId() const -> long { return Id; }
		auto setId(long id) -> void { Id = id; }

		auto getAllLength() const -> int { return Title.length() + std::to_string(Price).length(); }

		auto operator<(Entry e) -> bool;
	};

	auto operator<<(std::ostream& stream, Entry& e)->std::ostream&;
	auto operator==(const Entry& e1, const Entry& e2) -> bool;
}