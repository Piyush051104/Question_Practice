package OOPS.ParkingLot.ParkingSpot;

import OOPS.ParkingLot.enums.SpotType;
import OOPS.ParkingLot.vehicle.vehicle;

public class ParkingSpot{
    private int SpotId;
    private SpotType type;
    private boolean isOccupied;
    private vehicle vehicle;

    public ParkingSpot(int SpotId,SpotType type){
        this.SpotId = SpotId;
        this.type = type;
        isOccupied = false;
        vehicle = null;
    }

    public void occupySpot(vehicle v){
        vehicle = v;
        isOccupied = true;
    }

    public void releaseSeat(){
        vehicle = null;
        isOccupied = false;
    }

    public int getSpotId(){
        return SpotId;
    }
    public SpotType getSpotType(){
        return type;
    }
    public vehicle getVehicle(){
        return vehicle;
    }
    public boolean getoccupied(){
        return isOccupied;
    }
}

