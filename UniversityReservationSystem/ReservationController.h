#pragma once

#include "IController.h"
#include "Reservation.h"
#include "DataContext.h"

class ReservationController : public IController<Reservation>
{
public:
	ReservationController(DataContext & _context)
		: IController(_context) { }

	bool Add(Reservation& toAdd)
	{
		if (toAdd.BoundGroups .CheckCollisions(toAdd)) return false;
		if (toAdd.BoundTeacher.CheckCollisions(toAdd)) return false;
		if (toAdd.Room        .CheckCollisions(toAdd)) return false;

		toAdd.BoundGroups .AddReservation(toAdd);
		toAdd.BoundTeacher.AddReservation(toAdd);
		toAdd.Room        .AddReservation(toAdd);

		Context.Reservations.Add(toAdd, true);
		return true;
	}

	bool Edit(Reservation& toEdit)
	{
		return true;
	}
	
	bool Delete(Reservation& toDelete)
	{
		toDelete.BoundTeacher.Reservations.Remove(toDelete);
		return false;
	}
};