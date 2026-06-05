package OOPS.ParkingLot.FeeStrategy;

public class Hourlyfee implements FeeStrategy {
    private static int rate = 20;
    @Override
    public double calculatefee(long hours){
        if(hours == 0) hours = 1;
        return hours * rate;
    }   
}
