namespace Second;

public class Card : IComparable<Card>, IEquatable<Card>
{
    public char Symbol { get; private set; }
    public int Value { get; private set; }
    private Card(int value, char symbol)
    {
        Value = value;
        Symbol = symbol;
    }

    public static Card Create(char symbol)
    {
        var value = symbol switch
        {
            'J' => 0,
            '2' => 1,
            '3' => 2,
            '4' => 3,
            '5' => 4,
            '6' => 5,
            '7' => 6,
            '8' => 7,
            '9' => 8,
            'T' => 9,
            'Q' => 10,
            'K' => 11,
            'A' => 12,
            _ => throw new ArgumentException($"value {symbol} not allowed. Allowed values: 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A", nameof(symbol))
        };
        return new Card(value, symbol);
    }

    public int CompareTo(Card? other)
    {
        return Value.CompareTo(other?.Value);
    }

    public bool Equals(Card? other)
    {
        return Value.Equals(other?.Value);
    }

    public override bool Equals(object? obj)
    {
        if (obj is Card otherCard)
        {
            return Equals(otherCard);
        }
        return false;
    }

    public override int GetHashCode()
    {
        return Value.GetHashCode();
    }
}