#include "Entry.h"

namespace relentless {
	std::ostream & operator<<(std::ostream & stream, Entry & e)
	{
		stream << e.getTitle() << ": " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << e.getPrice() << " Euro";
		return stream;
	}

	bool operator==(Entry & e1, Entry & e2)
	{
		return (e1.getTitle() == e2.getTitle() && e1.getPrice() == e2.getPrice());
	}

	bool Entry::operator<(Entry e)
	{
		return Price < e.getPrice();
	}
}