public class CreditAccount:Account
{
    public double Creditlimit { get; set; }
    public CreditAccount(double limit, string id, string pwd, double money)
        :base(id, pwd, money)
    {
        this.Creditlimit = limit;
    }

    public override bool  WithdrawMoney(double money)
    {
        if (this.Creditlimit >= money)
        {
            this.Creditlimit -= money;
            this.money -= money;
            return true;
        }
        return false;
    }
}