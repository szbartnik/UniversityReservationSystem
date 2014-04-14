#pragma once

#include "ISerializable.h"
#include "Reservation.h"
#include "TAntiCollisionQueue.h"
#include <fstream>

class Reservation;

class IRoom : public ISerializable
{
public:
	string Name;
	string Type;
	int Capacity;
	TAntiCollisionQueue<Reservation> Reservations;

	IRoom(string _name, string _type, int _capacity)
	{
		Name = _name;
		Type = _type;
		Capacity = _capacity;
	}

	IRoom(string _name, string _type, int _capacity, int _id)
		: ISerializable(_id)
	{
		Name = _name;
		Type = _type;
		Capacity = _capacity;
	}

	static IRoom& Deserialize(ifstream& is, DataContext& context)
	{
		string stringBuffer;

		getline(is, stringBuffer);

		if (stringBuffer == "Exercise")
		{
			return ExerciseRoom::Deserialize(is, context);
		}
		else if (stringBuffer == "Lab")
		{
			return LabRoom::Deserialize(is, context);
		}
		throw "Blad typu pokoju";
	}

	virtual void Edit(IRoom roomToEdit)
	{
		this->Name = roomToEdit.Name;
		this->Capacity = roomToEdit.Capacity;
	}

	bool CheckCollisions(Reservation& reservation)
	{
		return Reservations.CheckCollisions(reservation);
	}

	void AddReservation(Reservation &reservationToAdd)
	{
		Reservations.Add(reservationToAdd);
	}

	void RemoveReservation(Reservation &reservationToRemove)
	{
		Reservations.Remove(reservationToRemove);
	}

	virtual void Serialize(ostream& os) const
	{
		os << Type << endl;
		ISerializable::Serialize(os);
		os << Name << endl
			<< Capacity << endl;
	}

	virtual ~IRoom();
};

IRoom::~IRoom() { }