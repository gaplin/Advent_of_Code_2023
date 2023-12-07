using Second;
using HandBid = (Second.Hand Hand, int Bid);

var lines = await File.ReadAllLinesAsync("../../../../input/input.txt");

List<HandBid> handBids = [];

foreach (var line in lines)
{
    var lineSplit = line.Split(" ", StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries);
    var cards = lineSplit[0].Select(Card.Create).ToArray();
    var hand = Hand.Create(cards);
    var bid = int.Parse(lineSplit[1]);
    handBids.Add(new(hand, bid));
}

handBids.Sort((x, y) => x.Hand.CompareTo(y.Hand));

long result = 0;
for (int i = 0; i < handBids.Count; i++)
{
    result += (i + 1) * handBids[i].Bid;
}

File.WriteAllText("../../../../output/out_second.txt", result.ToString());