namespace Cards
{
	class PlayingCard
	{
        private readonly Suit suit;  //花色
        private readonly Value value; //点数

		public PlayingCard(Suit s, Value v)
		{
			this.suit = s;
			this.value = v;
		}

        public override string ToString()
		{
            string result = $"{this.value} of {this.suit}";
            return result;
		}

        public Suit CardSuit()
        {
            return this.suit;
        }

        public Value CardValue()
        {
            return this.value;
        }
	}
}