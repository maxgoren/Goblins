class Fov {
    public:
    int mapW;
    int mapH;
    std::vector<Point> marked;
    std::vector<Point> Radius;
    void get_rad(Point p, int rad);
    void plot(field& layout, int x, int y);
    void Bresenham(field& layout, Point p1, Point p2);
    void plot_fov(field& layout, Point p1, int rad);
    bool onmap(Point curr);
    Fov(int mw, int mh);
    Fov()
    {

    }
};

Fov::Fov(int mw, int mh)
{
    this->mapW = mw;
    this->mapH = mh;
}

bool Fov::onmap(Point curr)
{
  if ((curr.x > 0 && curr.x < mapW) && (curr.y > 0 && curr.y < mapH)) 
    return true;
  
  return false;
}

void Fov::plot(field& layout, int x, int y)
{
    marked.push_back({x,y});
}

void Fov::Bresenham(field& layout, Point p1, Point p2)
{
    int dx, dy, sx, sy, err, e2;

    dx = abs(p2.x - p1.x);
    sx = (p1.x < p2.x) ? 1:-1;
    dy = -abs(p2.y - p1.y);
    sy = (p1.y < p2.y) ? 1:-1;
    err = dx+dy;

    while (true)
    {
      if (p1 == p2 || (layout[p1.x][p1.y].blocks && layout[p1.x][p1.y].populated == false))
            break;
      
      if (onmap(p1)) 
      {
        plot(layout, p1.x, p1.y);
        e2 = 2*err;
        if (e2 >= dy)
        {
            err += dy;
            p1.x += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            p1.y += sy;
        }
      }
    }
}

void Fov::get_rad(Point p, int radius)
{
    Radius.clear();
    int i; Point next;
    for (i = -radius; i <= radius; i++)
    {
        Radius.push_back({p.x + radius, p.y + i});
        Radius.push_back({p.x + (-radius), p.y + i});
        Radius.push_back({p.x + i, p.y + (-radius)});
        Radius.push_back({p.x + i, p.y + radius});
    }
}

void Fov::plot_fov(field& layout, Point p, int rad)
{
    marked.clear();
    get_rad(p, rad);
    for (auto e : Radius)
    {
        Bresenham(layout, p, e);
    }

}

