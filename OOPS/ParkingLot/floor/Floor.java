package OOPS.ParkingLot.floor;
import java.util.ArrayList;
import java.util.List;

import OOPS.ParkingLot.ParkingSpot.ParkingSpot;
import OOPS.ParkingLot.enums.SpotType;
import OOPS.ParkingLot.enums.VehicleType;
import OOPS.ParkingLot.vehicle.vehicle;;
public class Floor {
    private int floorId;
    private List<ParkingSpot>spots ;

    public Floor(int floorId, int small, int medium, int large) {
        this.floorId = floorId;
        this.spots   = new ArrayList<>();
        initializeSpots(small, medium, large);
    }
    
    private void initializeSpots(int small, int medium, int large) {
        int id = 1;

        for(int i = 0; i < small; i++) {
            spots.add(new ParkingSpot(id++, SpotType.SMALL));
        }

        for(int i = 0; i < medium; i++) {
            spots.add(new ParkingSpot(id++, SpotType.MEDIUM));
        }

        for(int i = 0; i < large; i++) {
            spots.add(new ParkingSpot(id++, SpotType.LARGE));
        }
    }
    public ParkingSpot getavailablespot(VehicleType type){
        SpotType req =  getRequiredSpotType(type);

        for(ParkingSpot spot: spots){
            if(spot.getSpotType() == req && spot.getoccupied() == false){
                return spot;
            }
        }
        return null;
    }
    private SpotType getRequiredSpotType(VehicleType type) {
        switch(type) {
            case BIKE:  return SpotType.SMALL;
            case CAR:   return SpotType.MEDIUM;
            case TRUCK: return SpotType.LARGE;
            default:    return SpotType.MEDIUM;
        }
    }

    public int getFloorId(){
        return floorId;
    }
    public List<ParkingSpot> getSpots(){
        return spots;
    }


}
