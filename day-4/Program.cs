var input = System.IO.File.ReadAllLines("./input.txt");
var p1 = part1(input);
Console.WriteLine("Part 1: " + p1);

int part1(string[] pairs) {
	int counter = 0;

	foreach (var pair in pairs) {
		var split = pair.Split(',');
		var range1 = new Range(split[0]);
		var range2 = new Range(split[1]);

		if (range1.Contains(range2) || range2.Contains(range1)) {
			counter++;
		}
	}

	return counter;
}

class Range {
	public readonly int Start;
	public readonly int End;

	public Range(string raw) {
		var split = raw.Split('-');
		this.Start = int.Parse(split[0]);
		this.End = int.Parse(split[1]);
	}

	public bool Contains(Range that) {
		return this.Start <= that.Start && this.End >= that.End;
	}
}
