//  Umut Cem Avin
//  150140018
//  19.04.2019
//  Analysis of Algorithms Project 2

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <time.h>


using namespace std;

int equalizeLength(string &num1, string &num2) 
{ 
	if(num1.size()>num2.size()){
            int diff = num1.size()-num2.size();
            int size = num1.size();

            while(diff!=0){
                num2 = '0' + num2;
                diff--;
            }
            return size;
    }
	else if(num2.size()>num1.size()){
            int diff = num2.size()-num1.size();
            int size = num2.size();
            while(diff!=0){
                num1 = '0' + num1;
                diff--;
            }
            return size;
    }
    else{
        int size = num2.size();
        return size;
    }
} 

string bitAddition(string first, string second )
{
    string result;
    int length = equalizeLength(first, second); 
    
    int carry = 0; 
    for (int i = length-1 ; i >= 0 ; i--){
        int firstBit = first[i] - '0';
        int secondBit = second[i] - '0';
        int sum = (firstBit + secondBit + carry)%2 + '0'; // calculate sum of bit addition
        //calculate carry
        if((firstBit + secondBit + carry) >= 2) 
            carry = 1;
        else 
            carry = 0;
  		result = (char)sum + result; 

    }
    // -overflow situation-
    if(carry==1)
        result = '1' + result;

    return result;
}

long int karatsubaMethod(string num1, string num2){
   
        int size = equalizeLength(num1, num2); 
        if(size==1){
            return (num1[0] - '0')*(num2[0] - '0');
        }
        if(size==0){
            return 0;
        }
        int firstHalf = size/2;
        int secondHalf = size-firstHalf;
        
       //divide num1 as left and right strings 
        string num1_l = num1.substr(0, firstHalf);
        string num1_r = num1.substr(firstHalf, secondHalf);
        //divide num2 as left and right strings 
        string num2_l = num2.substr(0, firstHalf);
        string num2_r = num2.substr(firstHalf, secondHalf);
        
        long int P1 = karatsubaMethod(num1_l, num2_l);
        long int P2 = karatsubaMethod(num1_r, num2_r);
        long int P3 = karatsubaMethod(bitAddition(num1_l, num1_r), bitAddition(num2_l, num2_r));
        
        //return P1 * pow(2,size) + (P3 - P1 - P2)* pow(2,size/2) + P2;
        return P1*(1<<(2*secondHalf)) + (P3 - P1 - P2)*(1<<secondHalf) + P2; 

    
}

long int convertToDecimal(string result){
    long int value = 0;
    int indexCounter = 0;
    for(int i=result.length()-1;i>=0;i--){
        if(result[i]=='1'){
            value += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return value;
}

long int classicMethod(string num1, string num2){
    string bitBlock;
    string temp;
    string result;
    string finalResult;
    int counter = 1;
    int length = equalizeLength(num1, num2); 
    int zeroPad = length;

    for (int i = length-1 ; i >= 0 ; i--){
        int lastBitOfNum2 = num2[i] - '0';
        bitBlock.clear();
        for (int j = length-1 ; j >= 0 ; j--){
            int num1Bit = num1[j] - '0';
            int sum = lastBitOfNum2 * num1Bit + '0';
            bitBlock = char(sum) + bitBlock;
        }
        while(zeroPad!=length){
                bitBlock = bitBlock + '0';
                zeroPad++;
                //cout << "padding: " << bitBlock << endl;
        }
        //cout << "bb: " << bitBlock << endl;
        result = bitAddition(bitBlock, temp);
        //cout << "result: " << result << endl;
        temp = result;
        zeroPad = zeroPad - counter;
        counter++;
    }
    return convertToDecimal(result);
}

int main(int argc, const char * argv[]){
    string fileName;
    fileName = argv[1];
    //2 Bits
    clock_t begin = clock();
    long int x1 = karatsubaMethod("11", "10");
    clock_t end = clock();
    double elapsed_sec1 = double(end-begin)/ CLOCKS_PER_SEC;

    begin = clock();
    long int y1 = classicMethod("11", "10");
    end = clock();
    double elapsed_sec2 = double(end-begin)/ CLOCKS_PER_SEC;

    //4 Bits
    begin = clock();
    long int x2 = karatsubaMethod("1100", "1010");
    end = clock();
    double elapsed_sec3 = double(end-begin)/ CLOCKS_PER_SEC;

    begin = clock();
    long int y2 = classicMethod("1100", "1010");
    end = clock();
    double elapsed_sec4 = double(end-begin)/ CLOCKS_PER_SEC;


    //8 Bits
    begin = clock();
    long int x3 = karatsubaMethod("10101111", "101010101");
    end = clock();
    double elapsed_sec5 = double(end-begin)/ CLOCKS_PER_SEC;

    begin = clock();
    long int y3 = classicMethod("10101111", "101010101");
    end = clock();
    double elapsed_sec6 = double(end-begin)/ CLOCKS_PER_SEC;

    //16 Bits
    begin = clock();
    long int x4 = karatsubaMethod("1010111111111111", "101010101101010101");
    end = clock();
    double elapsed_sec7 = double(end-begin)/ CLOCKS_PER_SEC;

    begin = clock();
    long int y4 = classicMethod("1010111111111111", "101010101101010101");
    end = clock();
    double elapsed_sec8 = double(end-begin)/ CLOCKS_PER_SEC;

    //32 Bits
    begin = clock();
    long long int x5 = karatsubaMethod("11100011101110001110111000111010", "11101110111011101110111011101110");
    end = clock();
    double elapsed_sec9 = double(end-begin)/ CLOCKS_PER_SEC;

    begin = clock();
    long long int y5 = classicMethod("11100011101110001110111000111010", "11101110111011101110111011101110");
    end = clock();
    double elapsed_sec10 = double(end-begin)/ CLOCKS_PER_SEC;
      
    //64 Bits
    begin = clock();
    long long int x6 = karatsubaMethod("1110001110111000111011100011101011100011101110001110111000111010", "11101110111011101110111011101110");
    end = clock();
    double elapsed_sec11 = double(end-begin)/ CLOCKS_PER_SEC;

    begin = clock();
    long long int y6 = classicMethod("1110001110111000111011100011101011100011101110001110111000111010", "11101110111011101110111011101110");
    end = clock();
    double elapsed_sec12 = double(end-begin)/ CLOCKS_PER_SEC;


    ofstream outputFile(fileName, ofstream::out);
    outputFile << "Algorithm    " << "Result    " << "Running Time    " << "Number Of Digits";
    outputFile << endl;

    outputFile << "Karatsuba Method    " << x1 << "    " << elapsed_sec1 << " " << 2;
    outputFile << endl;
    outputFile << "Classic Method    " << y1 << "    " <<  elapsed_sec2 << " " << 2;
    outputFile << endl;
    outputFile << "Karatsuba Method    "  << x2 << "    " << elapsed_sec3 << " " << 4;
    outputFile << endl;
    outputFile << "Classic Method    "  << y2 << "    " << elapsed_sec4 << " " << 4;
    outputFile << endl;
    outputFile << "Karatsuba Method    "  << x3 << "    " << elapsed_sec5 << " " << 8;
    outputFile << endl;
    outputFile << "Classic Method    "<< y3 << "    " << elapsed_sec6 << " " << 8;
    outputFile << endl;
    outputFile << "Karatsuba Method    " << x4 << "    " << elapsed_sec7 << " " << 16;
    outputFile << endl;
    outputFile << "Classic Method    " << y4 << "    " << elapsed_sec8 << " " << 16;
    outputFile << endl;
    outputFile << "Karatsuba Method   "<< x5 << "     " << elapsed_sec9 << " " << 32;
    outputFile << endl;
    outputFile << "Classic Method    " << y5 << "     " << elapsed_sec10 << " " << 32;
    outputFile << endl;
    outputFile << "Karatsuba Method   " << x6 << "    "<< elapsed_sec11 << " " << 64;
    outputFile << endl;
    outputFile << "Classic Method    " << y6 << "      " << elapsed_sec12 << " " << 64;
    outputFile << endl;

    outputFile.close();

    return 0;
}
