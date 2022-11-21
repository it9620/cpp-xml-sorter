#include "../lib/pugixml-1.13/src/pugixml.hpp"
#include <iostream>
//#include <algorithm>
#include <string>
#include <map>
#include <vector>

#define UNUSED(expr) do { (void)(expr); } while (0)

using namespace std;

//===================================================================================

int main()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(
        "files/input/parameters_servertools-mlsystem_witsmlTable_before_march22 (2).xml");
        //"files/input/params_srvtools-mlsystem_witsmlTable_march22 (2).xml");
    if (!result)
        return -1;

    auto array_of_chanel = doc.child("ArrayOfChannel");
    auto chldrn = array_of_chanel.children("Channel");

    // Read and save atribute list.
    vector<string> array_atributes_names;
    vector<string> array_atributes;
    for (const auto& atribute : array_of_chanel.attributes()) {
        array_atributes_names.push_back(atribute.name());
        array_atributes.push_back(atribute.as_string());        
    }

    // Make map instead sort function.
    map<int, pugi::xml_named_node_iterator> sorted_xml;
    auto it = chldrn.begin();
    while (it != chldrn.end()) {
        pugi::xml_node index_node = it->child("Index");
        string index_str = index_node.child_value();
        int index_val = stoi (index_str);
        sorted_xml[index_val] = it;
        ++it;
    } // */
    cout << "Map created." << endl;

//===================================================================================
// Work to save modified XML file.

    pugi::xml_document result_doc;
    result_doc.append_child("ArrayOfChannel");

    pugi::xml_node result_array_of_chanel = result_doc.child("ArrayOfChannel");

    // Set atributes to ArrayOfChanel.
    for (int i = 0; i < array_atributes.size(); ++i) {
        string str_name = array_atributes_names.at(i);
        string str_atribute = array_atributes.at(i);
        result_array_of_chanel.append_attribute(str_name.c_str()) = str_atribute.c_str();
    }
    
    for (const auto& [index, node] : sorted_xml) {
        pugi::xml_node tmp_node = *node;
        result_array_of_chanel.append_copy(tmp_node);
    }

    result_doc.save_file(
        "files/output/parameters_servertools-mlsystem_witsmlTable_before_march22_sorted.xml");
        //"files/output/params_srvtools-mlsystem_witsmlTable_march22_sorted.xml");

    cout << "Programm end." << endl;
    return 0;
}