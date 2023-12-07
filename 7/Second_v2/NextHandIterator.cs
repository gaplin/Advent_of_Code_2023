using System.Collections;

namespace Second_v2;

public class NextHandIterator : IEnumerator<Card[]>
{
    private readonly Card[] _startingCards;
    private Card[] _currentCards;
    private int _idx = -1;
    private int _maxIdx;
    private bool _disposed;
    private readonly List<int> _jokersPositions = [];

    private static readonly char[] _allowedJokerValues = Card.AllowedSymbols;

    public NextHandIterator(Card[] startingCards)
    {
        _startingCards = startingCards;
        _currentCards = startingCards;
    }

    public Card[] Current => _disposed ? throw new ObjectDisposedException(nameof(NextHandIterator)) : _currentCards;

    object IEnumerator.Current => _disposed ? throw new ObjectDisposedException(nameof(NextHandIterator)) : _startingCards;

    public void Dispose()
    {
        _disposed = true;
    }

    public bool MoveNext()
    {
        if (_disposed)
        {
            throw new ObjectDisposedException(nameof(NextHandIterator));
        }
        if (_idx == -1)
        {
            int maxIdx = 1;
            for (int i = 0; i < 5; ++i)
            {
                if (_startingCards[i].Symbol == 'J')
                {
                    _jokersPositions.Add(i);
                    maxIdx *= _allowedJokerValues.Length;
                }
            }
            _maxIdx = maxIdx - 1;
        }
        if (_idx + 1 > _maxIdx)
        {
            return false;
        }

        if (_maxIdx == 0)
        {
            _currentCards = _startingCards;
            _idx = 0;
            return true;
        }

        _idx += 1;
        _currentCards = new Card[5];
        for (int i = 0; i < 5; ++i)
        {
            _currentCards[i] = Card.Create(_startingCards[i].Symbol);
        }

        var idxCopy = _idx;
        var allowedValuesLength = _allowedJokerValues.Length;
        foreach (var jokerIdx in _jokersPositions)
        {
            var symbol = _allowedJokerValues[idxCopy % allowedValuesLength];
            idxCopy /= allowedValuesLength;
            _currentCards[jokerIdx] = Card.Create(symbol);
        }

        return true;
    }

    public void Reset()
    {
        if (_disposed)
        {
            throw new ObjectDisposedException(nameof(NextHandIterator));
        }
        _currentCards = _startingCards;
        _jokersPositions.Clear();
        _maxIdx = 0;
        _idx = 0;
    }
}