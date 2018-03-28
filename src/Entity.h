class Entity
{
  public:
    Entity();
    ~Entity();

    void update();
    void draw() const;

  private:
    int x;
};
