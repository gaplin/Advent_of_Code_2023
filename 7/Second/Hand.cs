namespace Second;

public class Hand : IComparable<Hand>
{
    private readonly Card[] _cards;
    public HandType Type { get; private set; }

    private Hand(Card[] cards, HandType type)
    {
        _cards = cards;
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
        var handType = CalculateType(cards);

        return new Hand(cards, handType);
    }

    private static HandType CalculateType(Card[] cards)
    {
        var jokersCount = cards.Count(x => x.Symbol == 'J');
        var groupedCards = cards.GroupBy(x => x.Value).Select(x => new { Count = x.Count() }).OrderByDescending(x => x.Count).ToList();
        if (groupedCards.Count == 5)
        {
            if (jokersCount != 0)
            {
                return HandType.OnePair;
            }
            return HandType.HighCard;
        }
        if (groupedCards.Count == 4)
        {
            if (jokersCount != 0)
            {
                return HandType.ThreeOfAKind;
            }
            return HandType.OnePair;
        }
        if (groupedCards.Count == 3)
        {
            if (groupedCards[0].Count == 3)
            {
                if (jokersCount != 0)
                {
                    return HandType.FourOfAKind;
                }
                return HandType.ThreeOfAKind;
            }
            if (jokersCount == 1)
            {
                return HandType.FullHouse;
            }
            if (jokersCount == 2)
            {
                return HandType.FourOfAKind;
            }
            return HandType.TwoPair;
        }
        if (groupedCards.Count == 2)
        {
            if (jokersCount != 0)
            {
                return HandType.FiveOfAKind;
            }
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