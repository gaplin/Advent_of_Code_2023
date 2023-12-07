namespace Second_v2;

public class Hand : IComparable<Hand>
{
    private readonly Card[] _cards;
    public HandType Type { get; private set; }

    private Hand(Card[] cards, HandType type)
    {
        _cards = [.. cards];
        Type = type;
    }

    public Card this[int key]
    {
        get => _cards[key];
    }

    public static Hand Create(Card[] cards)
    {
        if (cards.Length != 5)
        {
            throw new ArgumentException("Nunmber of cards must be exactly 5", nameof(cards));
        }
        var handType = HandType.HighCard;

        using (var cardsEnumerator = new NextHandIterator(cards))
        {
            while (cardsEnumerator.MoveNext())
            {
                var newCards = cardsEnumerator.Current;
                string newCardsString = "";

                for (int i = 0; i < 5; ++i)
                {
                    newCardsString += newCards[i].Symbol;
                }
                handType = (HandType)Math.Max((int)handType, (int)CalculateType(newCards));
            }
        }
        return new Hand(cards, handType);
    }

    private static HandType CalculateType(Card[] cards)
    {
        var groupedCards = cards.GroupBy(x => x.Value).Select(x => new { Count = x.Count() }).OrderByDescending(x => x.Count).ToList();
        if (groupedCards.Count == 5)
        {
            return HandType.HighCard;
        }
        if (groupedCards.Count == 4)
        {
            return HandType.OnePair;
        }
        if (groupedCards.Count == 3)
        {
            if (groupedCards[0].Count == 3)
            {
                return HandType.ThreeOfAKind;
            }
            return HandType.TwoPair;
        }
        if (groupedCards.Count == 2)
        {
            if (groupedCards[0].Count == 3)
            {
                return HandType.FullHouse;
            }
            return HandType.FourOfAKind;
        }

        return HandType.FiveOfAKind;
    }

    public int CompareTo(Hand? other)
    {
        var typeCompare = Type.CompareTo(other?.Type);
        if (typeCompare != 0)
        {
            return typeCompare;
        }

        for (int i = 0; i < _cards.Length; ++i)
        {
            var cardsCompare = _cards[i].CompareTo(other!._cards[i]);
            if (cardsCompare != 0)
            {
                return cardsCompare;
            }
        }

        return 0;
    }
}