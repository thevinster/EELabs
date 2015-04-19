#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
 public:
  Character();
  // the first parameter should just be passed in and saved to 
  //  the 'image' data member as in ( image = myimage; )
  Character(unsigned char (*myimage)[256], int ulr, int ulc, int h, int w );
  ~Character();


  void perform_tests();
  void classify();
  char get_classification();
  // returns upper-left point and lower-right point of bounding box
  //  DOES NOT compute bounding box...it's already in your data members
  //  just returns the bounding box if a user wants the bounds
  void get_bounding_box(int &ulr, int &ulc, int &lrr, int &lrc);
  void print_calculations(int idx);


 private:
  //==============
  // Helper Functions
  //==============
	 void calc_bit_quads();
	 int calc_euler_number();
	 void calc_spatial_moment(); // calcs the horizontal & vertical centroids
	 void calc_sym();            // calcs horizontal and vertical symmetry
	 double calc_aspect_ratio();
	 int isBlack(int i, int j);
  //==============
  // Data Members
  //==============
 private: 
  int ul_r, ul_c;
  int height, width;
  
  // For Character recognition variables
  int bq1, bq3, bqd;
  double vertical_center, horizontal_center;
  double norm_vertical_center, norm_horizontal_center;
  int euler;
  double aspect_ratio;
  double vSym, hSym;
  int vcenterTop, hcenterTop, centerBottom;

  char recognized_char;
  unsigned char (*_image)[256];


};

#endif

