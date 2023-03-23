#include <vector>
template <class T> class Field
{
  private:
    int						nx_;
    int						ny_;
    std::vector<T>				data_;
    int index_(int x, int y) const 
    { 
      x = (x+nx_)%nx_;	// Wrap around boundary
      y = (y+nx_)%ny_;	
      return x+nx_*y; 
    }
  public:
    Field(int nx, int ny) : nx_(nx), ny_(ny), data_(nx_*ny_)
    {
      int n=nx_*ny_;
      for (int i=0;i<n;i++) data_[i] = 0; 
    }

    T& operator() (int x, int y)       { return data_[index_(x,y)]; }
    T  operator() (int x, int y) const { return data_[index_(x,y)]; }
    int nx() const { return nx_; } 
    int ny() const { return ny_; } 
};