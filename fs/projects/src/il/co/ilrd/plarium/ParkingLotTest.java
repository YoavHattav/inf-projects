package il.co.ilrd.plarium;


import java.util.ArrayList;
import java.util.List;

import org.junit.jupiter.api.Test;

class ParkingLotTest {

	class Thread1 implements Runnable {
		private ParkingLot lot;

		public Thread1(ParkingLot lot) {
			this.lot = lot;
		}
		@Override
		public void run() {
			List<Vehicle> letMeIn = new ArrayList<>();
			int licencePlate = 100;
			for (int i = 0; i < 12 ; ++i) {
				letMeIn.add(new Motorcycle(++licencePlate));
			}
			for (int i = 0; i < 34 ; ++i) {
				letMeIn.add(new RegularCar(++licencePlate));
			}
			for (int i = 0; i < 14 ; ++i) {
				letMeIn.add(new LargeCar(++licencePlate));
			}

			for (Vehicle vehicle : letMeIn) {
				lot.parkVehicle(vehicle);
			}
		}

	}
	class Thread2 implements Runnable {
		private ParkingLot lot;

		public Thread2(ParkingLot lot) {
			this.lot = lot;
		}

		@Override
		public void run() {
			List<Vehicle> letMeIn = new ArrayList<>();
			int licencePlate = 200;
			for (int i = 0; i < 12 ; ++i) {
				letMeIn.add(new Motorcycle(++licencePlate));
			}
			for (int i = 0; i < 34 ; ++i) {
				letMeIn.add(new RegularCar(++licencePlate));
			}
			for (int i = 0; i < 14 ; ++i) {
				letMeIn.add(new LargeCar(++licencePlate));
			}

			for (Vehicle vehicle : letMeIn) {
				lot.parkVehicle(vehicle);
			}
		}
	}

	@Test
	void Parkingtest() {

		ParkingLot lot = new ParkingLot(2);
		Thread entrance1 = new Thread(new Thread1(lot));
		Thread entrance2 = new Thread(new Thread2(lot));

		entrance1.start();
		entrance2.start();

	}
}
