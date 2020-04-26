package il.co.ilrd.tests;

import java.util.ArrayList;
import java.util.List;

import il.co.ilrd.collections.Pair;
import il.co.ilrd.collections.PairCompare;

public class PairTest implements Comparable<PairTest>{
	
	private String gameName;
	private Double yearsGone;
	
	
	public PairTest(String gameName, double yearsGone) {
		super();
		this.gameName = gameName;
		this.yearsGone = yearsGone;
	}
	
	public String getGameName() {
		return gameName;
	}

	public void setGameName(String gameName) {
		this.gameName = gameName;
	}

	public double getYearsGone() {
		return yearsGone;
	}

	public void setYearsGone(double yearsGone) {
		this.yearsGone = yearsGone;
	}
	
	@Override
	public int compareTo(PairTest o) {
		if (this.getYearsGone() > o.getYearsGone())
		{
			return 1;
		}
		return 0;
	}
	
	@Override
	public String toString() {
		return "PairTest [gameName= " + gameName + ", yearsGone= " + yearsGone + "]";
	}

	public static void main(String[] args) {
		
		PairTest[] pairArray = new PairTest[5];
		
		PairTest diablo = new PairTest("Diablo", 3.5);
		PairTest leagueOfLegends = new PairTest("LeagueOfLegends", 6);
		PairTest mu = new PairTest("MU_Online", 3);
		PairTest rust = new PairTest("Rust", 2);
		PairTest fallOut = new PairTest("FallOut", 4);
		
		pairArray[0] = diablo;
		pairArray[1] = leagueOfLegends;
		pairArray[2] = mu;
		pairArray[3] = rust;
		pairArray[4] = fallOut;
		
		Pair<String, Double> newPair = Pair.of("Diablo", 3.5);
		System.out.println(newPair.getKey());
		System.out.println(newPair.getValue());
		Pair<Double, String> swapPair = Pair.of(null, null);
		swapPair = Pair.swap(newPair);
		System.out.println(swapPair.getKey());
		System.out.println(swapPair.getValue());
		
		System.out.println(leagueOfLegends);
		System.out.println(newPair);
		
		PairCompare<PairTest> compare = new PairCompare<PairTest>();
		
		Pair<PairTest, PairTest> compareMinMaxPair = Pair.of(null, null);
		Pair<PairTest, PairTest> minMaxPair = Pair.of(null, null);
		
		compareMinMaxPair = Pair.minMax(pairArray, compare);
		minMaxPair = Pair.minMax(pairArray);
		
		System.out.println(compareMinMaxPair);
		System.out.println(minMaxPair);

	}
}
