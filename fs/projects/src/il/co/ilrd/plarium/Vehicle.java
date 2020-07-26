package il.co.ilrd.plarium;

public class Vehicle {
	private final Integer licencePlate;
	private final VehicleSize size;
	
	public Vehicle(Integer licencePlate, VehicleSize size) {
		this.licencePlate = licencePlate;
		this.size = size;
	}

	public Integer getLicencePlate() {
		return licencePlate;
	}
	
	public VehicleSize getSize() {
		return size;
	}

	@Override
	public String toString() {
		return "Vehicle [licencePlate=" + licencePlate + ", size=" + size + "]";
	}
	
}
