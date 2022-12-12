var input = System.IO.File.ReadAllLines("./input.txt");
var (p1, p2) = run(input);
Console.WriteLine("Part 1: " + p1);
Console.WriteLine("Part 2: " + p2);

(int, int) run(string[] pairs) {
	int contains = 0;
	int overlaps = 0;

	foreach (var pair in pairs) {
		var split = pair.Split(',');
		var range1 = new Range(split[0]);
		var range2 = new Range(split[1]);

		if (range1.Overlaps(range2)) {
			overlaps++;
			if (range1.Contains(range2) || range2.Contains(range1)) {
				contains++;
			}
		}
	}

	return (contains, overlaps);
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

	public bool Overlaps(Range that) {
		return this.Start <= that.End && this.End >= that.Start;
	}
}
