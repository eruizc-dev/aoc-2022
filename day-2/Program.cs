var lines = System.IO.File.ReadAllLines("./input.txt");
var p1 = Part1.GetScore(lines);
Console.WriteLine(p1);
var p2 = Part2.GetScore(lines);
Console.WriteLine(p2);

public static class Part1 {
	public static int GetScore(string[] lines) {
		var total = 0;
		foreach (var line in lines) {
			total += GetMatchScore(line[0] - 'A', line[2] - 'X');
		}
		return total;
	}

	private static int GetMatchScore(int opponents, int mine) {
		var shapeScore = mine + 1;
		var resultScore = GetResultScore(opponents, mine);
		return shapeScore + resultScore;
	}

	private static int GetResultScore(int opponents, int mine) {
		var diff = opponents - mine;
		if (diff == 0) {
			return 3;
		}
		if (diff == -1 || diff == 2) {
			return 6;
		}
		return 0;
	}
}

public static class Part2 {
	public static int GetScore(string[] lines) {
		var total = 0;
		foreach (var line in lines) {
			total += GetMatchScore(line[0] - 'A', line[2]);
		}
		return total;
	}

	private static int GetMatchScore(int opponents, char result) {
		var mine = GetMyOption(opponents, result);
		var shapeScore = mine + 1;
		var resultScore = GetResultScore(opponents, mine);
		return shapeScore + resultScore;
	}

	private static int GetResultScore(int opponents, int mine) {
		var diff = opponents - mine;
		if (diff == 0) {
			return 3;
		}
		if (diff == -1 || diff == 2) {
			return 6;
		}
		return 0;
	}

	private static int GetMyOption(int opponents, char result) {
		if (result == 'Y') {
			return opponents;
		}

		if (result == 'X') {
			return (opponents + 2) % 3;
		}

		return (opponents + 1) % 3;
	}
}
