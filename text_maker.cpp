#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

void cleanse(std::string);
void convert_to_words();
std::string produce();
std::string random_sentence();
std::vector<std::string> sort(std::vector<std::string>);
std::vector<std::string> merge(std::vector<std::string>, std::vector<std::string>);

bool find(std::string s, std::vector<std::string> v){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == s){
            return true;
        }
    }
    return false;
}

int main(){
    std::srand(int(std::time(0)));
    
    cleanse("input.txt");
    //convert_to_words();
    
    std::cout << random_sentence() << "\n\n";
    for(int i = 0; i < 18; i++){
        std::cout << random_sentence() << " ";
    }
    std::cout << "\n\n";
    cleanse("compilation.txt");
    for(int i = 0; i < 7; i++){
        std::cout << random_sentence() << " ";
    }
    std::cout << "\n\n";
    
    return 0;
}

// larger stuff
void cleanse(std::string filename = "compilation.txt"){
    char wrd;
    std::ifstream stuff(filename, std::fstream::in);
    std::ofstream other_stuff("just_words.txt", std::fstream::out);
    while(stuff >> std::noskipws >> wrd){
        if((int(wrd) >= 65 && int(wrd) <= 90) || (int(wrd) >= 97 && int(wrd) <= 122)){
            other_stuff << static_cast<char>(std::tolower(wrd));
        }
        else if(int(wrd) <= 32 && int(wrd) >= 5){
            other_stuff << static_cast<char>(wrd);
        }
    }
    stuff.close();
    other_stuff.close();
}
void convert_to_words(){
    std::string wrd;
    std::vector<std::string> all;
    std::ifstream stuff("just_words.txt", std::fstream::in);
    std::ofstream other_stuff("words.txt", std::fstream::out);
    while(stuff >> wrd){
        if(!find(wrd, all)){
            all.push_back(wrd);
        }
    }
    all = sort(all);
    for(int i = 0; i < all.size(); i++){
        other_stuff << all[i] << std::endl;
    }
    stuff.close();
    other_stuff.close();
}
void convert_to_sentences(){}

// smaller stuff
std::string random_sentence(){
    std::string wrd;
    std::string sent = "";
    std::vector<std::string> wrds;
    std::ifstream stuff("just_words.txt", std::fstream::in);
    while(stuff >> wrd){
        wrds.push_back(wrd);
    }
    int i = 0, max = rand() % 10 + 5;
    for(; i < max; i++){
        sent += wrds[rand() % wrds.size()];
        if(i == max - 1){
            sent += ".";
        }
        else{
            sent += " ";
        }
    }
    sent[0] = std::toupper(sent[0]);
    return sent;
}
std::string produce(){
    std::string wrd;
    std::string sent = "";
    std::vector<std::string> wrds;
    std::ifstream stuff("input.txt", std::fstream::in);
    while(stuff >> wrd){
        wrds.push_back(wrd);
    }
    int i = 0, max = rand() % 10 + 5;
    for(; i < max; i++){
        sent += wrds[rand() % wrds.size()];
        if(i == max - 1){
            sent += ".";
        }
        else{
            sent += " ";
        }
    }
    sent[0] = std::toupper(sent[0]);
    return sent;
}

// sorting stuff
std::vector<std::string> sort(std::vector<std::string> v){
    if(v.size() < 2){
        return v;
    }
    if(v.size() == 2){
        if(v[0] > v[1]){
            return std::vector<std::string> {v[1], v[0]};
        }
        return v;
    }
    return merge(sort(std::vector<std::string> (&v[0], &v[floor(v.size()/2)])), sort(std::vector<std::string> (&v[floor(v.size()/2)], &v[v.size()])));
}
std::vector<std::string> merge(std::vector<std::string> v1, std::vector<std::string> v2){
    std::vector<std::string> fin(v1.size() + v2.size());
    int counter[2] = {0, 0};
    for(int i = 0; i < fin.size(); i++){
        if(counter[0] == v1.size()){
            fin[i] = v2[counter[1]++];
            continue;
        }
        else if(counter[1] == v2.size()){
            fin[i] = v1[counter[0]++];
            continue;
        }
        fin[i] = v1[counter[0]] < v2[counter[1]] ? v1[counter[0]++] : v2[counter[1]++];
    }
    return fin;
}
