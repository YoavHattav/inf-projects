package il.co.ilrd.plarium;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Stack;

public class ParkingLot {

	List<LotLevel> lotLevels = new ArrayList<>();
	Map<Integer, ParkingSpot> usedSpaces = new HashMap<>();

	public ParkingLot(Integer numOfLevels) {
		for (int level = 0; level < numOfLevels; ++level) {
			lotLevels.add(new LotLevel(level));
		}
	}

	private boolean parkHelper(Vehicle vehicle, Stack<ParkingSpot> curr_stack) {
		ParkingSpot spot = null;
		synchronized (curr_stack) {
			if (!curr_stack.isEmpty()) {
				spot = curr_stack.pop();
			}
		}
		if (null != spot) {
			synchronized (usedSpaces) {
				usedSpaces.put(vehicle.getLicencePlate(), spot);
			}
			System.out.println("thank you for choosing us: " + vehicle.getLicencePlate());
			inCaseOfSuccess();
			return true;
		}

		return false;
	}

	private void inCaseOfSuccess() {
		showDisplayBoard();
		showManagerBoard();
	}

	/**
	 * try for the right sized spot first.
	 * in case we didn't find a suitable space already, a regular car could potentially park in a large spot.
	 * @param vehicle
	 */
	public void parkVehicle(Vehicle vehicle) {
		for (LotLevel level : lotLevels) {
			Stack<ParkingSpot> curr_stack = level.rows.get(vehicle.getSize());
			if (parkHelper(vehicle, curr_stack)) {
				return;
			}
		}
		if (vehicle.getSize().equals(VehicleSize.REGULAR)) {
			for (LotLevel level : lotLevels) {
				Stack<ParkingSpot> curr_stack = level.rows.get(VehicleSize.LARGE);
				if (parkHelper(vehicle, curr_stack)) {
					return;
				}
			}
		}
		System.out.println("pls come back later, we have no spots left");
	}

	/**
	 * removes the car from the parking lot (if it exists).
	 * @param vehicle
	 */
	public void getVehicle(Vehicle vehicle) {
		ParkingSpot spot;
		synchronized (usedSpaces) {
			spot = usedSpaces.remove(vehicle.getLicencePlate());
		}
		LotLevel level = lotLevels.get(spot.getLevelId());
		Stack<ParkingSpot> curr_stack = level.rows.get(spot.getSpotSize());
		synchronized (curr_stack) {
			curr_stack.push(spot);
		}
	}

	public void showDisplayBoard() {
		int[] availableSpots = new int[3];
		for (LotLevel level : lotLevels) {
			int[] currentLvlSpots = level.getAvailableSpots();
			for (int i = 0; i < 3; ++i) {
				availableSpots[i] += currentLvlSpots[i];
			}
		}
		System.out.println("we have " + availableSpots[0] + " motoSpots, " + availableSpots[1] + " regularSpots, " + availableSpots[2] + " largeSpots.");
	}

	public void showManagerBoard() {
		synchronized(usedSpaces) {
			System.out.println(usedSpaces);
		}
	}

	class LotLevel {
		private Integer floor = 0;
		private final Integer NUM_OF_MOTORCYCLE_SPOTS = 10;
		private final Integer NUM_OF_REGULAR_SPOTS = 25;
		private final Integer NUM_OF_LARGE_SPOTS = 15;

		Stack<ParkingSpot> motoSizeStack = new Stack<>();
		Stack<ParkingSpot> regularSizeStack = new Stack<>();
		Stack<ParkingSpot> largeSizeStack = new Stack<>();

		Map<VehicleSize, Stack<ParkingSpot>> rows = new HashMap<>();

		public LotLevel(Integer floor) {
			this.floor = floor;
			Integer spotId = 0;
			int i = 0;

			for (i = 0; i < NUM_OF_MOTORCYCLE_SPOTS; ++i) {
				motoSizeStack.add(new ParkingSpot(floor, spotId, VehicleSize.MOTORCYCLE));
				++spotId;
			}
			for (i = 0; i < NUM_OF_REGULAR_SPOTS; ++i) {
				regularSizeStack.add(new ParkingSpot(floor, spotId, VehicleSize.REGULAR));
				++spotId;
			}
			for (i = 0; i < NUM_OF_LARGE_SPOTS; ++i) {
				largeSizeStack.add(new ParkingSpot(floor, spotId, VehicleSize.LARGE));
				++spotId;
			}
			rows.put(VehicleSize.MOTORCYCLE, motoSizeStack);
			rows.put(VehicleSize.REGULAR, regularSizeStack);
			rows.put(VehicleSize.LARGE, largeSizeStack);
		}
		public int[] getAvailableSpots() {
			int[] availableSpotsArray = new int[3];
			synchronized (motoSizeStack) {
				availableSpotsArray[0] = motoSizeStack.size();
			}
			synchronized (regularSizeStack) {
				availableSpotsArray[1] = regularSizeStack.size();
			}
			synchronized (largeSizeStack) {
				availableSpotsArray[2] = largeSizeStack.size();
			}

			return availableSpotsArray;
		}
	}
	class ParkingSpot {
		private final Integer levelId;
		private final Integer spotId;
		private final VehicleSize spotSize;

		private Vehicle parkedVehicle;

		public ParkingSpot(Integer levelId, Integer spotId, VehicleSize spotSize) {
			this.levelId = levelId;
			this.spotId = spotId;
			this.spotSize = spotSize;
		}

		public void reserveSpot(Vehicle parkedVehicle) {
			this.parkedVehicle = parkedVehicle;
		}

		public void vacateSpot() {
			parkedVehicle = null;
		}

		public Vehicle getParkedVehicle() {
			return parkedVehicle;
		}

		public Integer getLevelId() {
			return levelId;
		}

		public Integer getSpotId() {
			return spotId;
		}

		public VehicleSize getSpotSize() {
			return spotSize;
		}

		@Override
		public String toString() {
			return "ParkingSpot [levelId=" + levelId + ", spotId=" + spotId + "]";
		}

	}
}
