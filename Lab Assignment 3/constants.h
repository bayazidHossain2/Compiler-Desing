#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED
using namespace std;

const string separators = "(\\|\\|)|(&&)|(>=)|(<=)|(==)|(!=)|[!=<>\\+\\-\\*/\\(\\)\\{\\},\\.;\\[\\]]|(\\s)+";
const string keywords = "(auto)|(break)|(case)|(char)|(const)|(continue)|(default)|(do)|(double)|(else)|(enum)|(extern)|(float)|(for)|(goto)|(if)|(int)|(long)|(register)|(return)|(short)|(signed)|(sizeof)|(static)|(struct)|(switch)|(typedef)|(union)|(unsigned)|(void)|(volatile)|(while)";
const string number = "0|(-?[1-9][0-9]*)";
const string lattersValidName = "[A-Za-z_][A-Za-z0-9_]*";



#endif // CONSTANTS_H_INCLUDED
