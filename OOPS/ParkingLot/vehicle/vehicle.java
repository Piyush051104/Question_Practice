package OOPS.ParkingLot.vehicle;

import OOPS.ParkingLot.enums.VehicleType;

public abstract class vehicle{
    private String licensePlate;
    private VehicleType type;

    public vehicle(String licensePlate,VehicleType type){
        this.licensePlate = licensePlate;
        this.type = type;
    }

    public String getlicensePlate(){
        return licensePlate;
    }
    public VehicleType gettype(){
        return type;
    }
}





