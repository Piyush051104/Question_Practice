package OOPS.ParkingLot;
import OOPS.ParkingLot.FeeStrategy.DailyFee;
import OOPS.ParkingLot.Manager.ParkingLot;
import OOPS.ParkingLot.Ticket.Ticket;
import OOPS.ParkingLot.floor.Floor;
import OOPS.ParkingLot.vehicle.vehicle;
import OOPS.ParkingLot.vehicle.Bike;
import OOPS.ParkingLot.vehicle.Car;
import OOPS.ParkingLot.vehicle.Truck;

import OOPS.ParkingLot.ParkingSpot.ParkingSpot;

public class main {

    public static void main(String[] args) throws InterruptedException {



        ParkingLot lot = ParkingLot.getinstannce();

    
        ParkingLot lot2 = ParkingLot.getinstannce();
        System.out.println("Same instance? "
                         + (lot == lot2));  // true ✅

        System.out.println("\n=============================");
        System.out.println("     PARKING LOT SYSTEM      ");
        System.out.println("=============================\n");

        lot.addFloor(new Floor(1, 2, 2, 1));
        

        lot.addFloor(new Floor(2, 1, 1, 1));
        

        System.out.println("Parking lot setup complete!");
        System.out.println("Floor 1: 2 small, 2 medium, 1 large");
        System.out.println("Floor 2: 1 small, 1 medium, 1 large\n");


        // ── Step 3: Park Vehicles ─────────────────────

        System.out.println("--- VEHICLE ENTRY ---\n");

        // park a bike
        vehicle bike1 = new Bike("BIKE-001");
        Ticket bikeTicket = lot.ParkVechile(bike1);
        System.out.println();

        // park two cars
        vehicle car1 = new Car("CAR-001");
        Ticket carTicket1 = lot.ParkVechile(car1);
        System.out.println();

        vehicle car2 = new Car("CAR-002");
        Ticket carTicket2 = lot.ParkVechile(car2);
        System.out.println();

        // park a truck
        vehicle truck1 = new Truck("TRUCK-001");
        Ticket truckTicket = lot.ParkVechile(truck1);
        System.out.println();


        // ── Step 4: Test Parking Full ─────────────────

        System.out.println("--- TESTING FULL SCENARIO ---\n");

        // floor 1 has 2 medium spots → both taken by car1, car2
        // floor 2 has 1 medium spot  → try parking 2 more cars
        vehicle car3 = new Car("CAR-003");
        Ticket carTicket3 = lot.ParkVechile(car3);  // floor 2 spot
        System.out.println();

        vehicle car4 = new Car("CAR-004");
        Ticket carTicket4 = lot.ParkVechile(car4);  // should print FULL
        System.out.println();


        // ── Step 5: Exit vehicles ─────────────────────

        System.out.println("--- VEHICLE EXIT ---\n");

        // simulate time passing
        // Thread.sleep makes program wait so hours > 0
        // in real app — vehicle parks for actual hours
        Thread.sleep(1000);  // wait 1 second

        // bike exits
        System.out.println("Bike exiting...");
        lot.exitvechicle(bikeTicket);
        System.out.println();

        // car1 exits
        System.out.println("Car 1 exiting...");
        lot.exitvechicle(carTicket1);
        System.out.println();


        // ── Step 6: Spot Freed — Park Again ──────────

        System.out.println("--- PARK AFTER SPOT FREED ---\n");

        // car1 exited → its MEDIUM spot is now free
        // car4 was rejected earlier → try again now
        vehicle car5 = new Car("CAR-005");
        Ticket carTicket5 = lot.ParkVechile(car5);  // should succeed now
        System.out.println();


        // ── Step 7: Swap Fee Strategy ─────────────────

        System.out.println("--- SWAP FEE STRATEGY ---\n");

        // switch from HourlyFee to DailyFee
        lot.setStrategy(new DailyFee());
        System.out.println("Strategy swapped to DailyFee!\n");

        // park new truck
        vehicle truck2 = new Truck("TRUCK-002");
        Ticket truckTicket2 = lot.ParkVechile(truck2);
        System.out.println();

        Thread.sleep(1000);

        // truck exits with DailyFee
        System.out.println("Truck 2 exiting with Daily Fee...");
        lot.exitvechicle(truckTicket2);
        System.out.println();


        // ── Step 8: Singleton Verification ───────────

        System.out.println("--- SINGLETON VERIFICATION ---\n");
        System.out.println("lot  hashCode: " + lot.hashCode());
        System.out.println("lot2 hashCode: " + lot2.hashCode());
        System.out.println("Both same?    " + (lot == lot2));
    }
}