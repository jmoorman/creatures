enum Gender
{
  kMale,
  kFemale
};

class Creature
{
 public:
  Creature();
  ~Creature();

  void Move(); //decreases energy
  void Eat(); //increases satiation
  void Drink(); //increases hydration
  void Attack(); //decreases energy
  void Breed(); //creates a new creature

 private:
  Gender gender_; //male or female. determines mating
  float speed_;
  float size_;

  //float temperature_; //moves towards current environment temperature
  float hydration_; //drink water to increase hydration
  float satiation_; //food is digested and converted to energy over time
  float energy_; //decreases with actions but increases with digestion

  float health_; //changes based on other vitals. dead if reaches 0 
};
