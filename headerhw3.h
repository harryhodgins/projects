#include <vector>

class Field
{
private:
    int						qx_;
    int						qy_;
    std::vector<double>				data_;
    int index_(int x, int y) const { return x + qx_ * y; }
public:
    Field(int nx, int ny) : qx_(nx + 1), qy_(ny + 1), data_(qx_* qy_)
    {
        int n = qx_ * qy_;
        for (int i = 0; i < n; i++) data_[i] = 0.0;
    }

    double& operator() (int x, int y)
    {
        return data_[index_(x, y)];
    }
    double  operator() (int x, int y) const
    {
        return data_[index_(x, y)];
    }

    int nx() const { return qx_ - 1; }
    int ny() const { return qy_ - 1; }
};
