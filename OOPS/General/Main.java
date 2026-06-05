// 1. Strategy Interface
interface PaymentStrategy {
    void pay(int amount);
}

// 2. Concrete Strategies
class UPIPayment implements PaymentStrategy {
    public void pay(int amount) {
        System.out.println("Paid " + amount + " via UPI");
    }
}

class CreditCardPayment implements PaymentStrategy {
    public void pay(int amount) {
        System.out.println("Paid " + amount + " via Credit Card");
    }
}

// 3. Context
class ShoppingCart {
    private PaymentStrategy strategy;

    public void setStrategy(PaymentStrategy s) {
        this.strategy = s;
    }
    public void checkout(int amount) {
        strategy.pay(amount);
    }
}   

// Main
public class Main {
    public static void main(String[] args) {
        ShoppingCart cart = new ShoppingCart();
        cart.setStrategy(new UPIPayment());
        cart.checkout(500);              // Paid 500 via UPI

        cart.setStrategy(new CreditCardPayment());
        cart.checkout(1000);             // Paid 1000 via Credit Card
    }
}