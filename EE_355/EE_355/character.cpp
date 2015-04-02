#include "stdafx.h"
#include "character.h"
#include <cmath>
#include <iostream>

using namespace std;

Character::Character() {
	// base constructor not needed
}

Character::Character(unsigned char(*myimage)[256], int ulr, int ulc, int h, int w) {
	_image = myimage;
	ul_r = ulr;
	ul_c = ulc;
	height = h;
	width = w;
	vcenterTop = 0;
	centerBottom = 0;
	hcenterTop = 0;
	euler = 0;
	vSym = 0;
	hSym = 0;

}

Character::~Character() {

}

void Character::perform_tests() {
	calc_bit_quads();
	euler = calc_euler_number();
	calc_spatial_moment();
	//cout << "Euler Number: " << euler << endl;
	//cout << "Height: " << height << endl;
	//cout << "Width: " << width << endl;
	//cout << "Norm Vertical Center: " << norm_vertical_center << endl;
	//cout << "Norm Horizontal Center: " << norm_horizontal_center << endl;
	aspect_ratio = calc_aspect_ratio();
	//cout << "Aspect Ratio: " << aspect_ratio << endl;
	calc_sym();
	//cout << "Vertical Symmetry: " << vSym << endl;
	//cout << "Horizontal Symmetry: " << hSym << endl;
	//cout << "==============================================" << endl;
}

void Character::classify() {
	if (euler == -1) {
		recognized_char = '8';
	}
	else if (euler == 0) {
		if (vSym > 0.9 && hSym > 0.9) {
			recognized_char = '0';
		}
		else {
			if (norm_horizontal_center < 0.5 && norm_vertical_center > 0.5) {
				//horizontal_center < 16 && vertical_center > 23 || vertical_center < 16 && horizontal_center < 14
				recognized_char = '6';
			}
			else if (norm_horizontal_center > 0.5 && norm_vertical_center < 0.465)  {
				//horizontal_center < 17 && vertical_center > 21
				recognized_char = '9';
			}
			else  {//if (horizontal_center > 18 && vertical_center < 22) {
				recognized_char = '4';
			}
		}
	}
	else if (euler == 1) {
		if (vSym > 0.85) {
			recognized_char = '1';
		}
		else if ((norm_horizontal_center > 0.55 && norm_horizontal_center < 0.6) && (norm_vertical_center > 0.45 && norm_vertical_center < 0.5)) {
			//horizontal_center > 16 && vertical_center > 22) || (vertical_center < 15 && vertical_center > 14 &&				horizontal_center < 15 && horizontal_center > 14)
			recognized_char = '3';
		}
		else if (norm_horizontal_center > 0.5 && norm_vertical_center < 0.4) {
			//vSym > 0.6 && vSym < 0.7 && hSym > 0.5 && hSym < 0.6 && aspect_ratio > 1.45 && aspect_ratio < 1.55
			recognized_char = '7';
		}
		else if (vSym > 0.6 && hSym > 0.6) {
			recognized_char = '2';
		}
		else {
			recognized_char = '5';
		}
	}

	
}

char Character::get_classification() {
	return recognized_char;
}

void Character::get_bounding_box(int &ulr, int &ulc, int &lrr, int &lrc) {
	// returning all 4 items by reference
	ulr = ul_r;
	ulc = ul_c;
	lrr = height + ul_r - 1;
	lrc = width + ul_c - 1;

}

void Character::print_calculations(int idx) {
	cout << "Character in bounding box: " << ul_r << "," << ul_c << " to " << ul_r + height - 1 << "," << ul_c + width - 1 << endl;
	cout << "========================================" << endl;
	cout << "BQ1=" << bq1 << " BQ3=" << bq3 << " BQD=" << bqd << endl;
	cout << "Euler number=" << euler << endl;
	cout << "Norm VCentroid=" << norm_vertical_center << " / Norm HCentroid=" << norm_horizontal_center << endl;
	cout << "VSym=" << vSym << " / HSym= " << hSym << endl;
	cout << "Aspect ratio=" << aspect_ratio << endl;
	cout << "Character " << idx << " is classified as:    " << get_classification() << endl << endl;
}

void Character::calc_bit_quads() {
	for (int i = ul_r - 1; i <= ul_r + height + 1; i++){
		for (int j = ul_c - 1; j <= ul_c + width + 1; j++){
			if ((_image[i][j] == 0 && _image[i + 1][j] == 255 && _image[i][j + 1] == 255 && _image[i + 1][j + 1] == 255) ||
				(_image[i][j] == 255 && _image[i + 1][j] == 0 && _image[i][j + 1] == 255 && _image[i + 1][j + 1] == 255) ||
				(_image[i][j] == 255 && _image[i + 1][j] == 255 && _image[i][j + 1] == 0 && _image[i + 1][j + 1] == 255) ||
				(_image[i][j] == 255 && _image[i + 1][j] == 255 && _image[i][j + 1] == 255 && _image[i + 1][j + 1] == 0)) {
				bq1++;
			}
			else if ((_image[i][j] == 255 && _image[i + 1][j] == 0 && _image[i][j + 1] == 0 && _image[i + 1][j + 1] == 0) ||
				(_image[i][j] == 0 && _image[i + 1][j] == 255 && _image[i][j + 1] == 0 && _image[i + 1][j + 1] == 0) ||
				(_image[i][j] == 0 && _image[i + 1][j] == 0 && _image[i][j + 1] == 255 && _image[i + 1][j + 1] == 0) ||
				(_image[i][j] == 0 && _image[i + 1][j] == 0 && _image[i][j + 1] == 0 && _image[i + 1][j + 1] == 255)) {
				bq3++;
			}
			else if ((_image[i][j] == 0 && _image[i + 1][j] == 255 && _image[i][j + 1] == 255 && _image[i + 1][j + 1] == 0) ||
				(_image[i][j] == 255 && _image[i + 1][j] == 0 && _image[i][j + 1] == 0 && _image[i + 1][j + 1] == 255)) {
				bqd++;
			}
		}
	}
}

int Character::calc_euler_number() {
	return (0.25 * (bq1 - bq3 - 2 * bqd));
}

void Character::calc_spatial_moment() { // calcs the horizontal & vertical centroids
	
	for (int i = ul_r; i < ul_r + height; i++){
		for (int j = ul_c; j < ul_c + width; j++){
			//vertical_center
			vcenterTop += (i - ul_r)*isBlack(i, j);
			//horizontal_center
			hcenterTop += (j - ul_c)*isBlack(i, j);
			//denominator
			centerBottom += isBlack(i, j);
		}
	}
	vertical_center = (double)vcenterTop / centerBottom;
	horizontal_center = (double)hcenterTop / centerBottom;
	norm_vertical_center = vertical_center / height;
	norm_horizontal_center = horizontal_center / width;
}

void Character::calc_sym() {            // calcs horizontal and vertical symmetry
	// vertical symmetry
	int total = 0;
	int match = 0;
	for (int i = ul_r; i < ul_r + height; i++){
		for (int j = ul_c; j < ul_c + (width)/2; j++){
			if (_image[i][j] == _image[i][ul_c + width - 1 - (j - ul_c)])
				match++;
			total++;
		}
	}
	vSym = (double)match / total;
	// Horizontal Symmetry
	total = 0;
	match = 0;
	for (int i = ul_r; i < ul_r + (height)/2; i++){
		for (int j = ul_c; j < ul_c + width; j++){
			if (_image[i][j] == _image[ul_r + height - 1 - (i - ul_r)][j])
				match++;
			total++;
		}
	}
	hSym = (double)match / total;
}

double Character::calc_aspect_ratio() {
	return (double)height / width;
}

int Character::isBlack(int i, int j) {
	return ((_image[i][j] == 0) ? 1 : 0);
}