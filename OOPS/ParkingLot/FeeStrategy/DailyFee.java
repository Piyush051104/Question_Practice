package OOPS.ParkingLot.FeeStrategy;


public class DailyFee implements FeeStrategy {

    private static final int RATE = 200;  // Rs 200 per day

    @Override
    public double calculatefee(long hours) {
        long days = hours / 24;
        if(days == 0) days = 1;
        return days * RATE;
    }
}
