package OOPS.ParkingLot.vehicle;

import OOPS.ParkingLot.enums.VehicleType;

public class Truck extends vehicle{
    public Truck(String licensePlate){
        super(licensePlate, VehicleType.TRUCK);
    }
}
