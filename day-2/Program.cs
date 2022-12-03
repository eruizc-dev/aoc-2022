int GetResultScore(int opponents, int mine) {
	var diff = opponents - mine;
	if (diff == 0) {
		return 3;
	}
	if (diff == -1 || diff == 2) {
		return 6;
	}
	return 0;
}

int GetScore(int opponents, int mine) {
	var shapeScore = mine + 1;
	var resultScore = GetResultScore(opponents, mine);
	return shapeScore + resultScore;
}

var total = 0;
var lines = System.IO.File.ReadAllLines("./input.txt");
foreach (var line in lines) {
	total += GetScore(line[0] - 'A', line[2] - 'X');
}
Console.WriteLine(total);
