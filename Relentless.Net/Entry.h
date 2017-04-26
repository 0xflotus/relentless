#pragma once

ref class Entry
{
	System::String^ link;
	int timestamp;
public:
	property System::String^ Title;
	property System::String^ Link { void set(System::String^ s) { link = s; } }
	property float Price;
	property int Timestamp { void set(int i) { timestamp = i; } }

	Entry(System::String^ title, float price);

	auto ToString()->System::String^ override;
};

