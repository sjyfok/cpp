#ifndef __STONEWT1_H__
#define __STONEWT1_H__

class Stonewt
{
    private:
        enum {Lbs_per_stn = 14};
        int stone;
        double pds_left;
        double pounds;
    public:
        Stonewt(double lbs);
        Stonewt(int stn, double lbs);
        Stonewt();
        ~Stonewt();

        void show_lbs() const;
        void show_stn() const;

        operator int() const;
        operator double() const;
};

#endif

