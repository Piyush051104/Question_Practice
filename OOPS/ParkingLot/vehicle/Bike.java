package OOPS.ParkingLot.vehicle;

import OOPS.ParkingLot.enums.VehicleType;

public class Bike extends vehicle{
    public Bike(String licensePlate){
        super(licensePlate, VehicleType.BIKE);
    }
}
