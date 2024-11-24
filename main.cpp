#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

int main()
{
    int distribution[256][2] = {0};
    double shannons = 0.00;
    std::string FileName;
    for(int i = 0; i < 256; ++i)
    {
        distribution[i][0] = i;
    }
    std::cout << "Enter filepath of the file to examine: ";std::cin >> FileName;
    std::ifstream file(FileName, std::ios::binary);

    if(!file.is_open())
    {
        std::cout << "[-] error opening file!\n";
        return 1;
    }
    file.seekg(0, std::ios::end);
    long length = file.tellg();
    file.seekg (0, std::ios::beg);

    char byte;
    while(file.get(byte))
    {
        distribution[(int)(unsigned char)byte][1] += 1;
    }
    file.close();

    std::cout << "Length: " << length << "\n";
    for(int (&x)[2] : distribution)
    {
        std::cout << x[0] << ": " << x[1] << " --> "<< -(x[1] / (double)length) * (log2((x[1] / (double)length))) << "\n";
        if(x[1] == 0)
        {
            continue;
        }
        shannons -= (x[1] / (double)length) * (log2((x[1] / (double)length)));
    }
    std::cout << "Entropy: " << shannons << "\n";
    std::cout << "Likeliness of packing is: " << (shannons/8.00)*100 << "%\n"; // 8.00 is used because its the highest value the function outputs
}
