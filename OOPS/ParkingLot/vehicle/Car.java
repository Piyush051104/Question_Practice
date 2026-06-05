package OOPS.ParkingLot.vehicle;

import OOPS.ParkingLot.enums.VehicleType;

public class Car extends vehicle{
    public Car(String licensePlate){
        super(licensePlate, VehicleType.CAR);
    }
}
