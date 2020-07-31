#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Image { 
public: 

	//Default Constructor
	Image();
	//Copy constructor
	Image(const Image &img2);

	//Destructor
	//~Image();

  	//member functions
    bool readImage(string imageName);
    bool writeImageToFile(string fileName);
    bool convertToGrayscale();
    int menu();
    //getter functions
    string getImageName();
    int getArraySize();
    bool getIsConverted();
    //setter functions
    void setImageName(string name);
    void setArraySize(int arrSize);
    void setIsConverted(bool b);
    void setAllNumbers();

    //operator overloads
    Image operator +(const Image& img) ;
    void operator = (const Image &img ); 
    
private:

	string imageName;
	int* allNumbers;
	int* grayScaleNumbers;
	string imageFormat;
	int column;
	int row;
	int maximumColorValue;
	bool isConverted = false;
	int arraySize;

}; 

int menu();

int main(){
	
	
	menu();


	return 0;
}

Image::Image(){    // default constructor


}

Image::Image(const Image &img2){   // copy constructor

	this->row = img2.row;
	this->column = img2.column;
	this->maximumColorValue = img2.maximumColorValue;
	this->imageFormat = img2.imageFormat;
	this->arraySize = img2.arraySize;
	this->isConverted = img2.isConverted;

}

/*Image::~Image(){     //destructor


	delete [] allNumbers;
	allNumbers = nullptr;

	delete [] grayScaleNumbers;
	grayScaleNumbers = nullptr;

	arraySize = 0;

}*/

string Image::getImageName(){
	return this->imageName;
}
int Image::getArraySize(){
	return this->arraySize;
}

bool Image::getIsConverted(){
	return this->isConverted;
}

void Image::setImageName(string name){
	this->imageName = name;
}

void Image::setArraySize(int arrSize){
	this->arraySize = arrSize;
}

void Image::setIsConverted(bool b){

	this->isConverted = b;
}

void Image::setAllNumbers(){

	this->allNumbers = nullptr; 
	this->allNumbers = new(nothrow) int[this->arraySize];


}


Image Image::operator +(const Image& img )  {

	Image addImage = img;

	int size = addImage.getArraySize();   
	int i;
	
	
	addImage.allNumbers = nullptr; 
	addImage.allNumbers = new(nothrow) int[size];
	

	for(i=0; i<size; ){

		addImage.allNumbers[i] = this->allNumbers[i] + img.allNumbers[i];
		if(addImage.allNumbers[i] > 255 )
			addImage.allNumbers[i] = 255;
		
		i++;
		  
	}	

	return addImage;

}


void Image::operator = (const Image &img2 ) {   


	this->row = img2.row;
	this->column = img2.column;
	this->maximumColorValue = img2.maximumColorValue;
	this->imageFormat = img2.imageFormat;
	this->arraySize = img2.arraySize;
	this->isConverted = img2.isConverted;
	
}


bool Image::readImage(string imageName){

	int temp;
	int size;
	
	ifstream readingFile;
	readingFile.open (imageName);     // opening the file

	if(!readingFile.is_open()){       // error checking for file is not opened
       exit(-1);                      // exit the program
   	}

	readingFile >> this->imageFormat;
	readingFile >> this->column;
	readingFile >> this->row;
	readingFile >> this->maximumColorValue;


	this->setArraySize(row*column*3);
	size = this->getArraySize();
	this->allNumbers = nullptr; 
	this->allNumbers = new(nothrow) int[size];
	
	

	int i=0;
	while (!readingFile.eof()){    // finding values of pictures.   
         
		readingFile >> temp;
		this->allNumbers[i] = temp;

		i++;
	}
		

	readingFile.close();  // closing the opened file

	return true;

}

bool Image::writeImageToFile(string fileName){

	ofstream writingFile;
	writingFile.open (fileName);

	if(!writingFile){       // error checking for file is not created
       exit(-1);       // exit the program
   	}

	writingFile << this->imageFormat;
	writingFile << endl;

	writingFile << this->column << " " << this->row;
	writingFile << endl;

	writingFile << this->maximumColorValue;
	writingFile << endl;


	int i=0;

	// if the picture converted to gray scale 
	if(this->getIsConverted()){

		for(i=0; i< this->getArraySize(); i++){     // assign converted vector to all numbers vector. So, the picture changed.
			this->allNumbers[i] = this->grayScaleNumbers[i];
			
		}

	}

	i=0;
	while (i < this->getArraySize()){   
         
		writingFile << this->allNumbers[i];

		if(i != this->getArraySize()-1)
			writingFile << endl;

		i++;
	}

	writingFile.close();

	return true;
}

bool Image::convertToGrayscale(){

	
	float c_r; //user enters for red
	float c_g; //user enters for green
	float c_b; //user enters blue

	//values after conversion
	float new_red;
	float new_green;
	float new_blue;

	int sizeAllNumbers = this->getArraySize();
	
	
	//dynamic array allocation
	grayScaleNumbers = nullptr; 
	grayScaleNumbers = new(nothrow) int[sizeAllNumbers];
	

	cout << endl;
	cout << "Enter three float allNumbers which are in the range [0,1)" << endl;
	cin >> c_r >> c_g >> c_b;    // getting user input

	if(c_r<0 || c_r>1 || c_g<0 || c_g>1 || c_b<0 || c_b>1)   // error check out of range 
		exit(-1);

	int i;
	int r=0,g=1,b=2;    // r for red value index, g for green value index, b for blue value index 

	for(i=0; i < sizeAllNumbers ;){

		// RED
		new_red = (c_r * this->allNumbers[r]) + (c_g * this->allNumbers[g]) + (c_b * this->allNumbers[b]);  //new_red = red, green, blue 
		if(new_red>255)  // max value is 255
			new_red = 255;
		this->grayScaleNumbers[i] =  new_red ;  
		i++;
				
		// GREEN
		new_green = (c_r * this->allNumbers[r]) + (c_g * this->allNumbers[g]) + (c_b * this->allNumbers[b]);  //new_green = red, green, blue
		if(new_green >255)   // max value is 255
			new_green = 255;
		this->grayScaleNumbers[i] =  new_green ;
		i++;
				
		//BLUE
		new_blue = (c_r * this->allNumbers[r]) + (c_g * this->allNumbers[g]) + (c_b * this->allNumbers[b]); //new_blue = red, green, blue
		if(new_blue >255)  // max value is 255
			new_blue = 255;
		this->grayScaleNumbers[i] = new_blue ;
		i++;
			
		//every three number equal to one pixel. So, we move there index each loop	
		r=r+3;
		g=g+3;
		b=b+3;			

	}

	this->setIsConverted(true) ;

	return true;

}

int menu(){

	Image img1, img2, imgAddition;
	int size; // for imgaddition;

	int userChoice;    // get menu choice input from user
	string imageName;  // to read image
	string fileName;   // to write to file
	int countOfImage=0;
	int countFlag=0;
	int countFlagforGrayScale=0;
	int countImageforAddition=0;
	bool isAddition=false;

	do{

		cout << endl;
		cout << "MAIN MENU" << endl << endl;
		cout << "0 - Exit" << endl;
		cout << "1 - Open An Image(D)" << endl;
		cout << "2 - Save Image Data(D)" << endl;
		cout << "3 - Tool Menu" << endl;

		cin >> userChoice;

		if(userChoice == 0){   // return main menu
			exit(0);
		}
		else if(userChoice == 1){

			do{
				cout << endl;

				if(countOfImage != 1){
					cout << "How many pictures you want to read? Enter 1/2" << endl;
					cin >> countOfImage;
				}
				if(!(countOfImage == 1 || countOfImage == 2)){
					cout << "Can not reading " << endl;
					break;
				}


				cout << "OPEN AN IMAGE MENU" << endl;
				cout << "0 - UP" << endl;
				cout << "1 - Enter The Name Of The Image File" << endl;

				cin>> userChoice;

				if(userChoice == 0){    //return main menu
					break;
				}
				else if(userChoice == 1){
					cin >> imageName;
					img1.setImageName(imageName);
					img1.readImage(img1.getImageName());  //  calling reading member function
				}	
				else
					exit(-1);             // exit the program
				
				
				if(countOfImage == 2){    // reading second image

					cout << endl;
					cout << "Second image" << endl;
					cout << "OPEN AN IMAGE MENU" << endl;
					cout << "0 - UP" << endl;
					cout << "1 - Enter The Name Of The Image File" << endl;

					cin >> userChoice;

					if(userChoice == 0){    //return main menu
						break;
					}
					else if(userChoice == 1){
						cin >> imageName;
						img2.setImageName(imageName);
						img2.readImage(img2.getImageName());  //  calling reading member function
					}	
					else
						exit(-1);             // exit the program

				}	


			}while(userChoice == 1 && countOfImage !=2);	
				
			countFlag = countOfImage;
			countFlagforGrayScale=countOfImage;
			countImageforAddition = countOfImage;	
			countOfImage = 0;
		}

		else if(userChoice == 2){

			do{
				cout << endl;

				if(isAddition){
					countFlag = 0;
					cout << "For the addition Result" << endl;
				}


				if(countFlag == 2){
					cout << "For the First Image" << endl;
				}

				cout << "SAVE IMAGE DATA MENU" << endl;
				cout << "0 - UP" << endl;
				cout << "1 - Enter A File Name" << endl;

				cin>> userChoice;

				if(userChoice == 0)   //return main menu
					break;
				else if(userChoice == 1){


					cin >> fileName;
					
					if(isAddition){
						imgAddition.writeImageToFile(fileName);  
					}
					else{

						img1.writeImageToFile(fileName);
					}


					if(countFlag == 2){
						 
						cout << endl;
						cout << "For the Second Image" << endl;
						cout << "SAVE IMAGE DATA MENU" << endl;
						cout << "0 - UP" << endl;
						cout << "1 - Enter A File Name" << endl;

						cin>> userChoice;

						if(userChoice == 0)   //return main menu
							break;
						else if(userChoice == 1){

							cin >> fileName;


							img2.writeImageToFile(fileName);   //  calling writing member function
							break;
						}

					}


				}	
				else
					exit(-1);         // exit the program

				countFlag = 1;
			}while(userChoice == 1 );	

		}


		else if(userChoice == 3){

			do{
				cout << endl;
				cout << "TOOL MENU" << endl;
				cout << "0 - UP" << endl;
				cout << "1 - Convert To Grayscale(D)" << endl;
				cout << "2 - Addition Two Images" << endl;

				cin>> userChoice;

				if(userChoice == 0){    //return main menu
					break;
				}
				else if(userChoice == 1){

					cout << endl;

					if(countFlagforGrayScale == 2){
						cout << "For the First Image" << endl;
					}

					cout << "CONVERT TO GRAYSCALE MENU" << endl;
					cout << "0 - UP" << endl;
					cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;

					cin >> userChoice;

					if(userChoice == 0){
						break;
					}
					else if(userChoice == 1){

						img1.convertToGrayscale();


						if(countFlagforGrayScale == 2){
							
							cout << endl;
							cout << "For the Second Image" << endl;
							cout << "CONVERT TO GRAYSCALE MENU" << endl;
							cout << "0 - UP" << endl;
							cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;

							cin >> userChoice;
							
							if(userChoice == 0){
								break;
							}

							else if(userChoice == 1){

								img2.convertToGrayscale();
							
							}
						}	
						
					}

					else
						exit(-1);           // exit the program
					
					break;

				}	

				else if(userChoice == 2){

					if(countImageforAddition != 2){
						cout << "There is no two images" << endl;
						break;
					}

					

					cout << endl;
					cout << "ADDITION MENU" << endl;
					cout << "0 - UP" << endl;
					cout << "1 - Addition " << endl;

					cin >> userChoice;

					imgAddition = img1;    // assignment objects by = operator overloading
					
					imgAddition.setAllNumbers();   // dynamic array allocatation in this function

					imgAddition = img1 + img2;   // addition objects by + operator overloading

					isAddition = true;

					break;
					
				}

				else 
					exit(-1);             // exit the program

			}while(userChoice == 1);	

		}


	}while(userChoice==0 || userChoice==1 || userChoice==2 || userChoice==3);	//checking if the user enters invalid choice

}