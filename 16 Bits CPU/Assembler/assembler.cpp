#include <bits/stdc++.h>

using namespace std;

#define checkBit(n,p) (bool)(n&(1<<p))

/*============================================================================//
                       Two drifters, off to see the world
                       There's such a lot of world to see
           We're after the same rainbow's end, waiting round the bend
                   My Huckleberry Friend, Moon River, and me
//============================================================================*/

map<string,string> getMap(ifstream  &file)
{
    string word,value;
    map<string,string> m;
    while(file>>word>>value)
    {
        m[word] = value;
        cout<<"VALUE = "<<value<<endl;
    }
    file.close();
    return m;
}

string decToBin(int num,int length)
{
    string result = "";
    for(int i=0;i<length;i++)
    {
        if(checkBit(num,i))
        {
            result = "1" + result;
        }
        else
        {
            result = "0" + result;
        }
    }
    return result;
}

int main()
{
    cout << "Hello World!" << endl;
    int val;
    string ins,op,r1,r2,r3,cmnt;
    map<string,string> R_TYPE,I_TYPE,J_TYPE,RegisterValue;
    //Obtaining static values from storage
    ifstream rFile,iFile,jFile,regValue;
    rFile.open("R_TYPE.txt");
    iFile.open("I_TYPE.txt");
   // jFile.open("J_TYPE.txt");
    regValue.open("RegisterValue.txt");

    R_TYPE = getMap(rFile);
    I_TYPE = getMap(iFile);
   // J_TYPE = getMap(jFile);
    RegisterValue = getMap(regValue);

    ifstream inputFile;
    inputFile.open("input.txt");
    //ifstream inputFile("File/validtestcases.txt");
    //ifstream inputFile("File/invalidtestcases.txt");
    ofstream outputFile;
    outputFile.open("output.txt");


    while(getline(inputFile,ins))
    {
        stringstream ss;
        cout << ins << endl;
        //Checking if instruction is empty or not
        if(ins.size()==0)
        {
            cout << "Invalid: Instruction is empty" << endl;
            outputFile << "Invalid: Instruction is empty" << endl;
            continue;
        }
        ss << ins;
        ss >> op;
        ss >> r1;

        if(r1[0]!='$')
        {
            cout << "Invalid: '$' sign is missing before rd" << endl;
            outputFile << "Invalid: '$' sign is missing before rd" << endl;
            continue;
        }
        else if(r1[r1.size()-1]!=',')
        {
            cout << "Invalid: ',' is missing after rd" << endl;
            outputFile << "Invalid: ',' is missing after rd" << endl;
            continue;
        }
        r1.erase(r1.end()-1);

        //If operation code is R Type then the program will go in here
        if(R_TYPE.find(op)!=R_TYPE.end())
        {
            val = 0;

            if(op=="sll"||op=="srl")
            {
                r2 = "$zero";
            }
            else
            {
                ss >> r2;
                if(r2[0]!='$')
                {
                    cout << "Invalid: '$' sign is missing before rs" << endl;
                    outputFile << "Invalid: '$' sign is missing before rs" << endl;
                    continue;
                }
                else if(r2[r2.size()-1]!=',')
                {
                    cout << "Invalid: ',' is missing after rs" << endl;
                    outputFile << "Invalid: ',' is missing after rs" << endl;
                    continue;
                }
                r2.erase(r2.end()-1);
            }
            ss >> r3;
            if(r3[0]!='$')
            {
                cout << "Invalid: '$' sign is missing before rt" << endl;
                outputFile << "Invalid: '$' sign is missing before rt" << endl;
                continue;
            }
            if(op=="sll"||op=="srl")
            {
                if(r3[r3.size()-1]!=',')
                {
                    cout << "Invalid: ',' is missing after rt" << endl;
                    outputFile << "Invalid: ',' is missing after rt" << endl;
                    continue;
                }
                r3.erase(r3.end()-1);
                val = -1;
                ss >> val;
            }
            //Checking instruction validities
            print:
            if(r1=="$zero")
            {
                cout << "Invalid: $zero can not be used" << endl;
                outputFile << "Invalid: $zero can not be used" << endl;
            }
            else if(RegisterValue.find(r1)==RegisterValue.end())
            {
                cout << "Invalid: rd not found" << endl;
                outputFile << "Invalid: rd not found" << endl;
            }
            else if(RegisterValue.find(r2)==RegisterValue.end())
            {
                cout << "Invalid: rs not found" << endl;
                outputFile << "Invalid: rs not found" << endl;
            }
            else if(RegisterValue.find(r3)==RegisterValue.end())
            {
                cout << "Invalid: rt not found" << endl;
                outputFile << "Invalid: rt not found" << endl;
            }
            else if(val<0)
            {
                cout << "Invalid: value can not be neg" << endl;
                outputFile << "Invalid: value can not be neg" << endl;
            }
            else if(val>8)
            {
                cout << "Invalid: value is too large" << endl;
                outputFile << "Invalid: value is too large" << endl;
            }
            else if(ss>>cmnt&&(cmnt[0]!='/'||cmnt[1]!='/'))
            {
            	cout << "Invalid: comment structure not maintained" << endl;
            	outputFile << "Invalid: comment structure not maintained" << endl;
            }
            //Printing machine code if instruction is valid
            else
            {
                string result = R_TYPE[op]+RegisterValue[r2]+RegisterValue[r3]+RegisterValue[r1]+decToBin(val,3);
                cout<<"result = "<<result<<endl;
                bitset<16> set(result);
                cout << hex << set.to_ulong() << endl;
                outputFile <<result <<" (binary)\t"<<hex << set.to_ulong() <<" (Hexadecimal)"<< endl;

                //cout <<R_TYPE[op] << " " << RegisterValue[r2] << " " << RegisterValue[r3] << " " << RegisterValue[r1] << " " << decToBin(val,3)<< endl;
                //outputFile << R_TYPE[op] << " " << RegisterValue[r2] << " " << RegisterValue[r3] << " " << RegisterValue[r1] << " " << decToBin(val,3)<< endl;
            }
        }
        //If operation code is I Type then the program will go in here
        else if(I_TYPE.find(op)!=I_TYPE.end())
        {
        	val = -1;
        	if(op=="lw"||op=="sw")
        	{
        		ss >> val >> r2;
        		if(r2[0]!='(')
                {
                    cout << "Invalid: '(' is missing before rs" << endl;
                    outputFile << "Invalid: '(' is missing before rs" << endl;
                    continue;
                }
                else if(r2[r2.size()-1]!=')')
                {
                    cout << "Invalid: ')' is missing after rs" << endl;
                    outputFile << "Invalid: ')' is missing after rs" << endl;
                    continue;
                }
                else if(r2[1]!='$')
                {
                    cout << "Invalid: '$' sign is missing before rs" << endl;
                    outputFile << "Invalid: '$' sign is missing before rs" << endl;
                    continue;
                }
        		r2.erase(r2.begin());
        		r2.erase(r2.end()-1);
        		swap(r1,r2);
        		if(r1=="$zero")
                {
                    r1 = "";
                    cout << "Invalid: $zero can to be used" << endl;
                    outputFile << "Invalid: $zero can to be used" << endl;
                    continue;
                }
                else if(r2=="$zero")
                {
                    r2 = "";
                    cout << "Invalid: $zero can to be used" << endl;
                    outputFile << "Invalid: $zero can to be used" << endl;
                    continue;
                }
        	}
        	else
        	{
        		ss >> r2 >> val;
        		if(r2[0]!='$')
                {
                    cout << "Invalid: '$' sign is missing before rs" << endl;
                    outputFile << "Invalid: '$' sign is missing before rs" << endl;
                    continue;
                }
                else if(r2[r2.size()-1]!=',')
                {
                    cout << "Invalid: ',' is missing after rs" << endl;
                    outputFile << "Invalid: ',' is missing after rs" << endl;
                    continue;
                }
        		r2.erase(r2.end()-1);
        		if(op=="addi")
        		{
        		    swap(r1,r2);
        		    if(r1=="$zero")
                    {
                        r1 = "";
                        cout << "Invalid: $zero can to be used" << endl;
                        outputFile << "Invalid: $zero can to be used" << endl;
                        continue;
                    }
        		}
        		else
        		{
        		    if(val<0)
                    {
                        val -= 10;
                    }
        			val = ceil(val/4.0);
        		}
        	}
        	//Checking instruction validities
            if(RegisterValue.find(r1)==RegisterValue.end())
            {
                cout << "Invalid: rd not found" << endl;
                outputFile << "Invalid: rd not found" << endl;
            }
            else if(RegisterValue.find(r2)==RegisterValue.end())
            {
                cout << "Invalid: rs not found" << endl;
                outputFile << "Invalid: rs not found" << endl;
            }
            else if(op!="addi"&&op!="andi"&&op!="ori"&&val<0)
            {
                cout << "Invalid: value can not be neg" << endl;
                outputFile << "Invalid: value can not be neg" << endl;
            }
            else if(val>32)
            {
                cout << "Invalid: value is too large" << endl;
                outputFile << "Invalid: value is too large" << endl;
            }
            else if(val<-32)
            {
                cout << "Invalid: value is too small" << endl;
                outputFile << "Invalid: value is too small" << endl;
            }
            else if(ss>>cmnt&&(cmnt[0]!='/'||cmnt[1]!='/'))
            {
            	cout << "Invalid: comment structure not maintained" << endl;
            	outputFile << "Invalid: comment structure not maintained" << endl;
            }
            //Printing machine code if instruction is valid
            else
            {
                string result = I_TYPE[op]+RegisterValue[r1]+RegisterValue[r2]+decToBin(val,6);
                cout<<"result = "<<result<<endl;
                bitset<16> set(result);
                cout << hex << set.to_ulong() << endl;
                outputFile <<result <<" (binary)\t"<<hex << set.to_ulong() <<" (Hexadecimal)"<< endl;

            //	cout << I_TYPE[op] << " " << RegisterValue[r1] << " " << RegisterValue[r2] << " " << decToBin(val,6) << endl;
            //	outputFile << I_TYPE[op] << " " << RegisterValue[r1] << " " << RegisterValue[r2] << " " << decToBin(val,6) << endl;
            }
        }
        else
        {
        	cout << "Invalid: Op code not found" << endl;
        	outputFile << "Invalid: Op code not found" << endl;
        }
    }
    inputFile.close();
    outputFile.close();
}
