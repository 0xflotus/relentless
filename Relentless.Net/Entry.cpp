#include "Entry.h"

Entry::Entry(System::String ^ title, float price)
{
	Title = title;
	Price = price;
	Link = "http://exmaple.org";
	Timestamp = 0;
}

System::String^ Entry::ToString()
{
	return Title + ": " + Price.ToString("0.00");
}
