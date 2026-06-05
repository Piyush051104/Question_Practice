package OOPS.ParkingLot.FeeStrategy;

public class FeeCalculator{
    private FeeStrategy strategy;

    public FeeCalculator(FeeStrategy strategy){
        this.strategy = strategy;
    }

    public void setStrategy(FeeStrategy strategy){
        this.strategy = strategy;
    }

    public double calculate(long hours){
        return strategy.calculatefee(hours);
    }
}
