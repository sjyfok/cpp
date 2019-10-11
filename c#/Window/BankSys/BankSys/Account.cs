public class Account
{
    //属性
    private double m_money;
    public double money { get; set; }
    //{
    //    get
    //    {
    //        return m_money;
    //    }
    //    set
    //    {
    //        m_money = value;
    //    }
    //}
    private string m_id;
    public string id { get; set; }
    //{
    //    get
    //    {
    //        return m_id;
    //    }
    //    set
    //    {
    //        m_id = value;
    //    }
    //}
    private string m_pwd;
    public string pwd { get; set; }
    //{
    //    get
    //    {
    //        return m_pwd;
    //    }
    //    set
    //    {
    //        m_pwd = value;
    //    }
    //}

    public Account(string id, string pwd, double money)
    {
        this.id = id;
        this.pwd = pwd;
        this.money = money;
    }

    //public double getMoney()
    //{
    //    return money;
    //}

    //public void setMoney(double val)
    //{
    //    this.money = val;
    //}

    //public string getId()
    //{
    //    return id;
    //}

    //public void setId(string id)
    //{
    //    this.id = id;
    //}

    //public string getPwd()
    //{
    //    return this.pwd;
    //}

    //public void setPwd(string pwd)
    //{
    //    this.pwd = pwd;
    //}

    public bool SaveMoney(double money)
    {
        if (money < 0) return false;
        this.money += money;
        return true;
    }

    virtual public bool WithdrawMoney(double money)
    {
        if(this.money >= money)
        {
            this.money -= money;
            return true;
        }
        return false;
    }

    public bool IsMatch(string id, string pwd)
    {
        return id == this.id && pwd == this.pwd;
    }
}