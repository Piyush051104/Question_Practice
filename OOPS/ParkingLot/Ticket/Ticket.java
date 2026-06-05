package OOPS.ParkingLot.Ticket;

import OOPS.ParkingLot.vehicle.vehicle;

import java.time.LocalDateTime;

import OOPS.ParkingLot.ParkingSpot.ParkingSpot;

public class Ticket {
    private String TicketId;
    private vehicle vehicle;
    private ParkingSpot spot;
    private LocalDateTime entryTime;
    private double fees;


    public Ticket(vehicle vehicle,ParkingSpot spot){
        this.TicketId  = "TKT" + System.currentTimeMillis();
        this.vehicle = vehicle;
        this.spot = spot;
        this.entryTime = LocalDateTime.now();
        this.fees = 0;
    }

    public ParkingSpot getSpot(){
        return spot;
    }

    public vehicle getVehicle(){
        return vehicle;
    }

    public String getTicketId(){
        return TicketId;
    }

    public void setfee(double fee){
        this.fees = fee;
    }
    public double getfee(){
        return fees;
    }
    public LocalDateTime getLocalDateTime(){
        return  entryTime;
    }




}