namespace First;

public class Card : IComparable<Card>, IEquatable<Card>
{
    public int Value { get; private set; }
    private Card(int value)
    {
        Value = value;
    }

    public static Card Create(char symbol)
    {
        var value = symbol switch
        {
            '2' => 0,
            '3' => 1,
            '4' => 2,
            '5' => 3,
            '6' => 4,
            '7' => 5,
            '8' => 6,
            '9' => 7,
            'T' => 8,
            'J' => 9,
            'Q' => 10,
            'K' => 11,
            'A' => 12,
            _ => throw new ArgumentException($"value {symbol} not allowed. Allowed values: 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A", nameof(symbol))
        };
        return new Card(value);
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