package OOPS.ParkingLot.Manager;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

import OOPS.ParkingLot.FeeStrategy.FeeCalculator;
import OOPS.ParkingLot.FeeStrategy.FeeStrategy;
import OOPS.ParkingLot.FeeStrategy.Hourlyfee;
import OOPS.ParkingLot.ParkingSpot.ParkingSpot;
import OOPS.ParkingLot.Ticket.Ticket;
import OOPS.ParkingLot.enums.VehicleType;
import OOPS.ParkingLot.floor.Floor;
import OOPS.ParkingLot.vehicle.vehicle;


public class ParkingLot {
    private static ParkingLot instance;

    public static ParkingLot getinstannce(){
        if(instance == null){
            synchronized(ParkingLot.class){
                if(instance == null){
                    instance = new ParkingLot();
                }
            }
        }
        return instance;
    }

    private List<Floor>floors;
    private FeeCalculator feeCalculator;

    public ParkingLot(){
        this.floors = new ArrayList<>();
        this.feeCalculator = new FeeCalculator(new Hourlyfee());
    }

    public void addFloor(Floor floor){
        floors.add(floor);
    }

    public void setStrategy(FeeStrategy strategy){
        feeCalculator.setStrategy(strategy);
    }

    public Ticket ParkVechile(vehicle vech){
        ParkingSpot spot = findspot(vech.gettype());

        if(spot == null){
            System.out.println("Sorry! Parking full for "
                             + vech.gettype());
            return null;
        }
        spot.occupySpot(vech);
        Ticket tic = new Ticket(vech, spot);
        System.out.println("Vehicle parked successfully!");
        System.out.println("Ticket ID  : " + tic.getTicketId());
        System.out.println("Spot ID    : " + spot.getSpotId());
        System.out.println("Entry Time : " + tic.getLocalDateTime());

        return tic;
    }

    public ParkingSpot findspot(VehicleType type){
        for(Floor floor:floors){
            ParkingSpot spot= floor.getavailablespot(type);
            if( spot != null) return spot;
        }
        return null;
    }


    public double exitvechicle(Ticket tic){
        LocalDateTime entrytime = tic.getLocalDateTime();
        LocalDateTime exitTime = LocalDateTime.now();

        long hours = Duration.between(entrytime, exitTime).toHours();

        if(hours == 0) hours = 1;
        double fee = feeCalculator.calculate(hours);

        tic.setfee(fee);

        tic.getSpot().releaseSeat();

        System.out.println("Vehicle exited successfully!");
        System.out.println("Ticket ID  : " + tic.getTicketId());
        System.out.println("Hours      : " + hours);
        System.out.println("Fee        : Rs " + fee);

        return fee;

    }
}
